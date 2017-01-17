#include "DecrementCommand.h"

#include <QDebug>


DecrementCommand::DecrementCommand(QString value, int step)
    : ICommand(),
      _keyValue(value),
      _step(step)
{
}

DecrementCommand::~DecrementCommand()
{

}

void DecrementCommand::exec()
{
    QVariant value = ctx()->valueForKey(_keyValue);
    int val = value.toInt() - _step;
    ctx()->changeTmpValueForKey(_keyValue, val);
}
