#include "engine/gui/manager/GuiManager.h"
#include <rlImGui.h>


GuiManager::GuiManager() : activeViewIndex(0) {}

GuiManager::~GuiManager() {}

void GuiManager::AddView(const GuiView& view) {
    views.push_back(view);
}

void GuiManager::SetActiveView(int index) {
    if (index >= 0 && index < views.size()) {
        activeViewIndex = index;
    }
}

void GuiManager::Render() {
    if (views.empty()) return;

    rlImGuiBegin();
    views[activeViewIndex]();
    rlImGuiEnd();
}

void GuiManager::NextView() {
    if (views.empty()) return;
    activeViewIndex = (activeViewIndex + 1) % views.size();
}

void GuiManager::PrevView() {
    if (views.empty()) return;
    activeViewIndex = (activeViewIndex - 1 + views.size()) % views.size();
}
