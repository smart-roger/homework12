#ifndef TCOMMANDPROCESSOR_H
#define TCOMMANDPROCESSOR_H

#include "TObserver.h"
#include "TCommandStore.h"

#include <vector>
#include <string>
#include <ctime>
#include <fstream>
/*!
    Обработчик для потока команд "нулевого уровня
*/
class TCommandProcessor : public TObserver
{
    public:
        TCommandProcessor(size_t bulkSize);
        virtual ~TCommandProcessor();
        //  Добавление новой команды в хранилище
        void newCommand(const std::string& command);

    protected:

        virtual void handleCommand(const std::string& command) override;
        virtual void startBlock()   override;
        virtual void finishBlock()  override;

        void logBlock();

    private:
        //  Размер блока для вывода
        size_t  _bulkSize;
        //  Счётчик открытых блоков
        size_t  _blockCounter;

        std::time_t     _timeStart;
        //  Хранилище для команд
        TCommandStore   _store;
};

#endif // TCOMMANDPROCESSOR_H
