cmake_minimum_required(VERSION 3.26)
cmake_policy(VERSION 3.26)
enable_testing()

project(CMakeFeature2 LANGUAGES C CXX)

set(CMakeFeature2_USE_KHRONOS_RELEASE "v2023.04.17" CACHE STRING "Tag hash of Khronos release to fetch to test with")
set(CMakeFeature2_EP_BASE "external" CACHE PATH "Path of external projects (relative to PROJECT_BINARY_DIR)")

set(EP_INSTALL_ROOT "${PROJECT_BINARY_DIR}/${CMakeFeature2_EP_BASE}/Install")

set(OpenCL-Headers_OPTIONS
    "-DBUILD_TESTING:BOOL=OFF"
    "-DOPENCL_HEADERS_BUILD_TESTING:BOOL=OFF"
    "-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>"
)
set(OpenCL-CLHPP_OPTIONS
    "-DBUILD_TESTING:BOOL=OFF"
    "-DOPENCL_CLHPP_BUILD_TESTING:BOOL=OFF"
    "-DBUILD_DOCS:BOOL=OFF"
    "-DBUILD_EXAMPLES:BOOL=OFF"
    "-DCMAKE_PREFIX_PATH:PATH=${EP_INSTALL_ROOT}/OpenCL-Headers"
    "-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>"
)
set(OpenCL-ICD-Loader_OPTIONS
    "-DBUILD_TESTING:BOOL=OFF"
    "-DOPENCL_ICD_LOADER_BUILD_TESTING:BOOL=OFF"
    "-DCMAKE_PREFIX_PATH:PATH=${EP_INSTALL_ROOT}/OpenCL-Headers"
    "-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>"
)
set(OpenCL-SDK_OPTIONS
    "-DOPENCL_SDK_BUILD_SAMPLES:BOOL=OFF"
    ${OpenCL-Headers_OPTIONS}
    ${OpenCL-CLHPP_OPTIONS}
    ${OpenCL-ICD-Loader_OPTIONS}
)

include(ExternalProject)
set_directory_properties(PROPERTIES EP_BASE "${PROJECT_BINARY_DIR}/${CMakeFeature2_EP_BASE}")

ExternalProject_Add(OpenCL-Headers
    GIT_REPOSITORY         https://github.com/KhronosGroup/OpenCL-Headers.git
    GIT_TAG                ${CMakeFeature2_USE_KHRONOS_RELEASE}
    GIT_SUBMODULES_RECURSE OFF
    GIT_SUBMODULES         ""
    GIT_SHALLOW            ON
    CMAKE_CACHE_ARGS       ${OpenCL-Headers_OPTIONS}
)
ExternalProject_Add(OpenCL-CLHPP
    GIT_REPOSITORY         https://github.com/KhronosGroup/OpenCL-CLHPP.git
    GIT_TAG                ${CMakeFeature2_USE_KHRONOS_RELEASE}
    GIT_SUBMODULES_RECURSE OFF
    GIT_SUBMODULES         ""
    GIT_SHALLOW            ON
    CMAKE_CACHE_ARGS       ${OpenCL-CLHPP_OPTIONS}
    DEPENDS                OpenCL-Headers
)
ExternalProject_Add(OpenCL-ICD-Loader
    GIT_REPOSITORY         https://github.com/KhronosGroup/OpenCL-ICD-Loader.git
    GIT_TAG                ${CMakeFeature2_USE_KHRONOS_RELEASE}
    GIT_SUBMODULES_RECURSE OFF
    GIT_SUBMODULES         ""
    GIT_SHALLOW            ON
    CMAKE_CACHE_ARGS       ${OpenCL-ICD-Loader_OPTIONS}
    DEPENDS                OpenCL-Headers
)
ExternalProject_Add(OpenCL-SDK
    #GIT_REPOSITORY         https://github.com/KhronosGroup/OpenCL-SDK.git
    GIT_REPOSITORY         https://github.com/StreamHPC/OpenCL-SDK.git
    #GIT_TAG                ${CMakeFeature2_USE_KHRONOS_RELEASE}
    GIT_TAG                install-fixes
    GIT_SUBMODULES_RECURSE OFF
    GIT_SHALLOW            ON
    CMAKE_CACHE_ARGS       ${OpenCL-SDK_OPTIONS}
)
ExternalProject_Add(OpenCL-SDK-DLL
    #GIT_REPOSITORY         https://github.com/KhronosGroup/OpenCL-SDK.git
    GIT_REPOSITORY         https://github.com/StreamHPC/OpenCL-SDK.git
    #GIT_TAG                ${CMakeFeature2_USE_KHRONOS_RELEASE}
    GIT_TAG                install-fixes
    GIT_SUBMODULES_RECURSE OFF
    GIT_SHALLOW            ON
    CMAKE_CACHE_ARGS       "${OpenCL-SDK_OPTIONS};-DBUILD_SHARED_LIBS:BOOL=ON"
)

add_subdirectory(tests)