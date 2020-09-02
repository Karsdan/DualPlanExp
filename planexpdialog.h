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

};

#endif // PLANEXPDIALOG_H
