#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearBuffer(char *buffer, Dimensions dimensions) {
  for (int y = 0; y < dimensions.height; y++) {
    for (int x = 0; x < dimensions.width; x++) {
      buffer[y * dimensions.width + x] = ' ';
    }
  }
}

void printBuffer(char *buffer, Dimensions dimensions) {
  int bufSize = (dimensions.width * 2 + 1) * dimensions.height + 1;
  char *output = (char *)malloc(bufSize);
  if (!output) {
    fprintf(stderr, "Memory allocation failed\n");
    return;
  }

  char *ptr = output;
  for (int y = 0; y < dimensions.height; y++) {
    for (int x = 0; x < dimensions.width; x++) {
      *ptr++ = buffer[y * dimensions.width + x];
      *ptr++ = ' ';
    }
    *ptr++ = '\n';
  }
  *ptr = '\0';

  printf("%s", output);
  free(output);
}

bool cellIsLiving(char *buffer, int x, int y, Dimensions dimensions) {
  if (x > dimensions.width - 1 || y > dimensions.height - 1 || x < 0 || y < 0) {
    return false;
  }

  if (*(buffer + y * dimensions.width + x) == ' ') {
    return false;
  } else {
    return true;
  }
}

void printBufferWithSelector(char *buffer, Dimensions dimensions, int x,
                             int y) {
  for (int i = 0; i < dimensions.height; i++) {
    for (int j = 0; j < dimensions.width; j++) {
      bool liveCell = cellIsLiving(buffer, j, i, dimensions);
      if (y == i && x == j) {
        if (!liveCell) {
          printf("\033[43m%c\033[0m ", *(buffer + i * dimensions.width + j));
        } else {
          printf("\033[1;33m%c\033[0m ", *(buffer + i * dimensions.width + j));
        }
      } else {
        printf("%c ", *(buffer + i * dimensions.width + j));
      }
    }
    printf("\n");
  }
}

int killCell(char *buffer, int x, int y, Dimensions dimensions) {
  if (x > dimensions.width - 1 || y > dimensions.height - 1 || x < 0 || y < 0) {
    return -1;
  }

  *(buffer + y * dimensions.width + x) = ' ';

  return 0;
}

int giveLife(char *buffer, int x, int y, Dimensions dimensions) {
  if (x > dimensions.width - 1 || y > dimensions.height - 1 || x < 0 || y < 0) {
    return -1;
  }

  *(buffer + y * dimensions.width + x) = '#';

  return 0;
}

/**
 * NW N NE
 *
 * W     E
 *
 * SW S SE
 */
int getNeighbourCount(char *buffer, int x, int y, Dimensions dimensions) {
  int count = 0;

  // North
  if (y - 1 >= 0 && cellIsLiving(buffer, x, y - 1, dimensions)) {
    count++;
  }

  // East
  if (x + 1 < dimensions.width && cellIsLiving(buffer, x + 1, y, dimensions)) {
    count++;
  }

  // South
  if (y + 1 < dimensions.height && cellIsLiving(buffer, x, y + 1, dimensions)) {
    count++;
  }

  // West
  if (x - 1 >= 0 && cellIsLiving(buffer, x - 1, y, dimensions)) {
    count++;
  }

  // North West
  if (y - 1 >= 0 && x - 1 >= 0 &&
      cellIsLiving(buffer, x - 1, y - 1, dimensions)) {
    count++;
  }

  // North East
  if (y - 1 >= 0 && x + 1 < dimensions.width &&
      cellIsLiving(buffer, x + 1, y - 1, dimensions)) {
    count++;
  }

  // South East
  if (y + 1 < dimensions.height && x + 1 < dimensions.width &&
      cellIsLiving(buffer, x + 1, y + 1, dimensions)) {
    count++;
  }

  // South West
  if (y + 1 < dimensions.height && x - 1 >= 0 &&
      cellIsLiving(buffer, x - 1, y + 1, dimensions)) {
    count++;
  }

  return count;
}

void step(char *buffer, char *copyBuffer, Dimensions dimensions) {
  for (int y = 0; y < dimensions.height; y++) {
    for (int x = 0; x < dimensions.width; x++) {
      int neighbourCount = getNeighbourCount(buffer, x, y, dimensions);
      bool liveCell = cellIsLiving(buffer, x, y, dimensions);

      if (liveCell && (neighbourCount == 2 || neighbourCount == 3)) {
        giveLife(copyBuffer, x, y, dimensions);
      }

      if (!liveCell && neighbourCount == 3) {
        giveLife(copyBuffer, x, y, dimensions);
      }
    }
  }
}
