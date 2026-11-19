#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <raylib.h>

#include "scramble.h"
#include "cube_draw.h"

#define FONT_SIZE 48
#define MIN_FONT_SIZE 8
#define MAX_FONT_SIZE 400
#define TIMER_FORMAT "00.00"

double  t_start;
enum    { IDLE, RUNNING, STOPPED } state = IDLE;
char    t_buf[32] = TIMER_FORMAT;

void fmt_time(char *buf, double t) {
  int cs = (int)(t * 100);
  if (cs >= 6000) sprintf(buf, "%d:%02d.%02d", cs / 6000, cs / 100 % 60, cs % 100);
  else            sprintf(buf, "%02d.%02d", cs / 100, cs % 100);
}

int main(void) {
  int screenWidth = 800, screenHeight = 400;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(screenWidth, screenHeight, "cuub");

  // Simple fix for '1' as its not monospaced and breaks displaying looks
  Font f = GetFontDefault();
  f.glyphs['1' - 32].advanceX = (int)f.recs['0' - 32].width;
  f.glyphs['1' - 32].offsetX += 1;

  srand(time(NULL));
  scramble_gen();
  cube_calc(scramble);

  int fontSize = FONT_SIZE;
  int scramble_display = 1;

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      switch (state) {
      case IDLE:
	t_start = GetTime();
	state = RUNNING;

	scramble_display = 0;
	break;
      case RUNNING:
	fmt_time(t_buf, GetTime() - t_start);
	state = STOPPED;

	scramble_display = 1;
	break;
      case STOPPED:
	strcpy(t_buf, TIMER_FORMAT);
	scramble_gen();
	cube_calc(scramble);
	state = IDLE;
	break;
      }
    }

    if (IsKeyDown(KEY_EQUAL)) {
      if (fontSize < MAX_FONT_SIZE) {
	fontSize += 1;
      }
    }
    
    if (IsKeyDown(KEY_MINUS)) {
      if (fontSize > MIN_FONT_SIZE) {
	fontSize -= 1;
      }
    }

    if (IsKeyPressed(KEY_ZERO)) {
      fontSize = FONT_SIZE;
    }

    if (IsKeyPressed(KEY_F)) {
      ToggleFullscreen();
    }

    if (IsKeyPressed(KEY_S)) {
      scramble_display = !scramble_display;
    }

    if (state == RUNNING) fmt_time(t_buf, GetTime() - t_start);

    BeginDrawing();
    ClearBackground((Color){18, 18, 18, 255});

    int textW = MeasureText(TIMER_FORMAT, fontSize);
    DrawTextEx(f, t_buf, (Vector2){ GetScreenWidth()/2 - textW/2, GetScreenHeight()/2 - fontSize/2 }, fontSize, fontSize/10, WHITE);

    if (scramble_display > 0) {
      DrawText(scramble, 20, 20, 20, WHITE);

      int s = 12;
      cube_draw(20, GetScreenHeight() - 11*s, s);
    }
    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
