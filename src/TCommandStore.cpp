#include "../include/TCommandStore.h"

TCommandStore::TCommandStore():_commands()
{
    //ctor
}

TCommandStore::TCommandStore(size_t size): _commands()
{
    _commands.reserve(size);
}

TCommandStore::~TCommandStore()
{
    //dtor
}

void TCommandStore::addCommand(const std::string& strCommand){
    _commands.push_back(strCommand);
}

void TCommandStore::printCommands(std::ostream& out) const{

    if(!_commands.empty()){
        std::string output("bulk:");

        std::for_each(_commands.begin(), _commands.end(),
             [&output](auto command){output+= command+",";});
        output.resize(output.length()-1);
        std::lock_guard<std::mutex> lock(mutexOut);
        out << output << std::endl;
    };
}

void TCommandStore::clear(){
    _commands.clear();
}

size_t TCommandStore::size() const{
    return _commands.size();
}

bool TCommandStore::empty() const{
    return _commands.empty();
}
