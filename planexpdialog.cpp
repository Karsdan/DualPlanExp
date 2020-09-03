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

    initPlanDlg();
}

void PlanExpDialog::initPlanDlg()
{
    levelBox = new QGroupBox();
    levelBox->setTitle(tr("Уровни варьируемых факторов"));

    lblX1 = new QLabel();
    lblX1->setText(tr("X1"));

    lblX2 = new QLabel();
    lblX2->setText(tr("X2"));

    lblLowLevel = new QLabel();
    lblLowLevel->setText(tr("Нижний"));

    lblTopLevel = new QLabel();
    lblTopLevel->setText(tr("Верхний"));

    lblMidLevel = new QLabel();
    lblMidLevel->setText(tr("Основной"));

    lblRangeVar = new QLabel();
    lblRangeVar->setText(tr("Интервал\nварьирования"));

    boxLowLevelX1 = new QLineEdit();
    boxLowLevelX2 = new QLineEdit();

    boxTopLevelX1 = new QLineEdit();
    boxTopLevelX2 = new QLineEdit();

    boxMidLevelX1 = new QLineEdit();
    boxMidLevelX2 = new QLineEdit();
    boxMidLevelX1->setEnabled(false);
    boxMidLevelX2->setEnabled(false);

    boxRangeX1 = new QLineEdit();
    boxRangeX2 = new QLineEdit();
    boxRangeX1->setEnabled(false);
    boxRangeX2->setEnabled(false);


    //LAYOUTS

    QVBoxLayout *windowBoxLayout = new QVBoxLayout(this);
    windowBoxLayout->addWidget(levelBox);
    windowBoxLayout->addStretch(1);

    QGridLayout *levelBoxLayout = new QGridLayout(levelBox);
    levelBoxLayout->addWidget(lblX1, 0, 1);
    levelBoxLayout->addWidget(lblX2, 0, 2);
    levelBoxLayout->addWidget(lblLowLevel, 1, 0);
    levelBoxLayout->addWidget(boxLowLevelX1, 1, 1);
    levelBoxLayout->addWidget(boxLowLevelX2, 1, 2);
    levelBoxLayout->addWidget(lblTopLevel, 2, 0);
    levelBoxLayout->addWidget(boxTopLevelX1, 2, 1);
    levelBoxLayout->addWidget(boxTopLevelX2, 2, 2);
    levelBoxLayout->addWidget(lblMidLevel, 3, 0);
    levelBoxLayout->addWidget(boxMidLevelX1, 3, 1);
    levelBoxLayout->addWidget(boxMidLevelX2, 3, 2);
    levelBoxLayout->addWidget(lblRangeVar, 4, 0);
    levelBoxLayout->addWidget(boxRangeX1, 4, 1);
    levelBoxLayout->addWidget(boxRangeX2, 4, 2);

}
