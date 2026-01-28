#pragma once

#include "geom.hh"

class CursesWindow {
  typedef WINDOW *winptr;
public:
  CursesWindow();
  CursesWindow(int x, int y, int w, int h);
  ~CursesWindow();
  void move_cursor(int x, int y);
  void move_cursor(const Pt& p);
  void putch(int ch);
  int readch();
  void flush();
  void reset();
  void putstr(const char *fmt...);
  void set_nodelay(bool val);
  void box(int x, int y);

  Pt dims();

  inline winptr handle_ptr() const { return handle_; }

  CursesWindow make_child(int x, int y, int w, int h);
  CursesWindow get_parent();

private:
  winptr handle_;
  CursesWindow *parent_ = nullptr;
  bool sub=false;
};

class CursesAttrGuard {
public:
  CursesAttrGuard(const CursesWindow& w, int attr);
  ~CursesAttrGuard();

private:
  const CursesWindow& w;
  int attr;
};
