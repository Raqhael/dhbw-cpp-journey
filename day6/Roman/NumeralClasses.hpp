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
    Roman(): roman(""){};
    std::string getRoman();
    friend std::ostream &operator<<(std::ostream &os, Roman const &r)
    {
        return os << r.roman;
    }
    friend std::istream &operator>>(std::istream &input, Roman &a)
    {
        input >> a.roman;
        return input;
    }
};

class Arabic
{
    int value;

public:
    Arabic(int value) : value(value){};
    Arabic() : value(0){};
    Arabic(std::string roman);

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
    friend std::ostream &operator<<(std::ostream &os, Arabic const &a)
    {
        return os << a.value;
    }
};

#endif