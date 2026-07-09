cmake_minimum_required(VERSION 3.12)
project(juego_raylib LANGUAGES C CXX) # Habilitamos C y C++

# Forzar el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Definir dónde está Raylib (apuntando a tu carpeta local)
set(RAYLIB_PATH "/home/marc/Documentos/ProyectosMios/Raylib/raylib-gamejam/raylib" CACHE PATH "Path to raylib source directory")

if(DEFINED ENV{GITHUB_ACTIONS})
    # En GitHub Actions, le diremos que lo busque al mismo nivel (../raylib)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../raylib ${CMAKE_BINARY_DIR}/raylib)
else()
    # En tu Fedora local, sigue buscando en tu ruta absoluta externa de siempre
    add_subdirectory("/home/marc/Documentos/ProyectosMios/Raylib/raylib-gamejam/raylib" ${CMAKE_BINARY_DIR}/raylib)
endif()

# Definir nuestro ejecutable y sus archivos fuentes (.cpp)
add_executable(${PROJECT_NAME}
    src/raylib_game.cpp
        src/Shape.cpp
        src/Shape.hpp
        src/managers/GameManager.cpp
        src/managers/GameManager.hpp
        src/scenes/GameScene.cpp
        src/scenes/GameScene.hpp
        src/Shooter.cpp
        src/Shooter.hpp
        external/raygui.h
        src/scenes/Scene.hpp
        src/scenes/MenuScene.cpp
        src/scenes/MenuScene.hpp
        src/Button.cpp
        src/Button.hpp
        src/managers/SceneManager.hpp
        src/scenes/Sprite.cpp
        src/scenes/Sprite.hpp
        src/managers/GameUIManager.cpp
        src/managers/GameUIManager.hpp
)

# Definir que estamos en Escritorio (Para los #ifdef PLATFORM_DESKTOP)
target_compile_definitions(${PROJECT_NAME} PUBLIC PLATFORM_DESKTOP)

# Incluir la carpeta src para las cabeceras locales
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Enlazar con raylib y las librerías del sistema
target_link_libraries(${PROJECT_NAME} raylib)

# En Linux necesitamos enlazar librerías adicionales de gráficos/sistema
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} m pthread dl rt X11)
endif()

if(EMSCRIPTEN)
    # Forzamos a que el archivo de salida termine en .html en lugar de .js
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

    # Configuramos las opciones de enlazado correctas para Emscripten
    target_link_options(${PROJECT_NAME} PRIVATE 
        "--shell-file=${CMAKE_SOURCE_DIR}/src/minshell.html"
        "-sUSE_GLFW=3"
        "-sASYNCIFY"
    )
endif()

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/resources")

if(EXISTS ${ASSETS_DIR})
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${ASSETS_DIR}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
            COMMENT "Copiando assets al directorio de salida..."
    )
else()
    message(WARNING "¡Atención! No se encontró la carpeta de assets en: ${ASSETS_DIR}")
endif()
