cmake_minimum_required(VERSION 3.26) # FindOpenCL.cmake
cmake_policy(VERSION 3.26)
enable_testing()

project(Component_HeadersCppLoader_UseImported LANGUAGES CXX)

find_package(OpenCL REQUIRED COMPONENTS Headers HeadersCpp OpenCL)

# Works with both
add_executable(UseImported UseLoader.cpp)
target_link_libraries(UseImported PRIVATE OpenCL::Headers OpenCL::HeadersCpp OpenCL::OpenCL)
target_compile_definitions(UseImported
    PRIVATE
        CL_TARGET_OPENCL_VERSION=300
        CL_HPP_TARGET_OPENCL_VERSION=300
        CL_HPP_MINIMUM_OPENCL_VERSION=300
        CL_HPP_ENABLE_EXCEPTIONS)
add_test(NAME UseImported COMMAND UseImported)