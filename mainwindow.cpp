#include "mainwindow.h"
#include <QHBoxLayout>
#include "openglwidget.h"
#include <QLabel>
#include <QGroupBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("OpenGL");

    QWidget *window = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    QVBoxLayout *left_panel = new QVBoxLayout;
    QGroupBox *groupBox = new QGroupBox("Paramètres");

    opengl_widget = new OpenGLWidget;
    opengl_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    layout->addLayout(left_panel);
    layout->addWidget(opengl_widget);


    layout->setContentsMargins(0,0,0,0);

    window->setLayout(layout);
    setCentralWidget(window);

    left_panel->addWidget(groupBox);
}

MainWindow::~MainWindow()
{

}
