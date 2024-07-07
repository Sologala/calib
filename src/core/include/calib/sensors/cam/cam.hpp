#pragma once
#include <Eigen/Core>
#include <calib/utils/marco/marco.hpp>
namespace cali
{
namespace cam
{

using V3 = Eigen::Vector3f;
using V2 = Eigen::Vector2f;

class Camera
{
    CALIB_MARCO_MAKE_SMART_PTR(Camera)
  public:
    virtual ~Camera()                            = default;
    virtual void project(const V3 xyz, V2 &uv)   = 0;
    virtual bool LiftPlane(const V2 &uv, V3 xyz) = 0;
};

template <typename T, size_t DIST_CNT>
class CameraParam : public Camera
{
    size_t GetDistCnt()
    {
        return DIST_CNT;
    };

  public:
    T fx_, fy_, cx_, cy_;

    std::array<T, DIST_CNT> dist;
};

template <typename T>
class Pinhole : public CameraParam<T, 0>
{
  public:
    virtual void project(const V3 xyz, V2 &uv) override
    {
        uv(0) = this->fx_ * xyz[0] + this->cx_;
        uv(1) = this->fy_ * xyz[1] + this->cy_;
    }
    virtual bool LiftPlane(const V2 &uv, V3 xyz)
    {
        xyz[0] = (uv.x() - this->cx_) / this->fx_;
        xyz[1] = (uv.y() - this->cy_) / this->fy_;
        xyz[2] = 1.0;
    }
};

template <typename T>
class PinholeRadTan : public CameraParam<T, 3>
{
  public:
    virtual void project(const V3 xyz, V2 &uv) override
    {
        uv(0) = this->fx_ * xyz[0] + this->cx_;
        uv(1) = this->fy_ * xyz[1] + this->cy_;
    }
};

struct CameraFactoryBase
{
    CALIB_MARCO_MAKE_SMART_PTR(CameraFactoryBase);
    virtual ~CameraFactoryBase() = default;
    template <typename CamType, typename... Args>
    std::shared_ptr<CamType> CreateCamera(Args &&...args)
    {
    }
};

template <typename CamType>
struct CameraFactoryImpl : public CameraFactoryBase
{
    template <typename... Args>
    Camera::Sptr CreateCamera(Args &&...args)
    {
        return std::make_shared<CamType>(std::forward<Args>(args)...);
    }
};

template <typename CamType>
inline CameraFactoryBase::Sptr CreateCameraFactory()
{
    return std::make_shared<CameraFactoryImpl<CamType>>();
}

class CameraFactory
{
  public:
    static CameraFactoryBase::Sptr Create(const std::string &type)
    {
        static const std::unordered_map<std::string, CameraFactoryBase::Sptr> lut = {
            {"Pinhole", CreateCameraFactory<Pinhole<float>>()},
            {"PinholeRadTan", CreateCameraFactory<PinholeRadTan<float>>()},
        };
        return lut.at(type);
    }
};
} // namespace cam
} // namespace cali
