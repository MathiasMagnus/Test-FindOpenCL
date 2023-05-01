cmake_minimum_required(VERSION 3.26) # FindOpenCL.cmake
cmake_policy(VERSION 3.26)
enable_testing()

project(Component_UtilsCpp_UseImported LANGUAGES CXX)

find_package(OpenCL REQUIRED COMPONENTS Headers HeadersCpp Utils UtilsCpp OpenCL)

# Works with OpenCL-SDK-only
add_executable(UseUtils UseUtils.cpp)
target_link_libraries(UseUtils PUBLIC OpenCL::Headers OpenCL::HeadersCpp OpenCL::Utils OpenCL::UtilsCpp OpenCL::OpenCL)
target_compile_definitions(UseUtils
    PRIVATE
        CL_TARGET_OPENCL_VERSION=300
        CL_HPP_TARGET_OPENCL_VERSION=300
        CL_HPP_MINIMUM_OPENCL_VERSION=300
        CL_HPP_ENABLE_EXCEPTIONS)
target_compile_features(UseUtils
    PRIVATE
        cxx_std_17)
add_test(NAME UseUtils COMMAND UseUtils)