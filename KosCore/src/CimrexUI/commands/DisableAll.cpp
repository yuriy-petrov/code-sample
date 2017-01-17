#include "DisableAll.h"

DisableAll::DisableAll(QStringList list)
    : ICommand(),
      _keys(list)
{

}


DisableAll::~DisableAll()
{

}


void DisableAll::exec()
{
    qDebug() << "exec disable command";
    QString key;
    foreach (key, _keys) {
        ctx()->changeValueForKeyInModel(key, false);
    }
}
