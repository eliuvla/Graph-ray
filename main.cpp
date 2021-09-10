#include "raylib.h"
#include "raygui.h"
#include "interpreter.h"



int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    const int screenWidth = 640;
    const int screenHeight = 480;
    int samplesize = 4000;

    float positions[samplesize]; 
    Vector2 points[samplesize/2];
    int i;
    Vector2 camfocus = Vector2{0,0};


    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    
    InitWindow(screenWidth, screenHeight, "Ray Graph");

    
    Camera2D camera = { 0 };
    camera.target = (Vector2){  screenWidth/2,  screenHeight/2};
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 100.0;

    SetTargetFPS(60);                           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())                // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------




        // cam movement
        if (IsKeyDown(KEY_D)) camfocus.x += 2/camera.zoom;
        if (IsKeyDown(KEY_A)) camfocus.x -= 2/camera.zoom;
        if (IsKeyDown(KEY_W)) camfocus.y -= 2/camera.zoom;
        if (IsKeyDown(KEY_S)) camfocus.y += 2/camera.zoom;
        camera.target = (Vector2){ camfocus.x , camfocus.y };

        // Camera rotation controls
        if (IsKeyDown(KEY_LEFT)) camera.rotation--;
        else if (IsKeyDown(KEY_RIGHT)) camera.rotation++;

        // Camera zoom controls
        if (IsKeyDown(KEY_UP)) camera.zoom += 0.05f*camera.zoom;
        if (IsKeyDown(KEY_DOWN)) camera.zoom -= 0.05f*camera.zoom;
        if(camera.zoom<0) camera.zoom=0;


        // Camera reset (zoom and rotation)
        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 100.0f;
            camera.rotation = 0.0f;
            camfocus = Vector2{0,0};
            camera.target = camfocus;
        }
        // function adap 

        if(IsKeyDown(KEY_D)||IsKeyDown(KEY_A)||IsKeyDown(KEY_W)||IsKeyDown(KEY_S)||IsKeyDown(KEY_UP)||IsKeyDown(KEY_DOWN))
        {
            function(camfocus.x/camera.zoom, camera.zoom, 640/camera.zoom, 480/camera.zoom, samplesize, "tan(x)", positions);
                for(i=0; i<samplesize/2; i ++)
            {
                points[i].x = positions[2*i];
                points[i].y = positions[2*i+1];
            }
        } 


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode2D(camera);

                
                DrawLineStrip(points, samplesize/2 , GREEN);
                DrawLine(0,-screenHeight/2,0,screenHeight/2, WHITE);
                DrawLine(-screenWidth/2,0,screenWidth/2,0, WHITE);
                
                DrawCircle(0,0, 10/camera.zoom, RED);
            
            EndMode2D();
            DrawGrid(10, 20);
            DrawText("prueba jijijiji:", 20, 20, 10, WHITE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}