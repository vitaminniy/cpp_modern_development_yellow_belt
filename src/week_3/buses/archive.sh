#!/usr/bin/env sh

NAME="sources.tar.gz"

find . -type f -name "*.h" -print -o -name "*.cpp" -print | xargs tar -czf $NAME
