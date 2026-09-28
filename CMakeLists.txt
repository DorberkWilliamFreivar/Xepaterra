cmake_minimum_required(VERSION 3.15)

project(Xepaterra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB IMGUI_SOURCES 
    "lib/imgui-master/*.cpp"
    "lib/rlImGui-main/*.cpp"
)

file(GLOB_RECURSE APP_SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${APP_SOURCES} ${IMGUI_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    "C:/raylib/raylib/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui-master"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/rlImGui-main"
)

target_link_directories(${PROJECT_NAME} PRIVATE "C:/raylib/raylib/src")
target_link_libraries(${PROJECT_NAME} PRIVATE raylib opengl32 gdi32 winmm)