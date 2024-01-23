#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

inline void splitStereoImage(const cv::Mat &src, cv::Mat &left, cv::Mat &right)
{
    if (src.empty())
        return;
    int width = src.cols;
    left = src(cv::Rect2i(0, 0, width / 2, src.rows));
    right = src(cv::Rect2i(width / 2, 0, width / 2, src.rows));
}
