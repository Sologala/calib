#pragma once

#include <calib/core/camera/models/cam_model.hpp>
#include <calib/core/camera/rect/rectify.hpp>
namespace calib
{

class VCam
{
    CALIB_MARCO_MAKE_SMART_PTR(VCam)

  public:
    virtual Vec2 project(Vec3 P);

    CamModelBase::Ptr cam_model;
};
} // namespace calib
