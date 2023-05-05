cmake_minimum_required(VERSION 3.23)
set(project "MarioLite")
project(${project})

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


set(${project}_HEADERS
        src/tinyxml2.h
        src/GameComponent.h
        src/Collider.h
        src/StaticCollider.h
        src/Coin.h
        src/Brick.h
        src/Entity.h
        src/Player.h
        src/LevelData.h
        src/Game.h)


set(${project}_SOURCES
        src/GameComponent.cpp
        src/Entity.cpp
        src/Collider.cpp
        src/Player.cpp
        src/tinyxml2.cpp
        src/LevelData.cpp
        src/Game.cpp
        src/Main.cpp
)

set(${project}_SOURCE_LIST
        ${${project}_HEADERS}
        ${${project}_SOURCES})


add_executable(${project} ${${project}_SOURCE_LIST})


target_link_libraries(${project} PRIVATE sfml-graphics)
target_compile_features(${project} PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${project} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${project}> $<TARGET_FILE_DIR:${project}> COMMAND_EXPAND_LISTS)
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})


install(TARGETS ${PROJECT_NAME})