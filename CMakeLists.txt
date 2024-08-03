cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(InputsViewer VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
    src/IVEvent.cpp
    src/IVUtils.cpp
    src/json/serialize.cpp
    src/json/NodeTransform.cpp
    src/class/IVManager.cpp
    src/class/IVBackgroundSprite.cpp
    src/class/IVInputSprite.cpp
    src/class/IVPlayerInputNode.cpp
    src/class/IVSettingsLayer.cpp
    src/class/IVFloatSlider.cpp
    src/class/IVTransformSlider.cpp
    src/class/IVInputsViewLayer.cpp
    src/hooks/UILayer.cpp
    src/hooks/GJBaseGameLayer.cpp
    src/hooks/PlayLayer.cpp
    src/hooks/PauseLayer.cpp
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wimplicit-fallthrough
        -Werror
    )
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE
    src/macros.hpp
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

target_include_directories(${PROJECT_NAME} PRIVATE src/)

setup_geode_mod(${PROJECT_NAME})
