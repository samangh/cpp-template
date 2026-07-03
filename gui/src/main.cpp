#include "template/export/template_version.h"

#include <sg/imgui/imgui_wrappers.h>
#include <fmt/format.h>

#ifdef _MSC_VER
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int, char**)
{

    sg::imgui::IImGuiWrapper::on_start_t     start = [](sg::imgui::IImGuiWrapper&) {};
    sg::imgui::IImGuiWrapper::on_end_t       end   = [](sg::imgui::IImGuiWrapper&) {};
    sg::imgui::IImGuiWrapper::on_iteration_t ter   = [&](sg::imgui::IImGuiWrapper&, bool&) {
        ImGui::ShowDemoWindow();
    };

    sg::imgui::ImGuiWrapper::Callbacks cbs;
    cbs.onStart = start;
    cbs.onEnd   = end;
    cbs.onIteration = ter;

    auto wrap = sg::imgui::ImGuiWrapper(cbs, sg::imgui::ConfigFlags::Docking);

    wrap.start(fmt::format("{} v{}", PROJECT_DESCRIPTION, PROJECT_VERSION));

    return 0;
}
