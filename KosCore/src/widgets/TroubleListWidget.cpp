#include "TroubleListWidget.h"
#include "ui_TroubleListWidget.h"

#include <TroubleListController.h>
#include <QCheckBox>

TroubleListWidget::TroubleListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TroubleListWidget),
    m_troubleListController(NULL),
    m_isCheckboxEnabled(true)
{
    ui->setupUi(this);
}

TroubleListWidget::~TroubleListWidget()
{
    delete ui;
}

void TroubleListWidget::setTroubleListController(TroubleListController * troubleListController)
{
    m_troubleListController = troubleListController;
    QObject::connect(m_troubleListController, SIGNAL(troublesChanged(QList<Trouble>)),
                     this, SLOT(troublesChanged(QList<Trouble>)));
    QObject::connect(m_troubleListController, SIGNAL(activeTroublesChanged(QSet<QString>)),
                     this, SLOT(activeTroublesChanged(QSet<QString>)));

    //

    troublesChanged(m_troubleListController->troubles());
}

void TroubleListWidget::troublesChanged(QList<Trouble> troubles)
{
    Q_UNUSED(troubles);

    //

    foreach (QCheckBox * checkbox, m_checkboxes)
    {
        delete checkbox;
    }
    m_checkboxes.clear();

    //

    QSet<QString> activeTroubles = m_troubleListController->activeTroubles();
    foreach (Trouble trouble, m_troubleListController->troubles())
    {
        QCheckBox * checkBox = new QCheckBox(trouble.description(), this);
        checkBox->setChecked(activeTroubles.contains(trouble.key()));
        checkBox->setEnabled(m_isCheckboxEnabled);

        ui->lTroubles->addWidget(checkBox);
        m_checkboxes.insert(trouble.key(), checkBox);

        QObject::connect(checkBox, SIGNAL(toggled(bool)),
                         this, SLOT(checkboxToggled(bool)));
    }
}

void TroubleListWidget::activeTroublesChanged(QSet<QString> activeTroubles)
{
    foreach (Trouble trouble, m_troubleListController->troubles())
    {
        if (m_checkboxes.contains(trouble.key()))
        {
            m_checkboxes[trouble.key()]->setChecked(activeTroubles.contains(trouble.key()));
        }
    }
}

void TroubleListWidget::checkboxToggled(bool toggled)
{
    QCheckBox * checkbox = dynamic_cast<QCheckBox*>(sender());
    if (checkbox)
    {
        QString key = m_checkboxes.key(checkbox);

        QSet<QString> activeTroubles = m_troubleListController->activeTroubles();
        if (toggled)
        {
            activeTroubles.insert(key);
        }
        else
        {
            activeTroubles.remove(key);
        }

        QObject::disconnect(m_troubleListController, SIGNAL(activeTroublesChanged(QSet<QString>)),
                            this, SLOT(activeTroublesChanged(QSet<QString>)));
        m_troubleListController->setActiveTroubles(activeTroubles);
        QObject::connect(m_troubleListController, SIGNAL(activeTroublesChanged(QSet<QString>)),
                         this, SLOT(activeTroublesChanged(QSet<QString>)));
    }
}
bool TroubleListWidget::isCheckboxEnabled() const
{
    return m_isCheckboxEnabled;
}

void TroubleListWidget::setCheckboxEnabled(bool isCheckboxEnabled)
{
    m_isCheckboxEnabled = isCheckboxEnabled;
    foreach (QCheckBox * checkbox, m_checkboxes)
    {
        checkbox->setEnabled(m_isCheckboxEnabled);
    }
}

