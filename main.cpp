#include "curses.h"
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>

static bool end_thread( false );

std::string get_date_string() {
  char buff[0xFF];
  time_t rawtime;
  struct tm *timeinfo;
  time( &rawtime );
  timeinfo = localtime( &rawtime );
  mktime( timeinfo );
  strftime( buff, 0xFF, "%c", timeinfo );
  return std::string( buff );
}

void thread_func( WINDOW *win ) {
  using namespace std::literals::chrono_literals;

  while ( !end_thread ) {
    std::string datestr = get_date_string();
    mvwprintw( win, 1, COLS - datestr.size() - 1, datestr.c_str() );
    wrefresh( win );
    std::this_thread::sleep_for( 1s );
  }
}

int main( int argc, char *argv[] ) {
  std::string buff;
  WINDOW *win;
  auto curses = Curses();

  // height, width, starty, startx
  win = newwin( 3, COLS, 0, 0 );
  box( win, 0, 0 );
  wattron( win, A_BOLD );
  mvwprintw( win, 1, 1, "Hello there" );
  wattroff( win, A_BOLD );
  wrefresh( win );

  std::thread worker( thread_func, win );

  getch();
  mvwprintw( win, 1, 1, "quitting............." );
  wrefresh( win );
  end_thread = true;
  worker.join();
  return 0;
}
