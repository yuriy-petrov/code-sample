#include "SendCommand.h"
#include "Page.h"

SendCommand::SendCommand()
    : ICommand()
{
}

SendCommand::~SendCommand()
{

}

void SendCommand::exec()
{
    QString key = ctx()->currentPage()->currentSelectedKey();
    ctx()->changeValueForKeyInModel(key, ctx()->currentPage()->tmpKeyMap().value(key));
    QVariantHash hash = ctx()->currentPage()->tmpKeyMap();
    foreach (QString key, _keyList) {

        ctx()->changeValueForKeyInModel(key, hash.value(key));
    }
    ctx()->currentPage()->flushTmpKey();
}
