#pragma once
#include <calib/types/base/base.hpp>
#include <calib/types/base/geometry.hpp>
#include <calib/types/base/math.hpp>
#include <string>
namespace calib
{

struct Image : public FrameBase, cv::Mat
{
    Image(cv::Mat _cv_mat, const Timestamp ts = 0) : cv::Mat(_cv_mat), FrameBase(ts)
    {
    }
    Image(const std::string &file_name);
    ~Image()
    {
    }
    cv::Size sz;
};
} // namespace calib
