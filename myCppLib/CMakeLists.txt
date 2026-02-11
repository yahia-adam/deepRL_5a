cmake_minimum_required(VERSION 3.31.6)

set(CMAKE_CUDA_COMPILER "/usr/local/cuda/bin/nvcc")
project(myCppLib LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# PyTorch
set(CMAKE_PREFIX_PATH "/usr/local/lib/libtorch")
find_package(Torch REQUIRED)

# GLFW + OpenGL
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui)

include_directories(include)

add_executable(myCppLib main.cpp
        src/algos/DeepQLearning.cpp
        src/env/BaseEnv.cpp
        src/env/QuartoEnv.cpp
        include/QuartoEnv.h

        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        src/env/ui/calculatrice.cpp
        src/env/ui/QuartoUi.cpp
)

target_include_directories(myCppLib PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${TORCH_INCLUDE_DIRS}
        include
)

target_link_libraries(myCppLib
        ${TORCH_LIBRARIES}
        glfw
        OpenGL::GL
        ${CMAKE_DL_LIBS}
)

set_property(TARGET myCppLib PROPERTY CUDA_RESOLVE_DEVICE_SYMBOLS ON)