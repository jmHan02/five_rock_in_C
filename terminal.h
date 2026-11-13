#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

int getch(void);
int cursor_move(int *cursor_x, int *cursor_y );
#endif