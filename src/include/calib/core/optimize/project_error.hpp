#pragma once
#include <calib/core/camera/models/cam_model.hpp>

namespace calib
{

// class ProjectErrorCostFunc
// {
//   public:
//     ProjectErrorCostFunc(const CamModelBase::Ptr &cam, const Vec3 P, const Vec2 p) : P(P), p(p), cam(cam)
//     {
//     }
//
//     template <typename T> bool operator()(T *residuals) const
//     {
//         Vec2 p_p = cam->project(P);
//         // residuals[0] = ud - img(0);
//         // residuals[1] = vd - img(1);
//         return true;
//     }
//     // 生成误差函数
//     static ceres::CostFunction* Create(Eigen::Vector3d obj_pt, Eigen::Vector2d img_pixel
//     {        // 自动求导模板参数：误差类型，输出维度，输入维度
//         return (new ceres::AutoDiffCostFunction<ProjectErrorCostFunctionPinehole, 2, 4, 5, 4, 3>(
//             new ProjectErrorCostFunctionPinehole(obj_pt, img_pixel)));
//     }
// 	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
// private:
// 	const Vec3 P;
// 	const Vec2 p;
//     const CamModelBase::Ptr cam;
// };

} // namespace calib
