cmake_minimum_required(VERSION 3.21)
project(2DSurvival)
set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(libs/sfml)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Game.cpp src/include/Game.h
        src/State.cpp src/include/State.h
        src/GameState.cpp src/include/GameState.h
        src/Entity.cpp src/include/Entity.h
        src/MainMenuState.cpp src/include/MainMenuState.h
        src/Button.cpp src/include/Button.h
        src/Player.cpp src/include/Player.h
        src/MovementComponent.cpp src/include/MovementComponent.h
        src/AnimationComponent.cpp src/include/AnimationComponent.h
        src/HitboxComponent.cpp src/include/HitboxComponent.h
        src/include/Collision.h
        src/Tile.cpp src/include/Tile.h
        src/TileMap.cpp src/include/TileMap.h
        libs/noise/SimplexNoise.cpp libs/noise/SimplexNoise.h
        src/PauseMenu.cpp src/include/PauseMenu.h libs/threadpool/thread_pool.h)

target_link_libraries(${PROJECT_NAME} sfml-window)
target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} sfml-network)
target_link_libraries(${PROJECT_NAME} sfml-audio)

if (WIN32)
    file(GLOB MINGW_DEP_DLLS "C:/msys64/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()