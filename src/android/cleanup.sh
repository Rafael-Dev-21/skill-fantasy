#!/usr/bin/sh

for i in render.c chain.c game.c memory.c surface.c \
  render.h chain.h game.h memory.h surface.h \
  model.c model.h obj_pose.c \
  util.h vec.h
do
  rm "jni/${i}"
done

#for i in c h
#do
#  rm "jni/android_native_app_glue.${i}"
#done
