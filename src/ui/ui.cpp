#include <cstdlib>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

int ui()
{
    using namespace ftxui;

    auto screen = ScreenInteractive::Fullscreen();
    Component f1_button = Button({.label = "F1 Help", .on_click = [] {}});
    Component f2_button = Button("F2 Algorithm", [] {});
    Component f3_button = Button("F3 Overlay", [] {});
    Component f4_button = Button("F4 Spawn", [] {});
    Component f5_button = Button("F5 Map", [] {});
    Component f6_button = Button("F6 Simulation", [] {});
    Component f8_button = Button("F8 Logs", [] {});
    Component q_button = Button("q Quit", [&screen] { screen.ExitLoopClosure()(); });

    auto top_buttons = Container::Horizontal({
        f1_button,
        f2_button,
        f3_button,
        f4_button,
        f5_button,
        f6_button,
        f8_button,
        q_button,
    });

    int left_size = 20;
    int right_size = 20;
    int top_size = 5;
    int bottom_size = 10;

    auto RendererInfo = [](const std::string &name, int *size)
    {
        return Renderer([name, size]
                        { return text(name + ": " + std::to_string(*size)) | center; });
    };

    auto middle = Renderer([] { return text("Middle") | center; });
    auto left = RendererInfo("Left", &left_size);
    auto right = RendererInfo("Right", &right_size);
    auto top = Renderer(top_buttons, [&] { return top_buttons->Render() | border; });
    auto bottom = RendererInfo("Bottom", &bottom_size);

    auto main_grid = middle;
    main_grid = ResizableSplitLeft(left, main_grid, &left_size);
    main_grid = ResizableSplitRight(right, main_grid, &right_size);
    main_grid = ResizableSplitTop(top, main_grid, &top_size);
    main_grid = ResizableSplitBottom(bottom, main_grid, &bottom_size);

    struct ModalFlags
    {
        bool help;
        bool algo;
        bool overlay;
        bool spawn;
        bool map;
        bool sim;
        bool logs;
    };

    auto renderer = Renderer(main_grid, [&] { return main_grid->Render() | border; });

    screen.Loop(renderer);

    return EXIT_SUCCESS;
}