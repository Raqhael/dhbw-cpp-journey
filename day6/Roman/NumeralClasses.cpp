#include "NumeralClasses.hpp"
#include <vector>
#include <map>
typedef std::map<std::string, int> roman_arabic_map;
typedef std::vector<std::string> roman_vector;




int Arabic::getValue(){
    return value;
}

Arabic::Arabic(std::string roman){
    roman_arabic_map rmap = {{"I", 1}, {"V", 5}, {"IX", 9}, {"X", 10}, {"XL", 40}, {"L", 50}, {"XC", 90}, {"C", 100}, {"CD", 400}, {"D", 500}, {"CM", 900}, {"M", 1000}, {"Mↁ", 4000}, {"ↁ", 5000}, {"Mↂ", 9000}, {"ↂ", 10000}, {"ↂↇ", 40000}, {"ↇ", 50000}, {"ↂↈ", 90000}, {"ↈ", 100000}};
    roman_vector rvec = {"ↈ","ↇ","ↂ","ↁ","M", "D", "C", "L", "X", "V", "I"};
    this->value = 0;
    int bufferValue = 0;
    int bufferIndex = 0;
    while(roman.length() > 0){
        std::string buffer = roman.substr(bufferIndex,bufferIndex+1);
        roman = roman.substr(1,roman.size());
        bufferValue = rmap[buffer];
        std::string nextBuffer = roman.substr(bufferIndex,bufferIndex+1);
        int nextBufferValue = rmap[nextBuffer];
        if(nextBufferValue == 0){
            continue;
        }else if(bufferValue >= nextBufferValue){
            this->value += bufferValue;
        }
        else{
            std::cout << nextBufferValue << std::endl;
            int smallerValue = nextBufferValue - bufferValue;
            this->value += nextBufferValue - bufferValue;
            bufferIndex = 0;
        }
    }
}
Roman::Roman(int arabic){
    // Map of all values, and their roman representation. 
    roman_arabic_map rmap = {{"I", 1}, {"IV", 4}, {"V", 5}, {"IX", 9}, {"X", 10}, {"XL", 40}, {"L", 50}, {"XC", 90}, {"C", 100}, {"CD", 400}, {"D", 500}, {"CM", 900}, {"M", 1000}, {"Mↁ", 4000}, {"ↁ", 5000}, {"Mↂ", 9000}, {"ↂ", 10000}, {"ↂↇ", 40000}, {"ↇ", 50000}, {"ↂↈ", 90000}, {"ↈ", 100000}};
    roman_vector rvec = {"ↈ","ↂↈ","ↇ", "ↂↇ","ↂ", "Mↂ","ↁ","Mↁ","M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int pos = 0;
    this->roman = "";
    while (arabic > 0)
    {
        std::string key = rvec[pos];
        if (arabic >= rmap[key])
        {
            arabic -= rmap[rvec[pos]];
            roman += rvec[pos];
        }
        else
        {
            pos++;
        }
    }
}

std::string Roman::getRoman(){
    return roman;
}