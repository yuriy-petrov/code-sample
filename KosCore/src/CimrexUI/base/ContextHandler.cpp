#include "ContextHandler.h"
#include "ConfigReader.h"
#include "Page.h"
#include <QFile>
#include <QDir>
#include "CimrexModelBinding.h"

#include <QDebug>
ContextHandler::ContextHandler(Page *mainPage, QList<Action* > defaultActions)
    : IContextCommand(mainPage, defaultActions)
{
    qDebug() << "mkdir css" << QDir::current().mkdir("./css");
    qDebug() << "mkdir js" << QDir::current().mkdir("./js");
    qDebug() << "mkdir fonts" << QDir::current().mkdir("./fonts");
    qDebug() << "mkdir fonts" << QDir::current().mkdir("./i");

    qDebug() << "copy theme.css" << QFile::copy(":/css/main.css", QDir::currentPath() + "/css/main.css");
    qDebug() << "copy HM9.ttf" << QFile::copy(":/fonts/HM9.ttf", QDir::currentPath() + "/fonts/HM9.ttf");
    qDebug() << "COPY JS" << QFile::copy(":/i/arrow_h.png", QDir::currentPath() + "/i/arrow_h.png");
    qDebug() << "COPY JS" << QFile::copy(":/i/arrow_m.png", QDir::currentPath() + "/i/arrow_m.png");
    qDebug() << "COPY JS" << QFile::copy(":/i/clock.png", QDir::currentPath() + "/i/clock.png");
    qDebug() << "COPY JS" << QFile::copy(":/i/logo.png", QDir::currentPath() + "/i/logo.png");

    qDebug() << "COPY JS" << QFile::copy(":/js/gauge.js", QDir::currentPath() + "/js/gauge.js");
    qDebug() << "COPY JS JQuery" << QFile::copy(":/js/jquery.js", QDir::currentPath() + "/js/jquery.js");
    qDebug() << "COPY JS JQuery" << QFile::copy(":/js/main.js", QDir::currentPath() + "/js/main.js");

}

ContextHandler::~ContextHandler()
{
    QFile file(QDir::currentPath() + "/index.html");
//    qDebug() << "REMOVE" << file.remove();
}

QString ContextHandler::html()
{
    return currentPage()->html();
}

void ContextHandler::pressButtonById(QString &str)
{
//    qDebug() << "Click " << str  << " on page " << currentPage()->id();
//    qDebug() << "def act" << actions();
    Action* action;
    bool flag = true;
    QList<Action*> defListActions = defaultActions();
    qDebug() << defListActions.length();
    foreach (action, defListActions) {
        if ( action && (action->keyCode() == str) ) {
            flag = false;
            runDefaultAction(action);
        }
    }
    if (flag){
        currentPage()->runActionInContext(str, this);
    }
}

void ContextHandler::changeCurrentPage(Page *page)
{
    setCurrentPage(page);
}

void ContextHandler::changeValueByModelKey(QString key, QVariant value)
{
    changeValueForKey(key, value);
}

void ContextHandler::useThisBinder(CimrexModelBinding *bind)
{
    _binder = bind;
}

void ContextHandler::runDefaultAction(Action *action)
{
//    qDebug() << "Exec default actions";
    action->setContext(this);
    action->execChain();
}

void IContextCommand::setView(QWebView *view)
{
    _view = view;
}
