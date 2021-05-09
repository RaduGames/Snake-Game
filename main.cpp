#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include "Menu.h"
#include <math.h>

using namespace std;

char Map[20][20];
/* '-','|' - Borders of the map
   's' - collectible
   'x' - obstacle
   '*' - player
*/

//Order : S, W, A, D(rule for our formula)
/*FORMULA(Discovered by trial and error, which gives, based on the character input, the index for the direction!
    index = (toupper(w/s/a/d)/4)%6 - 2
*/
const int dirX[4] = {1, -1, 0, 0};
const int dirY[4] = {0, 0, -1, 1};

char avoid[5] = {'-', '|', 'x', '*', 's'};
bool ValidPoint(char x)
{
    for(int i = 0; i < 4; i++){
          if(avoid[i] == x) return false;
    }
    return true;
}


int ct = 0, Score = 0;

struct Player{
   int p_size[40][2];
} p;

void copyArray(int a[2], int b[2]){
  for(int i = 0; i < 2; i++){
        a[i] = b[i];
  }
}

//Spawners
bool CanSpawn(char item, int &xi, int &yi){
   bool canSpawn = true;
   int x = rand() % 19, y = rand() % 19;
   for(int i = 0; i < 5; i++){
        if(Map[x][y] == avoid[i]){
               return false;
        }
   }
   xi = x;
   yi = y;
   return true;
}
void SpawnItem(char item){
   int x, y;
   bool myItem = CanSpawn(item, x, y);
   while(!myItem){
         myItem = CanSpawn(item, x, y);
   }
   Map[x][y] = item;
}


void Initialize(int difficulty)
{
    //Map Initialization
    for(int i = 0; i < 20; i++){
          Map[i][19] = '|';
          Map[i][0] = '|';
          Map[0][i] = '-';
          Map[19][i] = '-';
    }
    //Player Initialization
    int x = rand() % 19, y = rand() % 19;
    while(Map[x][y] != 0){
           x = rand() % 19;
           y = rand() % 19;
    }
    Map[x][y] = '*';
    p.p_size[ct][0] = x;
    p.p_size[ct][1] = y;
    ct++;
    //Collectible Initialization
    x = rand() % 19;
    y = rand() % 19;
    while(Map[x][y] != 0 && Map[x][y] != '*'){
           x = rand() % 19;
           y = rand() % 19;
    }
    Map[x][y] = 's';

    //Obstacles Initialization
    int number = pow(3, difficulty) + 5;
    for(int i = 0; i < number; i++){
           SpawnItem('x');
    }

}

void UpdateTail(int x, int y)
{
        for(int i = ct - 1; i > 0; i--){
                    copyArray(p.p_size[i], p.p_size[i - 1]);
                    Map[p.p_size[i][0]][p.p_size[i][1]] = '*';
        }
}

bool Movement(int &x, int &y){
   char ans = getch();
   if(toupper(ans) == 'A' || toupper(ans) == 'D' || toupper(ans) =='S' || toupper(ans) == 'W'){
   int Dir = (toupper(ans)/4)%6 - 2;
   char newPoint = Map[x + dirX[Dir]][y + dirY[Dir]];
         if(ValidPoint(newPoint)){
             Map[p.p_size[ct - 1][0]][p.p_size[ct - 1][1]] = 0;
             UpdateTail(x, y);
             x += dirX[Dir];
             y += dirY[Dir];
             Map[x][y] = '*';
                if(newPoint == 's'){
                  SpawnItem('s');
                  Score += 10;
                  ct++;
             }
         }
         else{ return false;}
         return true;
  }
  else if(ans == 10 || ans == 13) return false;
     return true;
}


void Display()
{
    for(int i = 0; i < 20; i++){
          for(int j = 0; j < 20; j++){
              cout << Map[i][j] << " ";
          }
          cout << endl;
    }
    cout << "\n\nScore : " << Score << "\n";
}



int main()
{

    string options[4] = {"Easy", "Normal", "Hard", "Extreme"};
    Menu m(options, 4);
    int choice;
    while(1){
      choice = m.Update();
      if(choice != -1)
          break;
    }
    system("cls");
    srand((int)time(0));
    Initialize(choice);
    while(1){
          Display();
          if(!Movement(p.p_size[0][0], p.p_size[0][1]))
             break;
          system("cls");
    }
    return 0;
}
