#include "Exercise.h"

#include "EventFilterProvider.h"

#include <QFile>
#include <QFileInfo>
#include <QVariant>
#include <QJsonDocument>

Exercise::Exercise(QObject *parent)
    : QObject(parent)
    , m_isModified(false)
{
    m_stagesEventFilterProvider = new EventFilterProvider();
    m_modesEventFilterProvider = new EventFilterProvider();
}

Exercise::~Exercise()
{
    delete m_modesEventFilterProvider;
    delete m_stagesEventFilterProvider;
}

Exercise::Pointer Exercise::create()
{
    return Pointer(new Exercise());
}

bool Exercise::load(const QString & filepath)
{
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly))
    {
        m_isModified = false;
        m_filePath = filepath;
        QJsonObject jsonObject = QJsonDocument().fromJson(file.readAll()).object();
        loadFromJsonObject(jsonObject);

        emit changed();
        return true;
    }
    else
    {
        m_lastError = file.errorString();
        return false;
    }
}

bool Exercise::save(const QString &filepath)
{
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly))
    {
        m_isModified = false;
        m_filePath = filepath;
        QJsonObject jsonObject = toJsonObject();
        file.write(QJsonDocument(jsonObject).toJson());
        return true;
    }
    else
    {
        m_lastError = file.errorString();
        return false;
    }
}

void Exercise::clear()
{
    m_isModified = true;
    m_InitialValues.clear();
    emit changed();
}

EventFilterProvider * Exercise::stagesEventFilterProvider() const
{
    return m_stagesEventFilterProvider;
}

EventFilterProvider * Exercise::modesEventFilterProvider() const
{
    return m_modesEventFilterProvider;
}

QString Exercise::lastError() const
{
    return m_lastError;
}

bool Exercise::isEmpty() const
{
    return m_title.isEmpty();
}

bool Exercise::isModified()
{
    return m_isModified;
}

QString Exercise::filePath() const
{
    return m_filePath;
}

QString Exercise::title() const
{
    return m_title;
}

void Exercise::setTitle(const QString &title)
{
    m_title = title;
    m_isModified = true;
    emit changed();
}

Snapshot Exercise::initialValues() const
{
    return m_InitialValues;
}

void Exercise::setInitialValues(const Snapshot &snapshot)
{
    m_InitialValues = snapshot;
    m_isModified = true;
    emit changed();
}

QString Exercise::defaultSchemeKey() const
{
    return m_defaultSchemeKey;
}

void Exercise::setDefaultSchemeKey(const QString & defaultSchemeKey)
{
    m_defaultSchemeKey = defaultSchemeKey;
    emit changed();
}

QJsonObject Exercise::toJsonObject()
{
    QJsonObject jsonObject;
    jsonObject.insert("title", QJsonValue(m_title));
    jsonObject.insert("initial_values", m_InitialValues.toJsonValue());
    jsonObject.insert("stages_event_filters", m_stagesEventFilterProvider->toJsonObject());
    jsonObject.insert("modes_event_filters", m_modesEventFilterProvider->toJsonObject());
    jsonObject.insert("default_scheme_key", m_defaultSchemeKey);
    return jsonObject;
}

Exercise::Pointer Exercise::fromJsonObject(const QJsonObject & jsonObject)
{
    Exercise::Pointer exercise(new Exercise());
    exercise->loadFromJsonObject(jsonObject);
    return exercise;
}

void Exercise::loadFromJsonObject(const QJsonObject &jsonObject)
{
    m_isModified = false;
    m_title = jsonObject.value("title").toString();
    m_InitialValues = Snapshot::fromJsonValue(jsonObject.value("initial_values"));
    m_stagesEventFilterProvider->fromJsonObject(jsonObject.value("stages_event_filters").toObject());
    m_modesEventFilterProvider->fromJsonObject(jsonObject.value("modes_event_filters").toObject());
    m_defaultSchemeKey = jsonObject.value("default_scheme_key").toString();
    emit changed();
}


