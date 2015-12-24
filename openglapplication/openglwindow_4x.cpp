#include "%{WindowClassHeaderFileName}"
#include <QDebug>
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QImage>
#include <math.h>

static float quadVertices[] = { -1.0,  1.0, 0.0, 0.0, 0.0,
                                 1.0,  1.0, 0.0, 1.0, 0.0,
                                 1.0, -1.0, 0.0, 1.0, 1.0,
                                -1.0, -1.0, 0.0, 0.0, 1.0 };

static unsigned short quadIndices[] = { 0, 1, 3, 2 };

%{WindowClass}::%{WindowClass}() :
    m_frames(0),
    m_time(0.0f)
{
    QSurfaceFormat f;
    f.setDepthBufferSize(24);
    f.setSamples(4);
    f.setSwapInterval(1);
    f.setVersion(4, 1);
    f.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(f);
}

QOpenGLBuffer* %{WindowClass}::createBuffer(QOpenGLBuffer::Type type,
                                            QOpenGLBuffer::UsagePattern usagePattern,
                                            void *data, int byteSize)
{
    QOpenGLBuffer* b = new QOpenGLBuffer(type);
    b->setUsagePattern(usagePattern);
    if (!b->create())
        qFatal("Couldn't create buffer");
    b->bind();
    b->allocate(data, byteSize);
    b->release();
    return b;
}

void %{WindowClass}::initializeGL()
{
    if (!initializeOpenGLFunctions())
        qFatal("Couldn't initialze OpenGL functions");

    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple_vs.glsl");
    m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple_fs.glsl");
    if (!m_shader->link())
        qFatal(qPrintable(m_shader->log()));

    m_vbo = createBuffer(QOpenGLBuffer::VertexBuffer, QOpenGLBuffer::StaticDraw, quadVertices, sizeof(quadVertices));
    m_ibo = createBuffer(QOpenGLBuffer::IndexBuffer, QOpenGLBuffer::StaticDraw, quadIndices, sizeof(quadIndices));
    m_vbo->isCreated();
    m_ibo->isCreated();

    m_vao = new QOpenGLVertexArrayObject(this);
    m_vao->create();
    m_vao->bind();
    m_vbo->bind();
    m_ibo->bind();
    m_shader->setAttributeBuffer("aVertex", GL_FLOAT, 0, 3, 5 * sizeof(float));
    m_shader->setAttributeBuffer("aTexCoord0", GL_FLOAT, 3 * sizeof(float), 2, 5 * sizeof(float));
    m_shader->enableAttributeArray("aVertex");
    m_shader->enableAttributeArray("aTexCoord0");

    QImage i(":/data/texture.jpg");
    m_textureAspect = (float) i.width() / i.height();
    m_texture = new QOpenGLTexture(i);

    startTimer(1000);
}

void %{WindowClass}::paintGL()
{
    float ratio = devicePixelRatio();
    glViewport(0, 0, width() * ratio, height() * ratio);
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_shader->bind();
    m_texture->bind();

    QMatrix4x4 mvp;
    mvp.perspective(45, (float) width() / height(), 2.0, 300.0);
    mvp.translate(0, 0, -100.0);
    mvp.rotate(m_time * 30, 0.5, 1.5, 1.0);
    mvp.scale(20.0 * m_textureAspect, 20.0);
    m_shader->setUniformValue("uMvpMatrix", mvp);
    m_shader->setUniformValue("uTexture", 0);

    m_vao->bind();
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

    update();
    m_frames++;
    m_time += 0.016;
}

void %{WindowClass}::timerEvent(QTimerEvent *)
{
    qDebug() << "FPS:" << m_frames;
    m_frames = 0;
}
