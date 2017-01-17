#include "IContextCommand.h"
#include "Page.h"
#include <QDir>
#include "CimrexModelBinding.h"

#include "CimrexLogElement.h"
IContextCommand::IContextCommand(Page* mainPage, QList<Action*> defaultActions)
    :  QObject(),
      _page(mainPage),
      _currentPage(mainPage),
      _view(0),
      _defaultActions(defaultActions),
      _binder(0)
{
    _pageHistory.append(mainPage);
    dropRows();
}

IContextCommand::~IContextCommand()
{

}

Page *IContextCommand::childPageByName(QString &name)
{
    return _currentPage->childPageByName(name);
}


void IContextCommand::renderPage()
{
    generateHtml();
    if (!_binder || !_binder->on()) {
        return;
    }
    QUrl baseUrl = QUrl::fromLocalFile(QDir::currentPath() + "/index.html");
    if (_view ) {
        _view->load(baseUrl);
    }

}

void IContextCommand::updateView()
{
    if (_view) _view->reload();
}

void IContextCommand::changeCurrentPage(Page *page, bool historyOff)
{
    ////
    dropRows();
    ////
    qDebug() << "Current page" << _currentPage->id() << "new PAGE" << page->id();
    if (page) {
        if (historyOff) {
            _currentPage = page;
        } else {
            appendHistory(_currentPage);
            setCurrentPage(page);
        }
    }
    if (_binder) {
        _binder->useLastSnapshot();
    }

    if (_currentPage->rowsInTempalte()) {
        setUpRows(qMakePair(1, _currentPage->rowsInTempalte()));
    }
}

Page *IContextCommand::previousPage()
{
    if (_pageHistory.isEmpty()) {
        return mainPage();
    }
//    Page* page;
//    qDebug() << "History stack";
//    int i = 0;
//    foreach(page, _pageHistory) {
//        qDebug() << "page id" << i << page->id();
//        i++;
//    }
//    qDebug() << "TAKE FROM HISTORY" << _pageHistory.last()->id();

    return _pageHistory.takeLast();
}

void IContextCommand::resetToMainPage(bool historyOff)
{
    appendHistory(_currentPage);
    if (historyOff) {
        _currentPage = mainPage();
    } else {
        appendHistory(mainPage());
        setCurrentPage(mainPage());
    }
}

void IContextCommand::changeValueForKey(QString key, QVariant value)
{
    _currentPage->updateValueForKey(key, value);
    renderPage();
}

void IContextCommand::changeTmpValueForKey(QString key, QVariant value)
{
    _currentPage->updateTempValueForKey(key, value);
    renderPage();
}

void IContextCommand::changeValueForKeyInModel(QString key, QVariant value)
{
    if (_binder)
        _binder->outcommingChanges(key, value);
}

QVariant IContextCommand::valueForKey(QString key)
{
    QVariantHash tmp = _currentPage->tmpKeyMap();
    if ( tmp.contains(key) ){
        return tmp.value(key);
    } else {
        return _currentPage->keyMap().value(key);
    }
}

QPair<int, int> IContextCommand::currentRows()
{
    return qMakePair(_first_row, _last_row);
}

void IContextCommand::setUpRows(QPair<int, int> rows)
{
    _first_row = rows.first;
    _last_row = rows.second;
    renderPage();
}

int IContextCommand::avaiableRows()
{
    return _currentPage->avRows();
}

int IContextCommand::rows()
{
    return _currentPage->rowsInTempalte();
}

CimrexModelBinding *IContextCommand::cimrexModelBinding() const
{
    return _binder;
}

void IContextCommand::appendHistory(Page* page)
{
    qDebug() << "APPEND TO HISTORY" << page->id();
    _pageHistory.append(page);
}

Page *IContextCommand::mainPage()
{
    return _page;
}

QList<Action *> IContextCommand::defaultActions()
{
    return _defaultActions;
}

Page *IContextCommand::currentPage()
{
    return _currentPage;
}

void IContextCommand::setCurrentPage(Page *page)
{
    _currentPage = page;

    /////TODO
    CimrexLogElement log;
    log.setDisplayId(_currentPage->id());
    emit sendEventLog(&log);
}

void IContextCommand::dropRows()
{
    _last_row = 0;
    _first_row = 0;
}

void IContextCommand::generateHtml()
{
    Mustache::Renderer renderer;
    QVariantHash fromModel = _currentPage->keyMap();
    QVariantHash fromTmp = _currentPage->tmpKeyMap();
    QVariantHash mergedMap = fromModel;
    foreach (QString key, fromTmp.keys()) {
        mergedMap.insert(key, fromTmp.value(key));
    }
    mergedMap.insert("elementId", _currentPage->currentSelectedKey());
    if (_first_row && _last_row) {
        mergedMap.insert("first_row", _first_row);
        mergedMap.insert("last_row", _last_row);
    }

    Mustache::QtVariantContext context(mergedMap);

    QString output = renderer.render(_currentPage->html(), &context);

    QFile file("index.html");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << output;

    file.close();
}
