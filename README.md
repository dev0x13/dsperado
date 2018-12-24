# DSPerado
Some code I wrote for ultrasound processing compiled into this small DSP library.

## Build instructions
Clone and build FFTW3 (or turn off FFTW3 usage by passing -DUSE_FFTW=OFF to the cmake command):

```shell
git submodule update --init --recursive
cd tools/
./build_fftw3.sh
```

Build DSPerado with CMake:
```shell
mkdir build
cd build
cmake ..
cmake --build .
```

You can also build static library:
```
cmake -DSTATIC=ON ..
```

## Features
* Hilbert transform
* Cross correlation:
  * 2D complex normalized (different variants coming soon)
* FIR:
  * Low-pass
  * High-pass
  * Smoothed digital differentiator (other variants coming soon)
