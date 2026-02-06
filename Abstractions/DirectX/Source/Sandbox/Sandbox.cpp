#include <Window.h>

int main() {
    Engine::Window window(L"MyWindow", 960, 540);
    while (!window.ShouldClose()) {
        window.PollEvents();
    }
}