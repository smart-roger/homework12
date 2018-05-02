#include "../include/TCommandProcessor.h"

TCommandProcessor::TCommandProcessor(size_t bulkSize):
    TObserver(),
    _bulkSize(bulkSize),
    _blockCounter(0),
    _store(bulkSize)
{

}

TCommandProcessor::~TCommandProcessor()
{
    flush();
}

void TCommandProcessor::flush(){
    //���� ������� ���� - ���� ������� ����������� �������
    if(!_store.empty()){
        _store.printCommands();
        logBlock();
        _store.clear();
    }
}

void TCommandProcessor::newCommand(const std::string& newCommand){
    handleCommand(newCommand);
}

void TCommandProcessor::startBlock(){
    if(0==_blockCounter && 0<_store.size()){
        _store.printCommands();
        logBlock();
        _store.clear();
    }
    ++_blockCounter;
}

void TCommandProcessor::finishBlock(){

    if(0<_blockCounter) --_blockCounter;
    //  ��� ������ ����������� ��� ��������� ����������?
    //else{}
}

void TCommandProcessor::handleCommand(const std::string& command){
        if(_store.empty())
            _timeStart = std::time(nullptr);

        _store.addCommand(command);

        if(_bulkSize == _store.size()){
            _store.printCommands(std::cout);
            logBlock();
            _store.clear();
        }
    //  ����� �������������� � ������ �����������.
    //  else{}

}

void TCommandProcessor::logBlock(){
    std::ofstream fileLog("bulk_"+std::to_string(_timeStart)+"_"+std::to_string(rand())+".log");
    _store.printCommands(fileLog);
}
