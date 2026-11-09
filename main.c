#include <stdio.h>
#include <string.h>
#include <time.h>
#include <raylib.h>

#define initScreenWidth 800
#define initScreenHeight 400
#define initFontSize 24

clock_t t_start;
int     t_running = 0;
char    t_buf[32] = "0.000";

void timer_start(void) {
  t_start = GetTime();
  t_running = 1;
}

void timer_reset(void) {
  t_running = 0;
  strcpy(t_buf, "0.000");
}

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(initScreenWidth, initScreenHeight, "cuub");
  SetTargetFPS(60);

  int fontSize = initFontSize;

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE)) {
      if (t_running) timer_reset();
      else timer_start();
    }

    if (IsKeyDown(KEY_EQUAL)) {
      if (fontSize < 128) {
	fontSize += 1;
      }
    }
    
    if (IsKeyDown(KEY_MINUS)) {
      if (fontSize > 8) {
	fontSize -= 1;
      }
    }

    if (IsKeyPressed(KEY_ZERO)) {
      fontSize = initFontSize;
    }

    if (t_running) sprintf(t_buf, "%.3f", GetTime() - t_start);

    BeginDrawing();
    ClearBackground((Color){18, 18, 18, 1});

    int textW = MeasureText(t_buf, fontSize);
    DrawText(t_buf, GetScreenWidth()/2 - textW/2, GetScreenHeight()/2 - fontSize/2, fontSize, WHITE);

    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
