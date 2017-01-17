#ifndef ICONTEXTCOMMAND_H
#define ICONTEXTCOMMAND_H

#include <QWebView>
#include <QPair>

#include "AbstractEventLogElement.h"
class CimrexModelBinding;
class Page;
class Action;
class IContextCommand : public QObject
{
    Q_OBJECT
public:
    IContextCommand(Page* mainPage, QList<Action*> defaultActions);
    virtual ~IContextCommand();

    virtual Page* currentPage();
    virtual Page* childPageByName(QString& name);
    virtual void renderPage();
    virtual void updateView();
    void changeCurrentPage(Page* page, bool historyOff = false);
    void setView(QWebView* view);
    Page* previousPage();
    void resetToMainPage( bool historyOff = false);

    void changeValueForKey(QString key, QVariant value);
    void changeTmpValueForKey(QString key, QVariant value);
    void changeValueForKeyInModel(QString key, QVariant value);
    QVariant valueForKey(QString key);

    QPair<int, int> currentRows();
    void setUpRows(QPair<int, int> rows);
    int avaiableRows();
    int rows();

    CimrexModelBinding * cimrexModelBinding() const;

signals:
    void sendEventLog(AbstractEventLogElement * eventLogElement);

protected:
    void appendHistory(Page* page);
    Page *mainPage();
    QList<Action*> defaultActions();
    void setCurrentPage(Page* page);

    CimrexModelBinding* _binder;
private:
    void dropRows();
    void generateHtml();

    Page *_page;
    Page* _currentPage;
    QList<Action*> _defaultActions;
    QWebView* _view;

    QList<Page*> _pageHistory;
    int _first_row;
    int _last_row;
};

#endif // ICONTEXTCOMMAND_H
