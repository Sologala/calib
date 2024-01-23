#include "stereo_img_proc.hpp"
#include "v4l2_interface.hpp"
#include <set>

#include <algorithm>
#include <calib/core/pattern_detect/pattern_detector.hpp>
#include <calib/types/base/geometry.hpp>
#include <calib/types/images.hpp>
#include <deque>
#include <utils/logger/logger.h>
#include <opencv2/aruco/charuco.hpp>
#include <opencv2/aruco/dictionary.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <unordered_set>
#include <utils/cmdline.hpp>
#include <utils/filesystem.hpp>

const double pattern_cell_length = 0.25;
const int pattern_width = 7;
const int pattern_height = 10;

struct PointCollector
{
    PointCollector(cv::Size sz, cv::Size grid_size, const std::string &wnd_name)
        : imgsize(sz), grid_sz(grid_size), wnd_name(wnd_name)
    {
        grid_cell_height = imgsize.height * 1.0 / grid_size.height;
        grid_cell_width = imgsize.width * 1.0 / grid_size.width;
        patters.clear();

        grid2d_pts = std::vector<std::vector<std::vector<cv::Point2f>>>(
            grid_size.height, std::vector<std::vector<cv::Point2f>>(grid_size.width));
        grid2d_patter_idxs = std::vector<std::vector<std::vector<int>>>(
            grid_size.height, std::vector<std::vector<int>>(grid_size.width, std::vector<int>()));
    };
    void add(calib::patt::PatternBase &patter)
    {
        int idx = patters.size();
        patters.push_back(patter);
        // if (patters.size() > 100)
        // {
        //     patters.pop_front();
        // }
        for (const auto &pt : patter.pt_img)
        {
            int grid_row_idx = pt.y / grid_cell_height;
            int grid_col_idx = pt.x / grid_cell_width;
            grid2d_pts[grid_row_idx][grid_col_idx].push_back(pt);
            grid2d_patter_idxs[grid_row_idx][grid_col_idx].push_back(idx);
        }
    }
    void show()
    {
        cv::Mat canvas = cv::Mat::zeros(imgsize, CV_8UC3);
        for (int c = 1; c < grid_sz.width; c++)
        {
            int x = c * grid_cell_width;
            cv::line(canvas, cv::Point(x, 0), cv::Point(x, canvas.rows), cv::Scalar(255, 255, 255), 1);
        }
        for (int r = 1; r < grid_sz.height; r++)
        {
            int y = r * grid_cell_height;
            cv::line(canvas, cv::Point(0, y), cv::Point(canvas.cols, y), cv::Scalar(255, 255, 255), 1);
        }

        for (int r = 0; r < grid_sz.height; r++)
        {
            for (int c = 0; c < grid_sz.width; c++)
            {
                // printf("%d %d %d\n", r, c, grid2d_pts[r][c].size());
                int cnt = 0;
                for (const auto &pt : grid2d_pts[r][c])
                {
                    cv::circle(canvas, pt, 1, cv::Scalar(0, 255, 0), 1);
                    cnt++;
                    if (cnt > 30)
                    {
                        break;
                    }
                }
            }
        }
        cv::imshow(wnd_name, canvas);
    }
    const std::string wnd_name;
    cv::Size imgsize, grid_sz;
    double grid_cell_height, grid_cell_width;
    std::deque<calib::patt::PatternBase> patters;
    std::vector<std::vector<std::vector<cv::Point2f>>> grid2d_pts;
    std::vector<std::vector<std::vector<int>>> grid2d_patter_idxs;
};

void detectCharucoBoardWithCalibration(cv::VideoCapture &cap)
{
    // cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_100);
    // cv::Ptr<cv::aruco::CharucoBoard> board = cv::aruco::CharucoBoard::create(7, 10, 0.04f, 0.025f, dictionary);
    // cv::Ptr<cv::aruco::DetectorParameters> params = cv::aruco::DetectorParameters::create();
    // params->cornerRefinementMethod = cv::aruco::CORNER_REFINE_SUBPIX;

    cv::Mat grid;

    PointCollector collector_left({1280, 720}, {12, 7}, "left");
    PointCollector collector_right({1280, 720}, {12, 7}, "right");
    int f_id = 0;
    std::vector<std::vector<cv::Point2f>> aruco_pts;
    std::vector<std::vector<int>> pts_arucoids;

    while (cap.grab())
    {
        cv::Mat image;
        cap.retrieve(image);
        f_id += 1;
        cv::blur(image, image, cv::Size(3, 3));
        cv::medianBlur(image, image, 3);
        cv::Mat left, right;
        splitStereoImage(image, left, right);

        auto detectPatter = [](cv::Mat &img) {
            cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_100);
            cv::Ptr<cv::aruco::CharucoBoard> board = cv::aruco::CharucoBoard::create(7, 10, 0.04f, 0.025f, dictionary);
            cv::Ptr<cv::aruco::DetectorParameters> params = cv::aruco::DetectorParameters::create();
            params->cornerRefinementMethod = cv::aruco::CORNER_REFINE_SUBPIX;
            std::vector<int> markerIds;
            std::vector<std::vector<cv::Point2f>> markerCorners;
            cv::aruco::detectMarkers(img, board->dictionary, markerCorners, markerIds, params);
            calib::patt::PatternBase pattern;
            if (markerIds.size() > 0)
            {
                cv::aruco::drawDetectedMarkers(img, markerCorners, markerIds);
                std::vector<cv::Point2f> charucoCorners;
                std::vector<int> charucoIds;
                cv::aruco::interpolateCornersCharuco(markerCorners, markerIds, img, board, charucoCorners, charucoIds);
                // if at least one charuco corner detected
                if (charucoIds.size() > 0)
                {
                    cv::aruco::drawDetectedCornersCharuco(img, charucoCorners, charucoIds, cv::Scalar(255, 0, 0));
                    pattern.pts_size = charucoCorners.size();
                    pattern.pt_img = charucoCorners;
                    pattern.pt_3d.resize(pattern.pt_img.size());
                    pattern.pt_id = charucoIds;
                    for (int i = 0; i < pattern.pt_img.size(); i++)
                    {
                        int id = charucoIds[i];
                        pattern.pt_3d[i].x = id % 5 * pattern_cell_length;
                        pattern.pt_3d[i].y = id / 5 * pattern_cell_length;
                        pattern.pt_3d[i].z = 0;
                    }
                }
            }
            return pattern;
        };

        auto left_patt = detectPatter(left);
        auto right_patt = detectPatter(right);

        // or
        if (left_patt.pts_size && right_patt.pts_size)
        {
            collector_left.add(left_patt);
            collector_left.show();
            collector_right.add(right_patt);
            collector_right.show();
        }
        cv::imshow("out", image);
        char key = (char)cv::waitKey(30);
        if (key == 'q')
            break;
        else if (key == 'c')
        {
            std::vector<std::vector<cv::Point2f>> imgpts_left, imgpts_right;
            std::vector<std::vector<cv::Point3d>> objpts;

            for (int i = 0; i < collector_left.patters.size(); i++)
            {
                const auto pleft = collector_left.patters[i];
                const auto pright = collector_right.patters[i];
                std::vector<int> common_id;
                std::set_intersection(pleft.pt_id.begin(), pleft.pt_id.end(), pright.pt_id.begin(), pright.pt_id.end(),
                                      std::back_inserter(common_id));
                std::unordered_set<int> common_id_set(common_id.begin(), common_id.end());
                std::vector<cv::Point2f> pleft_stereo, pright_stereo;
                std::vector<cv::Point3d> objpt;

                for (int k = 0; k < pleft.pts_size; k++)
                {
                    int id = pleft.pt_id[k];

                    if (!common_id_set.count(id))
                        continue;
                    for (int j = 0; j < pright.pts_size; j++)
                    {
                        if (pright.pt_id[j] == id)
                        {

                            objpt.push_back({pleft.pt_3d[k].x, pleft.pt_3d[k].y, pleft.pt_3d[k].z});
                            pleft_stereo.push_back(pleft.pt_img[k]);
                            pright_stereo.push_back(pright.pt_img[j]);
                        }
                    }
                }

                imgpts_left.push_back(pleft_stereo);
                imgpts_right.push_back(pright_stereo);
                objpts.push_back(objpt);
            }

            if (objpts.size())
            {
                cv::Mat K1, K2, D1, D2, R, t;
                // single fisheye calibration
                cv::Mat cameraMatrix[2], distCoeffs[2];
                cv::Mat rvecs[2], tvecs[2];
                cv::Size img_sz{1280, 720};
                {
                    cv::fisheye::calibrate(objpts, imgpts_left, img_sz, K1, D1, rvecs[0], tvecs[0],
                                           cv::fisheye::CALIB_FIX_SKEW);
                    cv::fisheye::calibrate(objpts, imgpts_right, img_sz, K2, D2, rvecs[1], tvecs[1],
                                           cv::fisheye::CALIB_FIX_SKEW);
                }
                double rms = cv::fisheye::stereoCalibrate(objpts, imgpts_left, imgpts_right, K1, D1, K2, D2,
                                                          {1280, 720}, R, t, cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC);
                LOGI("rms is {}", rms);
                std::cout << K1 << std::endl;
                std::cout << K2 << std::endl;
            }
        }
    }

    // std::vector<std::vector<cv::Point2f>>
    // cv::aruco::calibrateCameraCharuco()
}

int main(int argc, char *argv[])
{
    cmdline::parser parser;
    parser.add<int>("conti_grap_cnt", 'n', "grap continualy n frames after c key pressed", false, 0);
    parser.add<std::string>("output_path", 'o', "oustput path", true, ".");
    parser.parse_check(argc, argv);
    std::string output_path = parser.get<std::string>("output_path");
    if (!calib::filesys::file_exist(output_path))
    {
        LOGI("output folder {} is not exist, will create next", output_path);
        calib::filesys::makedir(output_path);
    }

    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        LOGI("capture 0 can not be opened\n");
    }
    int cnt = 0;

    auto cam_setting =
        std::unordered_map<std::string, double>{{"auto_exposure", 1}, {"exposure_time_absolute", 2}, {"gain", 128}};
    // v4l2_control(cam_setting, 0);

    detectCharucoBoardWithCalibration(cap);

    return 0;
}
