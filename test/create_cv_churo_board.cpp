#include <opencv2/aruco/charuco.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
int main(int argc, char *argv[])
{
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_100);
    auto board = cv::aruco::CharucoBoard::create(7, 10, 0.04, 0.025, dictionary);

    cv::Mat boardImage;
    board->draw(cv::Size(1336, 2136), boardImage, 30, 1);
    // cv::imshow("img", boardImage);
    cv::imwrite("img.png", boardImage);
    // cv::waitKey(-1);
    return 0;
}
