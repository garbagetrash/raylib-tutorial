#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"


int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [models] example - heightmap loading and drawing");

    Camera3D camera = { 0 };
    camera.position = (Vector3) { 18.0f, 21.0f, 18.0f };
    camera.target = (Vector3) { 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3) { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    char *dir = RESOURCES_DIR;
    printf("dir: %s\n", dir);
    char *file = "/heightmap.png";
    char *path = calloc(sizeof(char), strlen(dir) + strlen(file) + 1);
    strcpy(path, dir);
    strcat(path, file);
    printf("path: %s\n", path);
    Image image = LoadImage(path);
    free(path);

    Texture2D texture = LoadTextureFromImage(image);

    Mesh mesh = GenMeshHeightmap(image, (Vector3) { 16, 8, 16 });
    Model model = LoadModelFromMesh(mesh);

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    Vector3 mapPosition = { -8.0f, 0.0f, -8.0f };

    UnloadImage(image);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        UpdateCamera(&camera, CAMERA_ORBITAL);

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawModel(model, mapPosition, 1.0f, RED);

        DrawGrid(20, 1.0f);

        EndMode3D();

        DrawTexture(texture, screenWidth - texture.width - 20, 20, WHITE);
        DrawRectangleLines(screenWidth - texture.width - 20, 20, texture.width, texture.height, GREEN);

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
