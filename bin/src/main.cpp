#include <sg/file_writer_uv.h>
#include <memory>

// Un-commonet when running a GUI (to hide Windows terminal)
//
// #ifdef WIN32
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
// #endif

int main(int, char **) {
    sg::file_writer_uv writer;
    writer.start("test.txt", nullptr, nullptr, 200);
    writer.write_line_async("TEST");
    writer.stop();
}
