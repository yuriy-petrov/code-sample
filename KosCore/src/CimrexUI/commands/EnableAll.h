#ifndef ENEBLEALL_H
#define ENEBLEALL_H

#include "ICommand.h"
#include <QStringList>

class EnableAll : public ICommand
{
public:
    EnableAll(QStringList keys);
    virtual ~EnableAll();

    virtual void exec();
private:
    QStringList _keys;
};

#endif // ENEBLEALL_H
