cmake_minimum_required (VERSION 3.8)

project ("battleship-game")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

IF (WIN32)
	set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.10/")
ENDIF()

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

IF (WIN32)
	add_executable (battleship-game WIN32 "./src/sdl2/main.cpp")
ELSE()
	add_executable (battleship-game "./src/sdl2/main.cpp")
ENDIF()

target_link_libraries(battleship-game ${SDL2_LIBRARY})
