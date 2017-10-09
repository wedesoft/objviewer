#!/bin/sh
while true; do
  clear;
  make check;
  inotifywait -e CLOSE_WRITE `git ls-files`;
done
