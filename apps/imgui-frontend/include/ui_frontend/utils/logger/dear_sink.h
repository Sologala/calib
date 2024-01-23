#ifndef __DEAR_SINK_H
#define __DEAR_SINK_H

#include <deque>
#include <iostream>
#include <mutex>

#include <calib/utils/logger/logger.h>
#include <imgui.h>
#include <spdlog/sinks/base_sink.h>

struct log_item
{
    std::string message;
    spdlog::level::level_enum level;
};

namespace calib
{
const ImColor TXT_DBG_CLR{0.5f, 0.5f, 0.5f, 1.0f};

const ImColor LVL_DBG_CLR{0.0f, 1.0f, 0.8f, 1.0f};
const ImColor LVL_LOG_CLR{0.65f, 0.2f, 1.0f, 1.0f};
const ImColor LVL_ERR_CLR{1.0f, 0.0f, 0.0f, 1.0f};
const ImColor LVL_WRN_CLR{1.0f, 0.5f, 0.0f, 1.0f};

template <typename Mutex> class CalibSink : public spdlog::sinks::base_sink<Mutex>
{

  public:
    CalibSink()
    {
    }

    void draw_imgui(float posx = 5.0f, float posy = 5.0f, float width = 200.0f, float height = 1000.0f)
    {
        /* ImGui::SetNextWindowPos({posx, posy}); */
        /* ImGui::SetNextWindowSize({width, height}); */
        /* ImGui::Begin("Log", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
         * ImGuiWindowFlags_NoCollapse); */

        // Options menu
        if (ImGui::BeginPopup("Options"))
        {
            ImGui::Checkbox("Auto-scroll", &auto_scroll);
            ImGui::EndPopup();
        }

        // Main window
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        bool clear = ImGui::Button("Clear");
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("Filter", -100.0f);

        ImGui::Separator();

        while (messages_.size() > max_shown_)
        {
            messages_.pop_front();
        }

        if (ImGui::BeginChild("scrolling", ImVec2(0, 0), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar))
        {
            if (clear)
                Clear();
            if (copy)
                ImGui::LogToClipboard();

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            if (Filter.IsActive())
            {
                for (auto iter = messages_.begin(); iter != messages_.end(); iter++)
                {
                    const auto &msg = iter->message;
                    if (Filter.PassFilter(msg.data(), msg.data() + msg.size()))
                        ImGui::TextUnformatted(msg.data(), msg.data() + msg.size());
                }
            }
            else
            {
                for (auto iter = messages_.begin(); iter != messages_.end(); iter++)
                {
                    auto const &msg = *iter;

                    switch (msg.level)
                    {
                    case spdlog::level::debug:
                        ImGui::TextColored(LVL_DBG_CLR, "DBG");
                        ImGui::SameLine();
                        ImGui::Text("|");
                        ImGui::SameLine();
                        ImGui::TextColored(LVL_DBG_CLR, "%s", msg.message.c_str());
                        break;
                    case spdlog::level::warn:
                        ImGui::TextColored(LVL_WRN_CLR, "WRN");
                        ImGui::SameLine();
                        ImGui::Text("|");
                        ImGui::SameLine();
                        ImGui::Text("%s", msg.message.c_str());
                        break;
                    case spdlog::level::err:
                        ImGui::TextColored(LVL_ERR_CLR, "ERR");
                        ImGui::SameLine();
                        ImGui::Text("|");
                        ImGui::SameLine();
                        ImGui::Text("%s", msg.message.c_str());
                        break;
                    default:
                        ImGui::TextColored(LVL_LOG_CLR, "LOG");
                        ImGui::SameLine();
                        ImGui::Text("|");
                        ImGui::SameLine();
                        ImGui::TextUnformatted(msg.message.c_str());
                        break;
                    }
                }
            }
            ImGui::PopStyleVar();

            // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the
            // frame. Using a scrollbar or mouse-wheel will take away from the bottom edge.
            if (auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);
        }
        ImGui::EndChild();
        ImGui::End();
    }

    /// <summary>
    /// Sets the maximum number of messages that are shown.
    /// </summary>
    /// <param name="max_shown"></param>
    void set_max_shown_messages(size_t max_shown)
    {
        max_shown_ = max_shown;
    }

    void Clear()
    {
        messages_.clear();
    }

  protected:
    void sink_it_(const spdlog::details::log_msg &msg) override
    {
        log_item it;
        it.message = std::string(msg.payload.data(), msg.payload.size());
        it.level = msg.level;
        messages_.push_back(it);
    }
    void flush_() override
    {
    }

  protected:
    std::deque<log_item> messages_ = {};
    size_t max_shown_ = 1024;
    bool auto_scroll{true};

    ImGuiTextFilter Filter;
};
using Sinker = std::shared_ptr<CalibSink<std::mutex>>;
} // namespace calib

const calib::Sinker dear_sink_mt();

#endif // __DEAR_SINK_H
