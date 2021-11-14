#include <iostream>
#include <fstream>
#include <ios>
#include <vector>
template <typename type1>
type1 readFromStream(std::ifstream &stream, char *buffer);
template <typename type1>
type1 byteFromBuffer(char *buffer, int offset);

class d2c
{
    int header;
    int fileVersion;
    int fileSize;
    int checkSum;
    int unknown1;
    char characterName[16];
    char characterStatus;      // BitField -> 2=Hardcore?, 3 = Died?, 4 = Unknown, 5 = ExpansionCharacter?, 7+6+0+1 = Unknown
    char characterProgression; // BitField -> Used to determine the Character progression
    char unknown2[2];
    char characterClass; // BitField -> 0 = Amazon, 1 = Sorceress, 2 = Necromancer, 3 = Paladin, 4 = Barbarian, 5 = Druid, 6 = Assassin
    char unknown3[2];
    char characterLevel;

public:
    bool isCharacterDead();
    bool isHardcore();
    bool isExpansionCharacter();
    std::string getCharacterName();
    std::string getCharacterTitle();
    int getCharacterLevel();
    std::string getCharacterClass();
};

std::string d2c::getCharacterClass(){
    switch(this->characterClass){
        case 0:
            return "Amazon";
        case 1:
            return "Sorceress";
        case 2:
            return "Necromancer";
        case 3:
            return "Paladin";
        case 4:
            return "Barbarian";
        case 5:
            return "Druid";
        case 6:
            return "Assassin";
        default:
            return "Unknown";
    }
}


int d2c::getCharacterLevel()
{
    return (int) characterLevel;
}



bool d2c::isCharacterDead()
{
    const unsigned short died_mask = 0b00001000;
    return (characterStatus & died_mask);
}

bool d2c::isExpansionCharacter()
{
    const unsigned short exp_mask = 0b00100000;
    return (characterStatus & exp_mask);
}

bool d2c::isHardcore()
{
    const unsigned short died_mask = 0b00000100;
    return (characterStatus & died_mask);
}

std::string d2c::getCharacterName()
{
    return std::string(this->characterName);
}
std::string d2c::getCharacterTitle()
{
    typedef std::vector<std::string> string_vector;
    string_vector stdTitlesMale = {"", "Sir", "Lord", "Baron"};
    string_vector stdTitlesFemale = {"", "Dame", "Lady", "Baroness"};
    string_vector hdcTitlesMale = {"", "Count", "Duke", "King"};
    string_vector hdcTitlesFemale = {"", "Countess", "Duchess", "Queen"};
    string_vector eStdTitlesMale = {"", "Slayer", "Champion", "Patriarch"};
    string_vector eStdTitlesFemale = {"", "Slayer", "Champion", "Matriarch"};
    string_vector eHdcTitles = {"", "Destroyer", "Conquer", "Guardian"};
    bool male = true;
    string_vector *titles;
    if (this->isExpansionCharacter())
    {
        if (this->isHardcore())
        {
            titles = &eHdcTitles;
        }
        else
        {
            if (male)
            {
                titles = &eStdTitlesMale;
            }
            else
            {
                titles = &eStdTitlesFemale;
            }
        }
    }
    else
    {
        if (this->isHardcore())
        {
            if (male)
            {
                titles = &hdcTitlesMale;
            }
            else
            {
                titles = &hdcTitlesFemale;
            }
        }
        else
        {
            if (male)
            {
                titles = &stdTitlesMale;
            }
            else
            {
                titles = &stdTitlesFemale;
            }
        }
    }
    int cP = (int) (this->characterProgression);

    if(this->isExpansionCharacter()){
        if(cP >=0 && cP<=3){
            return titles->at(0);
        }else if (cP<=8){
            return titles->at(1);
        }else if (cP<=13){
            return titles->at(2);
        }else{
            return titles->at(3);
        }
    }else{
    if(cP >=0 && cP<=3){
        return titles->at(0);
    }else if (cP<=7){
        return titles->at(1);
    }else if (cP<=11){
        return titles->at(2);
    }else{
        return titles->at(3);
    }
    }
    return "Not found!";
}


int main()
{
    char *buffer = new char[sizeof(d2c)];
    try
    {

        std::ifstream charakterStream("data/charakter.d2s");
        auto charakter = readFromStream<d2c>(charakterStream, buffer);
        // Print the Name, Hardcore, Expansion and Level
        std::cout << "Name: " << charakter.getCharacterName() << std::endl;
        std::cout << "Hardcore: " << charakter.isHardcore() << std::endl;
        std::cout << "Expansion: " << charakter.isExpansionCharacter() << std::endl;
        std::cout << "Level: " << charakter.getCharacterLevel() << std::endl;
        std::cout << "Class: " << charakter.getCharacterClass() << std::endl;
        std::cout << "Title: " << charakter.getCharacterTitle() << std::endl;
        std::cout << "Dead: " << charakter.isCharacterDead() << std::endl;
    
        charakterStream.close();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    delete[] buffer;
    return 0;
}

template <typename type1>
type1 readFromStream(std::ifstream &stream, char *buffer)
{

    if (stream.is_open())
    {
        stream.read(buffer, sizeof(type1));
        type1 *data = reinterpret_cast<type1 *>(buffer);
        return std::move(*data);
    }
    else
    {
        throw std::runtime_error("Could not read from File!");
    }
}

template <typename type1>
type1 byteFromBuffer(char *buffer, int offset)
{
    type1 *data = reinterpret_cast<type1 *>(buffer + offset);
    return std::move(*data);
}