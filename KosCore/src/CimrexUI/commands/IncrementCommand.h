#ifndef INCREMENTCOMMAND_H
#define INCREMENTCOMMAND_H

#include "ICommand.h"

class IncrementCommand : public ICommand
{
public:
    IncrementCommand(int step);
    virtual ~IncrementCommand();

    virtual void exec();
private:
    int _step;
};

#endif // INCREMENTCOMMAND_H
