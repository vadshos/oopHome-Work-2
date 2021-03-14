#include <iostream>
#include"AviaTicket.h"

int main()
{
    AccountingApplications data;
   std::cout<< data.getCountTicket();
   data.addInAppplications(AviaTicket("Shostak V.V.", { 14,03,2021 }, "Rivne-Kiev", 1));
    data.deleteByFullName("Shostak V.V.");
    data.print();
    std::cout << data.getCountTicket();

}

