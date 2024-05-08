cmake_minimum_required (VERSION 3.8)

add_executable (VersorStudio "main.cpp" "UseImGui.cpp" "UseImGui.h"
        "Versor.cpp"
        "Versor.h")

link_directories(VersorStudio/)

find_package(glad CONFIG REQUIRED)
target_link_libraries(VersorStudio PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(VersorStudio PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(VersorStudio PRIVATE imgui::imgui)