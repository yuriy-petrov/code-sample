#ifndef INVERTCOMMAND_H
#define INVERTCOMMAND_H

#include "ICommand.h"

class InvertCommand : public ICommand
{
public:
    InvertCommand(QString key);
    virtual ~InvertCommand();

    virtual void exec();
private:
    QString _key;
};

#endif // INVERTCOMMAND_H
