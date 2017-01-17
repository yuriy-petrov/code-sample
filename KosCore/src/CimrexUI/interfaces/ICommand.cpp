#include "ICommand.h"

ICommand::ICommand()
    :   _ctx(0)
{
}

ICommand::~ICommand()
{

}

void ICommand::setContext(IContextCommand *ctx)
{
    _ctx = ctx;
}

IContextCommand *ICommand::ctx()
{
    return _ctx;
}

