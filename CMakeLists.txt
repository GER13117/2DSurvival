cmake_minimum_required(VERSION 3.17)
project(2DSurvival)
set(CMAKE_CXX_STANDARD 20)
add_executable(2DSurvival src/main.cpp src/Game.cpp src/include/Game.h src/State.cpp src/include/State.h src/GameState.cpp src/include/GameState.h src/Entity.cpp src/include/Entity.h src/MainMenuState.cpp src/include/MainMenuState.h src/Button.cpp src/include/Button.h src/Player.cpp src/include/Player.h src/MovementComponent.cpp src/include/MovementComponent.h src/AnimationComponent.cpp src/include/AnimationComponent.h)
include_directories(headers /usr/local/include C:/SFML/include)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIRS})
    target_link_libraries(2DSurvival ${SFML_LIBRARIES})
endif ()


# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()