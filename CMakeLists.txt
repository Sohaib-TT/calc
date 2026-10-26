cmake_minimum_required(VERSION 3.21)
project(my_application LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Debug)
foreach(OUTPUT_CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUT_CONFIG} CONFIG_SUFFIX)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_SUFFIX} ${CMAKE_BINARY_DIR}/bin/${OUTPUT_CONFIG})
endforeach()

find_package(Slint QUIET)
if (NOT Slint_FOUND)
  message("Slint could not be located in the CMake module search path. Downloading it from Git and building it locally")
  include(FetchContent)
  FetchContent_Declare(
    Slint
    GIT_REPOSITORY https://github.com/slint-ui/slint.git
    # `release/1` will auto-upgrade to the latest Slint >= 1.0.0 and < 2.0.0
    # `release/1.0` will auto-upgrade to the latest Slint >= 1.0.0 and < 1.1.0
    GIT_TAG release/1
    SOURCE_SUBDIR api/cpp
  )
  FetchContent_MakeAvailable(Slint)
endif (NOT Slint_FOUND)

if(ANDROID)
    add_library(my_application SHARED src/main.cpp)
else()
    add_executable(my_application src/main.cpp)
endif()
target_link_libraries(my_application PRIVATE Slint::Slint)
slint_target_sources(my_application ui/app-window.slint)
# On Windows, copy the Slint DLL next to the application binary so that it's found.
if (WIN32)
    add_custom_command(TARGET my_application POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:my_application> $<TARGET_FILE_DIR:my_application> COMMAND_EXPAND_LISTS)
endif()

# Copies calc/ui/icons/ into build/bin/Debug/icons/
file(COPY ${CMAKE_SOURCE_DIR}/icons DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(my_application PROPERTIES SLINT_EMBED_RESOURCES embed-files)