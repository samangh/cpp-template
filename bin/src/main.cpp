#include <iostream>
#include <thread_pool/thread_pool.h>
#include <memory>

// Un-commonet when running a GUI (to hide Windows terminal)
//
// #ifdef WIN32
// #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
// #endif


int main(int, char **) {
    std::function<int(int)> f = [](int no){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << no <<std::endl;
        return no;
    };

    std::function<int(int)> f2 = [](int no){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "no:" << no <<std::endl;
        return no;
    };

    dp::thread_pool pool(4);
    std::vector<std::future<int>> vec;

    for (int i=0; i<100; ++i)    
        vec.emplace_back(pool.enqueue(f, i));

    vec[0].get();
    pool.clear_tasks();

    for (int i=0; i<10; ++i)
        vec.emplace_back(pool.enqueue(f2, i));

    return 0;
}
