#include <Complex.h>
#include <iostream>
#include <FFTransformer.h>

int main() {
    size_t n = 16;
    auto *signal = new float[n];
    auto *out1 = new dsperado::Complex<float>[n];
    auto *out2 = new dsperado::Complex<float>[n];

    for (size_t i = 0; i < n; ++i) {
        signal[i] = sin(i * M_PI / 10);
    }

    dsperado::FFTransformer<float> FFT(n);
    dsperado::FFTransformer<float, false> IFFT(n);

    FFT.transform(signal, out1);
    IFFT.transform(out1, out2);

    for (size_t i = 0; i < n; ++i) {
        std::cout << signal[i] << " ";
        std::cout << sqrt(out1[i].r * out1[i].r + out1[i].i * out1[i].i) << " ";
        std::cout << out2[i].r << "\n";
    }
}
