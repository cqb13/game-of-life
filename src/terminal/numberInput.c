#include "input.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int getNumberInput(int *current, char *prompt, int min, int max,
                   int defaultValue) {
  printf("%s", prompt);
  if (min != -1 && max != -1) {
    printf(" (%d <= b <= %d):\n\n", min, max);
  } else if (min != -1) {
    printf("(%d <= b):\n\n", min);
  } else if (max != -1) {
    printf("(b <= %d):\n\n", max);
  } else {
    printf(":\n\n");
  }
  set_input_mode();
  char c;
  int factor = 10;
  *current = -1;
  while (1) {
    c = getchar();
    if (c >= 0x30 && c <= 0x39) {
      if (*current == -1) {
        *current = c - 0x30;
        printf("\033[A\033[K%d\n", *current);
        continue;
      }
      *current *= factor;
      *current += (c - 0x30);
      reset_input_mode();
      printf("\033[A\033[K%d\n", *current);
      set_input_mode();
      continue;
    } else if (c == 27) {
      // TODO: fix this
      reset_input_mode();
      return Quit;
    } else if (c == 127) {
      // Backspace
      if (*current == -1) {
        continue;
      }
      *current /= 10;
      reset_input_mode();
      printf("\033[A\033[K%d\n", *current);
      set_input_mode();
      continue;
    } else if (c == 10) {
      if (*current == -1) {
        *current = defaultValue;
        return Enter;
      }
      if (min != -1 && *current < min) {
        continue;
      }

      if (max != -1 && *current > max) {
        continue;
      }
      reset_input_mode();
      return Enter;
    } else {
      continue;
    }
  }

  reset_input_mode();
}
