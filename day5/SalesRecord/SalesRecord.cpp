#include "SalesRecord.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Split.hpp"
#include "RecordRow.hpp"
#include <ios>
#include <vector>
#include <map>
#include <memory>

#define RSA_HR std::cout << "==========================================================" << std::endl;

std::string bold(std::string s);
std::string italic(std::string s);

SalesRecord::SalesRecord(std::string filename, int cap)
{
    std::ifstream file(filename);
    std::string line;
    // Source of using shared_ptr for a Vector+Pointer construction:
    // https://stackoverflow.com/a/18995565/14379859
    this->records = new std::vector<std::shared_ptr<RecordRow>>;
    this->capacity = cap;
    bool first = true; // To skip csv header
    int linenumber = 0; // Counter for break after reaching the capacity
    if (file.is_open())
    {
        while (std::getline(file, line, '\n') && linenumber < this->capacity)
        {
            if (first)
            {
                first = false;
                continue;
            }
            std::vector<std::string> splitVector;
            split(line, splitVector);
            std::string region = splitVector[0];
            std::string country = splitVector[1];
            std::string itemType = splitVector[2];
            std::string salesChannel = splitVector[3];
            std::string orderPriority = splitVector[4];
            std::string orderDate = splitVector[5];
            int orderId = std::stoi(splitVector[6]);
            std::string shipDate = splitVector[7];
            int unitsSold = stoi(splitVector[8]);
            double unitPrice = stod(splitVector[9]);
            double unitCost = stod(splitVector[10]);
            double totalRevenue = stod(splitVector[11]);
            double totalCost = stod(splitVector[12]);
            double totalProfit = stod(splitVector[13]);
            std::shared_ptr<RecordRow> rr(new RecordRow(region, country, itemType, salesChannel, orderPriority, orderDate, orderId, shipDate, unitsSold, unitPrice, unitCost, totalRevenue, totalCost, totalProfit));
            this->records->push_back(rr);
            linenumber++;
        }
    }
}

SalesRecord::~SalesRecord()
{
    /**
     * Heap-allocated vector of shared_ptr<RecordRow>
     **/
    delete this->records;
}

/**
 * @brief Starts the Menu to query reports and print them
 */
void SalesRecord::start()
{
    RSA_HR
    std::cout << "Capacity: " << this->capacity << std::endl;
    std::cout << "Number of records: " << this->records->size() << std::endl;
    RSA_HR
    std::cout << "Always come back with typing in " << bold("exit") << std::endl;
    RSA_HR
    std::cout << "[" + bold("1") + "] Total Revenue by Country/Item/Channel" << std::endl;
    std::cout << "[" + bold("2") + "] Proportion of Item Types relative to a Region" << std::endl;
    std::cout << "[" + bold("3") + "] Most Popular Item of a Country" << std::endl;
    std::cout << "[" + bold("4") + "] Online/Offline proportions of a Country" << std::endl;
    std::cout << "> ";
    std::string choice;
    std::cin >> choice;
    std::vector<std::string> splitVector;
    split(choice, splitVector, ',');
    if (splitVector[0].compare("exit") == 0)
        return;
    int n = std::stoi(splitVector[0]);
    try
    {
        switch (n)
        {
        case 1:
            this->totalProfit(splitVector[1]);
            break;
        case 2:
            this->proportionOfItemTypes(splitVector[1]);
            break;
        case 3:
            this->mostPopularItem();
            break;
        case 4:
            this->onlineOfflineProportion();
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
            break;
        }
    }
    catch (std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
int SalesRecord::size(){
    return this->records->size();
}

/**
 * @brief Prints the total Profits by country/item/channel 
 * @param filter to either filter by country, item or channel
 */
void SalesRecord::totalProfit(std::string filter)
{
    if (!(filter.compare("country") == 0 || filter.compare("item") == 0 || filter.compare("channel") == 0))
    {
        throw std::invalid_argument("Invalid Argument, Usage: 1,[country|item|channel]");
    }
    std::cout << "Insert the " + bold(filter) + " you want to filter by: ";

    std::string filterValue;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, filterValue);
    if (filterValue.compare("exit") == 0)
        start();
    long double totalProfit = 0;
    for (long long unsigned int i = 0; i < this->records->size(); i++)
    {
        if (filter.compare("country") == 0)
        {
            if (filterValue.compare(this->records->at(i)->getCountry()))
            {
                totalProfit += this->records->at(i)->getTotalProfit();
            }
        }
        else if (filter.compare("item") == 0)
        {
            if (filterValue.compare(this->records->at(i)->getItemType()))
            {
                totalProfit += this->records->at(i)->getTotalProfit();
            }
        }
        else if (filter.compare("channel") == 0)
        {
            if (filterValue.compare(this->records->at(i)->getSalesChannel()))
            {
                totalProfit += this->records->at(i)->getTotalProfit();
            }
        }
    }
    std::cout << std::fixed << "Total Profit: " << totalProfit << " Moneten" << std::scientific << std::endl;
    start();
}
/**
 * @brief Prints the proportion of item types relative to a region
 * @param[in] region Region to filter by
 * @param[in] found to check if the region was found before
 */
void SalesRecord::proportionOfItemTypes(std::string filter, bool found)
{
    if (!found)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (long long unsigned int i = 0; i < this->records->size(); i++)
    {
        if (filter.compare(this->records->at(i)->getRegion()) == 0 || found)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        throw std::invalid_argument("Invalid Argument, Region: " + filter + " not found");
    }
    RSA_HR
    std::cout << "Insert the item type you want to filter by: ";
    std::string filterValue;
    std::getline(std::cin, filterValue, '\n');
    RSA_HR
    long itemCount = 0;
    long itemRegionCount = 0;
    for (long long unsigned int i = 0; i < this->records->size(); i++)
    {
        if (filterValue.compare(this->records->at(i)->getItemType()) == 0)
        {
            itemCount++;
            if (filter.compare(this->records->at(i)->getRegion()) == 0)
            {
                itemRegionCount++;
            }
        }
    }
    if (itemRegionCount == 0)
    {
        std::cout << "There were no " << filterValue << "'s sold in " << filter << "." << std::endl;
        proportionOfItemTypes(filter, true);
    }
    std::cout << "There were " << itemRegionCount << " " << filterValue << " being sold in " << filter << ". That means " << filter << " covered roughly " << std::fixed << (double) itemRegionCount / (double) itemCount * 100 << "% of all globally sold " << filterValue << "." << std::scientific << std::endl;
    proportionOfItemTypes(filter, true);
}

/**
 * @brief Prints the most popular item of a country
 * @param[in] first to check if the first time the function was called
 */
void SalesRecord::mostPopularItem(bool first)
{
    std::string country; 
    RSA_HR
    if (first)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
        std::cout << "Insert the country you want to filter by: ";
        std::getline(std::cin, country);
        if (country.compare("exit") == 0) start();
    // Get the most popular item from the given country parameter
    std::map<std::string, int> itemCounts;
    for (long long unsigned int i = 0; i < this->records->size(); i++)
    {
        if(this->records->at(i)->getCountry().compare(country))
        {
            continue; // Skip if the country is not the same
        }
        std::string item = records->at(i)->getItemType();

        if (itemCounts.find(item) == itemCounts.end())
        {
            itemCounts[item] = 1;
        }
        else
        {
            itemCounts[item]++;
        }
    }
    int max = 0;
    std::string item;
    for (std::map<std::string, int>::iterator it = itemCounts.begin(); it != itemCounts.end(); it++)
    {
        if (it->second > max)
        {
            max = it->second;
            item = it->first;
        }
    }
    std::cout << "The most popular Item-Type in " << country << " is: " << item << " with " << max << " records" << std::endl;
    mostPopularItem(false);
}
/**
 * @brief Prints the proportion of sales by channel
 * @param[in] first to check if the first time the function was called
 */
void SalesRecord::onlineOfflineProportion(bool first)
{
    if(first)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Insert the country you want to filter by: ";
    std::string country;
    std::getline(std::cin, country);
    if (country.compare("exit") == 0) start();

    // Look for the proportion of online sales in the given country
    long onlineCount = 0;
    long offlineCount = 0;
    for (long long unsigned int i = 0; i < this->records->size(); i++)
    {  
        if (country.compare(this->records->at(i)->getCountry()) == 0)
        {
            if (this->records->at(i)->getSalesChannel().compare("Online") == 0)
            {
                onlineCount++;
            }
            else
            {
                offlineCount++;
            }
        }
    }
    double  sum = onlineCount + offlineCount;
    if (sum == 0)
    {
        throw std::invalid_argument("Invalid Argument, Country: " + country + " not found");
    }
    std::cout << std::fixed << "There were " << onlineCount << " online sales in " << country << " and " << offlineCount << " offline sales in " << country << " (" << sum << " in total)" << ". That means " << country << " had " << std::fixed << ((double) onlineCount / sum * 100) << "% of online sales and " << ((double) offlineCount / sum) * 100  << "% of offline sales." << std::scientific << std::scientific <<  std::endl;
    onlineOfflineProportion(false);
}

std::string bold(std::string s)
{
    return "\033[1m" + s + "\033[0m";
}

std::string italic(std::string s)
{
    return "\033[3m" + s + "\033[0m";
}