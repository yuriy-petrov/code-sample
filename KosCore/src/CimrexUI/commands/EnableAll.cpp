#include "EnableAll.h"

EnableAll::EnableAll(QStringList list)
    : ICommand(),
      _keys(list)
{

}

EnableAll::~EnableAll()
{

}

void EnableAll::exec()
{
    qDebug() << "exec enable command";
    QString key;
    foreach (key, _keys) {
        ctx()->changeValueForKeyInModel(key, true);
    }
}

