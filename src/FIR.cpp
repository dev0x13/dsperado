#include <FIR.h>

#include <map>
#include <vector>
#include <algorithm>
#include <cassert>

static constexpr double oneDivPi2 = 1.0 / M_PI_2;

// Low pass filter

void dsperado::FIR::lowPass(double *inOut, size_t inOutSize, int cutoff, int sampleRate) {
  double RC = oneDivPi2 / cutoff;
  double dt = 1.0 / sampleRate;
  double alpha = dt / (RC + dt);

  for (size_t i = 1; i < inOutSize; ++i) {
    inOut[i] = inOut[i - 1] + (alpha * (inOut[i] - inOut[i - 1]));
  }
}

void dsperado::FIR::lowPass(std::vector<double>& inOut, int cutoff, int sampleRate) {
  lowPass(inOut.data(), inOut.size(), cutoff, sampleRate);
}

// High pass filter

void dsperado::FIR::highPass(double *inOut, size_t inOutSize, int cutoff, int sampleRate) {
  double RC = oneDivPi2 / cutoff;
  double dt = 1.0 / sampleRate;
  double alpha = RC / (RC + dt);

  double prev = inOut[0], tmp;

  for (size_t i = 1; i < inOutSize; ++i) {
    tmp = inOut[i];
    inOut[i] = alpha * (inOut[i - 1] + inOut[i] - prev);
    prev = tmp;
  }
}

void dsperado::FIR::highPass(std::vector<double>& inOut, int cutoff, int sampleRate) {
  highPass(inOut.data(), inOut.size(), cutoff, sampleRate);
}

// Smoothed DD I

void dsperado::FIR::smoothedDD1(double *inOut, size_t inOutSize, size_t coeffsNum) {
  assert(coeffsNum >= 2);

  static std::map<int, std::vector<double>> coeffsMap;

  auto& coeffs = coeffsMap[coeffsNum];

  if (coeffs.empty()) {
    for (size_t i = 0; i < coeffsNum; ++i) {
      coeffs.emplace_back(1.0 / coeffsNum / (coeffsNum + 1));
    }
  }

  for (size_t i = 0; i < inOutSize; ++i) {
    for (size_t j = 1; j < coeffsNum + 1; ++j) {
      inOut[i] += coeffs[j - 1] * (inOut[std::min(i + j, inOutSize - 1)] - inOut[std::max(i - j, (size_t) 0)]);
    }
  }
}

void dsperado::FIR::smoothedDD1(std::vector<double>& inOut, size_t coeffsNum) {
  smoothedDD1(inOut.data(), inOut.size(), coeffsNum);
}
