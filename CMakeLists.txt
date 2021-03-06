cmake_minimum_required(VERSION 3.2)

set(BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})
if (NOT BUILD_NUMBER)
    set(BUILD_NUMBER $ENV{APPVEYOR_BUILD_NUMBER})
    if (NOT BUILD_NUMBER)
        # use zero for local builds.
        set(BUILD_NUMBER 0)
    endif()
endif()

project(MellowPlayer VERSION 3.0.0.${BUILD_NUMBER})
set(MELLOWPLAYER_VERSION "${MellowPlayer_VERSION}" CACHE STRING "")
add_definitions(-DMELLOWPLAYER_VERSION="${MellowPlayer_VERSION}")
add_definitions(-DMELLOWPLAYER_VERSION_MAJOR="${MellowPlayer_VERSION_MAJOR}")
add_definitions(-DMELLOWPLAYER_VERSION_MINOR="${MellowPlayer_VERSION_MINOR}")
add_definitions(-DMELLOWPLAYER_VERSION_PATCH="${MellowPlayer_VERSION_PATCH}")
add_definitions(-DMELLOWPLAYER_VERSION_TWEAK="${MellowPlayer_VERSION_TWEAK}")
add_definitions(-DCMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

include(scripts/cmake/Macros.cmake)
include(scripts/cmake/Config.cmake)
include(scripts/cmake/InstallDirs.cmake)

# Options
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)
set_option(BUILD_TESTS OFF BOOL "TRUE to build the tests, FALSE to ignore them.")
set_option(BUILD_INTEGRATION_TESTS OFF BOOL "TRUE to build the integration tests, FALSE to ignore them.")
set_option(ENABLE_COVERAGE OFF BOOL "True to build code coverage targerts")
set_option(ENABLE_LCOV_REPORT OFF BOOL "True to enable lcov coverage report. Default is False.")
set_option(STATIC_LIBSTDCPP OFF BOOL "True to link statically with libstdc++ and libgcc")
set_option(UPDATE_TRANSLATIONS OFF BOOL "True to update translations")
set_option(DEFAULT_THEME "Adaptive" STRING "The default theme (available: Default, Midna, MidnaDark, Breeze, BreezeDark, Deezer, Spotify,...)")

if (UNIX AND NOT APPLE)
    set(USE_LIBNOTIFY TRUE)
endif()

include(scripts/cmake/FindDependencies.cmake)

include_directories(lib)
# Sources
if(ENABLE_COVERAGE)
    include(scripts/cmake/CodeCoverage.cmake)
endif()
add_subdirectory(lib/MellowPlayer)
add_subdirectory(src)
if(BUILD_TESTS)
    enable_testing(true)
    add_subdirectory(tests)
endif()

install(DIRECTORY plugins DESTINATION ${CMAKE_INSTALL_DATADIR}/mellowplayer)
install(DIRECTORY share/applications DESTINATION ${CMAKE_INSTALL_DATADIR})
install(DIRECTORY share/icons DESTINATION ${CMAKE_INSTALL_DATADIR})

# Summary
message(STATUS "Building MellowPlayer v${MellowPlayer_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Default theme: ${DEFAULT_THEME}")
message(STATUS "Build tests: ${BUILD_TESTS}")
if (BUILD_TESTS)
    if (BUILD_INTEGRATION_TESTS)
        message("    [x] Integrations Tests")
    else()
        message("    [ ] Integrations Tests")
    endif()
    if (ENABLE_COVERAGE AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        message("    [x] Code Coverage")
    else()
        message("    [ ] Code Coverage")
    endif()
    if (ENABLE_COVERAGE AND ENABLE_LCOV_REPORT AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        message("    [x] LCOV Code Coverage Report")
    else()
        message("    [ ] LCOV Code Coverage Report")
    endif()
endif()