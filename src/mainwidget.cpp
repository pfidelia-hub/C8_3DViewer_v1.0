#include "mainwidget.h"
#include <QMouseEvent>

#include <cmath>
#include <QTime>

MainWidget::~MainWidget() {
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    // delete texture;
    delete geometries;
    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e) {
    // Save mouse press position
    mousePressPosition = QVector2D(e->position());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e) {
    return;
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->position()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *) {
    QString strCount = QString::number(counter);
        grabFramebuffer().save("screenshots/" + strCount + ".jpg", NULL, 100);
        counter--;
        qDebug() << QTime ::currentTime();
        if (counter == 0) {
            system("touch gif.sh");
            system("convert -delay 10 -loop 0 -alpha on -layers optimize -dispose previous $(ls -1 screenshots/*.jpg | sort -V) ./gifka.gif");
            timer.stop();
        }

}
//! [1]

void MainWidget::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    // initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]

    geometries = new GeometryEngine;
}

//! [3]
void MainWidget::initShaders() {
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]
void MainWidget::initColors() {
    qDebug() << "initColors";
    glClearColor(color_back->redF(), color_back->greenF(), color_back->blueF(), 0);

    int vertexLocation = program.attributeLocation("vertex");
    int colorLocation = program.uniformLocation("color");

    program.enableAttributeArray(vertexLocation);
    program.setUniformValue(colorLocation, *color);
    program.disableAttributeArray(vertexLocation);
}

void MainWidget::initColorsVer() {
//    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(color_back->redF(), color_back->greenF(), color_back->blueF(), 0);

    qDebug() << "initColorsVer";
//    color_ver->setRgb(0,0,0);

    int vertexLocation = program.attributeLocation("vertex");
    int colorLocation = program.uniformLocation("color");

    program.enableAttributeArray(vertexLocation);
    program.setUniformValue(colorLocation, *color_ver);
    program.disableAttributeArray(vertexLocation);
}

void MainWidget::resizeGL(int w, int h) {
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 70.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();
    if (proj_type == parallel) {
        QRectF orthoRectangle;
        orthoRectangle.setHeight(h);
        orthoRectangle.setWidth(w);
        projection.ortho(-10.0, 10.0, -10.0, 10.0, -100, 100);
    } else {
        projection.perspective(fov, aspect, zNear, zFar);
    }
}
//! [5]

void MainWidget::paintGL() {
    qDebug() << "paintGL";
    glLineWidth(line_width);

    initColors();

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    program.setUniformValue("mvp_matrix", projection * matrix);

    if (flag_dotted) {
//        glEnable(GL_LINE_STIPPLE);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_LINE_STIPPLE);
//        glLineStipple(3, 0xFFF8);
        glLineStipple(2, 58360);
        geometries->drawCubeGeometry(&program);
        glDisable(GL_LINE_SMOOTH);
        glDisable(GL_LINE_STIPPLE);
//        glDisable(GL_LINE_STIPPLE);
    } else {
        geometries->drawCubeGeometry(&program);
    }
    initColorsVer();
    geometries->drawDots(&program);
}

void MainWidget::upd() {
//    initColors();
    update();
    qDebug() << "update";
}

void MainWidget::setTimer() {
    counter = 50;
    system("mkdir screenshots");
    timer.start(100, this);
}
