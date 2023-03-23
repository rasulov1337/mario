cmake_minimum_required(VERSION 3.23)
set(PROJECT_NAME "MarioLite")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(${project}_SOURCES
        src/Main.cpp
        src/Source/Player.cpp)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${PROJECT_NAME} ${${project}_SOURCE_LIST})


target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS ${PROJECT_NAME})