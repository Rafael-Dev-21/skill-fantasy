#!/usr/bin/sh

for i in render.c chain.c game.c memory.c surface.c \
  render.h chain.h game.h memory.h surface.h \
  model.c model.h \
  util.h vec.h
do
  cp "../common/${i}" jni
done

#for i in c h
#do
#  cp "../3rdparty/android-ndk/android-native-app/android_native_app_glue.${i}" jni
#done
