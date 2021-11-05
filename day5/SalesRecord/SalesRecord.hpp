#ifndef SALESRECORD_HPP_GUARD
#define SALESRECORD_HPP_GUARD
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "RecordRow.hpp"
//Region,Country,Item Type,Sales Channel,Order Priority,Order Date,Order ID,Ship Date,Units Sold,Unit Price,Unit Cost,Total Revenue,Total Cost,Total Profit
class SalesRecord {
    private:
    // Source of using this type of Vector+Pointer construction:
    // https://stackoverflow.com/a/18995565/14379859
        std::vector<std::shared_ptr<RecordRow>> *records;
        int capacity;
    public:
        SalesRecord(std::string filename, int cap);
        SalesRecord(const SalesRecord  &) ;
        void start();
        ~SalesRecord();
        void totalProfit(std::string filter);
        void proportionOfItemTypes(std::string filter, bool found = false);
        void mostPopularItem(bool first = true);
        void onlineOfflineProportion(bool first = true);
        int size();
};
#endif