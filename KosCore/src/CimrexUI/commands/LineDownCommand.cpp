#include "LineDownCommand.h"

#include <QDebug>

LineDownCommand::LineDownCommand(int step)
    :   ICommand(),
      _step(step)
{

}

void LineDownCommand::exec()
{
    QPair<int, int> pair = ctx()->currentRows();
    qDebug() << "PAIR" << pair << "avRows" << ctx()->avaiableRows();
    if ( (pair.first - _step) > 0 ) {
        pair.first = pair.first - _step;
        pair.second = pair.second - _step;
    } else {
        pair.first = 1;
        pair.second = ctx()->rows();
    }
    ctx()->setUpRows(pair);
    qDebug() << "change to " << pair;
}
