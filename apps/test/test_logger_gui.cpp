#include <calib/utils/logger/logger.h>
#include <ui_frontend/utils/logger/dear_sink.h>
#include <imgui_app_base.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


int main(int argc, char *argv[])
{
    int width = 400;
    int height = 400;
    auto title = "log test";

    const auto ssink = dear_sink_mt();

    spdlog::info("info");
    spdlog::warn("info");
    spdlog::error("info");
    spdlog::debug("info");

    ImGuiApp::AppBase app("hhh", ImVec2(800, 800), {.font_size = 30});

    ImGui::StyleColorsClassic();
    static int i = 0;

    app.AddDrawCallBack([&]() {
        glfwPollEvents();
        ImGui::Begin("hhh", nullptr);
        /* ImGui::SetWindowSize(ImVec2(500, 500)); */
        ImGui::SetWindowPos(ImVec2(0, 0));
        if (ImGui::Button("log_btn", ImVec2(100, 100)))
        {
            SPDLOG_INFO("clicked");
            /* spdlog::get("llog")->log(spdlog::level::level_enum::info, "hhhhhhh{}", i++); */
            spdlog::info("hhhhhhh{}", i++);
        }

        ssink->draw_imgui();

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        return true;
    });
    app.Run();

    return 0;
}
