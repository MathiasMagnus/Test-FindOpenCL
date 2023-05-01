cmake_minimum_required(VERSION 3.26) # FindOpenCL.cmake
cmake_policy(VERSION 3.26)
enable_testing()

project(Component_HeadersLoader LANGUAGES C)

find_package(OpenCL REQUIRED COMPONENTS Headers OpenCL)

# Works with both
add_executable(UseLoader UseLoader.c)
target_link_libraries(UseLoader PRIVATE OpenCL::Headers OpenCL::OpenCL)
target_compile_definitions(UseLoader PRIVATE CL_TARGET_OPENCL_VERSION=300)
add_test(NAME UseLoader COMMAND UseLoader)