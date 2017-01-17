#ifndef KOSTYPESHELPER_H
#define KOSTYPESHELPER_H

#include "KosTypes.h"

#include <QObject>
#include <QHash>
#include <QColor>

class KosTypesHelper: public QObject
{

    Q_OBJECT

public:

    static KosTypesHelper * instance();

    QHash<KosTypes::SubstanceType,QString> substanceTypeTitles() const;
    QHash<KosTypes::ValveType,QString> valveTypeTitles() const;
    QHash<KosTypes::BasicElementType,QString> basicElementTypeTitles() const;
    QHash<KosTypes::PipelineState,QString> pipelineStateTitles() const;
    QHash<KosTypes::LevelElementType,QString> levelElementTypeTitles() const;

    QHash<KosTypes::SubstanceType,QColor> substanceTypeColors() const;

private:

    KosTypesHelper();

private:

    QHash<KosTypes::SubstanceType,QString> m_substanceTypeTitles;
    QHash<KosTypes::ValveType,QString> m_valveTypeTitles;
    QHash<KosTypes::BasicElementType,QString> m_basicElementTypeTitles;
    QHash<KosTypes::PipelineState,QString> m_pipelineStateTitles;
    QHash<KosTypes::LevelElementType,QString> m_levelElementTypeTitles;

    QHash<KosTypes::SubstanceType,QColor> m_substanceTypeColors;

    static KosTypesHelper * m_instance;

};

#endif // KOSTYPESHELPER_H
