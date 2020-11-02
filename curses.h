#pragma once
#include <ncurses.h>

class Curses {
  public:
  Curses () {
    initscr();
    raw();
    keypad( stdscr, TRUE );
    noecho();
    curs_set( 0 );
    refresh();
  }

  ~Curses() {
    endwin();
  }
};

