#include <ui_frontend/utils/logger/logger.h>
#include <ui_frontend/canvas/canvas.h>
#include <cmath>
#include <imgui_app_base.h>
#include <iostream>
#include <string>

int main(void)
{
    ImGuiApp::AppBase::Option opt;
    opt.font_size = 30;
    ImGuiApp::AppBase app("Test", ImVec2(1280 * 2, 960), opt);
    bool btn_clean_clicked = false;
    static int canvas_width = 1280, canvas_height = 960;
    static Canvas canvas(canvas_width, canvas_height);
    static int meum_width = 400, meum_height = 960;

    app.AddDrawCallBack([&]() {
        ImGuiWindowFlags flag = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
        ImGui::Begin("Meum", nullptr, flag);
        ImGui::SetWindowSize(ImVec2(meum_width, meum_height));
        ImGui::SetWindowPos(ImVec2(canvas_width, 0));
        if (ImGui::Button("Clean"))
        {
            btn_clean_clicked = true;
            canvas.Clean();
        }

        if (ImGui::Button("RandomPoints"))
        {
        }

        ImGui::End();
        return true;
    });

    app.AddDrawCallBack([&]() {
        ImGuiWindowFlags flag = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse;
        ImGui::Begin("draw", nullptr, flag);
        ImGui::SetWindowFocus();
        ImGui::SetWindowSize(ImVec2(canvas_width, canvas_height));
        ImGui::SetWindowPos(ImVec2(0, 0));

        const float window_width = ImGui::GetContentRegionAvail().x;
        const float window_height = ImGui::GetContentRegionAvail().y;

        ImVec2 pos = ImGui::GetCursorScreenPos();
        pos.x -= 5;
        pos.y -= 2;
        ImGui::InvisibleButton("iv_button", ImVec2(canvas_width, canvas_height));

        if (ImGui::IsItemHovered())
        {
            canvas.cam.m_zoom -= ImGui::GetIO().MouseWheel;
            canvas.cam.m_zoom = std::max(1.0f, canvas.cam.m_zoom);
            canvas.cam.m_zoom = std::min(50.0f, canvas.cam.m_zoom);
            if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            {
                canvas.cam.m_x_rot += (ImGui::GetIO().MouseDelta.y > 0 ? 1.f : -1.f) * 0.1 *
                                  std::min(std::abs(ImGui::GetIO().MouseDelta.y), 50.f);
                canvas.cam.m_z_rot += (ImGui::GetIO().MouseDelta.x > 0 ? 1.f : -1.f) * 0.1 *
                                  std::min(std::abs(ImGui::GetIO().MouseDelta.x), 50.f);
            }
            {
                if (ImGui::IsMouseDragging(ImGuiMouseButton_Middle))
                {
                    canvas.cam.m_x_trans += 0.03 * ImGui::GetIO().MouseDelta.x;
                    canvas.cam.m_y_trans -= 0.03 * ImGui::GetIO().MouseDelta.y;
                }
            }
        }

        ImGui::GetWindowDrawList()->AddImage((void *)canvas.texture, ImVec2(pos.x, pos.y),
                                             ImVec2(pos.x + canvas.fb_width, pos.y + canvas.cam.fb_height), ImVec2(0, 1),
                                             ImVec2(1, 0));
        ImGui::End();

        canvas.Clean();
        canvas.Render();

        return true;
    });

    app.Run();
    return 0;
}
