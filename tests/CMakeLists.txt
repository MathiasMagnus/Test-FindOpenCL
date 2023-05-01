set_directory_properties(PROPERTIES EP_BASE "${PROJECT_BINARY_DIR}/tests")

set(EP_BUILD_ROOT "${PROJECT_BINARY_DIR}/tests/Build")

set(OpenCL-Headers_CMAKE_PREFIX_PATH
    "-DCMAKE_PREFIX_PATH:PATH=${EP_INSTALL_ROOT}/OpenCL-Headers"
)
set(OpenCL-Headers-ICD-Loader_CMAKE_PREFIX_PATH
    "-DCMAKE_PREFIX_PATH:PATH=${EP_INSTALL_ROOT}/OpenCL-Headers;${EP_INSTALL_ROOT}/OpenCL-ICD-Loader"
)
set(OpenCL-Headers-ICD-Loader-CLHPP_CMAKE_PREFIX_PATH
    "-DCMAKE_PREFIX_PATH:PATH=${EP_INSTALL_ROOT}/OpenCL-Headers;${EP_INSTALL_ROOT}/OpenCL-ICD-Loader;${EP_INSTALL_ROOT}/OpenCL-CLHPP"
)
set(OpenCL-SDK_CMAKE_PREFIX_PATH
    "-DCMAKE_PREFIX_PATH:PATH=${EP_INSTALL_ROOT}/OpenCL-SDK"
)
set(OpenCL-SDK-DLL_CMAKE_PREFIX_PATH
    "-DCMAKE_PREFIX_PATH:PATH=${EP_INSTALL_ROOT}/OpenCL-SDK-DLL"
)

# Pre-CMake 3.8 style. SDK doesn't expose legacy variables
ExternalProject_Add(NoComponent_UseVariables_Separate
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/NoComponent/UseVariables"
    CMAKE_CACHE_ARGS ${OpenCL-Headers-ICD-Loader_CMAKE_PREFIX_PATH} # NOTE: both needed, even if only one is used
    DEPENDS          "OpenCL-Headers;OpenCL-ICD-Loader"             # NOTE: both needed, even if only one is used
)
add_test(
    NAME NoComponent_UseVariables_Separate
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/NoComponent_UseVariables_Separate" --build-config $<CONFIG>
)

# CMake 3.8+ style. SDK exposes usual OpenCL::OpenCL in backward compatible manner
ExternalProject_Add(NoComponent_UseImported_Separate
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/NoComponent/UseImported"
    CMAKE_CACHE_ARGS ${OpenCL-Headers-ICD-Loader_CMAKE_PREFIX_PATH}
    DEPENDS          "OpenCL-Headers;OpenCL-ICD-Loader"
)
add_test(
    NAME NoComponent_UseImported_Separate
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/NoComponent_UseImported_Separate" --build-config $<CONFIG>
)
ExternalProject_Add(NoComponent_UseImported_SDK
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/NoComponent/UseImported"
    CMAKE_CACHE_ARGS ${OpenCL-SDK_CMAKE_PREFIX_PATH}
    DEPENDS          "OpenCL-SDK"
)
add_test(
    NAME NoComponent_UseImported_SDK
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/NoComponent_UseImported_SDK" --build-config $<CONFIG>
)
ExternalProject_Add(NoComponent_UseImported_SDK_CONFIG
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/NoComponent/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON;${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          "OpenCL-SDK"
)
add_test(
    NAME NoComponent_UseImported_SDK_CONFIG
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/NoComponent_UseImported_SDK_CONFIG" --build-config $<CONFIG>
)

# SDK or CMake 3.27+ style.
ExternalProject_Add(Component_HeadersOnly_UseVariables_Separate
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/HeadersOnly/UseVariables"
    CMAKE_CACHE_ARGS ${OpenCL-Headers_CMAKE_PREFIX_PATH} # NOTE: works, but don't know who uses bleeding edge CMake
    DEPENDS          "OpenCL-Headers"                    #       yet still uses the legacy variables
)
add_test(
    NAME Component_HeadersOnly_UseVariables_Separate
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_HeadersOnly_UseVariables_Separate" --build-config $<CONFIG>
)
ExternalProject_Add(Component_HeadersOnly_UseImported_Separate
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/HeadersOnly/UseImported"
    CMAKE_CACHE_ARGS ${OpenCL-Headers_CMAKE_PREFIX_PATH} # NOTE: with components, for headers-only, no ICD needed
    DEPENDS          "OpenCL-Headers"                    # NOTE: with components, for headers-only, no ICD needed
)
add_test(
    NAME Component_HeadersOnly_UseImported_Separate
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_HeadersOnly_UseImported_Separate" --build-config $<CONFIG>
)
ExternalProject_Add(Component_HeadersOnly_UseImported_SDK
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/HeadersOnly/UseImported"
    CMAKE_CACHE_ARGS ${OpenCL-SDK_CMAKE_PREFIX_PATH}
    DEPENDS          "OpenCL-SDK"
)
add_test(
    NAME Component_HeadersOnly_UseImported_SDK
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_HeadersOnly_UseImported_SDK" --build-config $<CONFIG>
)
ExternalProject_Add(Component_HeadersOnly_UseImported_SDK_CONFIG
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/HeadersOnly/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON;${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          "OpenCL-SDK"
)
add_test(
    NAME Component_HeadersOnly_UseImported_SDK_CONFIG
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_HeadersOnly_UseImported_SDK_CONFIG" --build-config $<CONFIG>
)

ExternalProject_Add(Component_HeadersLoader_UseVariables_Separate
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/HeadersLoader/UseVariables"
    CMAKE_CACHE_ARGS ${OpenCL-Headers-ICD-Loader_CMAKE_PREFIX_PATH}
    DEPENDS          "OpenCL-Headers;OpenCL-ICD-Loader"
)
add_test(
    NAME Component_HeadersLoader_UseVariables_Separate
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_HeadersLoader_UseVariables_Separate" --build-config $<CONFIG>
)
ExternalProject_Add(Component_HeadersLoader_UseImported_Separate
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/HeadersLoader/UseImported"
    CMAKE_CACHE_ARGS ${OpenCL-Headers-ICD-Loader_CMAKE_PREFIX_PATH}
    DEPENDS          "OpenCL-Headers;OpenCL-ICD-Loader"
)
add_test(
    NAME Component_HeadersLoader_UseImported_Separate
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_HeadersLoader_UseImported_Separate" --build-config $<CONFIG>
)
ExternalProject_Add(Component_HeadersLoader_UseImported_SDK
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/HeadersLoader/UseImported"
    CMAKE_CACHE_ARGS ${OpenCL-SDK_CMAKE_PREFIX_PATH}
    DEPENDS          "OpenCL-SDK"
)
add_test(
    NAME Component_HeadersLoader_UseImported_SDK
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_HeadersLoader_UseImported_SDK" --build-config $<CONFIG>
)
ExternalProject_Add(Component_HeadersLoader_UseImported_SDK_CONFIG
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/HeadersLoader/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON;${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          "OpenCL-SDK"
)
add_test(
    NAME Component_HeadersLoader_UseImported_SDK_CONFIG
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_HeadersLoader_UseImported_SDK_CONFIG" --build-config $<CONFIG>
)

# Component_HeadersCppLoader_UseVariables_Separate doesn't exist, because C++ headers don't have a variable
# nor was it ever checked for. Users got the C++ headers "by chance". An SDK either shipped them or not.
# The system either had the opencl-clhpp-headers installed while detecting or not.
ExternalProject_Add(Component_HeadersCppLoader_UseImported_Separate
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/HeadersCppLoader/UseImported"
    CMAKE_CACHE_ARGS ${OpenCL-Headers-ICD-Loader-CLHPP_CMAKE_PREFIX_PATH}
    DEPENDS          "OpenCL-Headers;OpenCL-ICD-Loader;OpenCL-CLHPP"
)
add_test(
    NAME Component_HeadersCppLoader_UseImported_Separate
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_HeadersCppLoader_UseImported_Separate" --build-config $<CONFIG>
)
ExternalProject_Add(Component_HeadersCppLoader_UseImported_SDK
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/HeadersCppLoader/UseImported"
    CMAKE_CACHE_ARGS ${OpenCL-SDK_CMAKE_PREFIX_PATH}
    DEPENDS          "OpenCL-SDK"
)
add_test(
    NAME Component_HeadersCppLoader_UseImported_SDK
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_HeadersCppLoader_UseImported_SDK" --build-config $<CONFIG>
)
ExternalProject_Add(Component_HeadersCppLoader_UseImported_SDK_CONFIG
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/HeadersCppLoader/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON;${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          "OpenCL-SDK"
)
add_test(
    NAME Component_HeadersCppLoader_UseImported_SDK_CONFIG
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_HeadersCppLoader_UseImported_SDK_CONFIG" --build-config $<CONFIG>
)

# The utility libraries are part of the SDK, so they can't be built separately
ExternalProject_Add(Component_Utils_UseImported_SDK
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/Utils/UseImported"
    CMAKE_CACHE_ARGS ${OpenCL-SDK_CMAKE_PREFIX_PATH}
    DEPENDS          "OpenCL-SDK"
)
add_test(
    NAME Component_Utils_UseImported_SDK
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_Utils_UseImported_SDK" --build-config $<CONFIG>
)
ExternalProject_Add(Component_Utils_UseImported_SDK_CONFIG
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/Utils/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON;${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          "OpenCL-SDK"
)
add_test(
    NAME Component_Utils_UseImported_SDK_CONFIG
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_Utils_UseImported_SDK_CONFIG" --build-config $<CONFIG>
)
ExternalProject_Add(Component_UtilsCpp_UseImported_SDK
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/UtilsCpp/UseImported"
    CMAKE_CACHE_ARGS ${OpenCL-SDK_CMAKE_PREFIX_PATH}
    DEPENDS          "OpenCL-SDK"
)
add_test(
    NAME Component_UtilsCpp_UseImported_SDK
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_UtilsCpp_UseImported_SDK" --build-config $<CONFIG>
)
ExternalProject_Add(Component_UtilsCpp_UseImported_SDK_CONFIG
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/UtilsCpp/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON;${OpenCL-SDK_CMAKE_PREFIX_PATH}"
    DEPENDS          "OpenCL-SDK"
)
add_test(
    NAME Component_UtilsCpp_UseImported_SDK_CONFIG
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_UtilsCpp_UseImported_SDK_CONFIG" --build-config $<CONFIG>
)

# Check the utility libraries when built as .so/.dll
ExternalProject_Add(Component_Utils_UseImported_SDK_DLL
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/Utils/UseImported"
    CMAKE_CACHE_ARGS ${OpenCL-SDK-DLL_CMAKE_PREFIX_PATH}
    DEPENDS          "OpenCL-SDK-DLL"
)
add_test(
    NAME Component_Utils_UseImported_SDK_DLL
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_Utils_UseImported_SDK_DLL" --build-config $<CONFIG>
)
ExternalProject_Add(Component_Utils_UseImported_SDK_DLL_CONFIG
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/Utils/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON;${OpenCL-SDK-DLL_CMAKE_PREFIX_PATH}"
    DEPENDS          "OpenCL-SDK-DLL"
)
add_test(
    NAME Component_Utils_UseImported_SDK_DLL_CONFIG
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_Utils_UseImported_SDK_DLL_CONFIG" --build-config $<CONFIG>
)
ExternalProject_Add(Component_UtilsCpp_UseImported_SDK_DLL
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/UtilsCpp/UseImported"
    CMAKE_CACHE_ARGS ${OpenCL-SDK-DLL_CMAKE_PREFIX_PATH}
    DEPENDS          "OpenCL-SDK-DLL"
)
add_test(
    NAME Component_UtilsCpp_UseImported_SDK_DLL
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_UtilsCpp_UseImported_SDK_DLL" --build-config $<CONFIG>
)
ExternalProject_Add(Component_UtilsCpp_UseImported_SDK_DLL_CONFIG
    SOURCE_DIR       "${PROJECT_SOURCE_DIR}/tests/Component/UtilsCpp/UseImported"
    CMAKE_CACHE_ARGS "-DCMAKE_FIND_PACKAGE_PREFER_CONFIG:BOOL=ON;${OpenCL-SDK-DLL_CMAKE_PREFIX_PATH}"
    DEPENDS          "OpenCL-SDK-DLL"
)
add_test(
    NAME Component_UtilsCpp_UseImported_SDK_DLL_CONFIG
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${EP_BUILD_ROOT}/Component_UtilsCpp_UseImported_SDK_DLL_CONFIG" --build-config $<CONFIG>
)
set_tests_properties(
    Component_Utils_UseImported_SDK_DLL
    Component_Utils_UseImported_SDK_DLL_CONFIG
    Component_UtilsCpp_UseImported_SDK_DLL
    Component_UtilsCpp_UseImported_SDK_DLL_CONFIG
    PROPERTIES
        ENVIRONMENT_MODIFICATION "PATH=path_list_append:${EP_INSTALL_ROOT}/OpenCL-SDK-DLL/bin"
)
