#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <sstream>
#include "SalesRecord.hpp"
#include <limits>
int main()
{
    // std::string input;
    // RecordRow *record = new RecordRow("Europe","Russia","Office Supplies","Offline","L","5/2/2014",341417157,"5/8/2014",1779,651.21,524.96,1158502.59,933903.84,224598.75);
    // std::cout << record->getCountry() << std::endl;
    // delete record;
    int maxRecords = 1 ? std::numeric_limits<int>::max() : 1000;
    int t = time(NULL);
    SalesRecord *record = new SalesRecord("DANGER/DANGER-1500000SalesRecords.csv",maxRecords);
    std::cout << (double)(time(NULL)-t) << "s to load "<< record->size() << "rows of data" << std::endl;
    record->start();
    delete record;
    return 0;
}
