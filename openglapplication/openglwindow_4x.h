#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_4_1_Core>

class QOpenGLShaderProgram;
class QOpenGLTexture;

class %{WindowClass} : public QOpenGLWindow, public QOpenGLFunctions_4_1_Core
{
public:
    %{WindowClass}();

private:
    void paintGL();
    void initializeGL();
    void timerEvent(QTimerEvent *);

    QOpenGLBuffer* createBuffer(QOpenGLBuffer::Type type,
                                QOpenGLBuffer::UsagePattern,
                                void* data, int byteSize);

private:
    QOpenGLShaderProgram* m_shader;
    QOpenGLTexture* m_texture;
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer* m_vbo;
    QOpenGLBuffer* m_ibo;
    float m_textureAspect;
    int m_frames;
    float m_time;
};
