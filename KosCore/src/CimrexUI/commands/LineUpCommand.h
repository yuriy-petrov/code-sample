#ifndef LINEUPCOMMAND_H
#define LINEUPCOMMAND_H

#include "ICommand.h"

class LineUpCommand : public ICommand
{
public:
    LineUpCommand(int step);

    virtual ~LineUpCommand(){}

    virtual void exec();
private:
    int _step;
};

#endif // LINEUPCOMMAND_H
