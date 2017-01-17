#ifndef GOTOCOMMAND_H
#define GOTOCOMMAND_H

#include "ICommand.h"

class GoToCommand: public ICommand
{
public:
    GoToCommand(QString pageId);
    virtual ~GoToCommand();

    virtual void exec();
private:
    QString _gotoPageId;
};

#endif // GOTOCOMMAND_H
