#include "ui/StatsPanel.h"
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>

static double GetProcessMemoryUsageMB() {
    std::ifstream file("/proc/self/status");
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 6) == "VmRSS:") {
            std::string temp;
            int mem_kb;
            std::stringstream ss(line);
            ss >> temp >> mem_kb;
            return (double)mem_kb / 1024.0;
        }
    }
    return 0.0;
}

void DrawStatsPanel(float cameraRadius, Vector2 cameraAngle) {
    int sw       = GetScreenWidth();
    int panelW   = 230;
    int panelH   = 140;
    int panelX   = sw - panelW - 10;
    int panelY   = 10;
    int fps      = GetFPS();
    DrawRectangle(panelX, panelY, panelW, panelH, { 0, 0, 0, 160 });
    DrawRectangleLines(panelX, panelY, panelW, panelH, { 80, 80, 100, 200 });

    Color fpsColor = (fps >= 55) ? (Color){ 80, 220,  80, 255 }
                   : (fps >= 30) ? (Color){ 220, 180, 60, 255 }
                                 : (Color){ 220,  60, 60, 255 };
    DrawText(TextFormat("FPS: %d", fps),
             panelX + 10, panelY + 10, 18, fpsColor);

    Color statColor = { 180, 200, 255, 255 };
    DrawText(TextFormat("Zoom:  %.1f",  cameraRadius),
             panelX + 10, panelY + 34, 15, statColor);
    DrawText(TextFormat("Yaw:   %.1f deg", cameraAngle.x * (180.0f / PI)),
             panelX + 10, panelY + 56, 15, statColor);
    DrawText(TextFormat("Pitch: %.1f deg", cameraAngle.y * (180.0f / PI)),
             panelX + 10, panelY + 78, 15, statColor);
             
    double memUsage = GetProcessMemoryUsageMB();
    
    DrawText(TextFormat("Memory:   %.1f MB", memUsage),
             panelX + 10, panelY + 100, 15, statColor);
}
