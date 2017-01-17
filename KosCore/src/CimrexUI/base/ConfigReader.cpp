#include "ConfigReader.h"
#include <QFile>
#include <QDebug>
#include "GoToCommand.h"
#include "GoBackCommand.h"
#include "GoDefaultCommand.h"
#include "IncrementCommand.h"
#include "DecrementCommand.h"
#include "SendCommand.h"
#include "LineUpCommand.h"
#include "LineDownCommand.h"
#include "InvertCommand.h"
#include "EnableAll.h"
#include "DisableAll.h"

#include "Page.h"
#include "Action.h"

QStringList ConfigReader::_pagesById;

ConfigReader::ConfigReader(QString filePath)
    : _parrentXml(filePath), _currentXml(filePath)
{
    QFile config(filePath);
    if (config.exists()) {
        if (config.open(QIODevice::ReadOnly)) {
            read(&config);
        } else {
            qDebug() << "could not open exsting file " << config.errorString();
        }
    } else {
        qDebug() << "file not exist";
    }

}

bool ConfigReader::read(QIODevice *device)
{
    _parser.setDevice(device);

    if (_parser.readNextStartElement()) {
        if (_parser.name() == "controller" && _parser.attributes().value("version") == "1.0")
            startRead();
        else
            _parser.raiseError(QObject::tr("The file is not an KOS Config version 1.0 file."));
    }

    return _parser.error();

}

Page *ConfigReader::mainPage()
{
    return _mainPage;
}

void ConfigReader::startRead()
{
    Q_ASSERT(_parser.isStartElement() && _parser.name() == "controller");

    while (_parser.readNextStartElement()) {
        if (_parser.name() == "page") {
            readPage(0);
        }
        else if (_parser.name() == "default_actions"){
            readDefaultActions();
        }
        else
            _parser.skipCurrentElement();
    }

}

void ConfigReader::readPage(Page* page)
{
    Q_ASSERT(_parser.isStartElement() && _parser.name() == "page");

    Page* newPage;
    if (page == 0) {
        _mainPage = createNewPage(0);
        newPage = _mainPage;
    } else {
        newPage = createNewPage(page);
    }

    while (_parser.readNextStartElement()) {
        if (_parser.name() == "template")
            readTeamplate(newPage);
        else if (_parser.name() == "available_pages")
            readAvailablePages(newPage);
        else if (_parser.name() == "available_actions")
            readAvailableActions(newPage);
        else {
            _parser.skipCurrentElement();
        }
    }
}

void ConfigReader::readTeamplate(Page* page)
{
    Q_ASSERT(_parser.isStartElement() && _parser.name() == "template");

    QString str = _parser.attributes().value("file").toString();
    if (!str.isEmpty())
        page->setUpTemplate(str);
    _parser.skipCurrentElement();
}

void ConfigReader::readAvailablePages(Page* page)
{
    Q_ASSERT(_parser.isStartElement() && _parser.name() == "available_pages");

    while (_parser.readNextStartElement()) {
        if (_parser.name() == "page")
            readPage(page);
        else
            _parser.skipCurrentElement();
    }

}

void ConfigReader::readAvailableActions(Page* page)
{
    Q_ASSERT(_parser.isStartElement() && _parser.name() == "available_actions");
    while (_parser.readNextStartElement()) {
        if (_parser.name() == "action")
            readAction(page);
        else
            _parser.skipCurrentElement();
    }
}

void ConfigReader::readAction(Page* page)
{
    Q_ASSERT(_parser.isStartElement() && _parser.name() == "action");
    Action* newAction = createNewAction();
    if (page) {
        page->addAction(newAction);
    } else {
        _defaultActions.append(newAction);
    }

    while (_parser.readNextStartElement()) {
        if (_parser.name() == "command")
            readCommand(newAction);
        else
            _parser.skipCurrentElement();
    }

}

void ConfigReader::readCommand(Action *action)
{
    Q_ASSERT(_parser.isStartElement() && _parser.name() == "command");
    QXmlStreamAttributes attr = _parser.attributes();
    QString type = attr.value("type").toString();
//    qDebug() << "add command" << type;
    if (type == "goto") {
        ICommand* newCmd = new GoToCommand(attr.value("page_id").toString());
        action->appendCommand(newCmd);
    } else if (type == "go_default"){
        ICommand* newCmd = new GoDefaultCommand(attr.value("page_id").toString());
        action->appendCommand(newCmd);
    }else if (type == "go_back"){
        ICommand* newCmd = new GoBackCommand();
        action->appendCommand(newCmd);
    }else if (type == "increment_value"){
        ICommand* newCmd = new IncrementCommand(attr.value("step").toInt());
        action->appendCommand(newCmd);
    } else if (type == "decrement_value"){
        ICommand* newCmd = new DecrementCommand(attr.value("value").toString(),
                                                attr.value("step").toInt());
        action->appendCommand(newCmd);
    } else if (type == "send_value_to_model"){
        ICommand* newCmd = new SendCommand();
        action->appendCommand(newCmd);
    } else if (type == "line_up"){
        ICommand* newCmd = new LineUpCommand(attr.value("step").toInt());
        action->appendCommand(newCmd);
    } else if (type == "line_down"){
        ICommand* newCmd = new LineDownCommand(attr.value("step").toInt());
        action->appendCommand(newCmd);
    } else if (type == "invert"){
        ICommand* newCmd = new InvertCommand(attr.value("key").toString());
        action->appendCommand(newCmd);
    } else if (type == "enable"){
        ICommand* newCmd = new EnableAll(attr.value("keys").toString().split(" "));
        action->appendCommand(newCmd);
    } else if (type == "disable"){
        ICommand* newCmd = new DisableAll(attr.value("keys").toString().split(" "));
        action->appendCommand(newCmd);
    }

    _parser.skipCurrentElement();
}

void ConfigReader::readDefaultActions()
{
    Q_ASSERT(_parser.isStartElement() && _parser.name() == "default_actions");
    while (_parser.readNextStartElement()) {
        if (_parser.name() == "action")
            readAction();
        else
            _parser.skipCurrentElement();
    }
}

QList<Action *> ConfigReader::defaultActions()
{
    return _defaultActions;
}

Page *ConfigReader::createNewPage(Page *page)
{
    QString pageId = _parser.attributes().value("id").toString();
    Page* childPage = new Page(page, pageId);
    if (!_pagesById.contains(pageId)) {
        _pagesById.append(pageId);
    }
    if (page && childPage) {
        page->addChildPage(childPage);
    }
    return childPage;
}

Action *ConfigReader::createNewAction()
{    
    return new Action(_parser.attributes().value("key_code").toString());
}

QStringList ConfigReader::pagesById()
{
    return _pagesById;
}
