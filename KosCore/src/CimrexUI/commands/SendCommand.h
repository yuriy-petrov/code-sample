#ifndef SENDCOMMAND_H
#define SENDCOMMAND_H

#include "ICommand.h"

class SendCommand : public ICommand
{
public:
    SendCommand();
    virtual ~SendCommand();
    virtual void exec();
private:
    QStringList _keyList;
};

#endif // SENDCOMMAND_H
