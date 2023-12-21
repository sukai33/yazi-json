#!/bin/bash -eu
sed -i 's/g++/${CXX}/g' Makefile
sed -i 's/-Werror//g' Makefile
make

# Copy all fuzzer executables to $OUT/
$CXX $CFLAGS $LIB_FUZZING_ENGINE \
  $SRC/yazi-json/.clusterfuzzlite/parse_fuzzer.cpp \
  -o $OUT/parse_fuzzer \
  -I$SRC/yazi-json/json \
  json/Parser.o json/Json.o
