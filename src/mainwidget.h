#ifndef SRC_MAINWIDGET_H_
#define SRC_MAINWIDGET_H_

#include "geometryengine.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QColorDialog>
#include <QTimer>

class GeometryEngine;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  using QOpenGLWidget::QOpenGLWidget;
  ~MainWidget();
  GeometryEngine *geometries = nullptr;
  QOpenGLShaderProgram program;
  void paintGL() override;
  void upd();
  void initColors();
  void initColorsVer();
  QColor *color = new QColor(255, 249, 0, 255);
  QColor *color_back = new QColor(182, 0, 255, 255);
  QColor *color_ver = new QColor(17, 242, 0, 255);
  int line_width = 1;
  int flag_dotted = 0;
  void resizeGL(int w, int h) override;
  enum {
    parallel = 0,
    central = 1
  } proj_type;

  void setTimer();

protected:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void timerEvent(QTimerEvent *e) override;

  void initializeGL() override;

  void initShaders();

 private:
  QBasicTimer timer;
  unsigned counter = 0;
  QMatrix4x4 projection;

  QVector2D mousePressPosition;
  QVector3D rotationAxis;
  qreal angularSpeed = 0;
  QQuaternion rotation;
};

#endif  //  SRC_MAINWIDGET_H_
