cmake_minimum_required (VERSION 3.8)

project ("battleship-game")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

IF (WIN32)
	set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.10/;${PROJECT_SOURCE_DIR}/lib/SDL2_ttf-2.0.15/")
ENDIF()

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

#add_executable (battleship-game-original "./src/original/main.cpp")

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
message("src: ${SRC_FILES}")

set(BATTLESHIP_GAME_SDL_BIN "battleship-game-sdl")
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIRS})
IF (WIN32)
    add_executable (${BATTLESHIP_GAME_SDL_BIN} "./src/sdl2/main.cpp;${SRC_FILES}" )
ELSE()
    add_executable (${BATTLESHIP_GAME_SDL_BIN} "./src/sdl2/main.cpp;${SRC_FILES}")
ENDIF()
target_link_libraries(${BATTLESHIP_GAME_SDL_BIN} ${SDL2_LIBRARY} ${SDL2_SDLMAIN_LIBRARY} ${SDL2_TTF_LIBRARIES})

# Copy SDL2 DLLs to output folder on Windows
if(WIN32)
    set(SDL2_DLLS "${SDL2_RUNTIME_LIBRARY};${SDL2_TTF_RUNTIME_LIBRARY};${SDL2_TTF_LIBFREETYPE_RUNTIME_LIBRARY};${SDL2_TTF_ZLIB1_RUNTIME_LIBRARY}")
    foreach(DLL ${SDL2_DLLS})
        add_custom_command(TARGET ${BATTLESHIP_GAME_SDL_BIN} POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${DLL} ${CMAKE_BINARY_DIR})
    endforeach()
endif()

set(ASSETS_DIR "${PROJECT_SOURCE_DIR}/assets/")

add_custom_command(TARGET ${BATTLESHIP_GAME_SDL_BIN} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/assets/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${CMAKE_BINARY_DIR}/assets/
)
