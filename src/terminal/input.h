#ifndef INPUTS_H
#define INPUTS_H

typedef enum Input {
  Invalid,
  Left,
  Right,
  Down,
  Up,
  Enter,
  Backspace,
  Space,
  Quit,
} Input;

void set_input_mode();
void reset_input_mode();
void clearLines(int lines);
char getSingleCharKeyPress();
Input getControllerKeyPress();
#endif
