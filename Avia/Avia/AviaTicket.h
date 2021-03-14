#pragma once
#include <algorithm>
#include <iostream>
#include <list>
#include <fstream>
#include"Date.h"

class AviaTicket;

class WorkWithFile
{
public:

	static std::list<AviaTicket> loadFromList(const std::string& fileName);
	static void loadInList(const std::string& fileName, std::list<AviaTicket> list);

};

class AviaTicket
{
public:
	AviaTicket(const std::string& fullName = "Null n.n.", const Date& date = {1,1,100}, const std::string& destination = "null", const size_t& fligthNumber = 0) {
		setFullName(fullName);
		setDate(date);
		setDestination(destination);
		setFligthNumber(flightNumber);
	}
	void setFullName(const std::string& fullName)
	{
		size_t found = fullName.find(".");
		if (found != std::string::npos && fullName.size() < SIZE_CHAR_ARRAY+1&&!fullName.empty()) {
			found = fullName.find(".", found + 1);
			if (found != std::string::npos) {
				strcpy_s(this->fullName,fullName.c_str());
				return;
			}
		}
			throw "Bad full name";
	}
	void setDate(const Date& date)
	{
		this->date.setDate(date.getDay(), date.getMonth(), date.getYear());
	}
	void setDestination(const std::string& destination) {
		if (!destination.empty() && destination.size() < SIZE_CHAR_ARRAY + 1) {
			strcpy_s(this->destination, destination.c_str());
			return;
		}
		throw "Bad destination";
	}
	void setFligthNumber(const size_t& flightNumber) {
		if (flightNumber > 0) {
			this->flightNumber = flightNumber;
			return;
		}
		throw "bad fligth number";
	}
	const size_t& getFligthNumber()const {
		return flightNumber;
	}
	const std::string& getFullName() const {
		return (std::string)fullName;
	}
	const std::string& getDistination() const {
		return (std::string)destination;
	}
	const Date& getDate() const { 
		return date; 
	}
	const bool operator==(const std::string& obj) const {
		return this->fullName == obj;
	}
	friend std::ostream& operator<<(std::ostream& os,const  AviaTicket& obj);
private:
	static const size_t SIZE_CHAR_ARRAY = 256;
	char destination[SIZE_CHAR_ARRAY];
	size_t flightNumber;
	char fullName[SIZE_CHAR_ARRAY];
	Date date;
};

class AccountingApplications 
{
public:
	enum class Method_Sort{BY_FLIFHT_NUMBER,BY_DISTINATION};
	AccountingApplications(const std::string& fileName = "datebase.dat") {
		std::list<AviaTicket> it = WorkWithFile::loadFromList(fileName);
		for (auto& i : it)
		{
			applications.push_back(i);
		}
	}
	void deleteByFullName(const std::string& fullName) {

		auto it = std::find(applications.begin(), applications.end(),fullName);
		if (it != applications.end()) {
			applications.erase(it);
		}
	}
	void addInAppplications(const AviaTicket& ticket) {
		applications.push_back(ticket);
	}
	const void print(){
		size_t index = 1;
		for (auto& i : applications)
		{
			std::cout << index;
			std::cout<<") " << i<<std::endl;
			++index;
		}
	}
	size_t getCountTicket() {
		return applications.size();
	}
	void clear() {
		applications.clear();
	}
	void sort(Method_Sort method) {
		if (method == Method_Sort::BY_DISTINATION) {
			applications.sort([](const AviaTicket& objFirst,const AviaTicket& objSecond) {
				return objFirst.getDistination() == objSecond.getDistination();
				});
		}
		else if (method == Method_Sort::BY_FLIFHT_NUMBER) {
			applications.sort([](const AviaTicket& objFirst, const AviaTicket& objSecond) {
				return objFirst.getFligthNumber() == objSecond.getFligthNumber();
				});
		}
	}
	~AccountingApplications()
	{
		WorkWithFile::loadInList(fileName,applications);
	}
private:
	std::string fileName;
	std::list<AviaTicket> applications;
};

