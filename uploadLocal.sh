#!/bin/sh
./gradlew :lancer:publishToMavenLocal --no-daemon --no-parallel
./gradlew :plugin:tracePlugin:publishToMavenLocal --no-daemon --no-parallel
