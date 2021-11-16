#ifndef RSA_NUMERALCLASS_HPP
#define RSA_NUMERALCLASS_HPP

#include <iostream>
#include <string>

class Roman
{
    std::string roman;

public:
    Roman(std::string roman) : roman(roman){};
    Roman(int arabic);
    std::string getRoman();
    friend std::ostream &operator<<(std::ostream &os, Roman const &r)
    {
        return os << r.roman;
    }
};

class Arabic
{
    int value;

public:
    Arabic(int value) : value(value){};
    Arabic() : value(0){};
    
    int getValue();
    operator Roman()
    {
        return Roman(this->value);
    }
    friend std::istream &operator>>(std::istream &input, Arabic &a)
    {
        input >> a.value;
        return input;
    }
};

#endif