#include <iostream>
#include <raylib.h>
using namespace std;

// gloable veribale for the color and game score
Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int score_player = 0;
int score_cpu = 0;

class Ball {
public:
  float x, y;
  float radius;
  float speed_y, speed_x;
  Ball(){};
  Ball(float x, float y, float radius, float speed_y, float speed_x)
      : x(x), y(y), radius(radius), speed_x(speed_x), speed_y(speed_y) {}
  void Draw() { DrawCircle(x, y, radius, Yellow); }
  void Reset() {

    // static_cast for convert the type for the element
    x = static_cast<float>(GetScreenWidth()) / 2;
    y = static_cast<float>(GetScreenHeight()) / 2;
    int speed_choices[2] = {-1, 1};
    speed_x *= speed_choices[GetRandomValue(0, 1)];
    speed_y *= speed_choices[GetRandomValue(0, 1)];
  }
  void Update() {
    x += speed_x;
    y += speed_y;
    // some condiation for check if callson happend in the border for window ...
    if (x >= GetScreenWidth() - 40) {
      score_player++;
      Reset();
    }
    if (x <= 40) {
      score_cpu++;
      Reset();
    }
    if (y >= GetScreenHeight() || y <= 0) {
      speed_y *= -1;
    }
  }
};

class Paddle {

protected:
  void Limetiness() {
    if (y <= 0) {
      y = 0;
    }
    if (y + height >= GetScreenHeight()) {
      y = GetScreenHeight() - height;
    }
  }

public:
  float x, y, width, height, speed;
  Paddle() {}
  Paddle(float x, float y, float width, float height, float speed)
      : x(x), y(y), width(width), height(height), speed(speed) {}

  void Draw() {
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
  }
  void Update() {
    if (IsKeyDown(KEY_K)) {
      y = y - speed;
    }
    if (IsKeyDown(KEY_J)) {
      y = y + speed;
    }
    Limetiness();
  }
};

class CpuPaddle : public Paddle {
public:
  void Update(int ball_y) {
    if (y + height >= ball_y) {
      y = y - speed;
    }
    if (y + height <= ball_y) {
      y = y + speed;
    }
    Limetiness();
  }
};

int main() {
  cout << "Starting Game For Raylib Library ..." << endl;
  const float screen_width = 1280;
  const float screen_height = 800;
  Ball ball(screen_width / 2.00, screen_height / 2, 30, 7, 7);
  Paddle player(20, screen_height / 2 - 60, 25, 120, 6);
  CpuPaddle cpu;

  cpu.height = 120;
  cpu.width = 25;
  cpu.x = screen_width - 45;
  cpu.y = screen_height / 2 - 60;
  cpu.speed = 6;

  // for initalzation for the game window
  InitWindow(screen_width, screen_height, "Bing Bong Game Reylib");
  SetTargetFPS(60); // for the frame for second in the game

  // WindowShouldClose is function return true
  // when click on ESC or exit in the window
  while (WindowShouldClose() == false) {
    // start Drawing the window for the game
    ClearBackground(Dark_Green);
    BeginDrawing();

    // draw line in the middle for the game
    DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
    // draw second rectangle in anther part for player .. 
    DrawRectangle(0, 0, screen_width / 2, screen_height, Green);
    // draw Cricle in the middlle
    DrawCircle(screen_width / 2, screen_height / 2, 140, Light_Green);


    // draw the score for the player and cpu
    DrawText(TextFormat("%i", score_player), screen_width / 4 - 20,  20, 50, WHITE);
    DrawText(TextFormat("%i", score_cpu), 3 * screen_width / 4 - 20,  20, 50, WHITE);

    /* DrawRectangle(20, screen_height / 2 - 60, 25, 120, WHITE); */
    /* DrawRectangle(screen_width - 45, screen_height / 2 - 60, 25, 120, WHITE);
     */

    player.Draw();
    player.Update();

    cpu.Draw(); // draw the paddle for cpu
    cpu.Update(
        ball.y); /* update the paddle for cpu with position for the ball */

    // the line code under is for explain only
    /* DrawCircle(screen_width / 2, screen_height / 2, 30, WHITE); */
    ball.Draw();
    ball.Update();

    // collision for the paddle and ball and cpu
    if (CheckCollisionCircleRec(
            {ball.x, ball.y}, ball.radius,
            {player.x, player.y, player.width, player.height})) {
      ball.speed_x *= -1;
    }
    if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius,
                                {cpu.x, cpu.y, cpu.width, cpu.height})) {
      ball.speed_x *= -1;
    }

    // End the draw for and thing in the window..
    EndDrawing();
  };

  // closing the window when the loop end ....
  CloseWindow();

  return 0;
}
