#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

#define GLSL_VERSION 330


int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - raymarching shapes");

    Camera camera = { 0 };
    camera.position = (Vector3) { 2.5f, 2.5f, 3.0f };
    camera.target = (Vector3) { 0.0f, 0.0f, 0.7f };
    camera.up = (Vector3) { 0.0f, 1.0f, 0.0f };
    camera.fovy = 65.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    char *dir = RESOURCES_DIR;
    printf("dir: %s\n", dir);
    char *file = "/raymarching.fs";
    char *path = calloc(sizeof(char), strlen(dir) + strlen(file) + 1);
    strcpy(path, dir);
    strcat(path, file);
    printf("path: %s\n", path);
    Shader shader = LoadShader(0, path);
    free(path);

    int viewEyeLoc = GetShaderLocation(shader, "viewEye");
    int viewCenterLoc = GetShaderLocation(shader, "viewCenter");
    int runTimeLoc = GetShaderLocation(shader, "runTime");
    int resolutionLoc = GetShaderLocation(shader, "resolution");

    float resolution[2] = { (float)screenWidth, (float)screenHeight };
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    float runTime = 0.0f;

    DisableCursor();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        float cameraTarget[3] = { camera.target.x, camera.target.y, camera.target.z };

        float deltaTime = GetFrameTime();
        runTime += deltaTime;

        SetShaderValue(shader, viewEyeLoc, cameraPos, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, viewCenterLoc, cameraTarget, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, runTimeLoc, &runTime, SHADER_UNIFORM_FLOAT);

        if (IsWindowResized())
        {
            resolution[0] = (float)GetScreenWidth();
            resolution[1] = (float)GetScreenHeight();
            SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
        }

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginShaderMode(shader);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
        EndShaderMode();

        DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadShader(shader);

    CloseWindow();

    return 0;
}
