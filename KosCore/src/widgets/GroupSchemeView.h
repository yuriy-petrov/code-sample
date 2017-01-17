#ifndef GROUPSCHEMEVIEW_H
#define GROUPSCHEMEVIEW_H

class GroupSchemeSceneManager;
class SchemeView;
class QTabWidget;
class QHBoxLayout;

#include <GroupSchemeSceneManager.h>
#include <SchemeView.h>
#include <SchemeSceneManager.h>
#include <SchemeScene.h>

#include <QWidget>

class GroupSchemeView : public QWidget
{

    Q_OBJECT

public:

    GroupSchemeView(QWidget * parent = 0);
    ~GroupSchemeView();

public slots:

    void setGroupSchemeSceneManager(GroupSchemeSceneManager * groupSchemeSceneManager);
    void setCurrentScheme(const QString & schemeKey);

private slots:

    virtual void currentSchemeAdjust();
    virtual void currentTabChanged(int index);
    virtual void showEvent(QShowEvent * showEvent);

private:

    QHBoxLayout * m_layout;
    QTabWidget * m_tabWidget;

    GroupSchemeSceneManager * m_groupSchemeSceneManager;
    QHash<SchemeSceneManager*,SchemeView*> m_schemeSceneViews;
    QSet<SchemeSceneManager*> m_schemeVisibles;

};

#endif // GROUPSCHEMEVIEW_H
