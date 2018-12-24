#pragma once

#include <complex>
#include <vector>

namespace dsperado {
  namespace XCorr {
    /*
     * Normalized complex 2D cross correlation.
     * Params:
     *   m1 - first 2D array [cols][rows]
     *   m2 - second 2D array [cols][rows]
     *   row - row index of interest
     *   col - column index of interest
     *   lag - desired lag (delay)
     * Returns:
     *   Complex cross correlation value in point (col, row)
     */
    std::complex<double> XCorr2DNormComplex(
            const std::vector<std::vector<std::complex<double>*>>& m1,
            const std::vector<std::vector<std::complex<double>*>>& m2,
            size_t col, size_t row, size_t lag);
    }
}
