#include <cstring>
#include <algorithm>

void reference_calculation(unsigned int* inputVals,
                           unsigned int* inputPos,
                           unsigned int* outputVals,
                           unsigned int* outputPos,
                           const size_t numElems)
{
  unsigned int nBits = 4;
  unsigned int nBins = 1 << nBits; // 2^nBits

  unsigned int* vals_src = inputVals;
  unsigned int* pos_src = inputPos;

  unsigned int* vals_dst = outputVals;
  unsigned int* pos_dst = outputPos;

  unsigned int* hist = new unsigned int[nBins];
  unsigned int* scannedHist = new unsigned int[nBins];

  // Loop from LSD to MSD
  // In each loop, soft values according to the current digit (using STABLE sort)
  for (unsigned int bit = 0; bit < 8*sizeof(unsigned int); bit += nBits)
  {
    // Compute hist
    memset(hist, 0, nBins*sizeof(unsigned int));
    for (unsigned int i = 0; i < numElems; i++)
    {
      unsigned int bin = (vals_src[i] >> bit) & (nBins - 1);
      hist[bin]++;
    }

    // Do exclusive scan on hist
    scannedHist[0] = 0;
    for (unsigned int i = 1; i < nBins; i++)
    {
      scannedHist[i] = scannedHist[i-1] + hist[i-1];
    }

    // Scatter values to correct locations
    for (unsigned int i = 0; i < numElems; i++)
    {
      int bin = (vals_src[i] >> bit) & (nBins - 1);
      vals_dst[scannedHist[bin]] = vals_src[i];
      pos_dst[scannedHist[bin]] = pos_src[i];
      scannedHist[bin]++;
    }

    // Swap src and dst
    std::swap(vals_dst, vals_src);
    std::swap(pos_dst, pos_src);
  }

  // The above loop does an even number of iterations.
  // Its means the sorted array we need is store in input buffer,
  // so we need to copy from input buffer into output.
  std::copy(inputVals, inputVals + numElems, outputVals);
  std::copy(inputPos, inputPos + numElems, outputPos);

  delete[] hist;
  delete[] scannedHist;
}

