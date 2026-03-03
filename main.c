#include "raylib.h"
#include <stdlib.h>
#include <time.h>

typedef enum {
    NONE = -1,
    ROCK = 0,
    PAPER = 1,
    SCISSORS = 2
} Choice;

int CheckWinner(int player, int cpu) {
    if (player == cpu) return 0;
    if ((player == ROCK && cpu == SCISSORS) ||
        (player == PAPER && cpu == ROCK) ||
        (player == SCISSORS && cpu == PAPER))
        return 1;
    return -1;
}

int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 500;
    InitWindow(screenWidth, screenHeight, "Tas Kagit Makas");

    Texture2D rock = LoadTexture("rock.png");
    Texture2D paper = LoadTexture("paper.png");
    Texture2D scissors = LoadTexture("scissors.png");

    Rectangle buttons[3] = {
        { 100, 300, 100, 100 },
        { 250, 300, 100, 100 },
        { 400, 300, 100, 100 }
    };

    Choice playerChoice = NONE;
    Choice cpuChoice = NONE;

    int playerScore = 0;
    int cpuScore = 0;

    float animScale = 1.0f;

    srand(time(NULL));
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < 3; i++) {
                if (CheckCollisionPointRec(mouse, buttons[i])) {
                    playerChoice = i;
                    cpuChoice = rand() % 3;

                    int result = CheckWinner(playerChoice, cpuChoice);
                    if (result == 1) playerScore++;
                    if (result == -1) cpuScore++;

                    animScale = 1.4f;
                }
            }
        }

        if (animScale > 1.0f) animScale -= 0.02f;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("YOU", 150, 20, 20, DARKGRAY);
        DrawText("CPU", 650, 20, 20, DARKGRAY);

        DrawText(TextFormat("Score: %d", playerScore), 130, 50, 20, BLACK);
        DrawText(TextFormat("Score: %d", cpuScore), 630, 50, 20, BLACK);

        if (playerChoice != NONE) {
            Texture2D tex = (playerChoice == ROCK) ? rock :
                            (playerChoice == PAPER) ? paper : scissors;

            DrawTextureEx(tex, (Vector2){120, 100}, 0, animScale * 0.3f, WHITE);
        }

        if (cpuChoice != NONE) {
            Texture2D tex = (cpuChoice == ROCK) ? rock :
                            (cpuChoice == PAPER) ? paper : scissors;

            DrawTextureEx(tex, (Vector2){600, 100}, 0, 0.3f, WHITE);
        }

        DrawTextureEx(rock, (Vector2){buttons[0].x, buttons[0].y}, 0, 0.15f, WHITE);
        DrawTextureEx(paper, (Vector2){buttons[1].x, buttons[1].y}, 0, 0.15f, WHITE);
        DrawTextureEx(scissors, (Vector2){buttons[2].x, buttons[2].y}, 0, 0.15f, WHITE);

        DrawText("Click to choose", 300, 270, 20, GRAY);

        EndDrawing();
    }

    UnloadTexture(rock);
    UnloadTexture(paper);
    UnloadTexture(scissors);
    CloseWindow();

    return 0;
}
