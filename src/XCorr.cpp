#include <XCorr.h>
#include <cassert>

std::complex<double> desperado::XCorr::XCorr2DNormComplex(
        const std::vector<std::vector<std::complex<double>*>>& m1,
        const std::vector<std::vector<std::complex<double>*>>& m2,
        size_t col, size_t row, size_t lag) {

  std::complex<double> corr1(0, 0), corr2(0, 0), corr3(0, 0);

  auto N = m1.size();

  assert(N != 0 && N == m2.size() && col < N);

  auto M = m1[0].size();

  assert(M == m2[0].size() && row < M);

  for (size_t n_ = 0; n_ < N - col - lag; ++n_) {
    for (size_t m_ = 0; m_ < M - row - lag; ++m_) {
      corr1 += *m1[col + n_][row + m_] * std::conj(*m2[col + n_][row + m_ + lag]);
      corr2 += *m1[col + n_][row + m_] * std::conj(*m1[col + n_][row + m_]);
      corr3 += *m2[col + n_][row + m_ + lag] * std::conj(*m2[col + n_][row + m_ + lag]);
    }
  }

  return corr1 / sqrt(corr2 * corr3);
}