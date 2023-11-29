cmake_minimum_required(VERSION 3.26)
cmake_policy(VERSION 3.26)
enable_testing()

project(Test-FindOpenCL LANGUAGES C CXX)

set(TEST_FINDOPENCL_USE_TAG "v2023.04.17" CACHE STRING "Tag hash of Khronos release to fetch to test with")
set(TEST_FINDOPENCL_EP_BASE "external" CACHE PATH "Path of external projects (relative to PROJECT_BINARY_DIR)")
set(TEST_FINDOPENCL_HEADERS_URL ${TEST_FINDOPENCL_USE_TAG} CACHE STRING "Git repo URL of OpenCL-Headers")
set(TEST_FINDOPENCL_HEADERS_TAG ${TEST_FINDOPENCL_USE_TAG} CACHE STRING "Git tag of OpenCL-Headers")
set(TEST_FINDOPENCL_CLHPP_URL ${TEST_FINDOPENCL_USE_TAG} CACHE STRING "Git repo URL of OpenCL-CLHPP")
set(TEST_FINDOPENCL_CLHPP_TAG ${TEST_FINDOPENCL_USE_TAG} CACHE STRING "Git tag of OpenCL-CLHPP")
set(TEST_FINDOPENCL_ICD_LOADER_URL ${TEST_FINDOPENCL_USE_TAG} CACHE STRING "Git repo URL of OpenCL-ICD-Loader")
set(TEST_FINDOPENCL_ICD_LOADER_TAG ${TEST_FINDOPENCL_USE_TAG} CACHE STRING "Git tag of OpenCL-ICD-Loader")
set(TEST_FINDOPENCL_SDK_URL ${TEST_FINDOPENCL_USE_TAG} CACHE STRING "Git repo URL of OpenCL-SDK")
set(TEST_FINDOPENCL_SDK_TAG ${TEST_FINDOPENCL_USE_TAG} CACHE STRING "Git tag of OpenCL-SDK")

set(EP_INSTALL_ROOT "${PROJECT_BINARY_DIR}/${CMakeFeature2_EP_BASE}/Install")

# These Common_OPTIONS need to be given to _every_ external project, both those that fetch deps and those which will
# constitute the actual tests, because ExternalProject doesn't relay the entire command-line given to it, most
# problematic of all, it doesn't relay build-system related variables. If ninja isn't on the PATH, even if we
# selected one explicitly in a preset file (or any other way), it will not find it.
if(CMAKE_GENERATOR MATCHES [[Ninja|Makefiles]])
    set(Common_OPTIONS
        "-DCMAKE_MAKE_PROGRAM:PATH=${CMAKE_MAKE_PROGRAM}"
    )
elseif(CMAKE_GENERATOR MATCHES [[Visual]])
    set(Common_OPTIONS
        "-DCMAKE_GENERATOR_INSTANCE:STRING=${MAKE_GENERATOR_INSTANCE}"
        "-DCMAKE_GENERATOR_PLATFORM:STRING=${CMAKE_GENERATOR_PLATFORM}"
        "-DCMAKE_GENERATOR_TOOLSET:STRING=${CMAKE_GENERATOR_TOOLSET}"  
    )
elseif(CMAKE_GENERATOR MATCHES [[Xcode]])
    set(Common_OPTIONS
        "-DCMAKE_FIND_FRAMEWORK:STRING=${CMAKE_FIND_FRAMEWORK}"
        "-DCMAKE_FIND_APPBUNDLE:STRING=${CMAKE_FIND_APPBUNDLE}"
    )
else()
endif()
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
    GIT_REPOSITORY         ${TEST_FINDOPENCL_HEADERS_URL}
    GIT_TAG                ${TEST_FINDOPENCL_HEADERS_TAG}
    GIT_SUBMODULES_RECURSE OFF
    GIT_SUBMODULES         ""
    GIT_SHALLOW            ON
    CMAKE_CACHE_ARGS       "${Common_OPTIONS};${OpenCL-Headers_OPTIONS}"
)
ExternalProject_Add(OpenCL-CLHPP
    GIT_REPOSITORY         ${TEST_FINDOPENCL_CLHPP_URL}
    GIT_TAG                ${TEST_FINDOPENCL_CLHPP_TAG}
    GIT_SUBMODULES_RECURSE OFF
    GIT_SUBMODULES         ""
    GIT_SHALLOW            ON
    CMAKE_CACHE_ARGS       "${Common_OPTIONS};${OpenCL-CLHPP_OPTIONS}"
    DEPENDS                OpenCL-Headers
)
ExternalProject_Add(OpenCL-ICD-Loader
    GIT_REPOSITORY         ${TEST_FINDOPENCL_ICD_LOADER_URL}
    GIT_TAG                ${TEST_FINDOPENCL_ICD_LOADER_TAG}
    GIT_SUBMODULES_RECURSE OFF
    GIT_SUBMODULES         ""
    GIT_SHALLOW            ON
    CMAKE_CACHE_ARGS       "${Common_OPTIONS};${OpenCL-ICD-Loader_OPTIONS}"
    DEPENDS                OpenCL-Headers
)
ExternalProject_Add(OpenCL-ICD-Loader-Static
    GIT_REPOSITORY         ${TEST_FINDOPENCL_ICD_LOADER_URL}
    GIT_TAG                ${TEST_FINDOPENCL_ICD_LOADER_TAG}
    GIT_SUBMODULES_RECURSE OFF
    GIT_SUBMODULES         ""
    GIT_SHALLOW            ON
    CMAKE_CACHE_ARGS       "${Common_OPTIONS};${OpenCL-ICD-Loader_OPTIONS};-DOPENCL_ICD_LOADER_BUILD_SHARED_LIBS:BOOL=OFF"
    DEPENDS                OpenCL-Headers
)
ExternalProject_Add(OpenCL-SDK
    GIT_REPOSITORY         ${TEST_FINDOPENCL_SDK_URL}
    GIT_TAG                ${TEST_FINDOPENCL_SDK_TAG}
    GIT_SUBMODULES_RECURSE OFF
    GIT_SHALLOW            ON
    CMAKE_CACHE_ARGS       "${Common_OPTIONS};${OpenCL-SDK_OPTIONS}"
)
ExternalProject_Add(OpenCL-SDK-DLL
    GIT_REPOSITORY         ${TEST_FINDOPENCL_SDK_URL}
    GIT_TAG                ${TEST_FINDOPENCL_SDK_TAG}
    GIT_SUBMODULES_RECURSE OFF
    GIT_SHALLOW            ON
    CMAKE_CACHE_ARGS       "${Common_OPTIONS};${OpenCL-SDK_OPTIONS};-DBUILD_SHARED_LIBS:BOOL=ON"
)
ExternalProject_Add(OpenCL-SDK-Static-DLL
    GIT_REPOSITORY         ${TEST_FINDOPENCL_SDK_URL}
    GIT_TAG                ${TEST_FINDOPENCL_SDK_TAG}
    GIT_SUBMODULES_RECURSE OFF
    GIT_SHALLOW            ON
    CMAKE_CACHE_ARGS       "${Common_OPTIONS};${OpenCL-SDK_OPTIONS};-DOPENCL_ICD_LOADER_BUILD_SHARED_LIBS:BOOL=OFF;-DBUILD_SHARED_LIBS:BOOL=ON"
)

add_subdirectory(tests)