#pragma once

#include <calib/core/camera/models/cam_model.hpp>

namespace calib
{
struct Mei : public CamModelBase<4>
{
    CALIB_MARCO_MAKE_SMART_PTR(Mei)
};
} // namespace calib
