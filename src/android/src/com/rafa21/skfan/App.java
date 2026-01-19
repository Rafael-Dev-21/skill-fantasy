package com.rafa21.skfan;

import android.widget.Toast;


public class App extends android.app.Application {
  static App app = null;

  @Override
  public void onCreate() {
    super.onCreate();
    app = this;
  }

  public void logException(Exception e) {
    Toast.makeText(this, e.getMessage(), Toast.LENGTH_LONG).show();
  }
}
