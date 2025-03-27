#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  Dimensions dimensions = {10, 10};
  char *buffer =
      (char *)malloc(dimensions.height * dimensions.width * sizeof(char));
  char *copyBuffer =
      (char *)malloc(dimensions.height * dimensions.width * sizeof(char));

  clearBuffer(buffer, dimensions);

  giveLife(buffer, 6, 4, dimensions);
  giveLife(buffer, 6, 3, dimensions);
  giveLife(buffer, 6, 2, dimensions);
  giveLife(buffer, 5, 3, dimensions);
  giveLife(buffer, 5, 2, dimensions);
  giveLife(buffer, 5, 1, dimensions);

  printBuffer(buffer, dimensions);
  bool useCopy = false;
  int turns = 10;
  while (turns >= 0) {
    clearLines(dimensions.height);
    if (useCopy) {
      clearBuffer(buffer, dimensions);
      step(copyBuffer, buffer, dimensions);
      printBuffer(buffer, dimensions);
    } else {
      clearBuffer(copyBuffer, dimensions);
      step(buffer, copyBuffer, dimensions);
      printBuffer(copyBuffer, dimensions);
    }
    usleep(400000);
    useCopy = !useCopy;
    turns--;
  }

  free(buffer);
  free(copyBuffer);
}
