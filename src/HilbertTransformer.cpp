#include <HilbertTransformer.h>

void desperado::HilbertTransformer::transform(const double* in, fftw_complex* out) {
  for (int i = 0; i < this->bufferSize; ++i) {
    complexIn[i][0] = in[i];
    complexIn[i][1] = 0;
  }

  fftw_plan pf;

  {
    std::lock_guard<std::mutex> lock(_lock);

    pf = fftw_plan_dft_1d(this->bufferSize, complexIn, this->buffer, FFTW_FORWARD, FFTW_ESTIMATE);
  }

  fftw_execute(pf);

  for (int i = 1; i < limit1; ++i) {
    this->buffer[i][0] *= 2;
    this->buffer[i][1] *= 2;
  }

  for (int i = limit2; i < this->bufferSize; ++i) {
    this->buffer[i][0] = 0;
    this->buffer[i][1] = 0;
  }

  fftw_plan pb;

  {
    std::lock_guard<std::mutex> lock(_lock);

    pb = fftw_plan_dft_1d(this->bufferSize, this->buffer, out, FFTW_BACKWARD, FFTW_ESTIMATE);
  }

  fftw_execute(pb);

  for (int i = 0; i < this->bufferSize; ++i) {
    out[i][0] /= this->bufferSize;
    out[i][1] /= this->bufferSize;
  }

  {
    std::lock_guard<std::mutex> lock(_lock);

    fftw_destroy_plan(pf);
    fftw_destroy_plan(pb);
  }
}

void desperado::HilbertTransformer::transform(const std::vector<double>& in, std::vector<std::complex<double>>& out) {
  // Lazy allocation of output array
  if (!this->complexOutAllocated) {
    complexOut = (fftw_complex*) fftw_malloc(this->bufferSize * sizeof(fftw_complex));
    this->complexOutAllocated = true;
  }

  if (out.size() < (size_t) this->bufferSize) {
    out.reserve((size_t) this->bufferSize);
  }

  this->transform(in.data(), this->complexOut);

  for (int i = 0; i < this->bufferSize; ++i) {
    out.emplace_back(std::complex<double>(this->complexOut[i][0], this->complexOut[i][1]));
  }
}