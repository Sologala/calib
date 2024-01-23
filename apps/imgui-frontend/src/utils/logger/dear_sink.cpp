#include <ui_frontend/utils/logger/dear_sink.h>

#include <spdlog/sinks/base_sink.h>
#include <spdlog/spdlog.h>

namespace calib
{
    const calib::Sinker SinkerFactory()
    {
        auto llog = spdlog::create<CalibSink<std::mutex>>(std::string("llog"));

        // I don't understand this step, shouldn't it log to all registered loggers?
        spdlog::set_default_logger(llog);

        return std::dynamic_pointer_cast<CalibSink<std::mutex>>(llog->sinks()[0]);
    }
}
