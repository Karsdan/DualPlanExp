#include "applicationwindow.h"

ApplicationWindow::ApplicationWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea();
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    connect(mdiArea, &QMdiArea::subWindowActivated, this, &ApplicationWindow::updateMenu);

    setWindowTitle("Двухфакторный планированный эксперимент (DualPlanExp)");
}

ApplicationWindow::~ApplicationWindow()
{
}

void ApplicationWindow::updateMenu()
{
//    bool hasMdiChild = (activeMdiChild != 0);

//    actionSave->setEnabled(hasMdiChild);
//    actionSaveAs->setEnabled(hasMdiChild);

//#ifndef QT_NO_CLIPBOERD
//    actionPaste->setEnabled(hasMdiChild);
//#endif
//    actionClose->setEnabled(hasMdiChild);
//    actionCloseAll->setEnabled(hasMdiChild);
//    actionNext->setEnabled(hasMdiChild);
//    actionPrevious->setEnabled(hasMdiChild);
//    actionWindowMenuSeparator->setEnabled(hasMdiChild);

//#ifndef QT_NO_CLIPBOARD
//    bool hasSelection = (activeMdiChild() &&
//                         activeMdiChild()->textCursor().hasSelection());
//    actionCut->setEnabled(hasSelection);
//    actionCopy->setEnabled(hasSelection);
//#endif
}

class ActiveMdiSubWindowFunctor {
public:
    explicit ActiveMdiSubWindowFunctor(QMdiArea *mdiArea, QMdiSubWindow *activeWindow) : m_mdiArea(mdiArea), m_activeWindow(activeWindow) {}
    void operator()() const { m_mdiArea->setActiveSubWindow(m_activeWindow); }

private:
    QMdiArea *m_mdiArea;
    QMdiSubWindow *m_activeWindow;
};

