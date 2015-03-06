#include "mainwindow.h"
#include <QHBoxLayout>
#include "openglwidget.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *window = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    QVBoxLayout *left_panel = new QVBoxLayout;
    opengl_widget = new OpenGLWidget;
    opengl_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    layout->addLayout(left_panel);
    layout->addWidget(opengl_widget);

    window->setLayout(layout);
    setCentralWidget(window);

    left_panel->addWidget(new QLabel("Panel"));
}

MainWindow::~MainWindow()
{

}
