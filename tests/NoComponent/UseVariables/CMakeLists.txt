cmake_minimum_required(VERSION 3.1) # FindOpenCL.cmake
cmake_policy(VERSION 3.1)
enable_testing()

project(NoComponent_UseVariables LANGUAGES C)

find_package(OpenCL REQUIRED)

# FindOpenCL.cmake-only
add_executable(UseHeaders UseHeaders.c)
target_include_directories(UseHeaders PRIVATE "${OpenCL_INCLUDE_DIRS}")
target_compile_definitions(UseHeaders PRIVATE CL_TARGET_OPENCL_VERSION=300)
add_test(NAME UseHeaders COMMAND UseHeaders)

# FindOpenCL.cmake-only
add_executable(UseLoader UseLoader.c)
target_include_directories(UseLoader PRIVATE "${OpenCL_INCLUDE_DIRS}")
target_link_libraries(UseLoader PRIVATE "${OpenCL_LIBRARIES}")
target_compile_definitions(UseLoader PRIVATE CL_TARGET_OPENCL_VERSION=300)
add_test(NAME UseLoader COMMAND UseLoader)