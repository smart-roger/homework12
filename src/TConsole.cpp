#include "../include/TConsole.h"

TConsole::TConsole(size_t bulk_size):_processor(bulk_size)
{
    //ctor
}

TConsole::~TConsole()
{
    //dtor
}

void TConsole::commonInput(std::string line){
        std::lock_guard<std::mutex> lock(_mutex);
        _processor.newCommand(line);
}

void TConsole::flush(){
    std::lock_guard<std::mutex> lock(_mutex);
    _processor.flush();
}
