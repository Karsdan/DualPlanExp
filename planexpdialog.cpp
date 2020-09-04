#include "planexpdialog.h"
#include "calcplanexp.h"

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
    //levelBox

    levelBox = new QGroupBox();
    levelBox->setTitle(tr("Уровни варьируемых факторов"));

    lblX1 = new QLabel(tr("X1"));
//    lblX1->setText(tr("X1"));

    lblX2 = new QLabel(tr("X2"));
//    lblX2->setText(tr("X2"));

    lblLowLevel = new QLabel(tr("Нижний"));
//    lblLowLevel->setText(tr("Нижний"));

    lblTopLevel = new QLabel(tr("Верхний"));
//    lblTopLevel->setText(tr("Верхний"));

    lblMidLevel = new QLabel(tr("Основной"));
//    lblMidLevel->setText(tr("Основной"));

    lblRangeVar = new QLabel(tr("Интервал\nварьирования"));
//    lblRangeVar->setText(tr("Интервал\nварьирования"));

    QRegExp boxRx("^([0-9]*[-][0-9][0-9]*|0)(\\.|,)[0-9]{4}");
    QValidator *boxValidator = new QRegExpValidator(boxRx, this);

    boxLowLevelX1 = new QLineEdit();
    boxLowLevelX2 = new QLineEdit();
//    boxLowLevelX1->setValidator(boxValidator);
//    boxLowLevelX1->setAlignment(Qt::AlignCenter);
//    boxLowLevelX2->setValidator(new QRegExpValidator(QRegExp("^[0-9]*[-]{1}([1-9][0-9]*|0)(\\.|,)[0-9]{2}"), this));
//    boxLowLevelX2->setValidator(boxValidator);

    boxTopLevelX1 = new QLineEdit();
    boxTopLevelX2 = new QLineEdit();
//    boxTopLevelX1->setValidator(boxValidator);
//    boxTopLevelX2->setValidator(boxValidator);

    boxMidLevelX1 = new QLineEdit();
    boxMidLevelX2 = new QLineEdit();
    boxMidLevelX1->setEnabled(false);
    boxMidLevelX2->setEnabled(false);
    boxMidLevelX1->setValidator(boxValidator);
    boxMidLevelX2->setValidator(boxValidator);

    boxRangeX1 = new QLineEdit();
    boxRangeX2 = new QLineEdit();
    boxRangeX1->setEnabled(false);
    boxRangeX2->setEnabled(false);
    boxRangeX1->setValidator(boxValidator);
    boxRangeX2->setValidator(boxValidator);

    //planeBox
    planeBox = new QGroupBox();
    planeBox->setTitle(tr("План эксперимента"));

    //modelBox
    modelBox = new QGroupBox();
    modelBox->setTitle(tr("Математическая модель"));

    lblModel = new QLabel(tr("y=b0+b1X1+b2X2+b12X1X2"));
//    lblModel->setText(tr("y=b0+b1X1+b2X2+b12X1X2")); //Поменять внешний вид

    boxModel = new QLineEdit();

    //importanceBox
    importanceBox = new QGroupBox();
    importanceBox->setTitle(tr("Проверка значимости коэффициентов модели"));

    lblReprDispertion = new QLabel(tr("Дисперсия воспроизводимости"));
    boxReprDispertion = new QLineEdit();
    boxReprDispertion->setEnabled(false);

    lblReprStep = new QLabel(tr("Число степеней свободы"));
    boxReprStep = new QLineEdit();
    boxReprStep->setEnabled(false);

    lblTableStudent = new QLabel(tr("Табличное значение критерия Стьюента"));
    boxTableStudent = new QLineEdit();
    boxTableStudent->setEnabled(false);

    //adequacyBox
    adequacyBox = new QGroupBox();
    adequacyBox->setTitle(tr("Проверка адекватности модели"));

    lblAdeqDispertion = new QLabel(tr("Дисперисия адекватности модели"));
    boxAdeqDispertion = new QLineEdit();
    boxAdeqDispertion->setEnabled(false);

    lblAdeqStep = new QLabel(tr("Число степеней свободы"));
    boxAdeqStep = new QLineEdit();
    boxAdeqStep->setEnabled(false);

    lblTableFisher = new QLabel(tr("Табличное значение критерия Фишера"));
    boxTableFisher = new QLineEdit();
    boxTableFisher->setEnabled(false);

    lblCalcFisher = new QLabel(tr("Расчетное значение критерия Фишера"));
    boxCalcFisher = new QLineEdit();
    boxCalcFisher->setEnabled(false);

    //LAYOUTS
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

    QVBoxLayout *modelBoxLayout = new QVBoxLayout(modelBox);
    modelBoxLayout->addWidget(lblModel);
    modelBoxLayout->addWidget(boxModel);

    QGridLayout *importanceBoxLayout = new QGridLayout(importanceBox);
    importanceBoxLayout->addWidget(lblReprDispertion, 0, 0);
    importanceBoxLayout->addWidget(boxReprDispertion, 0, 1);
    importanceBoxLayout->addWidget(lblReprStep, 1, 0);
    importanceBoxLayout->addWidget(boxReprStep, 1, 1);
    importanceBoxLayout->addWidget(lblTableStudent, 2, 0);
    importanceBoxLayout->addWidget(boxTableStudent, 2, 1);

    QGridLayout *adequacyBoxLayout = new QGridLayout(adequacyBox);
    adequacyBoxLayout->addWidget(lblAdeqDispertion, 0, 0);
    adequacyBoxLayout->addWidget(boxAdeqDispertion, 0, 1);
    adequacyBoxLayout->addWidget(lblAdeqStep, 1, 0);
    adequacyBoxLayout->addWidget(boxAdeqStep, 1, 1);
    adequacyBoxLayout->addWidget(lblTableFisher, 2, 0);
    adequacyBoxLayout->addWidget(boxTableFisher, 2, 1);
    adequacyBoxLayout->addWidget(lblCalcFisher, 3, 0);
    adequacyBoxLayout->addWidget(boxCalcFisher, 3, 1);

    QVBoxLayout *windowBoxLayout = new QVBoxLayout(this);
    windowBoxLayout->addWidget(levelBox);
    windowBoxLayout->addWidget(planeBox);
    windowBoxLayout->addWidget(modelBox);
    windowBoxLayout->addWidget(importanceBox);
    windowBoxLayout->addWidget(adequacyBox);
    windowBoxLayout->addStretch(1);



    //CONNECTIONS
    connect(boxLowLevelX1, SIGNAL(textChanged(QString)), this, SLOT(calcMid()));
    connect(boxLowLevelX2, SIGNAL(textChanged(QString)), this, SLOT(calcMid()));
    connect(boxTopLevelX1, SIGNAL(textChanged(QString)), this, SLOT(calcMid()));
    connect(boxTopLevelX2, SIGNAL(textChanged(QString)), this, SLOT(calcMid()));
}

void PlanExpDialog::calcMid()
{
    //boxLowLevelX1->text().replace(',', '.').toDouble()

    const auto midX1 = (boxLowLevelX1->text().replace(',', '.').toDouble() + boxTopLevelX1->text().replace(',', '.').toDouble()) / 2;
    const auto rangeX1 = (boxTopLevelX1->text().replace(',', '.').toDouble()) - midX1;
    QString strMidX1 = QString::number(midX1);
    QString strRangeX1 = QString::number(qAbs(rangeX1));
    boxMidLevelX1->setText(strMidX1);
    boxRangeX1->setText(strRangeX1);

    const auto midX2 = (boxLowLevelX2->text().replace(',', '.').toDouble() + boxTopLevelX2->text().replace(',', '.').toDouble()) / 2;
    const auto rangeX2 = (boxTopLevelX2->text().replace(',', '.').toDouble()) - midX2;
    QString strMidX2 = QString::number(midX2);
    QString strRangeX2 = QString::number(qAbs(rangeX2));
    boxMidLevelX2->setText(strMidX2);
    boxRangeX2->setText(strRangeX2);

    testM();
}
