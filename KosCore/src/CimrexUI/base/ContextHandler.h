#ifndef CONTEXTHANDLER_H
#define CONTEXTHANDLER_H

#include "IContextCommand.h"

class CimrexModelBinding;
class Page;
class QString;
class Action;
class ContextHandler: public IContextCommand
{
public:
    ContextHandler(Page* mainPage, QList<Action* > defaultActions);
    ~ContextHandler();
    QString html();
    void pressButtonById(QString& str);
    void changeCurrentPage(Page* page);

    void changeValueByModelKey(QString key, QVariant value);
    void useThisBinder(CimrexModelBinding* bind);
private:
    void runDefaultAction(Action* action);
};

#endif // CONTEXTHANDLER_H
