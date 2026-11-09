#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <raylib.h>

#include "scramble.h"

#define initScreenWidth 800
#define initScreenHeight 400
#define initFontSize 32
#define initTimerFormat "0.00"

double  t_start;
enum    { IDLE, RUNNING, STOPPED } state = IDLE;
char    t_buf[32] = initTimerFormat;

void fmt_time(char *buf, double t) {
  int cs = (int)(t * 100);
  if (cs >= 6000) sprintf(buf, "%d:%02d.%02d", cs / 6000, cs / 100 % 60, cs % 100);
  else            sprintf(buf, "%d.%02d", cs / 100, cs % 100);
}

int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(initScreenWidth, initScreenHeight, "cuub");

  srand(time(NULL));
  scramble_gen();

  int fontSize = initFontSize;
  
  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_SPACE)) {
      switch (state) {
      case IDLE:
	t_start = GetTime();
	state = RUNNING;
	break;
      case RUNNING:
	fmt_time(t_buf, GetTime() - t_start);
	state = STOPPED;
	break;
      case STOPPED:
	strcpy(t_buf, initTimerFormat);
	scramble_gen();
	state = IDLE;
	break;
      }
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

    if (IsKeyPressed(KEY_F)) {
      ToggleFullscreen();
    }

    if (state == RUNNING) fmt_time(t_buf, GetTime() - t_start);

    BeginDrawing();
    ClearBackground((Color){18, 18, 18, 255});

    int textW = MeasureText(initTimerFormat, fontSize);
    DrawText(t_buf, GetScreenWidth()/2 - textW/2, GetScreenHeight()/2 - fontSize/2, fontSize, WHITE);
    
    DrawText(scramble, 20, 20, 20, WHITE);

    EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
