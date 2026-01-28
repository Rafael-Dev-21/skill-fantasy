extern "C" {
#ifndef _WIN32
#include <ncurses.h>
#else
#include <curses.h>
#endif
}
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

void CursesWindow::move_cursor(int x, int y)
{
  wmove(handle_, y, x);
}

void CursesWindow::move_cursor(const Pt& p)
{
  move_cursor(p.x, p.y);
}

void CursesWindow::putch(int ch)
{
  waddch(handle_, ch);
}

int CursesWindow::readch()
{
  return wgetch(handle_);
}

void CursesWindow::flush()
{
  wrefresh(handle_);
  if (parent_)
    parent_->flush();
}

void CursesWindow::reset()
{
  werase(handle_);
}

void CursesWindow::putstr(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vw_printw(handle_, fmt, args);
  va_end(args);
}

void CursesWindow::set_nodelay(bool val)
{
  nodelay(handle_, val);
}

void CursesWindow::box(int x, int y)
{
  ::box(handle_, y, x);
}

Pt CursesWindow::dims()
{
  Pt dm;
  getmaxyx(handle_, dm.y, dm.x);
  return dm;
}

CursesWindow CursesWindow::make_child(int x, int y, int w, int h)
{
  CursesWindow child(x, y, w, h);
  child.parent_ = this;
  return child;
}

CursesWindow CursesWindow::get_parent()
{
  if (parent_)
    return *parent_;
  return *this;
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
