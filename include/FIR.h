#include <vector>
#include <cstddef>

namespace dsperado {
  namespace FIR {
    /*
     * Low pass filter.
     * Params:
     *   (
     *     inOut: reference to the input-output vector
     *     or
     *     inOut: pointer to the input-output array
     *     inOutSize: input-output array size
     *   )
     *   cutoff: filter cutoff frequency
     *   sampleRate: signal sample rate
     */
    void lowPass(std::vector<double>& inOut, int cutoff, int sampleRate);
    void lowPass(double *inOut, size_t inOutSize, int cutoff, int sampleRate);

    /*
     * High pass filter.
     * Params:
     *   (
     *     inOut: reference to the input-output vector
     *     or
     *     inOut: pointer to the input-output array
     *     inOutSize: input-output array size
     *   )
     *   cutoff: filter cutoff frequency
     *   sampleRate: signal sample rate
     */
    void highPass(std::vector<double>& inOut, int cutoff, int sampleRate);
    void highPass(double *inOut, size_t inOutSize, int cutoff, int sampleRate);

    /*
     * Smoothed digital differentiator I.
     * Coefficients are cached once designed.
     * Params:
     *   (
     *     inOut: reference to the input-output vector
     *     or
     *     inOut: pointer to the input-output array
     *     inOutSize: input-output array size
     *   )
     *   coeffsNum: number of coefficients (filter length = 2 * coeffsNum + 1)
     */
    void smoothedDD1(std::vector<double>& inOut, size_t coeffsNum);
    void smoothedDD1(double *inOut, size_t inOutSize, size_t coeffsNum);
  }
}
