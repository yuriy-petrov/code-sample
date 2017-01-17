#ifndef DECREMENTCOMMAND_H
#define DECREMENTCOMMAND_H

#include "ICommand.h"

class DecrementCommand : public ICommand
{
public:
    DecrementCommand(QString value, int step);
    virtual ~DecrementCommand();

    virtual void exec();
private:
    QString _keyValue;
    int _step;
};


#endif // DECREMENTCOMMAND_H
