#pragma once

class CursesWindow {
  typedef WINDOW *winptr;
public:
  CursesWindow();
  CursesWindow(int x, int y, int w, int h);
  ~CursesWindow();
  void move(int x, int y);
  void addch(int ch);
  int getch();
  void refresh();
  void clear();
  void put(const char *fmt...);

  inline winptr handle_ptr() const { return handle_; }

private:
  winptr handle_;
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
