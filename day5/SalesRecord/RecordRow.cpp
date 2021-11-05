#include "RecordRow.hpp"
#include "Split.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
RecordRow::RecordRow(std::string region, std::string country, std::string itemType, std::string salesChannel, std::string orderPriority, std::string orderDate, int orderId, std::string shipDate, int unitsSold, double unitPrice, double unitCost, double totalRevenue, double totalCost, double totalProfit){
this->region = region;
    this->country = country;
    this->itemType = itemType;
    this->salesChannel = salesChannel;
    this->orderPriority = orderPriority;
    std::vector <std::string> dateV;
    split(orderDate, dateV, '/');
    int orderMonth = stoi(dateV[0]);
    int orderDay = stoi(dateV[1]);
    int orderYear = stoi(dateV[2]);
    this->orderYear = orderYear;
    this->orderMonth = orderMonth;
    this->orderDay = orderDay;
    this->orderId= orderId;
    this->shipDate = shipDate;
    this->unitsSold = unitsSold;
    this->unitPrice = unitPrice;
    this->unitCost = unitCost;
    this->totalRevenue = totalRevenue;
    this->totalCost = totalCost;
    this->totalProfit = totalProfit;
}

RecordRow::~RecordRow(){
}

RecordRow::RecordRow(const RecordRow &other){
    this->region = other.region;
    this->country = other.country;
    this->itemType = other.itemType;
    this->salesChannel = other.salesChannel;
    this->orderPriority = other.orderPriority;
    this->orderYear = other.orderYear;
    this->orderMonth = other.orderMonth;
    this->orderDay = other.orderDay;
    this->orderId = other.orderId;
    this->shipDate = other.shipDate;
    this->unitsSold = other.unitsSold;
    this->unitPrice = other.unitPrice;
    this->unitCost = other.unitCost;
    this->totalRevenue = other.totalRevenue;
    this->totalCost = other.totalCost;
    this->totalProfit = other.totalProfit;
}

// All getters 
std::string RecordRow::getRegion(){
    return this->region;
}



std::string RecordRow::getCountry(){
    return this->country;
}

std::string RecordRow::getItemType(){
    return this->itemType;
}

std::string RecordRow::getSalesChannel(){
    return this->salesChannel;
}

std::string RecordRow::getOrderPriority(){
    return this->orderPriority;
}

int RecordRow::getOrderID(){
    return this->orderId;
}

std::string RecordRow::getShipDate(){
    return this->shipDate;
}

int RecordRow::getOrderYear(){
    return this->orderYear;
}
int RecordRow::getOrderMonth(){
    return this->orderMonth;
}
int RecordRow::getOrderDay(){
    return this->orderDay;
}

double RecordRow::getUnitPrice(){
    return this->unitPrice;
}

double RecordRow::getUnitCost(){
    return this->unitCost;
}

double RecordRow::getTotalRevenue(){
    return this->totalRevenue;
}

double RecordRow::getTotalCost(){
    return this->totalCost;
}

double RecordRow::getTotalProfit(){
    return this->totalProfit;
}