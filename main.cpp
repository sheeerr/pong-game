#include <iostream>
#include <raylib.h>

using namespace std;

Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int player_score = 0;
int cpu_score = 0;

class Ball {
    public:
    float x, y, radius;
    float speed_x, speed_y;

    void Draw() {
        DrawCircle(x, y, radius, Yellow);
    }

    void update() {
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }

        if(x + radius >= GetScreenWidth()) {
            cpu_score++;
            ResetBall();
        }
        if(x - radius <= 0) {
            player_score++;
            ResetBall();
        }
    }

    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle {
    protected:
        void LimitMoment() {
            if(y <= 0) {
                y = 0;
            }
            if(y + height >= GetScreenHeight()) {
                y = GetScreenHeight() - height;
            }
        }

    public:
    float x, y;
    float width, height;
    int speed;

    void draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    void update() {
        if (IsKeyDown(KEY_UP) && y > 0) {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN) && y + height < GetScreenHeight()) {
            y += speed;
        }
        LimitMoment();
    }
};

class CpuPaddle: public Paddle {
    public:
        void update(int ball_y) {
            if (y + height / 2 > ball_y) {
                y -= speed;
            }
            if (y + height / 2 <= ball_y) {
                y += speed;
            }
            LimitMoment();
        }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main() {
    cout << "Starting the game" << endl;
    const int screen_width = 1160;
    const int screen_height = 648;
    InitWindow(screen_width, screen_height, "Pong");
    SetTargetFPS(60);               

    ball.radius = 10;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.x = screen_width - 30;
    player.y = screen_height / 2 - 50;
    player.width = 20;
    player.height = 100;
    player.speed = 6;

    cpu.height = 100;
    cpu.width = 20;
    cpu.x = 10;
    cpu.y = screen_height / 2 - 50;
    cpu.speed = 6;

    while (WindowShouldClose() == false) {
        BeginDrawing();

        ball.update();
        player.update();
        cpu.update(ball.y);

        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.speed_x *= -1;
        }

        ClearBackground(Dark_Green);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 130, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);  
        ball.Draw();
        player.draw();
        cpu.draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}