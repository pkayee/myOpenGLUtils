cmake_minimum_required(VERSION 4.1)
project(OpenGl1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

# GLAD static library
add_library(glad STATIC
        external/glad/src/glad.c
        src/Buffers/VBO.h
        "src/Buffers/EBO.cpp"
        "src/Buffers/VBO.cpp"
        "src/Buffers/VAO.cpp"
        src/Headers/FindDirs.h
)

add_library(ImGui STATIC
        "external/imgui/imgui.cpp"
        "external/imgui/imgui_draw.cpp"
        "external/imgui/imgui_widgets.cpp"
        "external/imgui/imgui_tables.cpp"
        "external/imgui/backends/imgui_impl_glfw.cpp" # Example backend (adjust as needed)
        "external/imgui/backends/imgui_impl_opengl3.cpp" # Example backend (adjust as needed)
)
target_include_directories(glad
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
)

target_include_directories(ImGui PUBLIC
        "external/imgui"
        "external/imgui/backends"
)
# Your executable
add_executable(OpenGl1 src/main.cpp
        src/Headers/Shaders.h
        src/shaderClass.cpp
        src/Buffers/EBO.h
        src/Buffers/VAO.h
        external/imgui/backends/imgui_impl_glfw.cpp
        src/Headers/shapes.h

)

# Give main.cpp direct access to GLAD headers (safety net + fixes intellisense)
target_include_directories(OpenGl1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include
)

target_link_libraries(OpenGl1 PRIVATE
        glad
        glfw
        glm
        ImGui
)

# Platform-specific libraries
if(WIN32)
    target_link_libraries(OpenGl1 PRIVATE opengl32)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(OpenGl1 PRIVATE X11 pthread dl)
elseif(APPLE)
    target_link_libraries(OpenGl1 PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()




