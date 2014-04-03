cmake_minimum_required(VERSION 2.6)
project(flip-four)

if (NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

if (NOT SFML_INCLUDE_PATH)
set(SFML_INCLUDE_PATH /usr/include CACHE PATH "Location of SFML's include folder")
endif()
if (NOT SFML_LIBRARY_PATH)
set(SFML_LIBRARY_PATH /usr/lib CACHE PATH "Location of SFML's lib folder")
endif()
if (NOT SFML_UI_INCLUDE_PATH)
set(SFML_UI_INCLUDE_PATH /usr/include CACHE PATH "Location of SFML UI's include folder")
endif()
if (NOT SFML_UI_LIBRARY_PATH)
set(SFML_UI_LIBRARY_PATH /usr/lib CACHE PATH "Location of SFML UI's lib folder")
endif()

include_directories(${SFML_INCLUDE_PATH})
include_directories(${SFML_UI_INCLUDE_PATH})
link_directories(${SFML_LIBRARY_PATH})
link_directories(${SFML_UI_LIBRARY_PATH})

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(EXECUTABLE flip-four)

file(
GLOB_RECURSE
sources
src/*
)

add_executable(
${EXECUTABLE}
${sources}
)

target_link_libraries(
${EXECUTABLE}
sfml-ui
sfml-graphics
sfml-window
sfml-system
)
