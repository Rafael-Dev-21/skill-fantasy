package com.rafa21.skfan;

import android.content.Context;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.MotionEvent;

public class GameView extends SurfaceView
  implements SurfaceHolder.Callback, Runnable {
  static {
    System.loadLibrary("skfantasy");
  }
  private Thread thread;
  private boolean running = false;
  private native void nativeInit(Object surface);
  private native void nativeStep();
  private native void nativeTouch(int x, int y);
  private native void nativeShutdown();
  private native int nativeFPS();
  private native int nativeWidth();
  private native int nativeHeight();
  public GameView(Context context) {
    super(context);
    getHolder().addCallback(this);
  }
  @Override
  public void surfaceCreated(SurfaceHolder holder) {
    nativeInit(holder.getSurface());
    running = true;
    thread = new Thread(this);
    thread.start();
  }
  @Override
  public void surfaceDestroyed(SurfaceHolder holder) {
    running = false;
    nativeShutdown();
    boolean retry = true;
    while (retry) {
      try {
        thread.join();
        retry = false;
      } catch (InterruptedException e) {}
    }
  }
  @Override
  public void surfaceChanged(SurfaceHolder holder, int format,
      int width, int height) {}
  @Override
  public void run() {
    final long frameTime = 1000L / nativeFPS();
    while (running) {
      long start = System.currentTimeMillis();
      nativeStep();
      long dt = System.currentTimeMillis() - start;
      if (dt < frameTime) {
        try { Thread.sleep(frameTime - dt); }
        catch (InterruptedException e) {}
      }
    }
  }
  @Override
  public boolean onTouchEvent(MotionEvent me) {
    nativeTouch(
        (int)me.getX()*nativeWidth()/getWidth(),
        (int)me.getY()*nativeHeight()/getHeight());
    return true;
  }
}
