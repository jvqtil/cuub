#pragma once

#include <raylib.h>
#include <string.h>

static void cube_rot(int v[3], int a) {
  int t = v[(a+1)%3];
  v[(a+1)%3] = -v[(a+2)%3];
  v[(a+2)%3] = t;
}

static void cube_draw(const char *scramble, int x0, int y0, int s) {
  static const char   names[]  = "RLUDFB";
  static const Color  color[6] = { RED, ORANGE, WHITE, YELLOW, GREEN, BLUE };

  static const int net[6][6] = {
    { 2,-1,  1,-1,  6,3 },  // R
    { 2, 1,  1,-1,  0,3 },  // L
    { 0, 1,  2, 1,  3,0 },  // U
    { 0, 1,  2,-1,  3,6 },  // D
    { 0, 1,  1,-1,  3,3 },  // F
    { 0,-1,  1,-1,  9,3 },  // B
  };

    int p[54][3], n[54][3];
  for (int k = 0; k < 54; k++) {
    int face = k / 9, axis = face / 2, sign = face % 2 ? -1 : 1;
    memset(p[k], 0, sizeof p[k]);
    memset(n[k], 0, sizeof n[k]);
    p[k][axis] = n[k][axis] = sign;
    p[k][(axis+1)%3] = k % 3 - 1;
    p[k][(axis+2)%3] = k / 3 % 3 - 1;
  }
 
  for (const char *m = scramble; *m; m++) {
    const char *f = strchr(names, *m);
    if (!f) continue;
    int i = f - names, axis = i / 2, sign = i % 2 ? -1 : 1, turns = 1;
    if      (m[1] == '\'') { turns = 3; m++; }
    else if (m[1] == '2')  { turns = 2; m++; }
    if (sign > 0) turns *= 3;
 
    for (int k = 0; k < 54; k++)
      if (p[k][axis] == sign)
        for (int t = 0; t < turns; t++) {
          cube_rot(p[k], axis);
          cube_rot(n[k], axis);
        }
  }
 
  for (int k = 0; k < 54; k++) {
    int axis = n[k][0] ? 0 : n[k][1] ? 1 : 2;
    const int *g = net[axis * 2 + (n[k][axis] < 0)];
    int col = g[4] + 1 + g[1] * p[k][g[0]];
    int row = g[5] + 1 + g[3] * p[k][g[2]];
    DrawRectangle(x0 + col * s, y0 + row * s, s - 2, s - 2, color[k / 9]);
  }
}
