#include "curses.h"
#include "networking.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <fstream>

static bool end_thread = false;

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

std::string get_test_str() {
  //return Networking::get_string();
  //std::ifstream JsonFile("test.json");
  //std::string data((std::istreambuf_iterator<char>(JsonFile)),
                    //std::istreambuf_iterator<char>());
  //JsonFile.close();
  std::string data = Networking::get_message_from_server();
  rapidjson::Document d;
  d.Parse(data.c_str());
  const rapidjson::Value& message = d["message"];
  return message.GetString();
}

void thread_func( WINDOW *win ) {
  using namespace std::literals::chrono_literals;
  int counter = 1;
  int counter2 = 0;
  std::string datestr = get_test_str();

  while ( !end_thread ) {
    werase( win );
    box( win, 0, 0 );

    wattron( win, A_BOLD );
    int over = datestr.size() + counter - (COLS - 1);
    if (over == datestr.size() ) {
      counter = 1;
      mvwprintw( win, 1, counter++, datestr.c_str() );
    }
    else if (over > 0) {
      std::string first = datestr.substr( 0, datestr.size() - over );
      std::string second = datestr.substr( datestr.size() - over, datestr.size() - 1 );
      mvwprintw( win, 1, counter++, first.c_str() );
      mvwprintw( win, 1, 1, second.c_str() );
    }
    else {
      mvwprintw( win, 1, counter++, datestr.c_str() );
    }
    wattroff( win, A_BOLD );
    wrefresh( win );
    counter2++;
    if (counter2 == 100) {
      counter2 = 0;
      datestr = get_test_str();
    }
    std::this_thread::sleep_for( 300ms );
  }
}

int main( int argc, char *argv[] ) {
  std::string buff;
  WINDOW *win;
  auto curses = Curses();

  // height, width, starty, startx
  win = newwin( 3, COLS, 0, 0 );
  box( win, 0, 0 );
  wrefresh( win );

  std::thread worker( thread_func, win );

  getch();
  mvwprintw( win, 1, 1, "quitting............." );
  wrefresh( win );
  end_thread = true;
  worker.join();
  return 0;
}
