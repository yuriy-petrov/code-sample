#include "AlignmentWidget.h"
#include "ui_AlignmentWidget.h"

AlignmentWidget::AlignmentWidget(QWidget * parent) :
    QWidget(parent),
    ui(new Ui::AlignmentWidget)
{
    ui->setupUi(this);

    m_buttons.insert( QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment>(KosTypes::Left, KosTypes::Top), ui->rbLT );
    m_buttons.insert( QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment>(KosTypes::Left, KosTypes::VCenter), ui->rbLC );
    m_buttons.insert( QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment>(KosTypes::Left, KosTypes::Bottom), ui->rbLB );
    m_buttons.insert( QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment>(KosTypes::HCenter, KosTypes::Top), ui->rbCT );
    m_buttons.insert( QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment>(KosTypes::HCenter, KosTypes::VCenter), ui->rbCC );
    m_buttons.insert( QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment>(KosTypes::HCenter, KosTypes::Bottom), ui->rbCB );
    m_buttons.insert( QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment>(KosTypes::Right, KosTypes::Top), ui->rbRT );
    m_buttons.insert( QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment>(KosTypes::Right, KosTypes::VCenter), ui->rbRC );
    m_buttons.insert( QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment>(KosTypes::Right, KosTypes::Bottom), ui->rbRB );
}

AlignmentWidget::~AlignmentWidget()
{
    delete ui;
}

KosTypes::HorizontalAlignment AlignmentWidget::horizontalAlignment() const
{
    QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment> key = m_buttons.key(ui->buttonGroup->checkedButton());
    return key.first;
}

KosTypes::VerticalAlignment AlignmentWidget::verticalAlignment() const
{
    QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment> key = m_buttons.key(ui->buttonGroup->checkedButton());
    return key.second;
}

void AlignmentWidget::setHorizontalAlignment(KosTypes::HorizontalAlignment horizontalAlignment)
{
    QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment> key = m_buttons.key(ui->buttonGroup->checkedButton());
    key.first = horizontalAlignment;
    m_buttons[key]->setChecked(true);
}

void AlignmentWidget::setVerticalAlignment(KosTypes::VerticalAlignment verticalAlignment)
{
    QPair<KosTypes::HorizontalAlignment, KosTypes::VerticalAlignment> key = m_buttons.key(ui->buttonGroup->checkedButton());
    key.second = verticalAlignment;
    m_buttons[key]->setChecked(true);
}
