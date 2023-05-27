#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ncurses.h>


using namespace std;


int main() {


  initscr();

  // timeout(-1);
  cbreak();
  noecho();
  clear();
  // intrflush(display, false);
  // raw();
  WINDOW *display = newwin(10, 50, 0, 0);
  box(display, 0, 0);
  refresh();

  keypad(display, true);

  int i;

  while(true) {
    i = wgetch(display);
    // printw("%d \n",i);
    // refresh();
    // move(0,0);
    if(i == KEY_UP) {
      mvwprintw(display,1,1,"up arrow pressed \n");
      wrefresh(display);
    } else if (i == KEY_DOWN) {
      mvwprintw(display,1,1,"down arrow pressed \n");
      wrefresh(display);
    } else if (i == KEY_RIGHT) {
      mvwprintw(display,1,1,"right arrow pressed \n");
      wrefresh(display);
    } else if (i == KEY_LEFT) {
      mvwprintw(display,1,1,"left arrow pressed \n");
      wrefresh(display);
    }
    // system("clear");
    // printw("............");
  }

    // getch();
  
  endwin();

  return 0;
}

