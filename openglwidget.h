#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QTimer>
#include <QTime>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    void prepareShaderProgram();

    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vertexPositionBuffer;
    QOpenGLBuffer m_vertexColorBuffer;
    QOpenGLShaderProgram m_shaderProgram;

    QMatrix4x4 m_projectionMatrix, m_viewMatrix, m_modelMatrix;

    QTimer m_timer;
    QTime m_time;

    int m_angle, m_lastTime, size;
    float m_fov;

    bool m_rotation;

public slots:
    void toggleRotation();


};

#endif // OPENGLWIDGET_H
