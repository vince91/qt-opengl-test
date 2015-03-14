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
    void keyPress(QKeyEvent *);

    ~OpenGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void wheelEvent(QWheelEvent *);

private:
    void prepareShaderProgram();
    void updateCamera();

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

    QVector3D m_eye, m_center;
    float m_cameraPhi, m_cameraTheta, m_cameraDistance;

public slots:
    void toggleRotation();


};

#endif // OPENGLWIDGET_H
