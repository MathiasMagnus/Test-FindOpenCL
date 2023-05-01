cmake_minimum_required(VERSION 3.26) # FindOpenCL.cmake
cmake_policy(VERSION 3.26)
enable_testing()

project(Component_Utils_UseImported LANGUAGES C)

find_package(OpenCL REQUIRED COMPONENTS Headers Utils OpenCL)

# Works with OpenCL-SDK-only
add_executable(UseUtils UseUtils.c)
target_link_libraries(UseUtils PRIVATE OpenCL::Headers OpenCL::Utils OpenCL::OpenCL)
target_compile_definitions(UseUtils PRIVATE CL_TARGET_OPENCL_VERSION=300)
add_test(NAME UseUtils COMMAND UseUtils)