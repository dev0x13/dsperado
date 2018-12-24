#!/bin/bash

root_dir=..

cd $root_dir/lib/fftw3 && mkdir build

./bootstrap.sh
make

cd build

cmake ..
cmake --build . -- -j2
