cmake_minimum_required(VERSION 3.15)
project(Template_SFML)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML-3.0.0/lib/cmake/SFML")
find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Window System)

# ImGui sources
set(IMGUI_SOURCES
    external/imgui/imgui.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES} "src/systems/TestSystem.h" "src/systems/TestSystem.cpp")
target_include_directories(imgui PUBLIC external/imgui)

# ImGui-SFML sources
set(IMGUI_SFML_SOURCES
    external/imgui-sfml/imgui-SFML.cpp
)

add_library(imgui-sfml STATIC ${IMGUI_SFML_SOURCES} "src/systems/TestSystem.h" "src/systems/TestSystem.cpp")
target_include_directories(imgui-sfml PUBLIC external/imgui-sfml external/imgui)
target_link_libraries(imgui-sfml PUBLIC imgui SFML::Graphics SFML::Window SFML::System)

# Executable
add_executable(${PROJECT_NAME} 
    src/main.cpp
 "src/systems/TestSystem.h" "src/systems/TestSystem.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE
    imgui-sfml          # Toujours linké
    SFML::Graphics
    SFML::Audio
    SFML::Window
    SFML::System
    opengl32.lib 
)

target_include_directories(${PROJECT_NAME} PRIVATE
    external/imgui
    external/imgui-sfml
)

# Active la macro DEBUG_MODE uniquement en Debug ou RelWithDebInfo
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_MODE)
endif()

# Liste des DLL Debug (avec suffix -d)
set(SFML_DLL_DIR "${CMAKE_SOURCE_DIR}/external/SFML-3.0.0/bin")

set(SFML_DLLS_DEBUG
    "${SFML_DLL_DIR}/sfml-graphics-d-3.dll"
    "${SFML_DLL_DIR}/sfml-window-d-3.dll"
    "${SFML_DLL_DIR}/sfml-audio-d-3.dll"
    "${SFML_DLL_DIR}/sfml-system-d-3.dll"
)

# Liste des DLL Release (sans suffix)
set(SFML_DLLS_RELEASE
    "${SFML_DLL_DIR}/sfml-graphics-3.dll"
    "${SFML_DLL_DIR}/sfml-window-3.dll"
    "${SFML_DLL_DIR}/sfml-audio-3.dll"
    "${SFML_DLL_DIR}/sfml-system-3.dll"
)

# Copier les DLL selon la configuration active
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    foreach(dll ${SFML_DLLS_DEBUG})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${dll}"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endforeach()
else() # Release ou autres configurations
    foreach(dll ${SFML_DLLS_RELEASE})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${dll}"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endforeach()
endif()

# Copie les assets après le build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)