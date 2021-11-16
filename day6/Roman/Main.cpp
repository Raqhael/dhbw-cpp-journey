#include <iostream>

#include <vector>
#include <map>

typedef std::map<std::string, int> arabic_roman_map;
typedef std::vector<std::string> roman_vector;
std::string arabicToRoman(int arabic)
{
    arabic_roman_map rmap = {{"I", 1}, {"IV", 4}, {"V", 5}, {"IX", 9}, {"X", 10}, {"XL", 40}, {"L", 50}, {"XC", 90}, {"C", 100}, {"CD", 400}, {"D", 500}, {"CM", 900}, {"M", 1000}};
    roman_vector rvec = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int pos = 0;
    std::string roman = "";
    while (arabic > 0)
    {
        if (arabic >= rmap[rvec[pos]])
        {
            arabic -= rmap[rvec[pos]];
            roman += rvec[pos];
        }
        else
        {
            pos++;
            if (pos >= rvec.size())
            {
                return "POS TOO BIG";
            }
        }
    }

    return roman;
}

int main()
{

    std::cout << arabicToRoman(14) << std::endl;
}
