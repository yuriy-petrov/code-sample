#ifndef ICOMMAND_H
#define ICOMMAND_H

#include "IContextCommand.h"

class ICommand
{
public:
    ICommand();
    virtual ~ICommand();
    void setContext(IContextCommand* ctx);
    virtual void exec() = 0;

protected:
    IContextCommand* ctx();
private:
    IContextCommand*_ctx;
};

#endif // ICOMMAND_H
