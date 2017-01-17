#include "storagesettingswidget.h"
#include "ui_storagesettingswidget.h"
#include "StringsKeys.h"

#include <GroupSchemeSceneManager.h>

#include <QFileInfo>
#include <QFileDialog>

StorageSettingsWidget::StorageSettingsWidget(bool isInterfaceEditable,
                                             GroupSchemeSceneManager * groupSchemeSceneManager,
                                             QWidget * parent) :
    AbstractSettingsWidget(parent),
    m_groupSchemeSceneManager(groupSchemeSceneManager),
    ui(new Ui::StorageSettingsWidget)
{
    ui->setupUi(this);

    ui->lineEditStorageRoot->setReadOnly(!isInterfaceEditable);
    ui->toolButtonStorageRoot->setEnabled(isInterfaceEditable);

    ui->lineEditExercisesRoot->setReadOnly(!isInterfaceEditable);
    ui->toolButtonExercisesRoot->setEnabled(isInterfaceEditable);

    int i = 0;
    foreach (QString schemeKey, m_groupSchemeSceneManager->schemeKeys())
    {
        QLabel * label = new QLabel(m_groupSchemeSceneManager->schemeTitle(schemeKey), this);
        QLineEdit * lineEdit = new QLineEdit(this);
        m_schemeLineEdits.insert(schemeKey, lineEdit);
        lineEdit->setReadOnly(true);
        QToolButton * toolButton = new QToolButton(this);
        m_schemeToolButtons.insert(schemeKey, toolButton);
        toolButton->setEnabled(isInterfaceEditable);
        toolButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton));

        QObject::connect(toolButton, SIGNAL(clicked()),
                         this, SLOT(toolButtonScheme_clicked()));
        int j = 0;
        ui->lSchemeFilepaths->addWidget(label, i, j++);
        ui->lSchemeFilepaths->addWidget(lineEdit, i, j++);
        ui->lSchemeFilepaths->addWidget(toolButton, i, j++);
        i++;
    }
}

StorageSettingsWidget::~StorageSettingsWidget()
{
    delete ui;
}


bool StorageSettingsWidget::isSettingsValid()
{
    return settingsInvalidText().isEmpty();
}

QString StorageSettingsWidget::settingsInvalidText()
{
    QString wrongSchemeTitle;
    foreach (QString schemeKey, m_schemeLineEdits.keys())
    {
        if (m_schemeLineEdits[schemeKey]->text().isEmpty() || !QFileInfo::exists(m_schemeLineEdits[schemeKey]->text()))
        {
            wrongSchemeTitle = m_groupSchemeSceneManager->schemeTitle(schemeKey);
        }
    }

    if ( ui->lineEditStorageRoot->text().isEmpty() ||
         !QFileInfo::exists(ui->lineEditStorageRoot->text()) )
    {
        return tr("Storage root path does not exist!");
    }
    else if ( ui->lineEditExercisesRoot->text().isEmpty() ||
              !QFileInfo::exists(ui->lineEditExercisesRoot->text()) )
    {
        return tr("Exercises root path does not exist!");
    }
    else if ( !wrongSchemeTitle.isEmpty() )
    {
        return tr("Scheme \"%1\" file does not exist!").arg(wrongSchemeTitle);
    }
    else
    {
        return QString();
    }
}

void StorageSettingsWidget::settingsLoad()
{
    ui->lineEditStorageRoot->setText(m_settingsStorage->value(SettingsKeys::STORAGE_ROOT).toString());
    ui->lineEditExercisesRoot->setText(m_settingsStorage->value(SettingsKeys::EXERCISES_ROOT).toString());

    foreach (QString line, m_settingsStorage->value(SettingsKeys::SCHEME_FILES).toStringList())
    {
        QStringList sections = line.split("////");
        if (sections.size() == 2)
        {
            if (m_schemeLineEdits.contains(sections[0]))
            {
                m_schemeLineEdits[sections[0]]->setText(sections[1]);
            }
        }
    }
}

void StorageSettingsWidget::settingsSave()
{
    m_settingsStorage->setValue(SettingsKeys::STORAGE_ROOT, ui->lineEditStorageRoot->text());
    m_settingsStorage->setValue(SettingsKeys::EXERCISES_ROOT, ui->lineEditExercisesRoot->text());

    QStringList filepaths;
    foreach (QString schemeKey, m_schemeLineEdits.keys())
    {
        filepaths.append(schemeKey + "////" + m_schemeLineEdits[schemeKey]->text());
    }

    m_settingsStorage->setValue(SettingsKeys::SCHEME_FILES, filepaths);
}

void StorageSettingsWidget::toolButtonScheme_clicked()
{
    QToolButton * button = (QToolButton*)sender();
    if (button)
    {
        QString schemeKey = m_schemeToolButtons.key(button);

        QString path = QFileDialog::getOpenFileName(this
                                                    , tr("Select scheme file")
                                                    , m_schemeLineEdits[schemeKey]->text()
                                                    , QString("Scheme files (*.%1)").arg(SettingsKeys::SCHEME_EXTENSION)
                                                    , 0
                                                    , QFileDialog::ReadOnly);
        if(!path.isEmpty()) {
            m_schemeLineEdits[schemeKey]->setText(path);
        }
    }
}

void StorageSettingsWidget::on_toolButtonStorageRoot_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this
                                                     , tr("Select archive root path")
                                                     , ui->lineEditStorageRoot->text());
    if(!path.isEmpty()) {
        ui->lineEditStorageRoot->setText(path);
    }
}

void StorageSettingsWidget::on_toolButtonExercisesRoot_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this
                                                     , tr("Select exercises root path")
                                                     , ui->lineEditExercisesRoot->text());
    if(!path.isEmpty()) {
        ui->lineEditExercisesRoot->setText(path);
    }
}

