#pragma once
#include <calib/types/base/base.hpp>
#include <calib/types/base/math.hpp>
#include <opencv2/core.hpp>

namespace calib
{

using Point2 = cv::Point_<Scalar>;
using Point2i = cv::Point2i;
using Point3 = cv::Point_<Scalar>;
using Point3i = cv::Point3i;
using Rect = cv::Rect_<Scalar>;
using Recti = cv::Rect2i;

struct Line
{
    Point2 left;
    Point2 right;
};

struct Segment
{
    Point2 left;
    Point2 right;
};

} // namespace calib
