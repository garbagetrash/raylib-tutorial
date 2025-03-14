#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"


void get_path(const char* filename, char* pathname)
{
    char *dir = RESOURCES_DIR;
    printf("dir: %s\n", dir);
    strcpy(pathname, dir);
    strcat(pathname, filename);
    printf("path: %s\n", pathname);
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - background scrolling");

    char* path = (char*)calloc(sizeof(char), 512);
    get_path("/cyberpunk_street_background.png", path);
    Texture2D background = LoadTexture(path);
    get_path("/cyberpunk_street_midground.png", path);
    Texture2D midground = LoadTexture(path);
    get_path("/cyberpunk_street_foreground.png", path);
    Texture2D foreground = LoadTexture(path);
    free(path);

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        scrollingBack -= 0.1f;
        scrollingMid -= 0.5f;
        scrollingFore -= 1.0f;

        if (scrollingBack <= -background.width * 2) scrollingBack = 0;
        if (scrollingMid <= -midground.width * 2) scrollingMid = 0;
        if (scrollingFore <= -foreground.width * 2) scrollingFore = 0;

        // Draw
        BeginDrawing();

        ClearBackground(GetColor(0x052c46ff));

        DrawTextureEx(background, (Vector2) { scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background, (Vector2) { background.width * 2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);

        DrawTextureEx(midground, (Vector2) { scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(midground, (Vector2) { midground.width * 2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);

        DrawTextureEx(foreground, (Vector2) { scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(foreground, (Vector2) { foreground.width * 2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);

        DrawText("BACKGROUND SCROLLING & PARALLAX", 10, 10, 20, RED);

        DrawFPS(700, 10);

        EndDrawing();
    }

    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);

    CloseWindow();

    return 0;
}
