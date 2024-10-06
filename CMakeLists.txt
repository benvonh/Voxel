cmake_minimum_required(VERSION 3.28)
project(Voxel)

set(CMAKE_CXX_STANDARD 20)

########################################################################################################################
# RAYLIB
########################################################################################################################
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

########################################################################################################################
# IMGUI
########################################################################################################################
set(IMGUI_VERSION v1.90.6-docking)
find_package(imgui QUIET)
if (NOT imgui_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            imgui
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/ocornut/imgui/archive/refs/tags/${IMGUI_VERSION}.tar.gz
    )
    FetchContent_Declare(
            rlimgui
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
            GIT_TAG main
    )
    FetchContent_GetProperties(imgui)
    FetchContent_MakeAvailable(rlimgui)
    if (NOT imgui_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(imgui)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_library(imgui STATIC
                ${imgui_SOURCE_DIR}/imgui.cpp
                ${imgui_SOURCE_DIR}/imgui_draw.cpp
                ${imgui_SOURCE_DIR}/imgui_tables.cpp
                ${imgui_SOURCE_DIR}/imgui_widgets.cpp
                ${rlimgui_SOURCE_DIR}/rlimgui.cpp
        )
        target_include_directories(imgui
                PRIVATE ${raylib_SOURCE_DIR}/src/
                PRIVATE ${rlimgui_SOURCE_DIR}
                PRIVATE ${imgui_SOURCE_DIR}
        )
    endif()
endif()

########################################################################################################################
add_executable(${PROJECT_NAME}
        main.cpp
        world.hpp
        block.hpp
        player.hpp
        rlights.hpp
)
target_link_libraries(${PROJECT_NAME}
        raylib
        imgui
)
target_include_directories(${PROJECT_NAME}
        PRIVATE ${raylib_SOURCE_DIR}/src/
        PRIVATE ${rlimgui_SOURCE_DIR}
        PRIVATE ${imgui_SOURCE_DIR}
)
include_directories(
        ${raylib_SOURCE_DIR}/src/
        ${rlimgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}
)