#ifndef RECORDROW_HPP_GUARD
#define RECORDROW_HPP_GUARD

#include <iostream>
//Region,Country,Item Type,Sales Channel,Order Priority,Order Date,Order ID,Ship Date,Units Sold,Unit Price,Unit Cost,Total Revenue,Total Cost,Total Profit
class RecordRow{
private:
    std::string region;
    std::string country;
    std::string itemType;
    std::string salesChannel;
    std::string orderPriority;
    int orderYear;
    int orderMonth;
    int orderDay;
    int orderId;
    std::string shipDate;
    int unitsSold;
    double unitPrice;
    double unitCost;
    double totalRevenue;
    double totalCost;
    double totalProfit;
public:
    RecordRow(std::string region, std::string country, std::string itemType, std::string salesChannel, std::string orderPriority, std::string orderDate, int orderId, std::string shipDate, int unitsSold, double unitPrice, double unitCost, double totalRevenue, double totalCost, double totalProfit);
    ~RecordRow();
    RecordRow(const RecordRow &);
    std::string getRegion();
    std::string getCountry();
    std::string getItemType();
    std::string getSalesChannel();
    std::string getOrderPriority();
    int getOrderID();
    std::string getShipDate();
    int getUnitsSold();
    int getOrderYear();
    int getOrderMonth();
    int getOrderDay();
    double getUnitPrice();
    double getUnitCost();
    double getTotalRevenue();
    double getTotalCost();
    double getTotalProfit();

    // std::string setRegion();
    // std::string setCountry();
    // std::string setItemType();
    // std::string setSalesChannel();
    // std::string setOrderPriority();
    // int setOrderID();
    // std::string setShipDate();
    // int setUnitsSold();
    // int setOrderYear();
    // int setOrderMonth();
    // int setOrderDay();
    // double setUnitPrice();
    // double setUnitCost();
    // double setTotalRevenue();
    // double setTotalCost();
    // double setTotalProfit();
};



#endif