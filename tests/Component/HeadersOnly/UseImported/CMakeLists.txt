cmake_minimum_required(VERSION 3.26) # FindOpenCL.cmake
cmake_policy(VERSION 3.26)
enable_testing()

project(Component_HeadersOnly_UseImported LANGUAGES C)

find_package(OpenCL REQUIRED COMPONENTS Headers)

# Works with both
add_executable(UseHeaders UseHeaders.c)
target_link_libraries(UseHeaders PRIVATE OpenCL::Headers)
target_compile_definitions(UseHeaders PRIVATE CL_TARGET_OPENCL_VERSION=300)
add_test(NAME UseHeaders COMMAND UseHeaders)