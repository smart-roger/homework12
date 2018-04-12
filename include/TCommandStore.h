#ifndef TCOMMANDSTORE_H
#define TCOMMANDSTORE_H

#include <iostream>
#include <string>
#include <vector>
#include <mutex>

#include <algorithm>

static std::mutex mutexOut;

/*!
    Класс для хранения команд и их вывода.
*/
class TCommandStore
{
    public:
        TCommandStore();
        TCommandStore(size_t size);
        virtual ~TCommandStore();

        //  Добавление команды в хранилище
        void addCommand(const std::string& strCommand);
        //  Вывод команд в поток
        void printCommands(std::ostream& out = std::cout) const;
        //  Очистка хранилища
        void clear();
        //  Число команд в хранилище
        size_t size() const;
        //  Пустой ли массив
        bool empty()    const;

    protected:

    private:
        //  Контейнер, хранящий команды
        std::vector<std::string> _commands;
};

#endif // TCOMMANDSTORE_H
