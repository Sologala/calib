#pragma once
#include <calib/types/base/timestamp.hpp>

namespace calib
{
using Scalar = double;

struct FrameBase
{
    FrameBase(const Timestamp &ts_ms = 0) : timestamp_ms(ts_ms)
    {
    }
    Timestamp timestamp_ms;
};
} // namespace calib
