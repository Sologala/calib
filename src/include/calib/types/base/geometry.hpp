#pragma once
#include <calib/types/base/math.hpp>
#include <opencv2/core.hpp>

namespace calib
{
using Point2 = cv::Point2f;
using Point2i = cv::Point2i;
using Point3 = cv::Point3f;
using Point3i = cv::Point3i;
using Rect = cv::Rect2f;
using Recti = cv::Rect2i;
template <typename Scalar>

struct Line
{
    Scalar line;
};

template <typename Scalar>

struct Segment
{
    Scalar left;
};

} // namespace calib
