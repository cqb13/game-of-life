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
  clearLines(2);
  int generations = -1;
  getNumberInput(&generations, "Generations [inf]", 1, 1000000000, -1);
  clearLines(2);
  // TODO: speed input

  Dimensions dimensions = {width, height};

  char *buffer =
      (char *)malloc(dimensions.height * dimensions.width * sizeof(char));
  char *copyBuffer =
      (char *)malloc(dimensions.height * dimensions.width * sizeof(char));

  clearBuffer(buffer, dimensions);

  int running = 1;
  int selectorX = width / 2;
  int selectorY = height / 2;
  printf("← ↑ ↓ →: Move Selector | Space: Toggle Cell | Enter: Run\n");
  printBufferWithSelector(buffer, dimensions, selectorX, selectorY);
  while (running == 1) {
    clearLines(dimensions.height);
    printBufferWithSelector(buffer, dimensions, selectorX, selectorY);
    Input keyPress = getKeyPress();
    switch (keyPress) {
    case Left:
      selectorX--;
      if (selectorX < 0) {
        selectorX = width - 1;
      }
      continue;
    case Right:
      selectorX++;
      if (selectorX >= width) {
        selectorX = 0;
      }
      continue;
    case Up:
      selectorY--;
      if (selectorY < 0) {
        selectorY = height - 1;
      }
      continue;
    case Down:
      selectorY++;
      if (selectorY >= height) {
        selectorY = 0;
      }
      continue;
    case Space: {
      bool liveCell = cellIsLiving(buffer, selectorX, selectorY, dimensions);

      if (liveCell) {
        killCell(buffer, selectorX, selectorY, dimensions);
      } else {
        giveLife(buffer, selectorX, selectorY, dimensions);
      }
      continue;
    }
    case Enter:
      running = 0;
      break;
    case Quit:
      exit(0);
    case Invalid:
      continue;
    default:
      continue;
    }
  }
  clearLines(dimensions.height + 1);

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
    usleep(200000);
    useCopy = !useCopy;
    if (generations != -1) {
      turns--;
    }
  }

  free(buffer);
  free(copyBuffer);
}
