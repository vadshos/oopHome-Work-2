#pragma once
#include <iostream>
#include<map>
#include<vector>
#include<fstream>
#include<string>



class CountyList
{
public:
	enum class ACHION_OUTPUT { ONLY_CITY,ONLY_COUNTRY,ALL};
	enum class ACHION_ADD { CITY,COUTRY, ALL};
	enum class ERASE_ACHION{CITY,COUTRY};
	bool erase(const std::string& Country = "NULL", const  std::string& City = "NULL", ERASE_ACHION achion = ERASE_ACHION::COUTRY);	
	void print(ACHION_OUTPUT achion = ACHION_OUTPUT::ALL);
	CountyList();
	void addInMap(std::pair<std::string, std::vector<std::string>> temp);
	void addCountryAndCity(const std::string& Country = "NULL", const  std::string& City = "NULL",ACHION_ADD achion = ACHION_ADD::ALL);
	size_t countCity() const;
	bool find(const std::string& Country = "NULL",const  std::string& City = "NULL");	
	bool changeNameCity(const std::string& Country, std::string CityOld, const std::string& CityNew);
	~CountyList();
private:
	std::map<std::string, std::vector<std::string>>country;

};

inline bool CountyList::erase(const std::string& Country, const std::string& City, ERASE_ACHION achion)
{
	if (achion == ERASE_ACHION::COUTRY )
	{
		country.erase(Country);
		return true;
	}
	else if (achion == ERASE_ACHION::CITY && find(Country, City)) {
		auto it  = std::find(country[Country].begin(), country[Country].end(), City);
		if (it != country[Country].end()) {
			country[Country].erase(it);
		}
	}
	return false;
}

inline void CountyList::print(ACHION_OUTPUT achion)
{
	for (auto& i : country)
	{
		if ((int)achion == 1 or (int)achion == 2)
		{
			std::cout << "-----------------------" << std::endl;
			std::cout<<i.first<<std::endl;
		}
		if((int)achion == 0 or (int)achion == 2)
		for (auto& v : i.second)
		{
			std::cout << v<<std::endl;
		}
	}
}

inline CountyList::CountyList()
{
	std::pair<std::string, std::vector<std::string>> temp;
	std::ifstream in("datebase.txt");
	if (in)
	{
		std::string Coutry = "Country";
		std::string City = "";
		while (!in.eof())
		{
			getline(in, Coutry);
			if (Coutry == "****") {
				country.insert(temp);
				getline(in, Coutry);
				if (Coutry == "") {
					break;
				}
				temp.first = Coutry;
				temp.second.clear();
			}
			else {
				temp.first = Coutry;
			}
			getline(in, City);
			temp.second.push_back(City);				
		}
		country.insert(temp);
	}
}

inline void CountyList::addInMap(std::pair<std::string, std::vector<std::string>> temp)
{
	country.insert(temp);
}

inline void CountyList::addCountryAndCity(const std::string& Country, const std::string& City, ACHION_ADD achion)
{
	if (achion == ACHION_ADD::ALL) {
		if (!find(Country, City)&&City.empty()) 
			return;	
	}
	else if (achion == ACHION_ADD::COUTRY) {
		country[Country];
		return;
	}
	else if (achion == ACHION_ADD::CITY) {
		auto it = country.find(Country);
		if(it == country.end()){
			std::cout << "This Country didn't found" << std::endl;
			return;
		}
	}
	if (!find(Country, City))
		country[Country].push_back(City);
}

inline size_t CountyList::countCity() const
{
	size_t count = 0;
	for (auto& i : country)
	{
		count = i.second.size();
	}
	return size_t();
}

inline bool CountyList::find(const std::string& Country, const std::string& City)
{
	auto it = country.find(Country);
	if (it == country.end()) {
		return false;
	}
	else {
		auto it = std::find(country[Country].begin(), country[Country].end(), Country);
		if(it != country[Country].end())
		return true;	
	}
	return false;
}

inline bool CountyList::changeNameCity(const std::string& Country,  std::string CityOld,const std::string& CityNew)
{
	if (!find(Country, CityOld))
	return false;
	else {
		auto it = country.find(Country);
		size_t index = 0;
		erase(CityOld);
		country[Country].push_back(CityNew);
	}
}

inline CountyList::~CountyList()
{
	std::ofstream out("datebase.txt");
	if (!out)
	{
		std::cerr << "Error opening for writing\n";
		return;
	}
	for (auto i : country)
	{
		for (auto& v: i.second)
		{
			out<<i.first<<std::endl;
			out << v << std::endl;
		}
		out << "****" << std::endl;

	}
	out.close();
}
