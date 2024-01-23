#pragma once

#include <calib/core/camera/models/cam_model.hpp>
namespace calib
{

struct Pinhole : public CamModelBase
{
    CALIB_MARCO_MAKE_SMART_PTR(Pinhole)

    virtual Vec2 project(Vec3 P) const override final
    {
        Vec2 uv;
        uv.x() = fx * P.x() / P.z() + cx;
        uv.y() = fy * P.y() / P.z() + cy;

        int a = float(1.0);
        return uv;
    };
    virtual Vec3 back_project(Vec2 p, ScalarType depth) const override final
    {
        Vec3 P_c;
        P_c.z() = 1.f;
        P_c.x() = (p.x() - cx) / fx;
        P_c.y() = (p.y() - cy) / fy;
        return depth * P_c;
    }

    struct ProjectErrorCostFunc
    {
      public:
        ProjectErrorCostFunc(const Vec3 P, const Vec2 p) : P(P), p(p)
        {
        }

        template <typename T> bool operator()(T *K, T *D, T *residuals) const
        {
            // residuals[0] = ud - img(0);
            // residuals[1] = vd - img(1);
            return true;
        }

        // 生成误差函数
        static ceres::CostFunction *Create(Eigen::Vector3d obj_pt, Eigen::Vector2d img_pixel)
        { // 自动求导模板参数：误差类型，输出维度，输入维度
            return (new ceres::AutoDiffCostFunction<ProjectErrorCostFunc, 2, 4, 5, 4, 3>(
                new ProjectErrorCostFunc(obj_pt, img_pixel)));
        }
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

      private:
        Vec3 P;
        Vec2 p;
    };
};

} // namespace calib
