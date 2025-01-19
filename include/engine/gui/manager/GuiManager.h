#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include <imgui.h>
#include <vector>
#include <functional>

class GuiManager {
public:
    // Typ für eine GUI-Ansicht, die eine Methode render() benötigt
    using GuiView = std::function<void()>;

    GuiManager();
    ~GuiManager();

    void AddView(const GuiView& view);

    void SetActiveView(int index);

    void Render();

    void NextView();
    void PrevView();

private:
    std::vector<GuiView> views;  // Enthält alle Views
    int activeViewIndex;         // Der Index der aktiven Ansicht
};

#endif // GUI_MANAGER_HPP
