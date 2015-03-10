#include "openglwidget.h"
#include <QOpenGLFunctions>
#include <QDebug>
#include <QSurfaceFormat>
#include <QOpenGLVertexArrayObject>
#include <iostream>
#include <QFileInfo>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_angle = 45.0f;
    m_time.start();
    m_lastTime = m_time.elapsed();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);

    float vertexPositions[] = {
        -0.5f,  0.5f,  -0.5f,
        0.5f, -0.5f,  -0.5f,
        -0.5f, -0.5f,  -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,

        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,

        -0.5f,  0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f
    };

    float vertexColors[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f
    };

    prepareShaderProgram();

    m_vao.create();
    m_vao.bind();

    /* vertex position buffer */


    m_vertexPositionBuffer.create();
    m_vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexPositionBuffer.bind();
    m_vertexPositionBuffer.allocate(vertexPositions, size*3*3*sizeof(float));

    /* vertex colors buffer */

    m_vertexColorBuffer.create();
    m_vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexColorBuffer.bind();
    m_vertexColorBuffer.allocate(vertexColors, size*3*3*sizeof(float));

    /* */
    m_shaderProgram.bind();

    m_vertexPositionBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertex");
    m_shaderProgram.setAttributeArray("vertex", GL_FLOAT, 0, 3);

    m_vertexColorBuffer.bind();
    m_shaderProgram.enableAttributeArray("color");
    m_shaderProgram.setAttributeArray("color", GL_FLOAT, 0, 3);

    /* matrices */

    m_projectionMatrix.setToIdentity();
    m_viewMatrix.setToIdentity();
    m_modelMatrix.setToIdentity();

    m_viewMatrix.rotate(-20.0f, 1.0f, 0.0f, 0.0f);

    m_shaderProgram.setUniformValue("projection_matrix", m_projectionMatrix);
    m_shaderProgram.setUniformValue("view_matrix", m_viewMatrix);
    m_shaderProgram.setUniformValue("model_matrix", m_modelMatrix);

    m_vao.release();

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(10);

}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_vao.bind();
    m_shaderProgram.bind();

    /* rotating model */
    m_angle = (m_time.elapsed() - m_lastTime) * 90 * 0.001;
    m_angle = m_angle%360;
    m_modelMatrix.rotate(m_angle, 0.0f, 1.0f, 0.0f);
    m_shaderProgram.setUniformValue("model_matrix", m_modelMatrix);

    glDrawArrays(GL_TRIANGLES, 0, size*3);

    m_lastTime = m_time.elapsed();
    m_vao.release();
}

void OpenGLWidget::prepareShaderProgram()
{
    if(!m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex"))
        qDebug() << "Couldn't compile vertex shader. " << m_shaderProgram.log();
    if(!m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment"))
        qDebug() << "Couldn't compile fragment shader. " << m_shaderProgram.log();
    if(!m_shaderProgram.link())
        qDebug() << "Couldn't link shader program. " << m_shaderProgram.log();
}

OpenGLWidget::~OpenGLWidget()
{

}



