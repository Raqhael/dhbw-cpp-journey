#include <iostream>
#include <vector>
#include <fstream>
#include <string>   
#include <functional>
#define PRINTLINE std::cout << "----------------------------------------" << std::endl;
typedef struct Entry
{
    std::string surname;
    std::string name;
    std::string telephone;
} Entry_t;

typedef struct Telefonbuch
{
    std::vector<Entry *> entries;
} Telefonbuch_t;

void startUI(Telefonbuch_t *tb);
Entry *searchEntry(Telefonbuch *tb, std::string surname);
Entry *searchEntryByNumber(Telefonbuch *tb, std::string telephone);
void addEntry(Telefonbuch *tb, std::string surname, std::string name, std::string telephone);
int showMenu(Telefonbuch *tb);
void loadEntries(Telefonbuch *tb, std::string filename);
void saveEntries(Telefonbuch *tb, std::string filename);
void split(const std::string &s, char c,std::vector<std::string> &v);

int main()
{
    Telefonbuch_t *tb = new Telefonbuch_t;
    startUI(tb);
    delete tb;
}

void loadEntries(Telefonbuch *tb, std::string filename){
    std::ifstream file(filename);
    std::string line;
    while(std::getline(file, line)){
        std::vector<std::string> v;
        split(line, ';', v);
        addEntry(tb, v[0], v[1], v[2]);
    }
}

void saveEntries(Telefonbuch *tb, std::string filename)
{
    std::ofstream file;
    file.open(filename);
    for (int i = 0; i < tb->entries.size(); i++)
    {
        file << tb->entries[i]->surname << ";" << tb->entries[i]->name << ";" << tb->entries[i]->telephone << std::endl;
    }
}

int showMenu(Telefonbuch *tb)
{
    PRINTLINE
    std::cout << "1. Suche nach Namen" << std::endl;
    std::cout << "2. Suche nach Telefonnummer" << std::endl;
    std::cout << "3. Neuer Eintrag" << std::endl;
    std::cout << "4. Alle anzeigen" << std::endl;
    std::cout << "5. Beenden" << std::endl;
    PRINTLINE
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
    {
        std::cout << "Suche nach Namen:" << std::endl;
        std::cout << "Nachname: ";
        // Read in the surname and search tb for it
        std::string surname;
        std::cin >> surname;
        Entry *e = searchEntry(tb, surname);
        if (e != NULL)
        {
            PRINTLINE
            std::cout << "Gefundener Eintrag:" << std::endl;
            std::cout << e->surname << " " << e->name << " " << e->telephone << std::endl;
        }
        else
        {
            std::cout << "Eintrag nicht gefunden" << std::endl;
        }
    }
    break;
    case 2:
    {
        std::cout << "Suche nach Telefonnummer:" << std::endl;
        // Read in the telephone number and search tb for it
        std::string telephone;
        std::cout << "Telefonnummer: ";
        std::cin >> telephone;
        Entry *e = searchEntryByNumber(tb, telephone);
        if (e != NULL)
        {
            std::cout << "Gefundener Eintrag:" << std::endl;
            std::cout << e->surname << " " << e->name << " " << e->telephone << std::endl;
        }
        else
        {
            std::cout << "Eintrag nicht gefunden" << std::endl;
        }
    }
    break;
    case 3:
    {
        std::cout << "Neuer Eintrag:" << std::endl;
        // Read in the surname, name and telephone number and add it to tb
        std::string surname;
        std::cout << "Vorname: ";
        std::cin >> surname;
        std::string name;
        std::cout << "Nachname: ";
        std::cin >> name;
        std::string telephone;
        std::cout << "Telefonnummer: ";
        std::cin >> telephone;
        addEntry(tb, surname, name, telephone);
    }
    break;
    case 4:
    {
        // Print all entries in tb
        for (int i = 0; i < tb->entries.size(); i++)
        {
            std::cout << tb->entries[i]->surname << " " << tb->entries[i]->name << " " << tb->entries[i]->telephone << std::endl;
        }
    }
    break;
    case 5:
    {
        std::cout << "Beenden" << std::endl;
        return 1;
    }
    break;
    default:
    {
        std::cout << "Falsche Eingabe" << std::endl;
        exit(0);
        break;
    }
    }
    return 0;
}

void startUI(Telefonbuch_t *tb)
{
    loadEntries(tb, "Telefonbuch.txt");
    while (std::cin.good() && !showMenu(tb))
        ;
    saveEntries(tb, "Telefonbuch.txt");
}
void addEntry(Telefonbuch *tb, std::string surname, std::string name, std::string telephone)
{
    Entry_t *e = new Entry_t;
    e->surname = surname;
    e->name = name;
    e->telephone = telephone;
    tb->entries.push_back(e);
}

Entry *searchEntry(Telefonbuch *tb, std::string surname)
{
    for (int i = 0; i < tb->entries.size(); i++)
    {
        if (tb->entries[i]->surname == surname)
        {
            return tb->entries[i];
        }
    }
    return nullptr;
}

Entry *searchEntryByNumber(Telefonbuch *tb, std::string telephone)
{
    for (int i = 0; i < tb->entries.size(); i++)
    {
        if (tb->entries[i]->telephone == telephone)
        {
            return tb->entries[i];
        }
    }
    return nullptr;
}

void split(const std::string &s, char c,std::vector<std::string> &v)
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
