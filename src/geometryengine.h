#ifndef SRC_GEOMETRYENGINE_H_
#define SRC_GEOMETRYENGINE_H_

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <qmath.h>
#include <QColor>

extern "C" {
#include "3d_viewer.h"
#include "affine_transformation.h"
}

class GeometryEngine : public QOpenGLFunctions {
    struct VertexData {
      QVector3D position;
    };

 public:
  int flag_ver = 0;
  int flag_sphere = 1;
  int size_ver = 2;
  GeometryEngine();
  virtual ~GeometryEngine();
  s21_data figure;

  void drawCubeGeometry(QOpenGLShaderProgram *program);
  void drawDots(QOpenGLShaderProgram *program);
  void initCubeGeometry(char *path);

  void Xrotation(float degree);
  void Yrotation(float degree);
  void Zrotation(float degree);

  void Xmoving(float dst);
  void Ymoving(float dst);
  void Zmoving(float dst);

  void XYZscale(float scale);
  void Xscale(float scale);
  void Yscale(float scale);
  void Zscale(float scale);

 private:
  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;

  GLsizei lines;
};

#endif  //  SRC_GEOMETRYENGINE_H_
