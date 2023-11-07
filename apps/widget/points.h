#pragma once
#include <QMouseEvent>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <calib/types/base/geometry.hpp>

class PointCloudOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{

    Q_OBJECT
  public:
    struct Config
    {
        bool pointcloud_show = true;
        int pointcloud_size = 5;
        QColor pointcloud_color;
    };

  public:
    PointCloudOpenGLWidget(QWidget *parent = 0);
    ~PointCloudOpenGLWidget();
    void addPoints(const QVector<QVector3D> &points);
    void addPoints(const std::vector<calib::Vec3> &points);

    void clean();
    void update_show();
    void setConfig(Config &config);

  protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    virtual unsigned int drawMeshline(float size, int count);
    virtual void drawCooraxis(float length);
    virtual unsigned int drawPointdata(std::vector<float> &pointVertexs);

  protected:
    QOpenGLShaderProgram m_shaderProgramMesh;
    QOpenGLShaderProgram m_shaderProgramAxis;
    QOpenGLShaderProgram m_shaderProgramPoint;

    unsigned int m_VBO_MeshLine;
    unsigned int m_VAO_MeshLine;

    unsigned int m_VBO_Axis;
    unsigned int m_VAO_Axis;

    unsigned int m_VBO_Point;
    unsigned int m_VAO_Point;

    std::vector<float> m_pointData;
    unsigned int m_pointCount;
    unsigned int m_vertexCount;

    float m_xRotate;
    float m_zRotate;
    float m_xTrans;
    float m_yTrans;
    float m_zoom;

    QPoint lastPos;
    Config conf;
};
