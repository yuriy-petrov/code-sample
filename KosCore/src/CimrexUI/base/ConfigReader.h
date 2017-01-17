#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QXmlStreamReader>
#include <QStringList>

class Page;
class Action;

class ConfigReader
{
public:
    ConfigReader(QString filePath = 0);
    bool read(QIODevice* device);
    Page* mainPage();
    QList<Action* > defaultActions();
    static QStringList pagesById();
private:
    void startRead();
    void readPage(Page* page);
    void readTeamplate(Page* page);
    void readAvailablePages(Page* page);
    void readAvailableActions(Page* page);
    void readAction(Page* page = 0);
    void readCommand(Action* action);
    void readDefaultActions();

    Page* createNewPage(Page* page);
    Action* createNewAction();
private:
    QXmlStreamReader _parser;

    QString _parrentXml;
    QString _currentXml;

    Page* _mainPage;
    QList<Action*> _defaultActions;
    static QStringList _pagesById;
};

#endif // CONFIGREADER_H
