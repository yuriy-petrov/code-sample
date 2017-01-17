#include "GroupSchemeView.h"

#include <GroupSchemeSceneManager.h>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QDebug>

GroupSchemeView::GroupSchemeView(QWidget * parent) :
    QWidget(parent),
    m_groupSchemeSceneManager(NULL)
{
    m_layout = new QHBoxLayout(this);
    m_tabWidget = new QTabWidget(this);
    m_layout->addWidget(m_tabWidget);

    QObject::connect(m_tabWidget, SIGNAL(currentChanged(int)),
                     this, SLOT(currentTabChanged(int)));
}

GroupSchemeView::~GroupSchemeView()
{
}

void GroupSchemeView::setGroupSchemeSceneManager(GroupSchemeSceneManager * groupSchemeSceneManager)
{
    m_groupSchemeSceneManager = groupSchemeSceneManager;
    m_schemeSceneViews.clear();
    m_schemeVisibles.clear();
    while (m_tabWidget->count())
    {
        m_tabWidget->removeTab(0);
    }

    //

    if (groupSchemeSceneManager)
    {
        foreach (QString key, groupSchemeSceneManager->schemeKeys())
        {
            SchemeView * schemeView = new SchemeView(this);
            schemeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            schemeView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            m_tabWidget->addTab(schemeView, groupSchemeSceneManager->schemeTitle(key));

            schemeView->setScene(groupSchemeSceneManager->schemeSceneManager(key)->schemeScene()->scene());
            groupSchemeSceneManager->schemeSceneManager(key)->schemeScene()->setSchemeView(schemeView);
            groupSchemeSceneManager->schemeSceneManager(key)->adjustZoomByCanvas();

            m_schemeSceneViews.insert(groupSchemeSceneManager->schemeSceneManager(key), schemeView);
        }
    }
}

void GroupSchemeView::setCurrentScheme(const QString & schemeKey)
{
    foreach (QString key, m_groupSchemeSceneManager->schemeKeys())
    {
        if (key == schemeKey)
        {
            m_tabWidget->setCurrentWidget(m_schemeSceneViews[m_groupSchemeSceneManager->schemeSceneManager(key)]);
            return;
        }
    }
}

void GroupSchemeView::currentSchemeAdjust()
{
    SchemeView * schemeView = dynamic_cast<SchemeView*>(m_tabWidget->currentWidget());
    if (schemeView)
    {
        SchemeSceneManager * schemeSceneManager = m_schemeSceneViews.key(schemeView);
        if (schemeSceneManager && !m_schemeVisibles.contains(schemeSceneManager))
        {
            schemeSceneManager->adjustZoomByCanvas();
            m_schemeVisibles.insert(schemeSceneManager);
        }
    }
}

void GroupSchemeView::currentTabChanged(int index)
{
    if (index != -1)
    {
        currentSchemeAdjust();
    }
}

void GroupSchemeView::showEvent(QShowEvent * showEvent)
{
    currentSchemeAdjust();
}
