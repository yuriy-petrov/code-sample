#ifndef ACTION_H
#define ACTION_H

#include <QString>
#include <QList>
#include "ICommand.h"
#include "IContextCommand.h"

const QString DefaultKeyCode = "F_0";

class Action
{
public:
    Action(QString keyCode = DefaultKeyCode);
    const QString keyCode() const;

    void appendCommand(ICommand *cmd);
    void execChain();

    void setContext(IContextCommand* ctx);
private:

    QString _keyCode;
    QList<ICommand* > _cmdChain;
    IContextCommand* _ctx;
};

#endif // ACTION_H
