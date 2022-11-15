#!/bin/sh
./gradlew :lancer:publishToMavenLocal
./gradlew :plugin:lancerPlugin:publishToMavenLocal