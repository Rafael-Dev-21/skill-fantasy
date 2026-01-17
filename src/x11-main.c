#include <X11/Xlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "game.h"

int main(void)
{
  Game game;
  Display *display;
  Window window;
  XWindowAttributes wa;
  XImage *image;
  GC gc;
  Atom wm_delete_window;
  XEvent event;
  struct timespec tsbegin, tsend;
  long delta, target;
  int running;

  game = Game_init();

  target = (1000*1000)/game.fps;

  display = XOpenDisplay(NULL);
  if (display == NULL) {
    return 1;
  }
  window = XCreateSimpleWindow(
      display,
      XDefaultRootWindow(display),
      0, 0,
      game.display_width, game.display_height,
      0,
      0,
      0);

  memset(&wa, 0, sizeof(wa));
  XGetWindowAttributes(display, window, &wa);
  image = XCreateImage(
      display,
      wa.visual,
      wa.depth,
      ZPixmap,
      0,
      (char*)game.display,
      game.display_width,
      game.display_height,
      32,
      game.display_width * sizeof(game.display[0]));

  gc = XCreateGC(display, window, 0, NULL);

  wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(display, window, &wm_delete_window, 1);

  XSelectInput(display, window, KeyPressMask | PointerMotionMask);

  XMapWindow(display, window);

  running = 1;
  while (running) {
    while (XPending(display)>0) {
      memset(&event, 0, sizeof(event));
      XNextEvent(display, &event);
      switch (event.type) {
      case ClientMessage: {
        if ((Atom) event.xclient.data.l[0] == wm_delete_window) {
          running = 0;
        }
      }
      break;
      case MotionNotify: {
        Game_mouseMove(event.xmotion.x, event.xmotion.y);
      }
      break;
      }
    }
    clock_gettime(CLOCK_MONOTONIC, &tsbegin);
    Game_update();
    XPutImage(display, window, gc, image, 0, 0, 0, 0,
        game.display_width, game.display_height);
    clock_gettime(CLOCK_MONOTONIC, &tsend);
    long delta = (tsend.tv_sec-tsbegin.tv_sec)*1000*1000 + (tsend.tv_nsec-tsbegin.tv_nsec)/1000;
    if (delta < target) {
      usleep(target-delta);
    }
  }
}
