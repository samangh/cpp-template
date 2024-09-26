#include "template/export/template_version.h"

#include <sg/imgui/imgui_wrapper_sdl2_opengl3.h>
#include <fmt/format.h>

#ifdef _MSC_VER
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int, char**)
{

    sg::imgui::IImGuiWrapper::on_start_t start = [&]() { };
    sg::imgui::IImGuiWrapper::on_end_t end = [&]() { };
    sg::imgui::IImGuiWrapper::on_iteration_t ter = [&](bool &done) {ImGui::ShowDemoWindow(); };
    sg::imgui::ImGuiWrapper_Sdl2_OpenGl3 wrap = sg::imgui::ImGuiWrapper_Sdl2_OpenGl3(start, end, ter, sg::imgui::ConfigFlags::Docking);

    wrap.start(fmt::format("{} v{}", PROJECT_DESCRIPTION, PROJECT_VERSION));

    return 0;
}
