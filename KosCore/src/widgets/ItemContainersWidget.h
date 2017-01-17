#ifndef ITEMCONTAINERSWIDGET_H
#define ITEMCONTAINERSWIDGET_H

class SchemeSceneManager;
class AbstractSchemeItemContainer;
class QCheckBox;

#include <QWidget>

namespace Ui
{
    class ItemContainersWidget;
}

class ItemContainersWidget : public QWidget
{

    Q_OBJECT

public:

    explicit ItemContainersWidget(QWidget * parent = 0);
    ~ItemContainersWidget();

public slots:

    void setSchemeSceneManager(SchemeSceneManager * schemeSceneManager);

private slots:

    void containerVisibleCheckboxToggled(bool checked);

    void on_pbCheckAll_clicked();

    void on_pbCheckAll_2_clicked();

private:

    Ui::ItemContainersWidget * ui;

    SchemeSceneManager * m_schemeSceneManager;

    QHash<AbstractSchemeItemContainer*,QCheckBox*> m_containerVisibleCheckboxes;

};

#endif // ITEMCONTAINERSWIDGET_H
