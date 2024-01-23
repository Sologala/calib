#pragma once
#include <unordered_map>

/*
User Controls

                     brightness 0x00980900 (int)    : min=-64 max=64 step=1 default=0 value=0
                       contrast 0x00980901 (int)    : min=0 max=95 step=1 default=32 value=32
                     saturation 0x00980902 (int)    : min=0 max=100 step=1 default=32 value=32
                            hue 0x00980903 (int)    : min=-2000 max=2000 step=1 default=0 value=0
        white_balance_automatic 0x0098090c (bool)   : default=1 value=1
                          gamma 0x00980910 (int)    : min=100 max=300 step=1 default=150 value=150
                           gain 0x00980913 (int)    : min=128 max=1984 step=8 default=128 value=1984
           power_line_frequency 0x00980918 (menu)   : min=0 max=2 default=1 value=2
      white_balance_temperature 0x0098091a (int)    : min=2800 max=6500 step=1 default=4600 value=4600 flags=inactive
                      sharpness 0x0098091b (int)    : min=1 max=100 step=1 default=28 value=28
         backlight_compensation 0x0098091c (int)    : min=0 max=1 step=1 default=0 value=0

Camera Controls

                  auto_exposure 0x009a0901 (menu)   : min=0 max=3 default=3 value=3
         exposure_time_absolute 0x009a0902 (int)    : min=1 max=80000 step=1 default=312 value=65536 flags=inactive
     exposure_dynamic_framerate 0x009a0903 (bool)   : default=0 value=0
                   pan_absolute 0x009a0908 (int)    : min=0 max=3600 step=3600 default=0 value=0
                  tilt_absolute 0x009a0909 (int)    : min=-345600 max=345600 step=3600 default=0 value=0

*/

inline bool v4l2_control(std::unordered_map<std::string, double> &inp, int device_id)
{
    char cmd[256] = {0};
    for (auto &p : inp)
    {
        snprintf(cmd, 256, "v4l2-ctl -d %d --set-ctrl=%s=%f", device_id, p.first.c_str(), p.second);
        int res = system(cmd);
        printf("set %s to %f %s\n", p.first.c_str(), p.second, res ? "faild" : "success");
    }
    return true;
};
