#ifndef PAGE_H
#define PAGE_H

#include <QMap>
#include <QString>
#include <QDebug>
#include <QMetaType>

#include "Action.h"
#include "HTMLTemplate.h"


class Page;

typedef QMap<QString, Page*> PagesMap;
typedef QMap<QString, Action*> ActionsMap;

class IPageCreatorInterface
{
public:
    virtual void addChildPage(Page* page) = 0;
    virtual void addAction(Action* action) = 0;

protected:
    virtual ~IPageCreatorInterface(){}
    IPageCreatorInterface(){}

private:

};

class IContextCommand;

class Page: public IPageCreatorInterface
{
public:
    Page(Page* parentPage = 0, QString id = QString("none"));
//    Page(const Page& page);
    void runActionInContext(QString& command, IContextCommand* ctx);
    QString html();
    const QString id() const;
    virtual void addChildPage(Page* page);
    virtual void addAction(Action* action);
    void setUpTemplate(QString filePath);
    bool isChild() const;
    Page* parentPage() const;
    bool hasNext() const;
    Page* childPageByName(QString& name);
    ~Page();
    QVariantHash keyMap();
    QVariantHash tmpKeyMap();
    void flushTmpKey();
    void updateValueForKey(QString key, QVariant value);
    void updateTempValueForKey(QString key, QVariant value);
    static void showStructure(Page* page);

    void nextKey();
    void previosKey();
    QString currentSelectedKey();

    int rowsInTempalte();
    int avRows();
protected:

private:
    void runAction(Action* action);

    QString _id;
    PagesMap _childPages;
    ActionsMap _actions;

    Page* _parentPage;
    HTMLTemplate* _htmlTemplate;

    QVariantHash _keyMap;
    QVariantHash _tempMap;

    QStringList _availableKeys;
    int _currentIndex;

    int _rows;
    int _avRows;
};

// TODO: Запилить конструктор копирования кошерный
//Q_DECLARE_METATYPE(Page)

//QDebug operator<< (QDebug d, const Page &page);
//QDebug operator<<(QDebug d, Page* page);

#endif // PAGE_H
