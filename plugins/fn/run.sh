#!/bin/bash

GCC=../../gcc-native/bin/gcc

$GCC -O0 -fplugin=./plugin.so main.c -o withPlugin #&> log
$GCC -O0 main.c -o noPlugin
