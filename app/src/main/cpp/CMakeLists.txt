cmake_minimum_required(VERSION 3.22.1)
project(juego_raylib LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------------------
# 1. DEFINICIÓN DE RUTAS Y MÓDULOS (SIEMPRE PRIMERO)
# ------------------------------------------------------------------------------
set(RAYLIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/raylib")
set(RAYMOB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/raymob")

# Registrar módulos de CMake de Raylib inmediatamente
list(APPEND CMAKE_MODULE_PATH "${RAYLIB_DIR}/cmake")

# ------------------------------------------------------------------------------
# 2. DETECCIÓN DE PLATAFORMA Y GUARDIANES
# ------------------------------------------------------------------------------
if(ANDROID OR CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(ANDROID TRUE)
    set(PLATFORM "Android" CACHE STRING "Raylib platform target" FORCE)
elseif(EMSCRIPTEN)
    set(ANDROID OFF CACHE BOOL "" FORCE)
    set(PLATFORM "Web" CACHE STRING "Raylib platform target" FORCE)
else()
    set(PLATFORM "Desktop" CACHE STRING "Raylib platform target" FORCE)
endif()

# ------------------------------------------------------------------------------
# 3. OPCIONES Y FIXES DE RAYLIB
# ------------------------------------------------------------------------------
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(CUSTOMIZE_BUILD OFF CACHE BOOL "" FORCE)
set(INCLUDE_EVERYTHING OFF CACHE BOOL "" FORCE)
set(RAYLIB_INSTALL OFF CACHE BOOL "" FORCE)

# Forzar rutas internas para evitar fallos en InstallConfigurations.cmake
set(RAYLIB_SOURCE_DIR "${RAYLIB_DIR}")
set(CMAKE_CURRENT_BINARY_DIR_CONFIG "${CMAKE_CURRENT_BINARY_DIR}/deps/raylib")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/deps/raylib/raylib-config-version.cmake" "")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/deps/raylib/raylib-config.cmake" "")

# Añadir subdirectorio de Raylib
if(NOT TARGET raylib)
    add_subdirectory(${RAYLIB_DIR} ${CMAKE_BINARY_DIR}/raylib)
endif()

# ------------------------------------------------------------------------------
# 4. RECOPILACIÓN DE FUENTES Y CONFIGURACIÓN COMÚN
# ------------------------------------------------------------------------------
file(GLOB_RECURSE GAME_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)
list(FILTER GAME_SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/deps/.*")
list(FILTER GAME_SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-.*")
list(FILTER GAME_SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/build.*")

set(COMMON_INCLUDES
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/external"
        "${CMAKE_CURRENT_SOURCE_DIR}/managers"
        "${CMAKE_CURRENT_SOURCE_DIR}/scenes"
        "${RAYLIB_DIR}/src"
)

# Carpeta de assets compartida (estructura Gradle)
set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../assets")

# ------------------------------------------------------------------------------
# 5. TARGETS POR PLATAFORMA
# ------------------------------------------------------------------------------
if(ANDROID)
    # ==================== BUILD ANDROID ====================
    add_subdirectory(${RAYMOB_DIR} ${CMAKE_BINARY_DIR}/raymob)

    list(FILTER GAME_SOURCES EXCLUDE REGEX "raylib_game\\.cpp")

    set(GLUE_DIR "${RAYLIB_DIR}/projects/VS2019-Android/raylib_android/raylib_android.NativeActivity")
    list(APPEND GAME_SOURCES "${GLUE_DIR}/android_native_app_glue.c")

    add_library(app SHARED ${GAME_SOURCES}
            main.c
            ray_gui_impl.cpp
            Utils.cpp)

    target_compile_definitions(app PRIVATE PLATFORM_ANDROID)
    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        target_compile_definitions(app PRIVATE _DEBUG DEBUG)
    endif()

    target_include_directories(app PRIVATE
            ${COMMON_INCLUDES}
            "${GLUE_DIR}"
            "${RAYMOB_DIR}"
    )

    target_link_libraries(app PRIVATE raylib raymoblib log android EGL GLESv2 OpenSLES)

else()
    # ==================== BUILD DESKTOP / WEB ====================
    list(FILTER GAME_SOURCES EXCLUDE REGEX "main\\.c")

    add_executable(${PROJECT_NAME} ${GAME_SOURCES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${COMMON_INCLUDES})

    if(EMSCRIPTEN)
        # --- WEB (Emscripten) ---
        target_compile_definitions(${PROJECT_NAME} PUBLIC GRAPHICS_API_OPENGL_ES2)
        set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html" OUTPUT_NAME "index")

        target_link_options(${PROJECT_NAME} PRIVATE
                "--shell-file=${CMAKE_CURRENT_SOURCE_DIR}/minshell.html"
                "-sUSE_GLFW=3"
                "-sASYNCIFY"
                "--preload-file=${ASSETS_DIR}@/resources"
                "-sUSE_WEBGL2=1"
                "-sTOTAL_MEMORY=134217728"
                "-sSTACK_SIZE=1048576"
        )
        target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

    else()
        # --- DESKTOP (Linux / Windows / macOS) ---
        target_compile_definitions(${PROJECT_NAME} PUBLIC PLATFORM_DESKTOP)
        target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

        if(UNIX AND NOT APPLE)
            target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl rt X11)
        endif()

        if(EXISTS ${ASSETS_DIR})
            add_custom_command(
                    TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${ASSETS_DIR}
                    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
                    COMMENT "Copiando assets al directorio de salida..."
            )
        endif()
    endif()
endif()