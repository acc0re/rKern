#include <raylib.h>
#include <rlImGui.h>
#include <imgui.h>
#include "engine/gui/manager/GuiManager.h"

void View1() {
  ImGui::Text("Dies ist Ansicht 1");
  if (ImGui::Button("Zur Ansicht 2 wechseln")) {
    // Ansicht im GuiManager ändern
  }
}

void View2() {
  ImGui::Text("Dies ist Ansicht 2");
  if (ImGui::Button("Zur Ansicht 1 wechseln")) {
    // Ansicht im GuiManager ändern
  }
}

int main() {
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(1280, 720, "GuiManager Example");
  SetTargetFPS(60);  // Ziel für 60 FPS

  rlImGuiSetup(true);

  GuiManager guiManager;
  guiManager.AddView(View1);
  guiManager.AddView(View2);

  while (!WindowShouldClose()) {
    // Berechne die DeltaTime für das aktuelle Frame
    float deltaTime = GetFrameTime();  // Berechnet Zeit seit dem letzten Frame

    // Beginne den Zeichnungsprozess
    BeginDrawing();
    ClearBackground(BLACK);  // Hintergrundfarbe

    guiManager.Render();
  //  ImGui::ShowDemoWindow();


    // Ende des Zeichnungsprozesses
    EndDrawing();
  }

  rlImGuiShutdown();
  CloseWindow();
  return 0;
}
