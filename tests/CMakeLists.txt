# Copyright (C) 2020 Jonathan Müller <jonathanmueller.dev@gmail.com>
# This file is subject to the license terms in the LICENSE file
# found in the top-level directory of this distribution.

# Fetch doctest.
include(FetchContent)
FetchContent_Declare(doctest GIT_REPOSITORY https://github.com/onqtam/doctest)
FetchContent_MakeAvailable(doctest)

# A generic test target.
add_library(lexy_test_base INTERFACE)
target_sources(lexy_test_base INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/doctest_main.cpp)
target_link_libraries(lexy_test_base INTERFACE foonathan::lexy::dev foonathan::lexy::file doctest)
target_compile_definitions(lexy_test_base INTERFACE DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING=1 LEXY_TEST)

# Add code coverage options to our test target.
if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU|Clang")
    if(NOT "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
        target_compile_options(lexy_test_base INTERFACE -O0 -g --coverage)
        target_link_options(lexy_test_base INTERFACE --coverage)
    endif()
endif()

# Add the individual tests.
add_subdirectory(lexy)
add_subdirectory(examples)

add_test(NAME unit_tests COMMAND lexy_test)
add_test(NAME email COMMAND lexy_test_email)
add_test(NAME json COMMAND lexy_test_json)
add_test(NAME shell COMMAND lexy_test_shell)
add_test(NAME xml COMMAND lexy_test_xml)

