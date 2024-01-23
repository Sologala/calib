#include <calib/utils/logger/logger.h>
#include <imgui_app_base.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <ui_frontend/utils/logger/dear_sink.h>

int main(int argc, char *argv[])
{
    int width = 400;
    int height = 400;
    auto title = "log test";

    const calib::Sinker ssink = calib::SinkerFactory();

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
            LOGI("clicked");
            /* spdlog::get("llog")->log(spdlog::level::level_enum::info, "hhhhhhh{}", i++); */
            LOGW("hhhhhhh{}", i++);
        }

        ssink->Draw();

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        return true;
    });
    app.Run();

    return 0;
}
