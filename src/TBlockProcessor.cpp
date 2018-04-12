#include "../include/TBlockProcessor.h"

TBlockProcessor::TBlockProcessor():
    TObserver(),
    _blockCounter(0),
    _timeStart(0),
    _store()
{
    //ctor
}

TBlockProcessor::~TBlockProcessor()
{
    //dtor
}

void TBlockProcessor::startBlock(){
    if(0==_blockCounter)
        _timeStart = std::time(nullptr);
    ++_blockCounter;
}

void TBlockProcessor::finishBlock(){

    if(0<_blockCounter) --_blockCounter;
    //  ��� ������ ����������� ��� ��������� ����������?
    //else{}

    if(0==_blockCounter){
            _store.printCommands();
            logBlock();
            _store.clear();
    }
}

void TBlockProcessor::handleCommand(const std::string& command){
    if(0<_blockCounter)
        _store.addCommand(command);

    //  ������� �������������� � ������ �����������.
    //  else{}
}

void TBlockProcessor::logBlock(){
    std::ofstream fileLog("bulk"+std::to_string(_timeStart)+".log");
    _store.printCommands(fileLog);
}
