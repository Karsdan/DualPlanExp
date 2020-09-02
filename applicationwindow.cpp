#include "applicationwindow.h"
#include "planexpdialog.h"

ApplicationWindow::ApplicationWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea();
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    initActions();

    connect(mdiArea, &QMdiArea::subWindowActivated, this, &ApplicationWindow::updateMenu);

    initStatusBar();

    setWindowTitle("Двухфакторный планированный эксперимент (DualPlanExp)");
    setUnifiedTitleAndToolBarOnMac(true);
}

ApplicationWindow::~ApplicationWindow()
{
}

void ApplicationWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
    if (mdiArea->currentSubWindow())
    {
        event->ignore();
    }
    else
    {
        //writeSettings();
        event->accept();
    }
}

void ApplicationWindow::newPlanExp()
{
    PlanExpDialog *planDlg = new PlanExpDialog;
    mdiArea->addSubWindow(planDlg);
    planDlg->show();
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

void ApplicationWindow::initActions()
{

    QMenu *fileMenu = menuBar()->addMenu(tr("&Файл"));
    QToolBar *fileToolBar = addToolBar(tr("&Файл"));

    const QIcon newPlanExpIcon = QIcon::fromTheme("Analysis-new", QIcon(":/images/new.png"));
    actionNew = new QAction(newPlanExpIcon, tr("&Создать окно"), this);
    actionNew->setShortcut(QKeySequence::New);
    actionNew->setStatusTip(tr("Создать новое окно расчетов"));
    connect(actionNew, SIGNAL(triggered(bool)), this, SLOT(newPlanExp()));
    fileMenu->addAction(actionNew);
    fileToolBar->addAction(actionNew);

    const QIcon openPlanExpIcon = QIcon::fromTheme("PlotWearSurface-new", QIcon(":/images/open.png"));
    actionOpen = new QAction(newPlanExpIcon, tr("&New Wear Surface"), this);
    actionNew->setShortcut(QKeySequence::Open);
    actionOpen->setStatusTip(tr("Create a new Surface"));
    //connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(newPlotWearSurface()));
    fileMenu->addAction(actionOpen);
    fileToolBar->addAction(actionOpen);

    const QIcon saveIcon = QIcon::fromTheme("save", QIcon(":/images/save_template.png"));
    actionSave = new QAction(saveIcon, tr("&Save"), this);
    actionSave->setShortcuts(QKeySequence::Save);
    actionSave->setStatusTip(tr("Save"));
    //connect(actionSave, SIGNAL(triggered(bool)), this, SLOT(save()));
    fileMenu->addAction(actionSave);
    fileToolBar->addAction(actionSave);

    const QIcon saveAsIcon = QIcon::fromTheme("saveAs", QIcon(":/images/saveAs.png"));
    actionSaveAs = new QAction(saveAsIcon, tr("Save &As..."), this);
    actionSaveAs->setShortcuts(QKeySequence::SaveAs);
    actionSaveAs->setStatusTip(tr("Save under a new name"));
    //connect(actionSaveAs, SIGNAL(triggered(bool)), this, SLOT(saveAs()));
    fileMenu->addAction(actionSaveAs);

//    fileMenu->addSeparator();
//    QMenu *recentMenu = fileMenu->addMenu(tr("Recent..."));
//    connect(recentMenu, &QMenu::aboutToShow, this, &ApplicationWindow::updateRecentFileActions);
//    actionRecentFileSubMenu = recentMenu->menuAction();

//    for (int i = 0; i < MaxRecentFiles; ++i)
//    {
//        actionRecentFile[i] = recentMenu->addAction(QString(), this, &ApplicationWindow::openRecentFile);
//        actionRecentFile[i]->setVisible(false);
//    }

//    actionRecentFileSeparator = fileMenu->addSeparator();

//    setRecentFilesVisible(ApplicationWindow::hasRecentFiles());


//! [0]
    const QIcon exitIcon = QIcon::fromTheme("application-exit", QIcon(":/images/exit.png"));
    QAction *actionExit = fileMenu->addAction(exitIcon, tr("E&xit"), qApp, &QApplication::closeAllWindows);
    actionExit->setShortcuts(QKeySequence::Quit);
    actionExit->setStatusTip(tr("Exit the application"));
    fileMenu->addAction(actionExit);
//! [0]

#ifndef QT_NO_CLIPBOARD
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));

    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
    actionCut = new QAction(cutIcon, tr("Cu&t"), this);
    actionCut->setShortcuts(QKeySequence::Cut);
    actionCut->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
//    connect(actionCut, &QAction::triggered, this, &ApplicationWindow::cut);
    editMenu->addAction(actionCut);
    editToolBar->addAction(actionCut);

    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/copy.png"));
    actionCopy = new QAction(copyIcon, tr("&Copy"), this);
    actionCopy->setShortcuts(QKeySequence::Copy);
    actionCopy->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
//    connect(actionCopy, &QAction::triggered, this, &ApplicationWindow::copy);
    editMenu->addAction(actionCopy);
    editToolBar->addAction(actionCopy);

    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/paste.png"));
    actionPaste = new QAction(pasteIcon, tr("&Paste"), this);
    actionPaste->setShortcuts(QKeySequence::Paste);
    actionPaste->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
//    connect(actionPaste, &QAction::triggered, this, &ApplicationWindow::paste);
    editMenu->addAction(actionPaste);
    editToolBar->addAction(actionPaste);
#endif

    editMenu->addSeparator();

//    const QIcon clearLogWindowIcon = QIcon::fromTheme("edit-log", QIcon(":/images/clear_log.png"));
//    actionClearLogWindow = new QAction(clearLogWindowIcon, tr("&Clear log"), this);
//    actionClearLogWindow->setStatusTip(tr("Clear Log Window"));
////    connect(actionPaste, &QAction::triggered, this, &ApplicationWindow::paste);
//    editMenu->addAction(actionClearLogWindow);
//    //editToolBar->addAction(actionClearLogWindow);

//    const QIcon showLogWindowIcon = QIcon::fromTheme("edit-show-log", QIcon(":/images/show_log.png"));
//    actionShowWindowLog = new QAction(showLogWindowIcon, tr("Show log"), this);
//    actionShowWindowLog->setStatusTip(tr("Show or hide log window"));
//    actionShowWindowLog->setCheckable(true);
//    actionShowWindowLog->setChecked(false);
//    editToolBar->addAction(actionShowWindowLog);
//    connect(actionShowWindowLog, &QAction::triggered, this, &ApplicationWindow::showLogWindow);


//    const QIcon preferencesIcon = QIcon::fromTheme("edit-preferences", QIcon(":/images/preferences.png"));
//    actionPreferences = new QAction(preferencesIcon, tr("&Preferences"), this);
//    actionPreferences->setStatusTip(tr("Open Preferences Dialog Window"));
//    connect(actionPreferences, &QAction::triggered, this, &ApplicationWindow::showPreferencesDialog);
//    editMenu->addAction(actionPreferences);
//    editToolBar->addAction(actionPreferences);

    windowMenu = menuBar()->addMenu(tr("&Window"));
//    connect(windowMenu, &QMenu::aboutToShow, this, &ApplicationWindow::updateWindowMenu);

    actionClose = new QAction(tr("Cl&ose"), this);
    actionClose->setStatusTip(tr("Close the active window"));
    connect(actionClose, &QAction::triggered,
            mdiArea, &QMdiArea::closeActiveSubWindow);

    actionCloseAll = new QAction(tr("Close &All"), this);
    actionCloseAll->setStatusTip(tr("Close all the windows"));
    connect(actionCloseAll, &QAction::triggered, mdiArea, &QMdiArea::closeAllSubWindows);

    actionTile = new QAction(tr("&Tile"), this);
    actionTile->setStatusTip(tr("Tile the windows"));
    connect(actionTile, &QAction::triggered, mdiArea, &QMdiArea::tileSubWindows);

    actionCascade = new QAction(tr("&Cascade"), this);
    actionCascade->setStatusTip(tr("Cascade the windows"));
    connect(actionCascade, &QAction::triggered, mdiArea, &QMdiArea::cascadeSubWindows);

    actionNext = new QAction(tr("Ne&xt"), this);
    actionNext->setShortcuts(QKeySequence::NextChild);
    actionNext->setStatusTip(tr("Move the focus to the next window"));
    connect(actionNext, &QAction::triggered, mdiArea, &QMdiArea::activateNextSubWindow);

    actionPrevious = new QAction(tr("Pre&vious"), this);
    actionPrevious->setShortcuts(QKeySequence::PreviousChild);
    actionPrevious->setStatusTip(tr("Move the focus to the previous "
                                 "window"));
    connect(actionPrevious, &QAction::triggered, mdiArea, &QMdiArea::activatePreviousSubWindow);

    actionWindowMenuSeparator = new QAction(this);
    actionWindowMenuSeparator->setSeparator(true);

//    updateWindowMenu();

    menuBar()->addSeparator();

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

//    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &ApplicationWindow::aboutQtFrictmap);
//    aboutAct->setStatusTip(tr("Show the application's About box"));

    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
}

void ApplicationWindow::initStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

