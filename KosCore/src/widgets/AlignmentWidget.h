#ifndef ALIGNMENTWIDGET_H
#define ALIGNMENTWIDGET_H

#include "KosTypes.h"

#include <QWidget>

class QAbstractButton;

namespace Ui
{
    class AlignmentWidget;
}

class AlignmentWidget : public QWidget
{

    Q_OBJECT

public:

    explicit AlignmentWidget(QWidget * parent = 0);
    ~AlignmentWidget();

    KosTypes::HorizontalAlignment horizontalAlignment() const;
    KosTypes::VerticalAlignment verticalAlignment() const;

public slots:

    void setHorizontalAlignment(KosTypes::HorizontalAlignment horizontalAlignment);
    void setVerticalAlignment(KosTypes::VerticalAlignment verticalAlignment);

private:

    Ui::AlignmentWidget * ui;

    QHash<QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment>, QAbstractButton*> m_buttons;

};

#endif // ALIGNMENTWIDGET_H
