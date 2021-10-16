mkdir Engine\Build\Win64

echo Generating CMake project...

cd Engine\Build\Win64
cmake ..\..\..\ -DCMAKE_BUILD_TYPE=Debug

PAUSE