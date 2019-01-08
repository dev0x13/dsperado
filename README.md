# DSPerado
Some code I wrote for ultrasound processing compiled into this small DSP library.

## Features
* Header only, C++11, dependency free library
* Quite fast FFT and IFFT
* Hilbert transform (within analytic signal calculation)
* Cross correlation:
  * 2D complex normalized (different variants coming soon)
* FIR:
  * Low-pass
  * High-pass
  * Smoothed digital differentiator (other variants coming soon)

You can build DSPerado example with CMake:
```shell
mkdir build
cd build
cmake ..
cmake --build .
```