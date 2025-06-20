#!/bin/bash

set -e

rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
echo "Build Complete"

case "$1" in
  -c)
    echo "Starting Client..."
    ./client/client
    ;;
  -s)
    echo "Starting Server..."
    ./server/server
    ;;
esac
