#include "AviaTicket.h"

std::list<AviaTicket> WorkWithFile::loadFromList(const std::string& fileName)
{
	std::list<AviaTicket> list;
	AviaTicket ticket;
	int value;
	std::ifstream in(fileName, std::ios_base::binary);
	if (!in)
	{
		throw std::exception("Error opening file for read");
	}
	size_t index = 0;
	while (in.read((char*)&ticket, sizeof(ticket)))
	{
		list.push_back(ticket);
	}
	return list;
}

void WorkWithFile::loadInList(const std::string& fileName, std::list<AviaTicket> list)
{
	std::ofstream out("datebase.dat", std::ios_base::binary);
	if (!out)
	{
		std::cerr << "Error opening for writing\n";
		return;
	}
	for (auto& i : list)
	{
	out.write((char*)&i, sizeof(i));
	out.close();
	}
}

std::ostream& operator<<(std::ostream& os, const AviaTicket& obj)
{
	os << "Full name : " << obj.fullName << " Destination :  " << obj.destination << " Flight number : " << obj.flightNumber << " Date : " << obj.date;
	return os;
}
