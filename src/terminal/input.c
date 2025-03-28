#include "input.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void set_input_mode() {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~(ICANON | ECHO);
  t.c_cc[VMIN] = 1;
  t.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void reset_input_mode() {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag |= (ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void clearLines(int lines) {
  for (int i = 0; i < lines; i++) {
    printf("\033[A\033[K");
  }
}

char getCharKeyPress() {
  set_input_mode();
  char c = getchar();
  reset_input_mode();
  return c;
}

Input getKeyPress() {
  set_input_mode();
  char c;

  while (1) {
    c = getchar();

    if (c == 27) {
      c = getchar();
      if (c == '[') {
        c = getchar();
        switch (c) {
        case 'A':
          reset_input_mode();
          return Up;
        case 'B':
          reset_input_mode();
          return Down;
        case 'C':
          reset_input_mode();
          return Right;
        case 'D':
          reset_input_mode();
          return Left;
        default:
          continue;
        }
      }
    } else if (c == '\x1b') {
      reset_input_mode();
      return Quit;
    } else if (c == 0x20) {
      reset_input_mode();
      return Space;
    } else if (c == 10) {
      reset_input_mode();
      return Enter;
    } else if (c == 127) {
      reset_input_mode();
      return Backspace;
    }
  }

  reset_input_mode();
}
