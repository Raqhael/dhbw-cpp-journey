#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <map>
#include <algorithm>
// a Struct that holds the information of a row from the file ../SacramentocrimeJanuary2006.csv
typedef struct SacramentoRow
{
    std::string adress;
    int district;
    std::string beat;
    std::string grid;
    std::string crimedescr;
    int ucr_ncic_code;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    double latitude;
    double longitude;
} SacramentoRow_t;

void loadCSV(std::string fileName, std::vector<SacramentoRow_t> &rows);
void split(const std::string &s, char c, std::vector<std::string> &v);
void createMostFrequentCrimesReport(std::vector<SacramentoRow_t> &rows);
void createMostFrequentDistrictsReport(std::vector<SacramentoRow_t> &rows);
void createMultipleAdressReport(std::vector<SacramentoRow_t> &rows);

int main()
{
    std::vector<SacramentoRow_t> rows;
    loadCSV("./sss.csv", rows);
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Crimes Report, Sacramento 2006: " << std::endl;
    std::cout << "Commited crimes in 2006: " << rows.size() << std::endl;
    createMostFrequentCrimesReport(rows);
    createMostFrequentDistrictsReport(rows);
    createMultipleAdressReport(rows);
    std::cout << "---------------------------------------------" << std::endl;

}

void createMultipleAdressReport(std::vector<SacramentoRow_t> &rows)
{

    std::map<std::string, int> adressMap;
    for (int i = 0; i < rows.size(); i++)
    {
        adressMap[rows[i].adress]++;
    }
    std::cout << "Multiple Adress Report:" << std::endl;
    // Sorting-Alg, source: https://www.techiedelight.com/sort-map-values-cpp/
    std::vector<std::pair<std::string, int>> vec;
    std::copy(adressMap.begin(), adressMap.end(), std::back_inserter<std::vector<std::pair<std::string, int>>>(vec));
    std::sort(vec.begin(), vec.end(),
              [](const std::pair<std::string, int> &l, const std::pair<std::string, int> &r)
              {
                  if (l.second != r.second)
                  {
                      return l.second > r.second;
                  }

                  return l.first > r.first;
              });

    std::map<std::string, int>::iterator it;
    for (auto const &pair: vec) {
        if (pair.second == 1) break;
        std::cout << pair.second << ": " << pair.first << std::endl;
    }
}

void createMostFrequentDistrictsReport(std::vector<SacramentoRow_t> &rows)
{
    std::map<int, int> districts;
    for (int i = 0; i < rows.size(); i++)
    {
        districts[rows[i].district]++;
    }
    std::map<int, int>::iterator it;
    int max = 0;
    int district;
    for (std::map<int, int>::iterator it = districts.begin(); it != districts.end(); it++)
    {
        if (it->second > max)
        {
            max = it->second;
            district = it->first;
        }
    }
    std::cout << "The most dangerous district: " << district << " with " << max << " crimes" << std::endl;
}

void createMostFrequentCrimesReport(std::vector<SacramentoRow_t> &rows)
{

    std::map<std::string, int> crimeCount;
    for (int i = 0; i < rows.size(); i++)
    {
        std::string crime = rows[i].crimedescr;
        if (crimeCount.find(crime) == crimeCount.end())
        {
            crimeCount[crime] = 1;
        }
        else
        {
            crimeCount[crime]++;
        }
    }
    
    // Get the highest value in crimeCount
    int max = 0;
    std::string crime;
    for (std::map<std::string, int>::iterator it = crimeCount.begin(); it != crimeCount.end(); it++)
    {
        if (it->second > max)
        {
            max = it->second;
            crime = it->first;
        }
    }
    std::cout << "The most frequent crime is: " << crime << " with " << max <<  " occurrences" << std::endl;
}

void loadCSV(std::string fileName, std::vector<SacramentoRow_t> &rows)
{
    std::ifstream file;
    file.open(fileName);
    // std::cout << fileName << std::endl;
    std::string line;
    bool first = true;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (first)
            {
                first = false;
                continue;
            }
            SacramentoRow_t *Srow = new SacramentoRow_t;
            std::vector<std::string> v;
            split(line, ',', v);
            std::vector<std::string> datetime;
            split(v[0], ' ', datetime);
            std::vector<std::string> date;
            std::vector<std::string> time;
            split(datetime[0], '/', date);
            split(datetime[1], ':', time);
            v[3].erase(std::remove_if(v[3].begin(), v[3].end(), ::isspace), v[3].end());
            Srow->month = std::stoi(date[0]);
            Srow->day = std::stoi(date[1]);
            Srow->year = std::stoi(date[2]);
            Srow->hour = std::stoi(time[0]);
            Srow->minute = std::stoi(time[1]);
            Srow->adress = v[1];
            Srow->district = std::stoi(v[2]);
            if (v[3] == "")
            {
                Srow->beat = "N/A";
            }
            else
            {
                Srow->beat = std::stoi(v[3]);
            }
            Srow->beat = v[3];
            Srow->grid = v[4];
            Srow->crimedescr = v[5]; Srow->ucr_ncic_code = std::stoi(v[6]); Srow->latitude = std::stod(v[7]);
            Srow->longitude = std::stod(v[8]);
            rows.push_back(*Srow);
        }
    }
    file.close();
}

void split(const std::string &s, char c, std::vector<std::string> &v)
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
