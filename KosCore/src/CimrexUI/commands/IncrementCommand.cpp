#include "IncrementCommand.h"

#include "Page.h"
#include <QDebug>

IncrementCommand::IncrementCommand(int step)
    : ICommand(),
      _step(step)
{
}

IncrementCommand::~IncrementCommand()
{

}

void IncrementCommand::exec()
{
    qDebug() << "CURRENTKEY" << ctx()->currentPage()->currentSelectedKey();
    QVariant value = ctx()->valueForKey(ctx()->currentPage()->currentSelectedKey());
    int val = value.toInt() + _step;
    ctx()->changeTmpValueForKey(ctx()->currentPage()->currentSelectedKey(), val);
}
