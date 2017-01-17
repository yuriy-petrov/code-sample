#include "Page.h"
#include <QFile>

Page::Page(Page* parentPage, QString id)
    :IPageCreatorInterface(),
      _id(id),
      _parentPage(parentPage),
      _htmlTemplate(new HTMLTemplate()),
      _currentIndex(0),
      _rows(0)
{
    QFile keyMapFile(":/templates/" + id + "/keys.map");
    if (!keyMapFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "KeyMap not readed" << id;
    }

    qDebug() << "Keys load for" << id;

    while (!keyMapFile.atEnd()) {
        QByteArray line = keyMapFile.readLine();
        QString key = QString(line).trimmed();
        if (key.contains("=====")) {
            break;
        }
        _keyMap.insert(key, 0);
        _availableKeys.append(key);
    }

    QString last = keyMapFile.readLine().trimmed();
    QStringList pair = last.split(":");
    if (pair.length()) {
        _rows = pair.first().toInt();
        _avRows = pair.last().toInt();
    }
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!KEY MAP" << _keyMap.keys() << _rows;
}

QVariantHash Page::keyMap()
{
    return _keyMap;
}

QVariantHash Page::tmpKeyMap()
{
    return _tempMap;
}

void Page::flushTmpKey()
{
    _tempMap.remove(currentSelectedKey());
}

void Page::updateValueForKey(QString key, QVariant value)
{
    _keyMap.insert(key, value);
}

void Page::updateTempValueForKey(QString key, QVariant value)
{
    _tempMap.insert(key, value);
}

void Page::nextKey()
{
    _currentIndex += 1;
    if (_currentIndex > _availableKeys.length() - 1) {
        _currentIndex = 0;
    }
}

void Page::previosKey()
{
    _currentIndex -= 1;
    if (_currentIndex == -1) {
        _currentIndex = _availableKeys.length() - 1;
    }
}

QString Page::currentSelectedKey()
{
    if (_currentIndex)
        return _availableKeys.at(_currentIndex);
    else
        return "none";
}

int Page::rowsInTempalte()
{
    return _rows;
}

int Page::avRows()
{
    return _avRows;
}

void Page::runActionInContext(QString &command, IContextCommand *ctx)
{
    if (_actions.isEmpty()) {
        return;
    }
    Action *action = _actions.value(command);
    if (action) {
        action->setContext(ctx);
        runAction(action);
    } else {
        qDebug() << "Action is not defined";
    }
}

void Page::runAction(Action* action)
{
    if (action) {
        qDebug() << "action is defined" << action->keyCode();
        action->execChain();
    } else {
        qDebug() << "action is not defined for key" << action->keyCode();
    }
}

QString Page::html()
{
    return _htmlTemplate->htmlTemplate();
}

//Page::Page(const Page &page)
//{
//    _id = page.id();
//    _parentPage = page.parentPage();
//}

const QString Page::id() const
{
    return _id;
}

Page* Page::parentPage() const
{
    return _parentPage;
}

bool Page::hasNext() const
{
    return !_childPages.isEmpty();
}

Page *Page::childPageByName(QString &name)
{
    return _childPages.value(name);
}

Page::~Page()
{
    QString key;
    foreach (key, _childPages.keys()) {
        delete _childPages.take(key);
    }
    foreach (key, _actions.keys()) {
        delete _actions.take(key);
    }
}

//void Page::showStructure(Page* page)
//{
//    Page* tmpPage;
//    QString key;
//    qDebug() << page->id();
//    foreach (key, page->_childPages.keys()) {
//        tmpPage = page->_childPages.value(key);
//        qDebug() << '\t' << tmpPage->id();
//        if (tmpPage->isChild()) {
//            qDebug() << '\t' <<
//        }
//    }
//}

void Page::addChildPage(Page *page)
{
    Q_ASSERT(!_childPages.contains(page->id()));
    _childPages.insert(page->id(), page);

}

void Page::addAction(Action *action)
{
    Q_ASSERT(!_actions.contains(action->keyCode()));
    qDebug() << "add action" << action->keyCode();
    _actions.insert(action->keyCode(), action);
}

void Page::setUpTemplate(QString filePath)
{
    if (_htmlTemplate) {
        delete _htmlTemplate;
    }
    _htmlTemplate = new HTMLTemplate(filePath);
}

bool Page::isChild() const
{
    return _parentPage ? true : false;
}

//QDebug operator<< (QDebug d, const Page &page) {

//    QString id = page.id();
//    if (page.isChild()) {
//        d.nospace() << "\t";
//    }
//    d.nospace() << "|--" << id;

//    return d.maybeSpace();
//}

//QDebug operator<<(QDebug dbg, Page* page)
//{
//    dbg.nospace() << '\t' << *page;
//}
