#include "LineUpCommand.h"
#include <QDebug>

LineUpCommand::LineUpCommand(int step)
    :   ICommand(),
      _step(step)
{

}

void LineUpCommand::exec()
{
    QPair<int, int> pair = ctx()->currentRows();
    qDebug() << "PAIR" << pair << "avRows" << ctx()->avaiableRows();
    if ( (pair.second + _step) <= ctx()->avaiableRows() ) {
        pair.first = pair.first + _step;
        pair.second = pair.second + _step;
    } else {
        pair.first = pair.second;
        pair.second = pair.second + _step;
    }
    ctx()->setUpRows(pair);
    qDebug() << "change to " << pair;
}
