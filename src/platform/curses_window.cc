#include "ui.hh"
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

CursesWindow::CursesWindow(const Pt& pos, const Pt& dims) :
  CursesWindow(pos.x, pos.y, dims.x, dims.y)
{}

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
Pt CursesWindow::pos()
{
  Pt ps;
  getbegyx(handle_, ps.y, ps.x);
  return ps;
}

void CursesWindow::move_window(int x, int y)
{
  mvwin(handle_, x, y);
}
void CursesWindow::move_window(const Pt& p)
{
  mvwin(handle_, p.x, p.y);
}
void CursesWindow::resize(int w, int h)
{
  wresize(handle_, w, h);
}
void CursesWindow::resize(const Pt& p)
{
  wresize(handle_, p.x, p.y);
}

CursesWindow CursesWindow::make_child(int x, int y, int w, int h)
{
  CursesWindow child(x, y, w, h);
  child.parent_ = this;
  return child;
}

CursesWindow CursesWindow::make_child(const Pt& p, const Pt& d)
{
  return make_child(p.x, p.y, d.x, d.y);
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
