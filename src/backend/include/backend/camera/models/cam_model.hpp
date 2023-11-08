#pragma once
#include <utils/marco/marco.hpp>
#include <calib/types/base/geometry.hpp>
#include <ceres/ceres.h>

namespace calib
{
enum class ModelType : uint
{
    PINHOLE,
    KANNALA_BRANDT,
    MEI,
    SCARAMUZZA
};

struct CamModelBase
{
    CALIB_MARCO_MAKE_SMART_PTR(CamModelBase)

    virtual ~CamModelBase() = default;
    virtual Vec2 project(Vec3 P) const = 0;
    virtual Vec3 back_project(Vec2 p, double depth) const = 0;

    double K[4] = {0};
    double &fx = K[0], &fy = K[1], &cx = K[2], &cy = K[3];
};

} // namespace calib
