// Copilot generated: Color Code printing red,yellow,green,blue,orange, cyan, magenta,white  background with fitting foreground
#define RED_BG_WHITE "\033[41m\033[37m"     /* Red Background Black */
#define YELLOW_BG_BLACK "\033[43m\033[30m"  /* Yellow Background Black */
#define GREEN_BG_BLACK "\033[42m\033[33m"   /* Green Background Black */
#define BLUE_BG_BLACK "\033[44m\033[37m"    /* Blue Background Black */
#define ORANGE_BG_BLACK "\033[45m\033[37m"  /* Orange Background Black */
#define CYAN_BG_BLACK "\033[46m\033[37m"    /* Cy#define WHITE_BG_BLACKan Background Black */
#define MAGENTA_BG_BLACK "\033[45m\033[30m" /* Magenta Background Black */
#define WHITE_BG_BLACK "\033[47m\033[30m"   /* White Background Black */
#define RESET "\033[0m"

#define MM_TRIES 10
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
//Will be used to obtain a seed for the random number engine
std::random_device rd;
//Standard mersenne_twister_engine seeded with rd()
std::mt19937 gen(rd());
void split(const std::string &s, char c, std::vector<std::string> &v);
int GetRandomNumberBetween(int lower, int upper);
void generateRandomColors();
void printColors(std::vector<std::string> colors);
void startGame();
std::vector<std::string> collectGuess();

std::vector<std::string> availableColors = {"red", "blue", "green", "yellow", "cyan", "magenta"};
enum Color { RED, BLUE, GREEN, YELLOW, CYAN, MAGENTA };
std::map<std::string, Color> colorMap = {
    {"red", RED}, {"blue", BLUE}, {"green", GREEN}, {"yellow", YELLOW}, {"cyan", CYAN}, {"magenta", MAGENTA}};
std::vector<std::string> choosenColors;
std::vector<std::string> randCol;

int main()
{
    std::cout << "Welcome to Mastermind!" << std::endl;
    generateRandomColors();
    startGame();
}

void startGame()
{
    std::cout << "Enter your guess [4]" << std::endl;
    printColors(availableColors);
    for(int trys = MM_TRIES; trys>0;trys--)
    {
        int colCorrect = 0;
        int posCorrect = 0;
        std::vector<std::string> lastg = collectGuess();
        for (int i = 0; i < lastg.size(); i++)
        {
            if(lastg[i] == choosenColors[i]){
                posCorrect++;
                continue;
            }
            for (int j = 0; j < choosenColors.size(); j++)
            {
                if (lastg[i] == choosenColors[j])
                {
                    colCorrect++;
                }
            }
        }
        std::cout << "Correct Positions: " << posCorrect << std::endl;
        std::cout << "Only orrect Color: " << colCorrect << std::endl;
        for (int i = 0; i<posCorrect;++i){
            std::cout  << GREEN_BG_BLACK << "-" << RESET << " ";
        }
        for (int i = 0; i<colCorrect;++i){
            std::cout  << RED_BG_WHITE << "-" << RESET << " ";
        }
        std::cout << std::endl;
        if(posCorrect == choosenColors.size()){
            std::cout << "You guessed the right colors!!! Congrats" << std::endl << "The Right Colors were:";
            printColors(choosenColors);
        }
    }
    std::cout << "You used all your tries!"<< std::endl << "The Right Colors were: ";
    printColors(choosenColors);

}

std::vector<std::string> collectGuess()
{
    std::string guess;
    std::cin >> guess;
    std::vector<std::string> guessColors;
    split(guess, ',', guessColors);
    std::cout << "Your guess was: ";
    printColors(guessColors);
    return guessColors;
}

void printColors(std::vector<std::string> colors)
{
    for (int i = 0; i < colors.size(); ++i)
    {
        std::string col = colors[i];
        if (col == "red")
        {
            std::cout << RED_BG_WHITE << "red" << RESET;
        }
        else if (col == "blue")
        {
            std::cout << BLUE_BG_BLACK << "blue" << RESET;
        }
        else if (col == "green")
        {
            std::cout << GREEN_BG_BLACK << "green" << RESET;
        }
        else if (col == "yellow")
        {
            std::cout << YELLOW_BG_BLACK << "yellow" << RESET;
        }
        else if (col == "magenta")
        {
            std::cout << MAGENTA_BG_BLACK << "magenta" << RESET;
        }
        else if (col == "cyan")
        {
            std::cout << CYAN_BG_BLACK << "cyan" << RESET;
        }
        else if (col == "orange")
        {
            std::cout << ORANGE_BG_BLACK << "orange" << RESET;
        }
        else
        {
            std::cout << "Error: Color not found" << std::endl;
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}
void generateRandomColors()
{
    for (int i = 0; i < 4; i++)
    {
        int randomIndex = GetRandomNumberBetween(0, availableColors.size() - 1);
        choosenColors.push_back(availableColors[randomIndex]);
    }
}

int GetRandomNumberBetween(int lower, int upper)
{
    std::uniform_int_distribution<> dis(lower, upper);
    return dis(gen);
}

void split(const std::string &s, char c, std::vector<std::string> &v)
{
    std::string::size_type i = 0;
    std::string::size_type j = s.find(c);

    while (j != std::string::npos)
    {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);

        if (j == std::string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}
