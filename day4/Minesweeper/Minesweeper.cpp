#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <locale>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <cstdio>

#define FIELD_SIZE_X 16
#define FIELD_SIZE_Y 16
#define BOMBS_COUNT 255
#define BOMBCHAR '#'
// Define colors for console output, with grey background

// GREY background console
#define GREY_BACKGROUND "\033[47m"

#define BLACK_TEXT "\033[3;47;30m"
#define RED_TEXT "\033[3;47;31m"
#define LIGHT_RED_TEXT "\033[3;47;31;1m"
#define GREEN_TEXT "\033[3;47;32m"
#define YELLOW_TEXT "\033[3;47;33m"
// #define DARK_BLUE_TEXT "\033[34m"
#define BLUE_TEXT "\033[3;47;34m"

// Color reset console print
#define COLOR_RESET "\033[0m"


char ms_field[FIELD_SIZE_X][FIELD_SIZE_Y];
void initField(char field[FIELD_SIZE_X][FIELD_SIZE_Y]);
void printField(char field[FIELD_SIZE_X][FIELD_SIZE_Y]);
void insertBombs(char field[FIELD_SIZE_X][FIELD_SIZE_Y]);
void insertNumbers(char field[FIELD_SIZE_X][FIELD_SIZE_Y]);
int GetRandomNumberBetween(int lower, int upper);

// C-Version of Random, because it's only peudso random on windows
int GetRandomNumberBetween(int lower, int upper){ 
    return lower + (rand() % (upper - lower + 1));
}

int main(){
    setlocale(LC_ALL, "en_US.utf8");
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
    #endif
    srand(time(NULL)); // Set random seed
    initField(ms_field);
    insertBombs(ms_field);
    insertNumbers(ms_field);
    printField(ms_field);    
}

void initField(char field[FIELD_SIZE_X][FIELD_SIZE_Y]){


    for(int i = 0; i < FIELD_SIZE_X; i++){
        for(int j = 0; j < FIELD_SIZE_Y; j++){
            field[i][j] = '.';
        }
    }
}
void insertBombs(char field[FIELD_SIZE_X][FIELD_SIZE_Y]){
    int bombCounter = 0;
    while(bombCounter < BOMBS_COUNT){
        int x = GetRandomNumberBetween(0, FIELD_SIZE_X - 1);
        int y = GetRandomNumberBetween(0, FIELD_SIZE_Y - 1);
        if(field[x][y] != BOMBCHAR){
            field[x][y] = BOMBCHAR;
            bombCounter++;
        }
    }
}

void insertNumbers(char field[FIELD_SIZE_X][FIELD_SIZE_Y]){
    int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (int i = 0; i < FIELD_SIZE_X; i++){
        for (int j = 0; j < FIELD_SIZE_Y; j++){
            if (field[i][j] != BOMBCHAR){
                int count = 0;
                for (int k = 0; k < 8; k++){
                    int x = i + dirs[k][0];
                    int y = j + dirs[k][1];
                    if (x >= 0 && x < FIELD_SIZE_X && y >= 0 && y < FIELD_SIZE_Y){
                        if (field[x][y] == BOMBCHAR){
                            count++;
                        }
                    }
                }
                if (count > 0){
                    field[i][j] = count + '0';
                }
            }
        }
    }
}
void printField(char field[FIELD_SIZE_X][FIELD_SIZE_Y]){
    // char* bomb_string = {'\0xF0', '\0x9F', '\0x92', '\0xA3'};
    std::string charSpace = " ";
    for(int i = 0; i < FIELD_SIZE_X; i++){
        for(int j = 0; j < FIELD_SIZE_Y; j++){
            switch(field[i][j]){
                case BOMBCHAR:
                    std::cout << GREY_BACKGROUND <<  "💣" << COLOR_RESET;
                    break;
                case '1':
                    std::cout << BLUE_TEXT  <<   field[i][j] << charSpace  << COLOR_RESET;
                    break;
                case '2':
                    std::cout << GREEN_TEXT <<   field[i][j] << charSpace  << COLOR_RESET;
                    break;
                case '3':
                    std::cout << RED_TEXT <<   field[i][j] << charSpace  << COLOR_RESET;
                    break;
                case '4': 
                    std::cout << BLUE_TEXT <<   field[i][j] << charSpace  << COLOR_RESET;
                    break;
                case '.':
                    std::cout << GREY_BACKGROUND <<  field[i][j] << charSpace  << COLOR_RESET;
                    break;
                default:
                    std::cout << RED_TEXT <<   field[i][j] << charSpace << COLOR_RESET;
                    break;    
        }
    }
        std::cout << std::endl;
}
}


