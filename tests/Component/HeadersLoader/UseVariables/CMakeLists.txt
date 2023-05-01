cmake_minimum_required(VERSION 3.26) # FindOpenCL.cmake
cmake_policy(VERSION 3.26)
enable_testing()

project(Component_HeadersLoader LANGUAGES C)

find_package(OpenCL REQUIRED COMPONENTS Headers OpenCL)

# FindOpenCL.cmake-only
add_executable(UseHeaders UseHeaders.c)
target_include_directories(UseHeaders PRIVATE "${OpenCL_INCLUDE_DIRS}")
target_link_libraries(UseHeaders PRIVATE "${OpenCL_LIBRARIES}")
target_compile_definitions(UseHeaders PRIVATE CL_TARGET_OPENCL_VERSION=300)
add_test(NAME UseHeaders COMMAND UseHeaders)