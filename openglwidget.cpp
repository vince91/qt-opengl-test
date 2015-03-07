#include "openglwidget.h"
#include <QOpenGLFunctions>
#include <QDebug>
#include <QSurfaceFormat>
#include <QOpenGLVertexArrayObject>
#include <iostream>
#include <QFileInfo>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);

    float vertexPositions[] = {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f};

    float vertexColors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f };

    m_vao.create();
    m_vao.bind();

    /* vertex position buffer */

    m_vertexPositionBuffer.create();
    m_vertexPositionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexPositionBuffer.bind();
    m_vertexPositionBuffer.allocate(vertexPositions, 3*3*sizeof(float));

    /* vertex colors buffer */

    m_vertexColorBuffer.create();
    m_vertexColorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexColorBuffer.bind();
    m_vertexColorBuffer.allocate(vertexColors, 3*3*sizeof(float));

    /* prepare shader program */

    if(!m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex"))
        qDebug() << "Couldn't compile vertex shader. " << m_shaderProgram.log();
    if(!m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragment"))
        qDebug() << "Couldn't compile fragment shader. " << m_shaderProgram.log();
    if(!m_shaderProgram.link())
        qDebug() << "Couldn't link shader program. " << m_shaderProgram.log();

    m_shaderProgram.bind();

    m_vertexPositionBuffer.bind();
    m_shaderProgram.enableAttributeArray("vertex");
    m_shaderProgram.setAttributeArray("vertex", GL_FLOAT, 0, 3);

    m_vertexColorBuffer.bind();
    m_shaderProgram.enableAttributeArray("color");
    m_shaderProgram.setAttributeArray("color", GL_FLOAT, 0, 3);

    m_vao.release();
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

    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_vao.release();
}

OpenGLWidget::~OpenGLWidget()
{

}



