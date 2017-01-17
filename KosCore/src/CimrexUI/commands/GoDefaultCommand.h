#ifndef GODEFAULTCOMMAND_H
#define GODEFAULTCOMMAND_H

#include "ICommand.h"

class GoDefaultCommand : public ICommand
{
public:
    GoDefaultCommand(QString pageId);
    virtual ~GoDefaultCommand();
    virtual void exec();
private:
    QString _defaultPage;
};

#endif // GODEFAULTCOMMAND_H
