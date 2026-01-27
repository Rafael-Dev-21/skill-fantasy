extern "C" {
#ifndef _WIN32
#include <ncurses.h>
#else
#include <curses.h>
#endif
}
#undef addch
#undef getch
#undef clear
#include "ui.hxx"
#include <cstdarg>

CursesWindow::CursesWindow() :
  handle_(initscr())
{
  if (handle_ == nullptr) {
    throw "Error: failed to init curses.\n";
  }
  cbreak();
  noecho();
  curs_set(0);
}

CursesWindow::CursesWindow(int x, int y, int w, int h) :
  handle_(newwin(h, w, y, x)), sub(true)
{
  if (handle_ == nullptr) {
    throw "Error: failed to init curses.\n";
  }
}

CursesWindow::~CursesWindow()
{
  if (sub)
    delwin(handle_);
  else
    endwin();
}

void CursesWindow::move(int x, int y)
{
  wmove(handle_, y, x);
}

void CursesWindow::addch(int ch)
{
  waddch(handle_, ch);
}

int CursesWindow::getch()
{
  return wgetch(handle_);
}

void CursesWindow::refresh()
{
  wrefresh(handle_);
}

void CursesWindow::clear()
{
  werase(handle_);
}

void CursesWindow::put(const char *fmt...)
{
  va_list args;
  va_start(args, fmt);
  vw_printw(handle_, fmt, args);
  va_end(args);
}

CursesAttrGuard::CursesAttrGuard(const CursesWindow& w, int attr) :
  w(w), attr(attr)
{
  wattron(w.handle_ptr(), attr);
}

CursesAttrGuard::~CursesAttrGuard()
{
  wattroff(w.handle_ptr(), attr);
}
