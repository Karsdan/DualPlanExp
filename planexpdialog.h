#ifndef PLANEXPDIALOG_H
#define PLANEXPDIALOG_H

#include <QDialog>
#include <QMdiSubWindow>
#include <QtWidgets>
#include <QKeyEvent>

class PlanExpDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlanExpDialog(QWidget *parent = nullptr);

private:
    QString curFile;
    bool isUntitled;

private:

    void initPlanDlg();

    QGroupBox *levelBox;
//    QTableWidget *tableLevel;
    QLabel *lblX1, *lblX2, *lblLowLevel, *lblTopLevel, *lblMidLevel, *lblRangeVar;
    QLineEdit *boxLowLevelX1, *boxTopLevelX1, *boxMidLevelX1, *boxRangeX1;
    QLineEdit *boxLowLevelX2, *boxTopLevelX2, *boxMidLevelX2, *boxRangeX2;

    QGroupBox *planeBox;

    QGroupBox *modelBox;
    QLabel *lblModel;
    QLineEdit *boxModel;

    QGroupBox *importanceBox;
    QLabel *lblReprDispertion, *lblReprStep, *lblTableStudent;
    QLineEdit *boxReprDispertion, *boxReprStep, *boxTableStudent;


    QGroupBox *adequacyBox;
    QLabel *lblAdeqDispertion, *lblAdeqStep, *lblTableFisher, *lblCalcFisher;
    QLineEdit *boxAdeqDispertion, *boxAdeqStep, *boxTableFisher, *boxCalcFisher;

private slots:
    void calcMid();

};

#endif // PLANEXPDIALOG_H
