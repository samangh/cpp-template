#include <sg/file_writer.h>
#include <memory>

// Un-commonet when running a GUI (to hide Windows terminal)
//
// #ifdef WIN32
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
// #endif

int main(int, char **) {
    sg::file_writer writer;
    writer.start("test.txt", nullptr, nullptr, nullptr, 200);
    writer.write_line("TEST");
    writer.stop();
}
