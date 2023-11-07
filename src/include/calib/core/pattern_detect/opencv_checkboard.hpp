#pragma once
#include <calib/core/pattern_detect/pattern_detector.hpp>
namespace calib
{
namespace patt
{

struct CheckBoardDetector : public DetectorBase
{
    CALIB_MARCO_MAKE_SMART_PTR(CheckBoardDetector)

    PatternBase detect(const Image &img);
};

} // namespace patt
} // namespace calib
