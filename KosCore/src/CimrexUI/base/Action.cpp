#include "Action.h"
#include <QDebug>

Action::Action(QString keyCode)
    : _keyCode(keyCode),
      _ctx(0)
{
}

const QString Action::keyCode() const
{
    return _keyCode;
}

void Action::appendCommand(ICommand *cmd)
{
    _cmdChain.append(cmd);
}

void Action::execChain()
{
//    qDebug() << "Start Exec chain";
    ICommand *cmd;
    foreach (cmd, _cmdChain) {
        cmd->setContext(_ctx);
        cmd->exec();
    }
}

void Action::setContext(IContextCommand *ctx)
{
    _ctx = ctx;
}
