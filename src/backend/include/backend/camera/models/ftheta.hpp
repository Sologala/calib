#pragma once
#include <backend/camera/models/cam_model.hpp>

namespace calib
{

namespace camodel
{
struct ftheta : public CamModelBase<3>
{
    virtual Vec2 project(Vec3 P) final
    {
        double norm = P.norm();
        Vec3 P_norm = P / norm;
        double &x = P.x();
        double &y = P.y();
        double &z = P.z();

        double theta = std::acos(z / std::max(norm, 0.000001));
        double r = std::sqrt(x * x + y * y);

        double phi = std::atan2(y, x);

        double k1 = paras[0];
        double k2 = paras[1];
        double k3 = paras[2];
        // double k4 = paras[3];

        double theta2 = theta * theta;
        double theta3 = theta2 * theta;
        double theta5 = theta3 * theta2;
        double theta7 = theta5 * theta2;

        double theta_d = theta + theta3 * k1 + theta5 * k2 + theta7 * k3;

        Vec2 p;
        p.x() = fx * theta_d * x / r + cx;
        p.y() = fy * theta_d * y / r + cy;
        return p;
    }

    virtual Vec3 back_project(Vec2) final
    {
    }
};
} // namespace camodel
} // namespace calib
