#include "GoToCommand.h"
#include "Page.h"

GoToCommand::GoToCommand(QString pageId)
    : ICommand(),
      _gotoPageId(pageId)
{
}

GoToCommand::~GoToCommand()
{

}

void GoToCommand::exec()
{
    qDebug() << "GOTO" << _gotoPageId;
    Page* parrentPage = 0;
    Page* currentPage = ctx()->currentPage();
    Page* gotoPage = ctx()->childPageByName(_gotoPageId);

    if ( currentPage->id() == _gotoPageId) {
        return;
    }

    if (currentPage) {
        parrentPage = currentPage->parentPage();
    }

    if (gotoPage) {
        ctx()->changeCurrentPage(gotoPage);
    } //else {

//        if ( parrentPage && (parrentPage->id() == parrentPage->id())){
//            ctx()->changeCurrentPage(parrentPage);
//        }
   // }

    ctx()->renderPage();
}
