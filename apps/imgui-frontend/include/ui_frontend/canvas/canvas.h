#pragma once

#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale
#include <glm/ext/scalar_constants.hpp>  // glm::pi
#include <glm/gtc/type_ptr.hpp>          // value_ptr//
#include <glm/mat4x4.hpp>                // glm::mat4
#include <glm/vec3.hpp>                  // glm::vec3
#include <glm/vec4.hpp>                  // glm::vec4
#include <calib/utils/marco/marco.hpp>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>

#include "drawable.h"
#include "framebuffer_shader.h"

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

struct Points : public Drawable
{
    int point_count = 0;
    float point_size = 2; // px
    Points() : Drawable(R"*(./shaders/shader_point.vs)*", R"*(./shaders/shader_point.fs)*"){
        
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

struct MeshGrid : public Drawable
{
    float mesh_size = 1.0f;
    int mesh_count = 20;
    MeshGrid() : Drawable(R"*(./shaders/shader_mesh.vs)*", R"*(./shaders/shader_mesh.fs)*")
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

struct Axis : public Drawable
{
    Axis() : Drawable(R"*(./shaders/shader_axis.vs)*", R"*(./shaders/shader_axis.fs)*")
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
        glLineWidth(2.0f);
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

class Canvas : public FrameBufferShader
{
  public:
    Canvas(int width, int height) : FrameBufferShader(width, height)
    {
    }
    ~Canvas()
    {
    }
    virtual void Clean()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
        // 1. draw axis in canvas
        /* if (!axis.Draw()) */
        /*     return false; */
        auto pvm = glm::mat4(1.0f);
        /* glm::translate(mvp, glm::vec3(1.0, 0, 0)); */
        static float temp = 0;

        /* pvm = glm::rotate(pvm, glm::radians(temp++), glm::vec3(1.0, 1.0, 0)); */
        glm::mat4 mat_p = glm::perspective(glm::radians(45.f), 4.0f / 4.0f, 0.001f, 1000.f);
        pvm = mat_p;
        // create transformations
        glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 50.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0));

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(m_zoom), (float)fb_width / (float)fb_height, 0.1f, 100.0f);

        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(m_x_trans, m_y_trans, 0.0));
        model = glm::rotate(model, glm::radians(m_x_rot), glm::vec3(1.0, 0.0, 0.0));
        model = glm::rotate(model, glm::radians(m_z_rot), glm::vec3(0.0, 0.0, 1.0));
        /* LOGM(model); */
        pvm = projection * view * model;
        axis.setUniformMatrix4x4("pvm", 1, GL_FALSE, glm::value_ptr(pvm));
        if (!axis.Draw())
            return false;
        mesh_grid.setUniformMatrix4x4("pvm", 1, GL_FALSE, glm::value_ptr(pvm));
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
    float m_x_rot = 0;
    float m_z_rot = 0;
    float m_x_trans = 0.0;
    float m_y_trans = 0.0;
    float m_zoom = 45.0;

  private:
    Axis axis;
    MeshGrid mesh_grid;
    std::list<Drawable::Sptr> draw_lists;
};
