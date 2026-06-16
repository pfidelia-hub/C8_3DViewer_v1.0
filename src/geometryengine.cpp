#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>


GeometryEngine::GeometryEngine() : indexBuf(QOpenGLBuffer::IndexBuffer) {
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry("");
}

GeometryEngine::~GeometryEngine() {
    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::initCubeGeometry(char *path) {
//    const char *path = "/Users/vjacki/Desktop/c.obj";
    figure = scan_obj(path);
    if (!strlen(path)) {
        figure = scan_obj("/Users/pfidelia/Desktop/cube.obj");
    }

    QVector<VertexData> vertices;
    for (unsigned i = 0; i < figure.count_vertexes; ++i) {
        VertexData tmp_vert = {QVector3D(figure.vertexes[i].x, figure.vertexes[i].y, figure.vertexes[i].z)};
        vertices.push_back(tmp_vert);
    }
    QVector<GLuint> indices;
    for (unsigned i = 0; i < figure.count_facets; ++i) {
        for (unsigned j = 0; j < figure.polygons[i].vertexes_in_facets - 1; ++j) {
            indices.push_back(figure.polygons[i].vertexes[j] - 1);
            indices.push_back(figure.polygons[i].vertexes[j + 1] - 1);
        }
        indices.push_back(figure.polygons[i].vertexes[0] - 1);
        indices.push_back(figure.polygons[i].vertexes[figure.polygons[i].vertexes_in_facets - 1] - 1);
    }

    lines = indices.length();

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices.data(), vertices.length() * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices.data(), lines * sizeof(GLuint));
    qDebug() << "a";
}

void GeometryEngine::Xrotation(float degree) {
    rotate_x(qDegreesToRadians(degree), figure.vertexes, figure.count_vertexes);
    qDebug() << qDegreesToRadians(degree);
}

void GeometryEngine::Yrotation(float degree) {
    rotate_y(qDegreesToRadians(degree), figure.vertexes, figure.count_vertexes);
}

void GeometryEngine::Zrotation(float degree) {
    rotate_z(qDegreesToRadians(degree), figure.vertexes, figure.count_vertexes);
}

void GeometryEngine::Xmoving(float dst) {
    mov_x(dst, figure.vertexes, figure.count_vertexes);
    qDebug() << dst;
}

void GeometryEngine::Ymoving(float dst) {
    mov_y(dst, figure.vertexes, figure.count_vertexes);
}

void GeometryEngine::Zmoving(float dst) {
    mov_z(dst, figure.vertexes, figure.count_vertexes);
}

void GeometryEngine::XYZscale(float scale) {
    scale_xyz(scale, figure.vertexes, figure.count_vertexes);
}

void GeometryEngine::Xscale(float scale) {
    scale_x(scale, figure.vertexes, figure.count_vertexes);
}

void GeometryEngine::Yscale(float scale) {
    scale_y(scale, figure.vertexes, figure.count_vertexes);
}

void GeometryEngine::Zscale(float scale) {
    scale_z(scale, figure.vertexes, figure.count_vertexes);
}

void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program) {
    // Tell OpenGL which VBOs to use
    indexBuf.bind();
//    rotate_x(0.04f,figure.vertexes,figure.count_vertexes);
    if (arrayBuf.isCreated()) {
        arrayBuf.destroy();
        arrayBuf.create();
        arrayBuf.bind();
        QVector<VertexData> vertices;
        for (unsigned i = 0; i < figure.count_vertexes; ++i) {
            VertexData
                tmp_vert = {QVector3D(figure.vertexes[i].x, figure.vertexes[i].y, figure.vertexes[i].z)};
            vertices.push_back(tmp_vert);
        }
        arrayBuf.allocate(vertices.data(), vertices.length() * sizeof(VertexData));
    }
    arrayBuf.bind();
    // Offset for position
    quintptr offset = 0;
    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    glDrawElements(GL_LINES, lines, GL_UNSIGNED_INT, nullptr);
    qDebug() << "s";
    qDebug() << figure.count_facets;
    qDebug() << figure.count_vertexes;
}

void GeometryEngine::drawDots(QOpenGLShaderProgram *program) {
    if (!flag_ver) return;
        if (flag_sphere) {
            glDisable(GL_POINT_SIZE);
            glEnable(GL_POINT_SMOOTH);
        } else {
            glDisable(GL_POINT_SMOOTH);
            glEnable(GL_POINT_SIZE);
        }

        glPointSize(size_ver);

        indexBuf.bind();
    //    rotate_x(0.04f,figure.vertexes,figure.count_vertexes);
        if (arrayBuf.isCreated()) {
            arrayBuf.destroy();
            arrayBuf.create();
            arrayBuf.bind();
            QVector<VertexData> vertices;
            for (unsigned i = 0; i < figure.count_vertexes; ++i) {
                VertexData
                    tmp_vert = {QVector3D(figure.vertexes[i].x, figure.vertexes[i].y, figure.vertexes[i].z)};
                vertices.push_back(tmp_vert);
            }
            arrayBuf.allocate(vertices.data(), vertices.length() * sizeof(VertexData));
        }
        arrayBuf.bind();
        // Offset for position
        quintptr offset = 0;
        // Tell OpenGL programmable pipeline how to locate vertex position data
        int vertexLocation = program->attributeLocation("a_position");
        program->enableAttributeArray(vertexLocation);
        program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
        // Offset for texture coordinate
        offset += sizeof(QVector3D);

        // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
        int texcoordLocation = program->attributeLocation("a_texcoord");
        program->enableAttributeArray(texcoordLocation);
        program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));
        glDrawElements(GL_POINTS, lines, GL_UNSIGNED_INT, nullptr);
}

