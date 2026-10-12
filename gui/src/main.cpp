#include "template/export/template_version.h"

#include <sg/imgui/imgui_wrappers.h>
#include <fmt/format.h>

#ifdef _MSC_VER
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int, char**)
{
    sg::imgui::ImGuiWrapper::Callbacks cbs;
    cbs.onStart     = [&](sg::imgui::IImGuiWrapper& gui) { gui.changeWindowTitle("Hello world!"); };
    cbs.onEnd       = [&](sg::imgui::IImGuiWrapper&) {};
    cbs.onIteration = [&](sg::imgui::IImGuiWrapper&, bool&) { ImGui::ShowDemoWindow(); };

    auto wrap = sg::imgui::ImGuiWrapper(cbs, sg::imgui::ConfigFlags::Docking);

    wrap.start(fmt::format("{} v{}", PROJECT_DESCRIPTION, PROJECT_VERSION));

    return 0;
}
