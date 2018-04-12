#ifndef TCONSOLE_H
#define TCONSOLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>

#include "TObserver.h"
#include "TCommandProcessor.h"



/*!
    Класс для реализации приёма данных из консоли
*/
class TConsole
{
    public:
        TConsole(size_t bulk_size);
        virtual ~TConsole();

        void commonInput(std::string);

    protected:

    private:
        TCommandProcessor           _processor;
        std::mutex                  _mutex;

};


using TConsolePtr = std::shared_ptr<TConsole>;
#endif // TCONSOLE_H
