#ifndef SNAPSHOTKEYHASH_H
#define SNAPSHOTKEYHASH_H

#include <QHash>
#include <cxxabi.h>

#include <snapshot.h>

template<typename T>
class SnapshotKeyHash : public QHash<Snapshot::Key, T>
{

public:
    SnapshotKeyHash()
        : QHash<Snapshot::Key, T>()
    {}

    QString toString() const
    {
        QStringList list;

        QList<Snapshot::Key> keys = QHash<Snapshot::Key, T>::keys();
        foreach(const Snapshot::Key& key, keys) {
            list << QString("%1%2%3")
                    .arg(key)
                    .arg(FIELDS_SEPARATOR)
                    .arg(QHash<Snapshot::Key, T>::value(key));
        }

        return list.join(VALUES_SEPARATOR);
    }

    static SnapshotKeyHash<T> fromString(const QString& string)
    {
        SnapshotKeyHash<T> instance;
        QRegExp parser(QString("(\\S+)%1(\\S+)").arg(FIELDS_SEPARATOR));

        foreach(const Snapshot::Key& key, string.split(VALUES_SEPARATOR, QString::SkipEmptyParts)) {
            if(parser.indexIn(key) != -1) {
                instance.insert(parser.cap(1), stringToType(parser.cap(2)));
            }
        }

        return instance;
    }

    QJsonValue toJsonValue() const
    {
        QByteArray buffer;
        QDataStream s(&buffer, QIODevice::WriteOnly);
        *this >> s;
        return QJsonValue(QString(buffer.toHex()));
    }

    template<typename K>
    static SnapshotKeyHash<K> fromJsonValue(const QJsonValue& value)
    {
        QDataStream s(QByteArray::fromHex(value.toString().toLocal8Bit()));
        SnapshotKeyHash<K> instance;
        instance << s;
        return instance;
    }

    QDataStream& operator >>(QDataStream& stream) const
    {
        return stream << *dynamic_cast<const QHash<Snapshot::Key, T>*>(this);
    }

    QDataStream& operator <<(QDataStream& stream)
    {
        return stream >> *dynamic_cast<QHash<Snapshot::Key, T>*>(this);;
    }

    QDebug& operator >>(QDebug& debug) const
    {
        int status;
        std::string tname = typeid(T).name();
        char *demangled_name = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
        if(status == 0) {
            tname = demangled_name;
            std::free(demangled_name);
        }
        debug.nospace() << "SnapshotKeyHash<" << tname.c_str() << "> : ";
        QList<Snapshot::Key> keys = QHash<Snapshot::Key, T>::keys();
        foreach(const Snapshot::Key& key, keys) {
            debug.nospace() << key << "=" << QHash<Snapshot::Key, T>::value(key) << "; ";
        }
        return debug.space();
    }

protected:
    virtual QString typeToString(const T& t) const = 0;
    virtual T stringToType(const QString& s) const = 0;

private:
    static const QChar FIELDS_SEPARATOR;
    static const QChar VALUES_SEPARATOR;
};

template<typename T>
const QChar SnapshotKeyHash<T>::FIELDS_SEPARATOR(QChar('='));
template<typename T>
const QChar SnapshotKeyHash<T>::VALUES_SEPARATOR(QChar(';'));

#endif // SNAPSHOTKEYHASH_H
