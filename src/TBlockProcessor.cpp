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
    //  „то должно происходить при нарушении синтаксиса?
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

    //   оманды обрабатываютс€ в другом наблюдателе.
    //  else{}
}

void TBlockProcessor::logBlock(){
    if(!_store.empty()){
        std::ofstream fileLog("bulk_"+std::to_string(_timeStart)+"_"+std::to_string(rand())+".log");
        _store.printCommands(fileLog);
    }
}
