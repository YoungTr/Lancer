#!/bin/sh
if [ "$1" = "on" ]
then
  echo './gradlew :app:iD --parallel --daemon --stacktrace'
  ./gradlew :app:installDebug --parallel --daemon --stacktrace
else
  echo './gradlew :app:iD --offline --parallel --daemon --stacktrace'
  ./gradlew :app:installDebug --offline --parallel --daemon --stacktrace
fi

adb shell am start com.bomber.strace/.MainActivity