#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "openglwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *);
private:
    OpenGLWidget *m_openglWidget;
};

#endif // MAINWINDOW_H
