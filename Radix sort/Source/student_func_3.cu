//Udacity HW 4
//Radix Sorting

#include "utils.h"

/* Red Eye Removal
   ===============
   
   For this assignment we are implementing red eye removal.  This is
   accomplished by first creating a score for every pixel that tells us how
   likely it is to be a red eye pixel.  We have already done this for you - you
   are receiving the scores and need to sort them in ascending order so that we
   know which pixels to alter to remove the red eye.

   Note: ascending order == smallest to largest

   Each score is associated with a position, when you sort the scores, you must
   also move the positions accordingly.

   Implementing Parallel Radix Sort with CUDA
   ==========================================

   The basic idea is to construct a histogram on each pass of how many of each
   "digit" there are.   Then we scan this histogram so that we know where to put
   the output of each digit.  For example, the first 1 must come after all the
   0s so we have to know how many 0s there are to be able to start moving 1s
   into the correct position.

   1) Histogram of the number of occurrences of each digit
   2) Exclusive Prefix Sum of Histogram
   3) Determine relative offset of each digit
        For example [0 0 1 1 0 0 1]
                ->  [0 1 0 1 2 3 2]
   4) Combine the results of steps 2 & 3 to determine the final
      output location for each element and move it there

   LSB Radix sort is an out-of-place sort and you will need to ping-pong values
   between the input and output buffers we have provided.  Make sure the final
   sorted results end up in the output buffer!  Hint: You may need to do a copy
   at the end.

 */
// Take current digit of each elements
//=====================================================================
__global__ void takeCurrentDigit(unsigned int* inData, unsigned int* outDigit,
			    	 int n, int currentDigit, int nBins)
{
  int i = blockDim.x * blockIdx.x + threadIdx.x;

  if (i < n)
  {
    outDigit[i] = (inData[i] >> currentDigit) & (nBins - 1);
  }  
}

// Histogram on digit
//=====================================================================
__global__ void sortAndHistogram(unsigned int* inData, unsigned int* inDigit,
			  unsigned int* hist, int n, int nBins)
{
  extern __shared__ unsigned int s_inDigit[];
  unsigned int* s_outData = &s_inDigit[blockDim.x];
  unsigned int* s_hist = &s_inDigit[2*blockDim.x];

  int idx = blockDim.x * blockIdx.x + threadIdx.x;

  // 1. Histogram
  // 1.1. Loads data and histogram on local data block on SMEM
  for (int i = threadIdx.x; i < nBins; i += blockDim.x)
    s_hist[i] = 0;
  __syncthreads();

  if (idx < n)
  {
    s_inDigit[threadIdx.x] = inDigit[idx];
    atomicAdd(&s_hist[s_inDigit[threadIdx.x]], 1);
  }
  __syncthreads();
  
  // 1.2. Loads histogram data from SMEM to GMEM
  for (int i = threadIdx.x; i < nBins; i += blockDim.x)
     hist[i*gridDim.x+blockIdx.x] = s_hist[i]; 
  
  // 2. Sort local data block on SMEM
  unsigned int location = 0;
  if (idx < n)
  {
    for (int i = 0; i < threadIdx.x; i++)
      location += (s_inDigit[i] <= s_inDigit[threadIdx.x]);
    int threshold = blockDim.x;
    if (blockIdx.x == gridDim.x - 1)
      threshold = n - blockDim.x * blockIdx.x;
    for (int i = threadIdx.x + 1; i < threshold; i++)
      location += (s_inDigit[i] < s_inDigit[threadIdx.x]);
    s_outData[location] = inData[idx];
  }
  __syncthreads();

  // 3. Loads sorted data from SMEM to GMEM
  if (idx < n)
  {
    inData[idx] = s_outData[threadIdx.x];
    inDigit[blockDim.x*blockIdx.x+location] = s_inDigit[threadIdx.x];
  }
}

// Inclusive scan
//=====================================================================
__global__ void inclusiveScan(unsigned int* inData, unsigned int* outData,
			      unsigned int* outLastData, int n)
{
  // 1. Each block loads data from GMEM to SMEM
  // (each thread will load 2 elements)
  extern __shared__ unsigned int s_inScanData[]; // It's size will be 2*blockDim.x (elements)
  int idx1 = (blockDim.x * blockIdx.x + threadIdx.x) * 2;
  int idx2 = (blockDim.x * blockIdx.x + threadIdx.x) * 2 + 1;
  if (idx1 < n)
    s_inScanData[2*threadIdx.x] = inData[idx1];
  if (idx2 < n)
    s_inScanData[2*threadIdx.x+1] = inData[idx2];
  __syncthreads();

  // 2. Each block does scan with data on SMEM
  // 2.1. Reduction phase
  for (int stride = 1; stride < 2 * blockDim.x; stride *= 2)
  {
    int s_idx = (threadIdx.x + 1) * 2 * stride - 1; // So active threads will be consecutive
    if (s_idx < 2 * blockDim.x)
      s_inScanData[s_idx] += s_inScanData[s_idx - stride];
    __syncthreads();
  }
  // 2.2. Post-reduction phase
  for (int stride = blockDim.x / 2; stride > 0; stride /= 2)
  {
    int s_idx = (threadIdx.x + 1) * 2 * stride - 1 + stride;
    if (s_idx < 2 * blockDim.x)
      s_inScanData[s_idx] += s_inScanData[s_idx - stride];
    __syncthreads();
  }

  // 3. Each block writes result from SMEM to GMEM
  // (each thread will write 2 elements)
  if (idx1 < n)
    outData[idx1] = s_inScanData[2*threadIdx.x];
  if (idx2 < n)
    outData[idx2] = s_inScanData[2*threadIdx.x+1];

  // 4. Each block write the result of the last thread block
  // (for regression if the array has large size)
  if (threadIdx.x == (blockDim.x-1) || (blockIdx.x * blockDim.x + threadIdx.x) == (n-1)/2)
    if (idx2 < n)
      outLastData[blockIdx.x] = s_inScanData[2 * threadIdx.x + 1];
    else
      outLastData[blockIdx.x] = s_inScanData[2 * threadIdx.x];
}

// Add scanned block sum to the before scanned block sum
//=====================================================================
__global__ void lastScan(unsigned int* odata, unsigned int* sums, const int n)
{
  if (blockIdx.x > 0)
  {
    int idx1 = (blockIdx.x * blockDim.x + threadIdx.x) * 2;
    int idx2 = (blockIdx.x * blockDim.x + threadIdx.x) * 2 + 1;
    
    if (idx1 < n)
      odata[idx1] += sums[blockIdx.x - 1];
    if (idx2 < n)
      odata[idx2] += sums[blockIdx.x - 1];
  }
}

// Inclusive scan on large size array
//=====================================================================
void scanOnLargeSize(dim3 blockSize, dim3 gridSize, unsigned int *in, unsigned int *out, int n)
{
  dim3 _gridSize = gridSize;
  unsigned int *outlast;

  // Allocate device memory
  checkCudaErrors(cudaMalloc((unsigned int**)&outlast, gridSize.x*sizeof(unsigned int)));
  
  // Launch scan kernel to find sum of each block (each thread block solve 2 value)
  inclusiveScan<<<gridSize, blockSize, 2*blockSize.x*sizeof(unsigned int)>>>(in, out, outlast, n);
  cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

  // Regress until gridSize just contain 1 block
  if (_gridSize.x > 1)
  {
    int nsize = _gridSize.x;
    unsigned int *sums;

    _gridSize.x = (_gridSize.x-1)/2/blockSize.x+1;
    checkCudaErrors(cudaMalloc((unsigned int**)&sums, nsize*sizeof(unsigned int)));

    scanOnLargeSize(blockSize, _gridSize, outlast, sums, nsize);
      
    // Add scanned block sum (each thread block solve 2 value)
    lastScan<<<gridSize, blockSize>>>(out, sums, n);
    cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
    
    checkCudaErrors(cudaFree(sums));
  }
  checkCudaErrors(cudaFree(outlast));  
}

// Compute rank of each nBits-digit
//=====================================================================
__global__ void computeRank(unsigned int* inData, unsigned int* outData, int n)
{
  extern __shared__ unsigned int s_inData[];
  int idx = blockDim.x * blockIdx.x + threadIdx.x;

  if (idx < n)
    s_inData[threadIdx.x] = inData[idx];
  __syncthreads();

  if (idx < n)
  {
    // Compute rank on local block
    unsigned int rank = 0;
    for (int i = threadIdx.x - 1; i >= 0; i--)
    {
      if (s_inData[i] < s_inData[threadIdx.x])
	break;
      rank++;
    }
    outData[idx] = rank;
  }
}

// Scatter values corresponding to its location
//=====================================================================
__global__ void scatter(unsigned int* inData1, unsigned int* outData1,
			unsigned int* inData2, unsigned int* outData2,
		   	unsigned int* inDigit, unsigned int* exScanHist,
		    	unsigned int* rank, int n)
{
  int idx = blockDim.x * blockIdx.x + threadIdx.x;

  if (idx < n)
  {
    outData1[exScanHist[inDigit[idx]*gridDim.x+blockIdx.x] + rank[idx]] = inData1[idx];
    outData2[exScanHist[inDigit[idx]*gridDim.x+blockIdx.x] + rank[idx]] = inData2[idx];
  }
}

//=====================================================================
void your_sort(unsigned int* const d_inputVals,
               unsigned int* const d_inputPos,
               unsigned int* const d_outputVals,
               unsigned int* const d_outputPos,
               const size_t numElems)
{ 
  //TODO
  //PUT YOUR SORT HERE
  
  //
  unsigned int nBits = 8;
  unsigned int nBins = 1 << nBits;
 
  // for takeCurrentDigit kernel
  const dim3 blockDigit(256);
  const dim3 gridDigit((numElems-1)/blockDigit.x+1);

  // for histogram kernel, compute rank kernel and scatter kernel
  const dim3 blockSize(128);
  const dim3 gridSize((numElems-1)/blockSize.x+1);

  // for inclusive scan kernel
  const dim3 blockScan(512);
  const dim3 gridScan((gridSize.x*nBins-1)/2/blockScan.x+1);

  //
  unsigned int* d_vals_src = d_inputVals;
  unsigned int* d_pos_src = d_inputPos;
  unsigned int* d_vals_dst = d_outputVals;
  unsigned int* d_pos_dst = d_outputPos;

  //
  unsigned int *digit;
  unsigned int *hist, *exScanHist;
  unsigned int *rank;
  
  checkCudaErrors(cudaMalloc((unsigned int**)&digit, numElems*sizeof(unsigned int)));
  checkCudaErrors(cudaMalloc((unsigned int**)&hist, 
				nBins*gridSize.x*sizeof(unsigned int)));
  checkCudaErrors(cudaMalloc((unsigned int**)&exScanHist, 
				(nBins*gridSize.x+1)*sizeof(unsigned int)));
  checkCudaErrors(cudaMalloc((unsigned int**)&rank, numElems*sizeof(unsigned int)));

  // Loop from LSD to MSD
  // In each loop, soft values according to the current digit (using STABLE sort)
  for (unsigned int i = 0; i < 8*sizeof(unsigned int); i += nBits)
  {
    checkCudaErrors(cudaMemset(hist, 0, nBins*gridSize.x*sizeof(unsigned int)));
    checkCudaErrors(cudaMemset(exScanHist, 0, (nBins*gridSize.x+1)*sizeof(unsigned int)));

    // Step 1: Compute histogram
    takeCurrentDigit<<<gridDigit, blockDigit>>>(d_vals_src, digit, numElems, i, nBins);
    cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

    sortAndHistogram<<<gridSize, blockSize, (2*blockSize.x+nBins)*sizeof(unsigned int)>>>
							(d_vals_src, digit, hist, numElems, nBins);
    cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

    // Step 2: Scan on histogram
    scanOnLargeSize(blockScan, gridScan, hist, exScanHist+1, nBins*gridSize.x);

    // Step 3: Compute rank of each nBits-digit
    computeRank<<<gridSize, blockSize, blockSize.x*sizeof(unsigned int)>>>(digit, rank, numElems);
    cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

    // Step 4: Scatter values on correct location    
    scatter<<<gridSize, blockSize>>>(d_vals_src, d_vals_dst, d_pos_src, d_pos_dst,
				     digit, exScanHist, rank, numElems);
    cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());

    // Swap src and dst
    std::swap(d_vals_dst, d_vals_src);
    std::swap(d_pos_dst, d_pos_src);
  }
  
  // The above loop does an even number of iterations.
  // Its means the sorted array we need is store in input buffer,
  // so we need to copy from input buffer into output.
  checkCudaErrors(cudaMemcpy(d_outputVals, d_inputVals, 
			numElems*sizeof(unsigned int), cudaMemcpyDeviceToDevice));
  checkCudaErrors(cudaMemcpy(d_outputPos, d_inputPos, 
			numElems*sizeof(unsigned int), cudaMemcpyDeviceToDevice));

  // Free device memory
  checkCudaErrors(cudaFree(digit));
  checkCudaErrors(cudaFree(hist));
  checkCudaErrors(cudaFree(exScanHist));
  checkCudaErrors(cudaFree(rank));
}
