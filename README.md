# Test-FindOpenCL.cmake

This repository serves as testing grounds for CMake's own `FindOpenCL.cmake`.

It tests all the supported ways of consuming an OpenCL SDK, and some specific components of the Khronos OpenCL-SDK (which vendors are open to package in their own SDKs as well).

## Using

The repository pulls all the necessary components using ExternalProject. CTest is used to test whether built targets actually execute and linkage is proper.
