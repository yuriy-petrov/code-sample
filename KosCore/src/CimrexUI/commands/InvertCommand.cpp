#include "InvertCommand.h"

#include <QDebug>

InvertCommand::InvertCommand(QString key)
    : ICommand(),
      _key(key)
{
}

InvertCommand::~InvertCommand()
{

}

void InvertCommand::exec()
{
    qDebug() << "exec Invert command";
    QVariant value = ctx()->valueForKey(_key);
    bool val = !value.toBool();
    ctx()->changeValueForKeyInModel(_key, val);
}
