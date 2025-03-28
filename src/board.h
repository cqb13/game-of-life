#include <stdbool.h>

#ifndef BOARD_H
#define BOARD_H

typedef struct Dimensions {
  int width;
  int height;
} Dimensions;

void clearLines(int lines);
void clearBuffer(char *buffer, Dimensions dimensions);
void printBuffer(char *buffer, Dimensions dimensions);
bool cellIsLiving(char *buffer, int x, int y, Dimensions dimensions);
void printBufferWithSelector(char *buffer, Dimensions dimensions, int x, int y);
int giveLife(char *buffer, int x, int y, Dimensions dimensions);
int killCell(char *buffer, int x, int y, Dimensions dimensions);
void step(char *buffer, char *copyBuffer, Dimensions dimensions);
#endif
