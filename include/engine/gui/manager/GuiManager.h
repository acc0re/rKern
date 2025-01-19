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

    // Fügt eine neue Ansicht hinzu
    void AddView(const GuiView& view);

    // Setzt die Ansicht, die gerade aktiv ist
    void SetActiveView(int index);

    // Rendert die aktive Ansicht
    void Render();


    // Wechselt zur nächsten Ansicht (falls vorhanden)
    void NextView();

    // Wechselt zur vorherigen Ansicht (falls vorhanden)
    void PrevView();

private:
    std::vector<GuiView> views;  // Enthält alle Views
    int activeViewIndex;         // Der Index der aktiven Ansicht
};

#endif // GUI_MANAGER_HPP
