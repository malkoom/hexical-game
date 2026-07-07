cmake_minimum_required(VERSION 3.12)
project(juego_raylib LANGUAGES C CXX) # Habilitamos C y C++

# Forzar el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Definir dónde está Raylib (apuntando a tu carpeta local)
set(RAYLIB_PATH "~/Documentos/ProyectosMios/Raylib/raylib-gamejam/raylib" CACHE PATH "Path to raylib source directory")

# Incluir subdirectorio de raylib para que CMake lo compile automáticamente
add_subdirectory(${RAYLIB_PATH} ${CMAKE_BINARY_DIR}/raylib)

# Definir nuestro ejecutable y sus archivos fuentes (.cpp)
add_executable(${PROJECT_NAME}
    src/raylib_game.cpp
        src/Player.cpp
        src/Player.hpp
        src/Shape.cpp
        src/Shape.hpp
        src/Bullet.cpp
        src/Bullet.hpp
        src/GameManager.cpp
        src/GameManager.hpp
        src/GameScene.cpp
        src/GameScene.hpp
        src/BulletPool.cpp
        src/BulletPool.hpp
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
