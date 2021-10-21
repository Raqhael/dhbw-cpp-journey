#include <iostream>
#include <vector>

typedef struct en{
    std::string name;
    std::string surname;
    std::string telephone;
    std::string email;
} Entry;
typedef struct Telefonbuch{
    std::vector<Entry *> entries;
};

Entry searchEntry(Telefonbuch *tb, std::string name);
void addEntry(Telefonbuch *tb, std::string name, std::string surname, std::string number, std::string email) ;

int main(){
    Telefonbuch tb;
    addEntry(&tb, "Max", "Mustermann", "0123456789", "max.mustermann@muster.com");
    addEntry(&tb, "hhh", "ghddgshgsd", "2904652", "rprhi@khk.de");
    addEntry(&tb, "Raphael", "Sack", "0123456789", "i20029@hb.dhbw-stuttgart.de");

    std::cout << searchEntry(&tb, "Max").telephone << std::endl;

    



}

Entry searchEntry(Telefonbuch *tb, std::string name){
    for(int i = 0; i < tb->entries.size(); i++){
        if(tb->entries[i]->name == name){
            return *tb->entries[i];
        }
    }
    return *new Entry();
}

void addEntry(Telefonbuch *tb, std::string name, std::string surname, std::string number, std::string email) {
    Entry e2e;
    e2e.name = name;
    e2e.email = email;
    e2e.telephone = number;
    e2e.surname = surname;
    tb->entries.push_back(&e2e);
}