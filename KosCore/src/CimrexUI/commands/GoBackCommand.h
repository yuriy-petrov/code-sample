#ifndef GOBACKCOMMAND_H
#define GOBACKCOMMAND_H

#include "ICommand.h"

class GoBackCommand : public ICommand
{
public:
    GoBackCommand();
    virtual ~GoBackCommand();
    virtual void exec();
};

#endif // GOBACKCOMMAND_H
