#include "raylib.h"
#define TEAN (Color) {240, 233, 216, 255}

int main(void){
    // Initialization
    const int screen_width = 800;
    const int screen_height = 450;
    float x_ship = 150;
    float y_ship = 225;
    float y_comet_eas = GetRandomValue(0, screen_height);
    float x_comet_eas = screen_width;
    int speed = 5;
    bool can_move = true;
    bool alive = true;
    bool playing = false;
    Rectangle comet_eas = {x_comet_eas, y_comet_eas, 50, 50};
    Rectangle ship = {x_ship, y_ship, 100, 50};

    InitWindow(screen_width, screen_height, "comet_eass");

    SetTargetFPS(60);
    // Main game loop
    while (!WindowShouldClose()){
        // Update
        if (playing){
            // Comet
            if (alive) x_comet_eas -= speed;
            else x_comet_eas = screen_width;
            if (x_comet_eas < -49) y_comet_eas = GetRandomValue(0, screen_height);
            if (x_comet_eas == -50) x_comet_eas = screen_width;
            // Collision
            bool collision = CheckCollisionRecs(ship, comet_eas);
            // Alive or not
            if (collision) alive = false;
            if (!alive) {can_move = false; ship = {x_ship, y_ship, 100, 50}; y_ship = 150; x_ship = 150;}
            // Movement
            y_ship += 5;
            if (can_move){
                if (IsKeyDown(KEY_SPACE)) y_ship -= 10;
            }
            if (y_ship == 500) alive = false;
            if (y_ship == 0) alive = false;
            // Updating Recs
            comet_eas = {x_comet_eas, y_comet_eas, 50, 50};
            ship = {x_ship, y_ship, 100, 50};
            // Reviving
            if (!alive && IsKeyDown(KEY_R)) {alive = true; can_move = true;}
        }
        // Main menu
        if (!playing){
            if (IsKeyDown(KEY_ENTER)) playing = true;
        }
        // Draw
        BeginDrawing();

            if (!playing){
                ClearBackground(BLACK);
                DrawText("Asteroids", screen_width / 2 - 90, screen_height / 2 - 150, 20, TEAN);
                DrawText("Controls: Up(space key) & exit(escape key)\nIn this game you need to avoid asteroids\nthere're 2 versions of this game.\nThis is the hard version where\nspeed of the meteors can change.\nPress enter to continue.", 100, screen_height / 2, 20, WHITE);
            }
            if (alive && playing){
                ClearBackground(BLACK);
                DrawRectangleRec(ship, WHITE);
                DrawRectangleRec(comet_eas, GRAY);
            }
            if (!alive){
                ClearBackground(BLACK);
                DrawText("You died\nPress R to retry", screen_width / 2, screen_height / 2, 20, RED);
            }
            

        EndDrawing();
    }
    // De-Initialization
    CloseWindow();
    return 0;
}