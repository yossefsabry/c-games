#include <cstdlib>
#include <ctime>
#include <iostream>
/* #include <conio.h> */
using namespace std;

struct Map {int Width, Height, FruitX, FruitY; };
struct Snake {int Headx, Heady, TailCount; char Dir;};
struct Player {int Score; bool Lose;};
// --------------------
Map map; Snake snake; Player player;


void GenerateFruits() {
  srand(time(NULL));
  map.FruitX = rand() % (map.Width - 2) + 1;
  map.FruitY = rand() % (map.Height - 2) + 1;
};

void Setup() {
  map.Width = 40;
  map.Height = 30;
  GenerateFruits();
  // -----------------
  snake.Headx = map.Width / 2;
  snake.Heady = map.Height / 2;
  snake.TailCount = 0;
  // -----------------
  player.Score = 0;
  player.Lose = false;
};

void Draw() {
  for (int i = 0; i < map.Height; i++) {
    for (int j = 0; i < map.Width; i++) {
      if (i == 0 || i == map.Height - 1) cout << "*";
      else if(j == 0 || j == map.Width - 1) cout << "*";
      else if(i == snake.Heady && j == snake.Headx) cout << "O";
      else if(i == map.FruitY && j == map.FruitX) cout << "$";
      else cout << " ";
    }
    cout << endl;
  }

}

void input() {
  if(_Kbhit()) {
    char c = _getch;

  }
}


int main () {

  Setup();
  Draw();
  return 0;
}
