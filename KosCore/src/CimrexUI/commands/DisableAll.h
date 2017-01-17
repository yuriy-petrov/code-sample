#ifndef DISABLEALL_H
#define DISABLEALL_H

#include "ICommand.h"
#include <QStringList>

class DisableAll : public ICommand
{
public:
    DisableAll(QStringList keys);
    virtual ~DisableAll();

    virtual void exec();
private:
    QStringList _keys;
};

#endif // DISABLEALL_H
