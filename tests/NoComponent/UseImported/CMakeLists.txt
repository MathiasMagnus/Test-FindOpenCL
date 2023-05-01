cmake_minimum_required(VERSION 3.7) # OpenCL::OpenCL
cmake_policy(VERSION 3.1)
enable_testing()

project(NoComponent_UseImported LANGUAGES C)

find_package(OpenCL REQUIRED)

# Works with both
add_executable(UseLoader UseLoader.c)
target_link_libraries(UseLoader PRIVATE OpenCL::OpenCL)
target_compile_definitions(UseLoader PRIVATE CL_TARGET_OPENCL_VERSION=300)
add_test(NAME UseLoader COMMAND UseLoader)