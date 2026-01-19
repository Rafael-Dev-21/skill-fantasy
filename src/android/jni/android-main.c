#include <jni.h>
#include <android/native_window_jni.h>
#include <android/native_window.h>
#include <unistd.h>
#include <stdlib.h>

#include "game.h"

static Game game;
static ANativeWindow *window = NULL;
static int running = 0;

JNIEXPORT void JNICALL
Java_com_rafa21_skfan_GameView_nativeInit(
    JNIEnv *env,
    jobject thiz,
    jobject surface)
{
  window = ANativeWindow_fromSurface(env, surface);
  game = Game_init();

  ANativeWindow_setBuffersGeometry(
      window,
      game.display_width,
      game.display_height,
      WINDOW_FORMAT_RGBA_8888);

  running = 1;
}
/*
JNIEXPORT void JNICALL
Java_com_rafa21_skfan_GameView_nativeRezize() {}*/
JNIEXPORT void JNICALL
Java_com_rafa21_skfan_GameView_nativeTouch(
    JNIEnv *env,
    jobject thiz,
    jint x,
    jint y)
{
  Game_mouseMove(x, y);
}
JNIEXPORT void JNICALL
Java_com_rafa21_skfan_GameView_nativeStep(
    JNIEnv *env,
    jobject thiz)
{
  if (!running || !window) return;
  ANativeWindow_Buffer buffer;
  if (ANativeWindow_lock(window, &buffer, NULL) != 0)
    return;
  Game_update();
  uint32_t *dst = (uint32_t *)buffer.bits;
  uint32_t *src = game.display;
  for (int y=0; y<game.display_height; y++) {
    memcpy(
        dst + y * buffer.stride,
        src + y * game.display_width,
        game.display_width * 4);
  }
  ANativeWindow_unlockAndPost(window);
}
JNIEXPORT void JNICALL
Java_com_rafa21_skfan_GameView_nativeShutdown(
    JNIEnv *env,
    jobject thiz)
{
  running = 0;
  if (window) {
    ANativeWindow_release(window);
    window = NULL;
  }
}
JNIEXPORT jint JNICALL
Java_com_rafa21_skfan_GameView_nativeFPS(
    JNIEnv *env,
    jobject thiz)
{
  return game.fps;
}
JNIEXPORT jint JNICALL
Java_com_rafa21_skfan_GameView_nativeWidth(
    JNIEnv *env,
    jobject thiz)
{
  return game.display_width;
}
JNIEXPORT jint JNICALL
Java_com_rafa21_skfan_GameView_nativeHeight(
    JNIEnv *env,
    jobject thiz)
{
  return game.display_height;
}

#if 0
void handle_cmd(struct android_app *pApp, int32_t cmd)
{}

void android_main(struct android_app *pApp)
{
  pApp->onAppCmd = handle_cmd;

  int events;
  struct android_poll_source *pSource;
  do {
    if (ALooper_pollOnce(0, NULL, &events, (void **) &pSource) >= 0) {
      if (pSource) {
        pSource->process(pApp, pSource);
      }
    }
  } while(!pApp->destroyRequested);
}
#endif
