#include "opencv2/imgproc.hpp"
#include <calib/core/pattern_detect/opencv_checkboard.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
namespace calib
{
namespace patt
{

PatternBase CheckBoardDetector::detect(const Image &img)
{
    cv::Mat img_gray = img;
    if (img.channels() == 3)
    {
        cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    }
    PatternBase ret;
    ret.id = -1;
    cv::findChessboardCorners(img_gray, cv::Size(5, 7), ret.pt_img);
    ret.pts_size = ret.pt_img.size();
    if (ret.pts_size)
    {
        cv::cornerSubPix(img_gray, ret.pt_img, cv::Size(5, 5), cv::Size(-1, -1),
                         cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30,
                                          0.1)); // 对角点进行亚像素级别的精确定位 return ret;
    }
    return ret;
}
} // namespace patt
} // namespace calib
