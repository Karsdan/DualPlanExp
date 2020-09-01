#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
QT_END_NAMESPACE

class ApplicationWindow : public QMainWindow
{
    Q_OBJECT

public:
    ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow();

private:
    QMdiArea *mdiArea;

private slots:
    void updateMenu();
};
#endif // APPLICATIONWINDOW_H
