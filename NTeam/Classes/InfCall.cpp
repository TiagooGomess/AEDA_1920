
#include "InfCall.h"
#include <iomanip>
#include <iostream>

using namespace std;

InfCall::InfCall(unsigned int id, unsigned int soccerPlayerId, Date arrived, Date left){
    this->id = id;
    this->soccerPlayerId = soccerPlayerId;
    this->arrived = arrived;
    this->left = left;
}

unsigned int InfCall::getId()
{
    return id;
}


unsigned int InfCall::getSoccerPlayerId()
{
    return soccerPlayerId;
}

Date InfCall::getDateArrived()
{
    return arrived;
}

Date InfCall::getDateLeft()
{
    return left;
}

void InfCall::setDateArrived(Date date)
{
    arrived = date;
}

void InfCall::setDateLeft(Date date)
{
    left = date;
}

void InfCall::info()
{
    ostringstream o_stream1, o_stream2;
    o_stream1 << left;
    o_stream2 << arrived;
    cout << std::left << setw(5) << id <<
         std::left << setw(30) << soccerPlayerId << std::left << setw(20) << o_stream1.str() <<
         std::left << setw(20) << o_stream2.str() << endl;
}

void InfCall::header()
{
    std::cout << std::endl;
    std::cout << std::left << std::setw(5) << "ID" << std::left << std::setw(30) << "Soccer Player ID"
              << std::left << std::setw(20) << "Arrived Date" << std::left << std::setw(20) << "Left Date" << std::endl;
    std::cout << "===================================================================================================================================================================================================================" << std::endl;
}
