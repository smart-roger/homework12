#ifndef TBLOCKPROCESSOR_H
#define TBLOCKPROCESSOR_H

#include "TObserver.h"
#include "TCommandStore.h"
#include <ctime>
#include <fstream>

class TBlockProcessor : public TObserver
{
    public:
        TBlockProcessor();
        virtual ~TBlockProcessor();

    protected:
        virtual void handleCommand(const std::string& command) override;
        virtual void startBlock()   override;
        virtual void finishBlock()  override;

        void logBlock();

    private:
        size_t          _blockCounter;
        std::time_t     _timeStart;
        TCommandStore   _store;
};

#endif // TBLOCKPROCESSOR_H
