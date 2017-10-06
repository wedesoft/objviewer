#!/bin/sh
while true; do
  clear;
  make && ./test;
  inotifywait -e CLOSE_WRITE `git ls-files`;
done
