#pragma once

#include <calib/utils/marco/marco.hpp>
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale
#include <glm/ext/scalar_constants.hpp>  // glm::pi
#include <glm/gtc/type_ptr.hpp>          // value_ptr//
#include <glm/mat4x4.hpp>                // glm::mat4
#include <glm/vec3.hpp>                  // glm::vec3
#include <glm/vec4.hpp>                  // glm::vec4
#include <list>
#include <string>
#include <unordered_set>
#include <vector>

#include "drawable.h"
#include "framebuffer_shader.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

void LOGM(const glm::mat4 &mat)
{
    const float *data = glm::value_ptr(mat);
    LOGI("----------");
    for (int i = 0; i < 16; i += 4)
    {
        LOGI("{} {} {} {}", data[i], data[i + 1], data[i + 2], data[i + 3]);
    }
    LOGI("----------");
}

const char *point_vs = "#version 330 core\n\
layout (location = 0) in vec3 aPos;\n\
layout (location = 1) in vec3 aIntensity;\n\
uniform mat4 pvm;\n\
out vec3 ourColor;\n\
void main()\n\
{\n\
    gl_Position = projection * view * model * vec4(aPos, 1.0);\n\
    float height = smoothstep(-10.0, 10.0, aPos.z);\n\
    ourColor = vec3(height, 0.5f, 0.5f);\n\
}\n\
";

const char *point_fs = " #version 330 core\n\
out vec4 FragColor;\n\
in vec3 ourColor;\n\
void main()\n\
{\n\
    FragColor = vec4(ourColor, 1.0f);\n\
}\n\
";

struct Points : public Drawable
{
    int point_count = 0;
    float point_size = 2; // px
    Points()
        : Drawable(point_vs, point_fs){

          };
    bool Draw()
    {
        Shader::Bind();
        glBindVertexArray(vao);
        glLineWidth(1.0f);
        glDrawArrays(GL_POINT, 0, point_count);
        glBindVertexArray(0);
        Shader::UnBind();
        return true;
    }
};

const char *mesh_vs = "#version 330 core \n\
layout (location = 0) in vec3 aPos;\n\
uniform mat4 pvm;\n\
void main()\n\
{\n\
    gl_Position = pvm * vec4(aPos, 1.0);\n\
}\n\
";
const char *mesh_fs = "\
#version 330 core\n\
out vec4 FragColor;\n\
void main()\n\
{\n\
    FragColor = vec4(1.f, 1.0f, 1.0f, 1.0f);\n\
}\n\
";
struct MeshGrid : public Drawable
{
    float mesh_size = 1.0f;
    int mesh_count = 20;
    MeshGrid() : Drawable(mesh_vs, mesh_fs)
    {
        init(mesh_size, mesh_count);
    };

    void init(float size, int count)
    {
        LOGI("mesh size {} count {}", mesh_size, mesh_count);
        std::vector<float> mesh_vertexs;
        unsigned int vertex_count = 0;

        float start = count * (size / 2);
        float pos_x = start, pos_z = start;

        for (int i = 0; i <= count; ++i)
        {
            mesh_vertexs.push_back(pos_x);
            mesh_vertexs.push_back(start);
            mesh_vertexs.push_back(0);

            mesh_vertexs.push_back(pos_x);
            mesh_vertexs.push_back(-start);
            mesh_vertexs.push_back(0);

            mesh_vertexs.push_back(start);
            mesh_vertexs.push_back(pos_z);
            mesh_vertexs.push_back(0);

            mesh_vertexs.push_back(-start);
            mesh_vertexs.push_back(pos_z);
            mesh_vertexs.push_back(0);

            pos_x = pos_x - size;
            pos_z = pos_z - size;
        }

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, mesh_vertexs.size() * sizeof(float), &mesh_vertexs[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        draw_count = (int)mesh_vertexs.size() / 3;
    }
    bool Draw()
    {
        Shader::Bind();
        glBindVertexArray(vao);
        glLineWidth(1.0f);
        glDrawArrays(GL_LINES, 0, draw_count);
        glBindVertexArray(0);
        Shader::UnBind();
        return true;
    }
    virtual bool Render()
    {
        return true;
    }
    /* const float vertices[9] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f}; */
    float m_axis_len = 2.0;
    int draw_count;
};
// clang-format off
    

const char *axis_vs = "\
    #version 330 core\n\
    layout (location = 0) in vec3 aPos;\n\
    layout (location = 0) in vec3 aColor;\n\
    out vec3 vertexColor; \n\
    uniform mat4 pvm;\n\
    void main()\
    {\n\
        gl_Position = pvm * vec4(aPos, 1.0);\n\
        vertexColor = aColor;\n\
    }\n\
";

const char *axis_fs = "\
    #version 330 core \n\
    in vec3 vertexColor;\n\
    out vec4 FragColor;\n\
    void main() \n\
    { \n\
        FragColor = vec4(vertexColor, 1.0); \n\
    } \n\
";
// clang-format on

struct Axis : public Drawable
{

    Axis() : Drawable(axis_vs, axis_fs)
    {
        init();
    };

    void init()
    {
        std::vector<float> axis_vertexs = {
            // x,y ,z ,r, g, b
            0.0, 0.0, 0.0, 1.0, 0.0, 0.0, m_axis_len, 0.0,        0.0,        1.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,        m_axis_len, 0.0,        0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,        0.0,        m_axis_len, 0.0, 0.0, 1.0,
        };
        // 1. 绑定VAO
        glBindVertexArray(vao);
        // 2. 把顶点数组复制到缓冲中供OpenGL使用
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, axis_vertexs.size() * sizeof(float), &axis_vertexs[0], GL_STATIC_DRAW);
        // 3. 设置顶点属性指针
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    bool Draw()
    {
        Shader::Bind();
        glBindVertexArray(vao);
        glLineWidth(5.0f);
        glDrawArrays(GL_LINE_STRIP, 0, 6);
        glBindVertexArray(0);
        Shader::UnBind();
        return true;
    }
    virtual bool Render()
    {
        return true;
    }
    /* const float vertices[9] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f}; */
    float m_axis_len = 2.0;
};

/* Eigen::Matrix4f lookAt(Eigen::Vector3f position, Eigen::Vector3f target, Eigen::Vector3f world_up) */
/* { */
/*     //  Calculate cameraDirection */
/*     Eigen::Vector3f z_axis = position - target; */
/*     z_axis.normalize(); */
/*     //  Get positive right axis vector */
/*     Eigen::Vector3f x_axis = world_up; */
/*     x_axis.normalize(); */
/*     x_axis = x_axis.cross(z_axis); */
/*     x_axis.normalize(); */
/*  */
/*     //  Calculate camera up vector */
/*     Eigen::Vector3f y_axis = z_axis; */
/*     y_axis = y_axis.cross(x_axis); */
/*  */
/*     //  Create translation matrix */
/*     Eigen::Matrix4f translation = Eigen::Matrix4f::Identity(); */
/*     translation(3, 0) = -position(0); //  Fourth column, first row */
/*     translation(3, 1) = -position(1); */
/*     translation(3, 2) = -position(2); */
/*  */
/*     //  Create rotation matrix */
/*     Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity(); */
/*     rotation(0, 0) = x_axis(0); //  First column, first row */
/*     rotation(1, 0) = x_axis(1); */
/*     rotation(2, 0) = x_axis(2); */
/*     rotation(0, 1) = y_axis(0); //  First column, second row */
/*     rotation(1, 1) = y_axis(1); */
/*     rotation(2, 1) = y_axis(2); */
/*     rotation(0, 2) = z_axis(0); //  First column, third row */
/*     rotation(1, 2) = z_axis(1); */
/*     rotation(2, 2) = z_axis(2); */
/*     return rotation * translation; */
/* } */

class Camera
{
  public:
    Camera(const float width, const float height) : fb_width(width), fb_height(height)
    {
    }
    Eigen::Matrix4f getPVM()
    {
        Eigen::Affine3f model = Eigen::Affine3f::Identity();
        model.translate(Eigen::Vector3f(m_x_trans, m_y_trans, 0.0));        // 平移
        model.rotate(Eigen::AngleAxisf(m_x_rot / 180 * M_PI, Eigen::Vector3f::UnitX())); // 绕X轴旋转
        model.rotate(Eigen::AngleAxisf(m_z_rot / 180 * M_PI, Eigen::Vector3f::UnitZ())); // 绕X轴旋转

        // 设置视图矩阵
        Eigen::Affine3f view = Eigen::Affine3f::Identity();
        Eigen::Vector3f eye(0, 0, 50.0);   // 相机位置
        Eigen::Vector3f center(0, 0, 1.0); // 相机看向的点
        Eigen::Vector3f up(0, 1, 0);       // 相机的向上向量
        view = lookAt(eye, center, up);

        // 设置投影矩阵
        float near = 0.1f;                                      // 近裁剪面
        float far = 100.0f;                                     // 远裁剪面
        float fov = m_zoom / 180 * M_PI;                        // 垂直视场角度 (弧度)
        float aspectRatio = (float)fb_width / (float)fb_height; // 宽高比
        const float tanHalfFovy = tan(0.5 * fov);

        Eigen::Matrix4f projection = Eigen::Matrix4f::Zero();
        projection = perspective(m_zoom, aspectRatio, near, far);
        // 计算总的MVP矩阵
        return (projection * view.matrix() * model.matrix());
    }

    Eigen::Matrix4f perspective(float fovy, float aspect, float zNear, float zFar)
    {
        Eigen::Transform<float, 3, Eigen::Projective> tr;
        tr.matrix().setZero();
        assert(aspect > 0);
        assert(zFar > zNear);
        assert(zNear > 0);
        float radf = M_PI * fovy / 180.0;
        float tan_half_fovy = std::tan(radf / 2.0);
        tr(0, 0) = 1.0 / (aspect * tan_half_fovy);
        tr(1, 1) = 1.0 / (tan_half_fovy);
        tr(2, 2) = -(zFar + zNear) / (zFar - zNear);
        tr(3, 2) = -1.0;
        tr(2, 3) = -(2.0 * zFar * zNear) / (zFar - zNear);
        return tr.matrix();
    }

    Eigen::Matrix4f lookAt(Eigen::Vector3f const &eye, Eigen::Vector3f const &center, Eigen::Vector3f const &up)
    {
        Eigen::Vector3f f = (center - eye).normalized();
        Eigen::Vector3f u = up.normalized();
        Eigen::Vector3f s = f.cross(u).normalized();
        u = s.cross(f);
        Eigen::Matrix4f mat = Eigen::Matrix4f::Zero();
        mat(0, 0) = s.x();
        mat(0, 1) = s.y();
        mat(0, 2) = s.z();
        mat(0, 3) = -s.dot(eye);
        mat(1, 0) = u.x();
        mat(1, 1) = u.y();
        mat(1, 2) = u.z();
        mat(1, 3) = -u.dot(eye);
        mat(2, 0) = -f.x();
        mat(2, 1) = -f.y();
        mat(2, 2) = -f.z();
        mat(2, 3) = f.dot(eye);
        mat.row(3) << 0, 0, 0, 1;
        return mat;
    }

    float m_x_rot = 0; // deg
    float m_z_rot = 0;
    float m_x_trans = 0.0;
    float m_y_trans = 0.0;
    float m_zoom = 45.0; // deg
    float fb_width = 1280;
    float fb_height = 960;
};

class Canvas : public FrameBufferShader
{
  public:
    Canvas(int width, int height) : FrameBufferShader(width, height), cam(width, height)
    {
    }
    ~Canvas()
    {
    }
    virtual void Clean()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glClearColor(0.18f, 0.18f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        draw_lists.clear();
    }
    virtual void AddDrawable(Drawable::Sptr pdrawable)
    {
        draw_lists.push_back(pdrawable);
    }
    virtual void RemoveDrawable(Drawable::Sptr pdrawable)
    {
        draw_lists.remove(pdrawable);
    }
    virtual bool Render()
    {
        glViewport(0, 0, fb_width, fb_height);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        Eigen::Matrix4f pvm_eigen = cam.getPVM();
        axis.setUniformMatrix4x4("pvm", 1, GL_FALSE, pvm_eigen.data());
        if (!axis.Draw())
            return false;
        mesh_grid.setUniformMatrix4x4("pvm", 1, GL_FALSE, pvm_eigen.data());
        if (!mesh_grid.Draw())
            return false;

        // draw all drawables in draw_lists;
        for (auto &draw : draw_lists)
        {
            if (draw->Draw())
            {
                return false;
            }
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        FrameBufferShader::RenderToTexture();
        return true;
    }

  public:
    Camera cam;

  private:
    Axis axis;
    MeshGrid mesh_grid;
    std::list<Drawable::Sptr> draw_lists;
};
