#include "raylib.h"
#include "raymath.h"
#include "projectiles.h"
#include "arena.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_PROJECTILES 100

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
Camera camera = { 0 };
Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
Ray mouseRay = { 0 };
Vector3 mouseWorldPosition = { 0 };
//  these plane vector values will make calculating intersections much easier
Vector3 xzPlanePoint = { 0.0f, 1.0f, 0.0f };
Vector3 xzPlaneVector1 = { 1.0f, 0.0f, 0.0f };
Vector3 xzPlaneVector2 = { 0.0f, 0.0f, 1.0f };
Vector3 xzNormalvector = { 1.0f, 0.0f, 1.0f };
char buf1[50];
char buf2[50];
char buf3[50];

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(ProjectilePool *p, Arena *a);          // this is terrible, fix it pls
Vector3 GetMouseWorldPosition(Ray *mouseRay);

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "-not-tanks!-");

    camera.position = (Vector3){ 0.0f, 30.0f, -15.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;
    ProjectilePool *playerProjectiles = PoolCtor(MAX_PROJECTILES);
    Arena* test_arena = ArenaCtor(78, 50, 2.0f);

    //--------------------------------------------------------------------------------------
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        sprintf(buf1, "actives: %d", playerProjectiles->actives);
        sprintf(buf2, "nextFree:%p", playerProjectiles->nextFree);
        sprintf(buf3, "arrEnd:%p", playerProjectiles->arrEnd);

        mouseRay = GetMouseRay(GetMousePosition(), camera);
        mouseWorldPosition = GetMouseWorldPosition(&mouseRay);
        UpdateProjectilePosition(playerProjectiles);
        // UpdatePlayer();

        if (IsKeyDown(KEY_D)) cubePosition.x -= 1;
        else if (IsKeyDown(KEY_A)) cubePosition.x += 1;
        if (IsKeyDown(KEY_W)) cubePosition.z += 1;
        else if (IsKeyDown(KEY_S)) cubePosition.z -= 1;
        if (IsKeyPressed(KEY_SPACE)) cubePosition = (Vector3) { 0.0f, 1.0f, 0.0f};
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector3 projectileDirection = Vector3Subtract(mouseWorldPosition, cubePosition);
            NewProjectile(playerProjectiles, Vector3Add(cubePosition, Vector3Scale(Vector3Normalize(projectileDirection), 1.0f)), projectileDirection);
        } 
        if (IsKeyPressed(KEY_R)) DeleteAllProjectiles(playerProjectiles);

        CheckProjectileCollision(playerProjectiles);

        UpdateDrawFrame(playerProjectiles, test_arena);
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    PoolDtor(playerProjectiles);
    ArenaDtor(test_arena);
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(ProjectilePool *p, Arena *a)
{
    // Update
    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

            DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
            DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
            DrawGrid(50, 2.0f);
            DrawArena(a);
            DrawProjectiles(p);           

        EndMode3D();

        DrawText(buf1, 10, 70, 10, DARKGRAY);
        DrawText(buf2, 10, 90, 10, DARKGRAY);
        DrawText(buf3, 10, 110, 10, DARKGRAY);

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

//  returns intersection of mouseRay and xzPlane
Vector3 GetMouseWorldPosition(Ray *mouseRay)
{
    //  ((mouseRay.position) + t(mouseRay.direction)) = (xzPlanePoint) + r(xzPlaneVector1) + s(xzPlaneVector2)
    //  aka. ((0 30 -15) + t(mouseRay.direction)) = (0 1 0) + r(1 0 0) + s(0 0 1)
    float r = 0.0f, s = 0.0f, t = 0.0f;
    Vector3 tmpMouseRayDirection = Vector3Scale(mouseRay->direction, -1.0);
    Vector3 tmpPointVector = Vector3Subtract(mouseRay->position, xzPlanePoint);

    //  (tmpPointVector) = r(1 0 0) + s(0 0 1) - t(tmpMouseRay.direction)
    t = tmpPointVector.y / tmpMouseRayDirection.y;              	                    //  y values in other vectors are 0 so we can immediately solve for t
    tmpMouseRayDirection = Vector3Scale(tmpMouseRayDirection, t);                       //  insert t
    if (tmpMouseRayDirection.x >= 0) r = tmpPointVector.x - tmpMouseRayDirection.x;     //  solve for r
    else r = tmpPointVector.x + abs(tmpMouseRayDirection.x);
    if (tmpMouseRayDirection.z >= 0) s = tmpPointVector.z - tmpMouseRayDirection.z;     //  solve for s
    else s = tmpPointVector.z + abs(tmpMouseRayDirection.z);

    //  insert r and s into plane equation to find intersection
    Vector3 planeVector1 = Vector3Scale(xzPlaneVector1, r);
    Vector3 planeVector2 = Vector3Scale(xzPlaneVector2, s);
    planeVector1 = Vector3Add(planeVector1, planeVector2);
    Vector3 intersection = Vector3Add(xzPlanePoint, planeVector1);
    return intersection;
}