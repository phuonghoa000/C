#include <stdio.h>
#include <time.h>
#include <cstring>
#include <algorithm>

void initial_data(unsigned int* arr, const size_t n, const size_t limit)
{
  // Generate different seed for random number
  time_t t;
  srand((unsigned) time(&t));
  for (int i = 0; i < n; i++) 
  {
    arr[i] = (unsigned int)(rand() % limit);
  }
}

void output_array(unsigned int* arr, const size_t n)
{
  for (int i = 0; i < n; i++)
    printf("\t%d", arr[i]);
  printf("\n");
}

void radix_sort(unsigned int* inputVals, unsigned int* outputVals, const size_t numElems)
{
  unsigned int nBits = 4;
  unsigned int nBins = 1 << nBits; // 2^nBits

  unsigned int* vals_src = inputVals;
  unsigned int* vals_dst = outputVals;

  unsigned int* hist = new unsigned int[nBins];
  unsigned int* scannedHist = new unsigned int[nBins];
  
  // Loop from LSD to MSD
  // In each loop, soft values according to the current digit (using STABLE sort)
  for (int bit = 0; bit < 8*sizeof(unsigned int); bit += nBits)
  {
    // Compute hist
    memset(hist, 0, nBins*sizeof(unsigned int));
    for (int i = 0; i < numElems; i++)
    {
      unsigned int bin = (vals_src[i] >> bit) & (nBins - 1);
      hist[bin]++;
    }

    // Do exclusive scan on hist
    scannedHist[0] = 0;
    for (int i = 1; i < nBins; i++)
    {
      scannedHist[i] = scannedHist[i-1] + hist[i-1];
    }

    // Scatter values to correct locations
    for (int i = 0; i < numElems; i++)
    {
      int bin = (vals_src[i] >> bit) & (nBins - 1);
      vals_dst[scannedHist[bin]] = vals_src[i];
      scannedHist[bin]++;
    }

    // Swap src and dst
    std::swap(vals_dst, vals_src);
  }

  // The above loop does an even number of iterations.
  // Its means the sorted array we need is store in input buffer,
  // so we need to copy from input buffer into output.
  std::copy(inputVals, inputVals + numElems, outputVals);

  delete[] hist;
  delete[] scannedHist;
}

int main()
{
  int numElems = 10;
  int limit = 21;
  unsigned int* arr = new unsigned int[numElems];
  unsigned int* sortedArray = new unsigned int[numElems];

  initial_data(arr, numElems, limit);
  printf("Array is:\n");
  output_array(arr, numElems);

  radix_sort(arr, sortedArray, numElems);
  printf("Sorted array is:\n");
  output_array(sortedArray, numElems);

  delete[] arr;
  delete[] sortedArray;

  return 0;
}

