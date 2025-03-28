#include "./terminal/input.h"
#include "./terminal/numberInput.h"
#include "board.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int width = -1;
  getNumberInput(&width, "Enter board width [50]", 0, 100, 50);
  clearLines(2);
  int height = -1;
  getNumberInput(&height, "Enter board height [50]", 0, 100, 50);
  int generations = -1;
  getNumberInput(&generations, "Generations [inf]", 1, 1000000000, -1);

  Dimensions dimensions = {width, height};

  char *buffer =
      (char *)malloc(dimensions.height * dimensions.width * sizeof(char));
  char *copyBuffer =
      (char *)malloc(dimensions.height * dimensions.width * sizeof(char));

  clearBuffer(buffer, dimensions);

  giveLife(buffer, 4, 2, dimensions);
  giveLife(buffer, 3, 2, dimensions);
  giveLife(buffer, 2, 2, dimensions);
  giveLife(buffer, 3, 1, dimensions);
  giveLife(buffer, 2, 1, dimensions);
  giveLife(buffer, 1, 1, dimensions);

  printBuffer(buffer, dimensions);
  bool useCopy = false;
  int turns = generations;
  if (generations == -1) {
    turns = 1;
  }
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
    if (generations != -1) {
      turns--;
    }
  }

  free(buffer);
  free(copyBuffer);
}
