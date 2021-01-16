# Copyright (c) Microsoft Corporation. All rights reserved.
# SPDX-License-Identifier: MIT

cmake_minimum_required (VERSION 3.13)
project(azure-security-keyvault-common LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake-modules")

include(az_vcpkg)
include(az_version)
include(CodeCoverage)
include(DefineTransportAdapter)
include(doxygen_common)
include(global_compile_options)

az_vcpkg_integrate()

if(NOT AZ_ALL_LIBRARIES)
  find_package(azure-core-cpp CONFIG QUIET)
  if(NOT azure-core-cpp_FOUND)
    find_package(azure-core-cpp REQUIRED)
  endif()
endif()

set(
  AZURE_KEYVAULT_COMMON_HEADER
    inc/azure/keyvault/common/keyvault_constants.hpp
    inc/azure/keyvault/common/keyvault_exception.hpp
    inc/azure/keyvault/common/keyvault_pipeline.hpp
    inc/azure/keyvault/common/version.hpp
)

set(
  AZURE_KEYVAULT_COMMON_SOURCE
    src/keyvault_exception.cpp
    src/keyvault_pipeline.cpp
)

add_library(
    azure-security-keyvault-common
    ${AZURE_KEYVAULT_COMMON_HEADER} ${AZURE_KEYVAULT_COMMON_SOURCE}
)
add_library(Azure::keyvault::common ALIAS azure-security-keyvault-common)

target_include_directories(
    azure-security-keyvault-common
      PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:include/azure-security-keyvault-common>
        ${azure-core-cpp_INCLUDE_DIRS}
)

target_link_libraries(azure-security-keyvault-common PUBLIC Azure::azure-core)

# coverage. Has no effect if BUILD_CODE_COVERAGE is OFF
create_code_coverage(keyvault azure-security-keyvault-common azure-security-keyvault-common-test)

get_az_version("${CMAKE_CURRENT_SOURCE_DIR}/inc/azure/keyvault/common/version.hpp")
generate_documentation(azure-security-keyvault-common ${AZ_LIBRARY_VERSION})

if(BUILD_TESTING)
    # tests
    add_subdirectory(test)
endif()

az_vcpkg_export(azure-security-keyvault-common)