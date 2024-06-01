#!/usr/bin/env bash
echo "Build Eco.MemoryManager1Lab"
DIR=$(cd "$(dirname "$0")"; pwd)
echo $DIR
export TARGET=0
export DEBUG=0
make -f Makefile
export TARGET=0
export DEBUG=1
make -f Makefile
export TARGET=1
export DEBUG=0
make -f Makefile
export TARGET=1
export DEBUG=1
make -f Makefile