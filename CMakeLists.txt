cmake_minimum_required (VERSION 3.8)

project ("battleship-game")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

IF (WIN32)
	set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.10/")
ENDIF()

find_package(SDL2 REQUIRED)

#add_executable (battleship-game-original "./src/original/main.cpp")

set(BATTLESHIP_GAME_SDL_BIN "battleship-game-sdl")
include_directories(${SDL2_INCLUDE_DIR})
IF (WIN32)
    add_executable (${BATTLESHIP_GAME_SDL_BIN} "./src/sdl2/main.cpp")
ELSE()
    add_executable (${BATTLESHIP_GAME_SDL_BIN} "./src/sdl2/main.cpp")
ENDIF()
target_link_libraries(${BATTLESHIP_GAME_SDL_BIN} ${SDL2_LIBRARY} ${SDL2_SDLMAIN_LIBRARY})

# Copy SDL2 DLLs to output folder on Windows
if(WIN32)
    set(SDL2_DLLS "${SDL2_RUNTIME_LIBRARY}")
    foreach(DLL ${SDL2_DLLS})
        add_custom_command(TARGET ${BATTLESHIP_GAME_SDL_BIN} POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${DLL} ${CMAKE_BINARY_DIR})
    endforeach()
endif()
