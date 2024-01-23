#pragma once
#include <calib/utils/marco/marco.hpp>
#include <ui_frontend/utils/shader.h>
/* using Drawable = Shader; */
class Drawable : public Shader
{
    CALIB_MARCO_MAKE_SMART_PTR(Drawable)
  public:
    Drawable(const std::string &vs_path, const std::string &fs_path) : Shader(vs_path, fs_path)
    {
    }

    virtual bool Draw() = 0;
};
