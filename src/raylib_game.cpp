/*******************************************************************************************
*
*   raylib gamejam template
*
*   Code licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2026 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "GameScene.hpp"
#include "raymath.h"


#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>      // Emscripten library
#endif

#include <stdio.h>                          // Required for: printf()
#include <stdlib.h>                         // Required for: 
#include <string.h>                         // Required for:

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
// Simple log system to avoid printf() calls if required
// NOTE: Avoiding those calls, also avoids const strings memory usage
#define SUPPORT_LOG_INFO
#if defined(SUPPORT_LOG_INFO)
    #define LOG(...) printf(__VA_ARGS__)
#else
    #define LOG(...)
#endif

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum { 
    SCREEN_LOGO = 0, 
    SCREEN_TITLE, 
    SCREEN_GAMEPLAY, 
    SCREEN_ENDING
} GameScreen;

// TODO: Define your custom data types here

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static const int virtualWidth = 1920;
static const int virtualHeight = 1920;

static RenderTexture2D target{0};  // Render texture to render our game
static int frameCounter{0};

// TODO: Define global variables here, recommended to make them static

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
static void InitGame(GameScene* gameScene);            // Initialize game
static void UpdateDrawFrame(GameScene* gameScene);      // Update and Draw one frame

//----------------------------------------------------------------------------------
// Extra
//----------------------------------------------------------------------------------
float GetMin(float a, float b);
bool IsOutOfBounds(const Vector2& position, float radius = 0.0f);



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
#if !defined(_DEBUG)
    SetTraceLogLevel(LOG_NONE);         // Disable raylib trace log messages
#endif

    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(virtualWidth, virtualHeight, "raylib gamejam template");
    
    // TODO: Load resources / Initialize variables at this point
    auto gameScene = new GameScene{};
    InitGame(gameScene);

    // Render texture to draw, enables screen scaling
    // NOTE: If screen is scaled, mouse input should be scaled proportionally
    target = LoadRenderTexture(virtualWidth, virtualHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);



    //--------------------------------------------------------------------------------------

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop_arg(UpdateDrawFrame, gameScene, 60, 1);
#else
    SetTargetFPS(60);     // Set our game frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button
    {
        UpdateDrawFrame(gameScene);
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(target);
    
    // TODO: Unload all loaded resources at this point
    delete gameScene;

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//--------------------------------------------------------------------------------------------
// Module Functions Definition
//--------------------------------------------------------------------------------------------
// Init Game
void InitGame(GameScene* gameScene)
{
    gameScene->init();
}

// Update and draw frame
void UpdateDrawFrame(GameScene* gameScene)
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update variables / Implement example logic at this point
    float windowWidth = (float)GetScreenWidth();
    float windowHeight = (float)GetScreenHeight();

    // Calculamos cuánto debemos escalar manteniendo la relación de aspecto perfecta
    float scale = GetMin(windowWidth / virtualWidth, windowHeight / virtualHeight);
    Vector2 mouse = GetMousePosition();
    Vector2 virtualMouse = { (mouse.x - (windowWidth - virtualWidth * scale) * 0.5f) / scale, (mouse.y - (windowHeight - virtualHeight * scale) * 0.5f) / scale };

    gameScene->update(virtualMouse);

    frameCounter++;
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    // Render game screen to a texture, 
    // it could be useful for scaling or further shader postprocessing
    BeginTextureMode(target);
        ClearBackground(RAYWHITE);
        // TODO: Draw your game screen here

        gameScene->draw(virtualMouse);


        
    EndTextureMode();
    
    // Render to screen (main framebuffer)
    BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw render texture to screen, scaled if required
    DrawTexturePro(
        target.texture,
        (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height },
        (Rectangle){
            (windowWidth - ((float)virtualWidth * scale)) * 0.5f,
            (windowHeight - ((float)virtualHeight * scale)) * 0.5f,
            (float)virtualWidth * scale,
            (float)virtualHeight * scale
        },
        (Vector2){ 0, 0 },
        0.0f,
        WHITE
    );

        // TODO: Draw everything that requires to be drawn at this point, maybe UI?

    EndDrawing();
    //----------------------------------------------------------------------------------  
}

float GetMin(float a, float b) { return (a < b) ? a : b; }

bool IsOutOfBounds(const Vector2& position, float radius)
{
    if (position.x + radius < 0 || position.x - radius > 1920 ||
        position.y + radius < 0 || position.y - radius > 1920)
    {
        return true;
    }
    return false;
}