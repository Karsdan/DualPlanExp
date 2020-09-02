#include "planexpdialog.h"

PlanExpDialog::PlanExpDialog(QWidget *parent)
    : QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumSize(400,400);

    srand(QDateTime::currentDateTime().toTime_t());

    static int sequenceNumber = 1;
    isUntitled = true;
    curFile = tr("PlanExp %1").arg(sequenceNumber++);
    setWindowTitle(curFile + "[*]");
}
