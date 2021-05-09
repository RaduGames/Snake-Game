#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <windows.h>

class Menu{
    private : std::string* options;
             int currentChoice = 0, string_size;

    public :
            Menu(std::string* o, int s)
            {
                options = new std::string[s];
                for(int i = 0; i < s; i++){
                      *(options + i) = *(o + i);
                }
                *options += "<-";
                string_size = s;
            }

            //Returns true if enter has been pressed, false otherwise
            bool Change_Event(){
                  char ans = getch();
                  if(tolower(ans) == 'w' && currentChoice != 0){
                          std::string temp = options[currentChoice].substr(0, options[currentChoice].size() - 2);
                          options[currentChoice].assign(temp);
                          options[currentChoice - 1] += "<-";
                          currentChoice--;
                  }
                  else if(tolower(ans) == 's' && currentChoice != string_size - 1){
                        std::string temp = options[currentChoice].substr(0, options[currentChoice].size() - 2);
                        options[currentChoice].assign(temp);
                        options[currentChoice + 1] += "<-";
                        currentChoice++;
                  }
                  else if(ans == 10 || ans == 13)
                            return true;
                  return false;
            }
            ~Menu(){
                delete[] options;
            }
            //Returns -1 if the user presses 'w' or 's', the selected option otherwise(when enter is pressed)
            int Update(){
                  system("cls");
                  int num;
                  for(int i = 0; i < string_size; i++)
                      std::cout << options[i] << "\n";
                  if(Change_Event()){
                          num = getChoice();
                          return num;
                  }
                  else{
                       return -1;
                  }
            }
            int getChoice(){ return currentChoice;}
};



#endif // MENU_H_INCLUDED
