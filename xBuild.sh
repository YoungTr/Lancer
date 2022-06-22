#!/bin/sh
if [ "$1" = "on" ]
then
  echo './gradlew :app:iD --parallel --daemon --stacktrace'
  ./gradlew :app:installRelease --parallel --stacktrace
else
  echo './gradlew :app:iD --offline --parallel --daemon --stacktrace'
  ./gradlew :app:installRelease --offline --parallel --stacktrace
fi

adb shell am start com.bomber.strace/.MainActivity