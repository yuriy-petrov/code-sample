#include "GoBackCommand.h"

GoBackCommand::GoBackCommand()
    : ICommand()
{
}

GoBackCommand::~GoBackCommand()
{

}

void GoBackCommand::exec()
{
    qDebug() << "GO BACK";
    Page* prevPage = ctx()->previousPage();

    if (prevPage) {
        ctx()->changeCurrentPage(prevPage, true);
    } else {
        ctx()->resetToMainPage(true);
    }

    ctx()->renderPage();
}
