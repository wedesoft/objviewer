#!/bin/sh
while true; do
  clear;
  make check -j 4;
  inotifywait -e CLOSE_WRITE `git ls-files`;
  sleep 1;
done
