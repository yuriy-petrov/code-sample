#include "ItemContainersWidget.h"
#include "ui_ItemContainersWidget.h"

#include <AbstractSchemeItemContainer.h>
#include <SchemeSceneManager.h>
#include <SchemeScene.h>

#include <QCheckBox>

ItemContainersWidget::ItemContainersWidget(QWidget * parent) :
    QWidget(parent),
    ui(new Ui::ItemContainersWidget),
    m_schemeSceneManager(NULL)
{
    ui->setupUi(this);
}

ItemContainersWidget::~ItemContainersWidget()
{
    delete ui;
}

void ItemContainersWidget::setSchemeSceneManager(SchemeSceneManager * schemeSceneManager)
{
    m_schemeSceneManager = schemeSceneManager;

    foreach (AbstractSchemeItemContainer * itemContainer, m_schemeSceneManager->schemeScene()->schemeItemContainers())
    {
        QCheckBox * checkbox = new QCheckBox(itemContainer->name(), this);
        checkbox->setChecked(itemContainer->isVisible());
        ui->lVisible->addWidget(checkbox);

        m_containerVisibleCheckboxes.insert(itemContainer, checkbox);
        QObject::connect(checkbox, SIGNAL(toggled(bool)),
                         this, SLOT(containerVisibleCheckboxToggled(bool)));
    }
}

void ItemContainersWidget::containerVisibleCheckboxToggled(bool checked)
{
    QCheckBox * checkbox = (QCheckBox*)sender();
    AbstractSchemeItemContainer * itemContainer = m_containerVisibleCheckboxes.key(checkbox);
    itemContainer->setVisible(checked);
}

void ItemContainersWidget::on_pbCheckAll_clicked()
{
    foreach (QCheckBox * checkbox, m_containerVisibleCheckboxes)
    {
        checkbox->setChecked(true);
    }
}

void ItemContainersWidget::on_pbCheckAll_2_clicked()
{
    foreach (QCheckBox * checkbox, m_containerVisibleCheckboxes)
    {
        checkbox->setChecked(false);
    }
}
