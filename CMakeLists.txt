cmake_minimum_required(VERSION 3.30)
project(Spirit_of_Fire)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4
)

FetchContent_MakeAvailable(glfw)

# glad
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG        master
)

FetchContent_MakeAvailable(glad)

# glm
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG        1.0.1
)

FetchContent_MakeAvailable(glm)

add_executable(${PROJECT_NAME} src/main.cpp
        src/shader_program.cpp
        src/shader_program.hpp
        src/utils/file_utils.hpp
        src/utils/file_utils.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad glm)

#if(WIN32)
#    target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
#endif()