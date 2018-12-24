#pragma once

#include <fftw3.h>
#include <mutex>
#include <vector>
#include <complex>
#include <cassert>

namespace desperado {
  /*
   * Hilbert transformer class.
   * Intended to be used if multiple one-size transformations are needed.
   * Thread safe.
   */
  class HilbertTransformer {
  private:
    std::mutex _lock;
    int bufferSize;
    int limit1;
    int limit2;
    thread_local static fftw_complex *buffer;
    thread_local static fftw_complex *complexIn;
    thread_local static fftw_complex *complexOut;
    bool complexOutAllocated = false;

  public:
    /*
     * Constructor.
     * Params:
     *   bufferSize_ - size of the transformer
     */
    HilbertTransformer(int bufferSize_) : bufferSize(bufferSize_) {
      assert(bufferSize_ > 0);

      buffer = (fftw_complex*) fftw_malloc(this->bufferSize * sizeof(fftw_complex));
      complexIn = (fftw_complex*) fftw_malloc(this->bufferSize * sizeof(fftw_complex));

      auto mod_ = this->bufferSize % 2;
      limit1 = (this->bufferSize + mod_) / 2;
      limit2 = limit1 + ~mod_;
    }

    /*
     * Perform Hilbert transform (C style).
     * Params:
     *   in - pointer to the input real number array
     *   out - pointer to the output complex number array
     */
    void transform(const double* in, fftw_complex* out);

    /*
     * Perform Hilbert transform (C++ style).
     * Params:
     *   in - reference to the input real number vector
     *   out - reference to the output complex number vector
     */
    void transform(const std::vector<double>& in, std::vector<std::complex<double>>& out);

    ~HilbertTransformer() {
      fftw_free(buffer);
      fftw_free(complexIn);

      if (complexOutAllocated) {
        fftw_free(complexOut);
      }
    }
  };
}