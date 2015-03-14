#include "mainwindow.h"
#include <QHBoxLayout>
#include "openglwidget.h"
#include <QLabel>
#include <QGroupBox>
#include <QAction>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("OpenGL");

    QWidget *window = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    QVBoxLayout *left_panel = new QVBoxLayout;

    m_openglWidget = new OpenGLWidget;
    m_openglWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    layout->addLayout(left_panel);
    layout->addWidget(m_openglWidget);

    layout->setContentsMargins(0,0,0,0);

    window->setLayout(layout);
    setCentralWidget(window);

    /* toolbar */

    QAction *rotationAction = new QAction(QIcon(":/icons/rotation.png"), "Toggle rotation", this);
    rotationAction->setCheckable(true);
    connect(rotationAction, SIGNAL(triggered()), m_openglWidget, SLOT(toggleRotation()));
    QToolBar *toolBar = addToolBar("Toolbar");
    toolBar->addAction(rotationAction);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    m_openglWidget->keyPress(event);
}

MainWindow::~MainWindow()
{

}
