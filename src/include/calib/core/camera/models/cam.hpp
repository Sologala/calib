#pragma once

namespace calib
{
class CamBase
{
    virtual ~CamBase() = 0;
    virtual void project() = 0;
};

} // namespace calib
