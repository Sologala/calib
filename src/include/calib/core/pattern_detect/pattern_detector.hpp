#pragma once
#include <calib/marco/marco.hpp>
#include <calib/types/base/geometry.hpp>
#include <calib/types/images.hpp>
namespace calib
{
namespace patt
{

struct PatternBase
{
    int id = -1;
    int pts_size = 0;
    int w = 0;
    int h = 0;
    std::vector<Point2> pt_img;
    std::vector<Point3> pt_3d;
    std::vector<int> pt_id;
    virtual ~PatternBase() = default;
};

struct DetectorBase
{
    CALIB_MARCO_MAKE_SMART_PTR(DetectorBase)

    virtual ~DetectorBase() = default;
    virtual PatternBase detect(const Image &) = 0;
};

struct StereoPattern
{
};

namespace Excp
{
CALIB_MARCO_MAKE_EXCEPTION(WrongID)
}

} // namespace patt
} // namespace calib
