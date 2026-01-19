package com.rafa21.skfan;

public class SkillFantasy extends android.app.Activity {

  public void onCreate(android.os.Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(new GameView(this));
  }
}
