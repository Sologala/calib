#include "stereo_img_proc.hpp"
#include <calib/core/pattern_detect/opencv_checkboard.hpp>
#include <calib/types/images.hpp>
#include <fmt/core.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <timer.hpp>

int main(int argc, char *argv[])
{
    cv::VideoCapture cap(0);
    while (1)
    {
        cv::Mat img_cv;
        cv::Mat left, right;
        cap >> img_cv;
        splitStereoImage(img_cv, left, right);
        calib::Image img(img_cv);

        calib::patt::DetectorBase::Ptr detector = std::make_shared<calib::patt::CheckBoardDetector>();
        calib::patt::PatternBase patter = detector->detect(left);

        fmt::print("detect pts {} ", patter.pt_img.size());
        fmt::print("{} {}\n", img.cols, img.rows);
        if (patter.pt_img.size())
        {
            cv::drawChessboardCorners(left, cv::Size{5, 7}, patter.pt_img, true);
        }
        cv::imshow("cap", img_cv);
        cv::waitKey(10);
    }
    return 0;
}
