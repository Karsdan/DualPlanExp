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

protected:
    void closeEvent(QCloseEvent *event);

private:
    void initWindow();
    void initActions();
    void initStatusBar();
    void readSettings();
    void writeSettings();

    QMdiArea *mdiArea;
    QMenu *windowMenu;
    QAction *actionNew, *actionOpen, *actionSave, *actionSaveAs;
#ifndef QT_NO_CLIPBOARD
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
#endif
    QAction *actionClose, *actionCloseAll, *actionTile, *actionCascade, *actionNext, *actionPrevious, *actionWindowMenuSeparator;

private slots:
    void updateMenu();
};
#endif // APPLICATIONWINDOW_H
