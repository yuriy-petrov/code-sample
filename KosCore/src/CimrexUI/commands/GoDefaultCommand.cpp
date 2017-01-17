#include "GoDefaultCommand.h"
#include "Page.h"

GoDefaultCommand::GoDefaultCommand(QString pageId)
    :   ICommand(), _defaultPage(pageId)
{
}

GoDefaultCommand::~GoDefaultCommand()
{

}

void GoDefaultCommand::exec()
{
    qDebug() << "Go Default" << _defaultPage;
    if (ctx()->currentPage()->id() == _defaultPage) {
        return;
    }
    ctx()->resetToMainPage(true);
    Page* goDefPage = ctx()->childPageByName(_defaultPage);
    if (goDefPage) {
        ctx()->changeCurrentPage(goDefPage, true);
    }
    ctx()->renderPage();

}
