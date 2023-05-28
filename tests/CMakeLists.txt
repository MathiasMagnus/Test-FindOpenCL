set_directory_properties(PROPERTIES EP_BASE "${PROJECT_BINARY_DIR}/tests")

set(EP_BUILD_ROOT "${PROJECT_BINARY_DIR}/tests/Build")

set(OpenCL-Headers_CMAKE_PREFIX_PATH
    "-DCMAKE_PREFIX_PATH:PATH=${EP_INSTALL_ROOT}/OpenCL-Headers"
)
set(OpenCL-Headers-ICD-Loader_CMAKE_PREFIX_PATH
    "-DCMAKE_PREFIX_PATH:PATH=${EP_INSTALL_ROOT}/OpenCL-Headers$<SEMICOLON>${EP_INSTALL_ROOT}/OpenCL-ICD-Loader"
)
set(OpenCL-Headers-ICD-Loader-CLHPP_CMAKE_PREFIX_PATH
    "-DCMAKE_PREFIX_PATH:PATH=${EP_INSTALL_ROOT}/OpenCL-Headers$<SEMICOLON>${EP_INSTALL_ROOT}/OpenCL-ICD-Loader$<SEMICOLON>${EP_INSTALL_ROOT}/OpenCL-CLHPP"
)
set(OpenCL-SDK_CMAKE_PREFIX_PATH
    "-DCMAKE_PREFIX_PATH:PATH=${EP_INSTALL_ROOT}/OpenCL-SDK"
)
set(OpenCL-SDK-DLL_CMAKE_PREFIX_PATH
    "-DCMAKE_PREFIX_PATH:PATH=${EP_INSTALL_ROOT}/OpenCL-SDK-DLL"
)

function(add_find_opencl_test)
    list(POP_FRONT ARGN ARG_NAME)
    set(options "")
    set(one_value_args SOURCE_DIR)
    set(multi_value_args CMAKE_CACHE_ARGS DEPENDS)
    cmake_parse_arguments(ARG
        "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN}
    )
    ExternalProject_Add(${ARG_NAME}
        SOURCE_DIR       "${PROJECT_SOURCE_DIR}/${ARG_SOURCE_DIR}"
        CMAKE_CACHE_ARGS "${Common_OPTIONS};${ARG_CMAKE_CACHE_ARGS}"
        DEPENDS          "${ARG_DEPENDS}"
    )
    add_test(
        NAME ${ARG_NAME}
        COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/${ARG_NAME}" --build-config $<CONFIG>
    )
endfunction(add_find_opencl_test)

# Pre-CMake 3.8 style. SDK doesn't expose legacy variables
add_find_opencl_test(NoComponent_UseVariables_Separate
    SOURCE_DIR       "tests/NoComponent/UseVariables"
    CMAKE_CACHE_ARGS "${OpenCL-Headers-ICD-Loader_CMAKE_PREFIX_PATH}" # NOTE: both needed, even if only one is used
    DEPENDS          OpenCL-Headers OpenCL-ICD-Loader                 # NOTE: both needed, even if only one is used
)

# CMake 3.8+ style. SDK exposes usual OpenCL::OpenCL in backward compatible manner
add_find_opencl_test(NoComponent_UseImported_Separate
    SOURCE_DIR       "tests/NoComponent/UseImported"
    CMAKE_CACHE_ARGS "${OpenCL-Headers-ICD-Loader_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-Headers OpenCL-ICD-Loader
)
add_find_opencl_test(NoComponent_UseImported_SDK
    SOURCE_DIR       "tests/NoComponent/UseImported"
    CMAKE_CACHE_ARGS "${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK
)
add_find_opencl_test(NoComponent_UseImported_SDK_CONFIG
    SOURCE_DIR       "tests/NoComponent/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON" "${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK
)

# SDK or CMake 3.27+ style.
add_find_opencl_test(Component_HeadersOnly_UseVariables_Separate
    SOURCE_DIR       "tests/Component/HeadersOnly/UseVariables"
    CMAKE_CACHE_ARGS "${OpenCL-Headers_CMAKE_PREFIX_PATH}" # NOTE: works, but don't know who uses bleeding edge CMake
    DEPENDS          OpenCL-Headers                        #       yet still uses the legacy variables
)
add_find_opencl_test(Component_HeadersOnly_UseImported_Separate
    SOURCE_DIR       "tests/Component/HeadersOnly/UseImported"
    CMAKE_CACHE_ARGS "${OpenCL-Headers_CMAKE_PREFIX_PATH}" # NOTE: with components, for headers-only, no ICD needed
    DEPENDS          OpenCL-Headers                        # NOTE: with components, for headers-only, no ICD needed
)
add_find_opencl_test(Component_HeadersOnly_UseImported_SDK
    SOURCE_DIR       "tests/Component/HeadersOnly/UseImported"
    CMAKE_CACHE_ARGS "${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK
)
add_find_opencl_test(Component_HeadersOnly_UseImported_SDK_CONFIG
    SOURCE_DIR       "tests/Component/HeadersOnly/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON" "${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK
)

add_find_opencl_test(Component_HeadersLoader_UseVariables_Separate
    SOURCE_DIR       "tests/Component/HeadersLoader/UseVariables"
    CMAKE_CACHE_ARGS "${OpenCL-Headers-ICD-Loader_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-Headers OpenCL-ICD-Loader
)
add_find_opencl_test(Component_HeadersLoader_UseImported_Separate
    SOURCE_DIR       "tests/Component/HeadersLoader/UseImported"
    CMAKE_CACHE_ARGS "${OpenCL-Headers-ICD-Loader_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-Headers OpenCL-ICD-Loader
)
add_find_opencl_test(Component_HeadersLoader_UseImported_SDK
    SOURCE_DIR       "tests/Component/HeadersLoader/UseImported"
    CMAKE_CACHE_ARGS "${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK
)
add_find_opencl_test(Component_HeadersLoader_UseImported_SDK_CONFIG
    SOURCE_DIR       "tests/Component/HeadersLoader/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON" "${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK
)

# Component_HeadersCppLoader_UseVariables_Separate doesn't exist, because C++ headers don't have a variable
# nor was it ever checked for. Users got the C++ headers "by chance". An SDK either shipped them or not.
# The system either had the opencl-clhpp-headers installed while detecting or not.
add_find_opencl_test(Component_HeadersCppLoader_UseImported_Separate
    SOURCE_DIR       "tests/Component/HeadersCppLoader/UseImported"
    CMAKE_CACHE_ARGS "${OpenCL-Headers-ICD-Loader-CLHPP_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-Headers OpenCL-ICD-Loader OpenCL-CLHPP
)
add_find_opencl_test(Component_HeadersCppLoader_UseImported_SDK
    SOURCE_DIR       "tests/Component/HeadersCppLoader/UseImported"
    CMAKE_CACHE_ARGS "${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK
)
add_find_opencl_test(Component_HeadersCppLoader_UseImported_SDK_CONFIG
    SOURCE_DIR       "tests/Component/HeadersCppLoader/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON" "${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK
)

# The utility libraries are part of the SDK, so they can't be built separately
add_find_opencl_test(Component_Utils_UseImported_SDK
    SOURCE_DIR       "tests/Component/Utils/UseImported"
    CMAKE_CACHE_ARGS "${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK
)
add_find_opencl_test(Component_Utils_UseImported_SDK_CONFIG
    SOURCE_DIR       "tests/Component/Utils/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON" "${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK
)
add_find_opencl_test(Component_UtilsCpp_UseImported_SDK
    SOURCE_DIR       "tests/Component/UtilsCpp/UseImported"
    CMAKE_CACHE_ARGS "${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK
)
add_find_opencl_test(Component_UtilsCpp_UseImported_SDK_CONFIG
    SOURCE_DIR       "tests/Component/UtilsCpp/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON" "${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK
)

# Check the utility libraries when built as .so/.dll
add_find_opencl_test(Component_Utils_UseImported_SDK_DLL
    SOURCE_DIR       "tests/Component/Utils/UseImported"
    CMAKE_CACHE_ARGS "${OpenCL-SDK-DLL_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK-DLL
)
add_find_opencl_test(Component_Utils_UseImported_SDK_DLL_CONFIG
    SOURCE_DIR       "tests/Component/Utils/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON" "${OpenCL-SDK-DLL_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK-DLL
)
add_find_opencl_test(Component_UtilsCpp_UseImported_SDK_DLL
    SOURCE_DIR       "tests/Component/UtilsCpp/UseImported"
    CMAKE_CACHE_ARGS "${OpenCL-SDK-DLL_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK-DLL
)
add_find_opencl_test(Component_UtilsCpp_UseImported_SDK_DLL_CONFIG
    SOURCE_DIR       "tests/Component/UtilsCpp/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON" "${OpenCL-SDK-DLL_CMAKE_PREFIX_PATH}"
    DEPENDS          OpenCL-SDK-DLL
)
set_tests_properties(
    Component_Utils_UseImported_SDK_DLL
    Component_Utils_UseImported_SDK_DLL_CONFIG
    Component_UtilsCpp_UseImported_SDK_DLL
    Component_UtilsCpp_UseImported_SDK_DLL_CONFIG
    PROPERTIES
        ENVIRONMENT_MODIFICATION "PATH=path_list_append:${EP_INSTALL_ROOT}/OpenCL-SDK-DLL/bin"
)
