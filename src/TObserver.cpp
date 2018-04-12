#include "../include/TObserver.h"

TObserver::TObserver()
{
    //ctor
}

TObserver::~TObserver()
{
    //dtor
}

void TObserver::parseCommand(const std::string& input){
    //  ��� ���� ������ ���� ������ �������� ������? ���������� ��� ����������?!
    if(input.empty())   handleCommand(input);
    else switch(input.at(0)){
            case charType::blockStart : {startBlock(); break;}
            case charType::blockFinish : {finishBlock(); break;}
            default: handleCommand(input);
        }
}
