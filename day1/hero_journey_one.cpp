#include <iostream>
#include <vector>

// We put this stuff here, so that the main method can see them,
// if they are not declared before they are used -> Compile error
// We come here again if we get to headers


/*
* Displays all heroes in the vector and makes it possible 
* to select one. 
* The return value is the position of the element in the vector.
*/
int ShowHeroSelect(std::vector<std::string> &heroes);
int ShowHeroSelect(std::vector<std::string> &heroes){
    std::cout << "Choose your hero: ";
    for(int i = 0; i < heroes.size(); i++){
        std::cout << i+1 << ") " << heroes[i] << std::endl;
    }
    int choice;
    std::cin >> choice;
    std::cout << "========================" << std::endl;

    return choice;
}
/**
 * Displays the initial menu, which gives you the possibility to
 * a) Create a new Hero
 * b) Start a new game by selecting a hero
 * c) close the application
 */
int ShowStartMenuSelect();
int ShowStartMenuSelect(){
    std::cout << "Please select an option:" << std::endl;
    std::cout << "1) Create a new Hero" << std::endl;
    std::cout << "2) Start a new game by selecting a hero" << std::endl;
    std::cout << "3) Close the application" << std::endl;
    int selection;
    std::cin >> selection;
    std::cout << "========================" << std::endl;

    return selection;
}
/**
 * Creates a new Hero, which is nothing more but a string cointaining 
 * it's name , and add it to the inserted vector of strings
 * 
 */
void CreateAndAddHero(std::vector<std::string> &heroes);
void CreateAndAddHero(std::vector<std::string> &heroes){
    std::string name;
    std::cout << "Please enter the name of your hero: ";
    std::cin >> name;
    std::cout << "========================" << std::endl;
    heroes.push_back(name);
}
/**
 * Displays a message containing the hero's name,
 * which tells about the encouraging adventures in the DLC
 * 
 */
void ShowStartDialog(std::string &hero);
void ShowStartDialog(std::string &hero){
    std::cout << "Welcome to the game " << hero << "!" << std::endl;
    std::cout << "You have been chosen to go on an adventure!" << std::endl;
    std::cout << "You have been given the task to find the legendary sword, " << std::endl;
    std::cout << "which is said to be hidden in the depths of the dungeon." << std::endl;
    std::cout << "You must find it before the evil wizard can destroy it!" << std::endl;
    std::cout << "Good luck!" << std::endl;
    std::cout << "========================" << std::endl;
}

/**
 * Program to run
 */
int main(){
    std::vector<std::string> heroes;
    int selection;
    while(!std::cin.fail() && selection != 2){
    selection = ShowStartMenuSelect();
    std::cout<< "You selected: " << selection << std::endl;
    switch(selection){
        case 1:
            CreateAndAddHero(heroes);
            break;
        case 2:
            ShowStartDialog(heroes[ShowHeroSelect(heroes)]);
            break;
        case 3:
            return 0;
            break;
        default:
            std::cout << "Invalid selection" << std::endl;
            break;
    }}
    return 0;
}

