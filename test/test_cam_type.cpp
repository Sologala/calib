#include <calib/sensors/cam/cam.hpp>
#include <calib/types/images.hpp>
#include <fmt/core.h>
#include <gtest/gtest.h>
#include <opencv2/highgui.hpp>

using namespace cali::cam;

int main(int argc, char *argv[])
{

    CameraFactory::Create("Pinhole")->CreateCamera(0.1);

    return 0;
}
