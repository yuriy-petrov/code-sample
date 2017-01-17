#ifndef LINEDOWNCOMMAND_H
#define LINEDOWNCOMMAND_H

#include "ICommand.h"

class LineDownCommand : public ICommand
{
public:
    LineDownCommand(int step);

    virtual ~LineDownCommand(){}

    virtual void exec();
private:
    int _step;
};

#endif // LINEDOWNCOMMAND_H
