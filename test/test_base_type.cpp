#include <calib/types/images.hpp>
#include <fmt/core.h>
#include <gtest/gtest.h>
#include <timer.hpp>
#include <opencv2/highgui.hpp>
TEST(calib, timer)
{
    {
        MyTimer::Timer("hhh");
    }

    for (auto t : MyTimer::Timer::COUNT)
    {
        printf("%s, %f\n", t.first.c_str(), t.second.fps());
        fmt::print("{} {:.2f}\n", t.first.c_str(), t.second.fps());
    }
}

TEST(calib, imgframe)
{
    calib::Image img(cv::imread(std::string(DATA_FOLDER) + "/Lenna.png"));
    fmt::print("{} {}", img.cols, img.rows);
}
