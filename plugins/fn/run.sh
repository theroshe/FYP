#!/bin/bash

GCC=../../gcc-native/bin/gcc

$GCC -fplugin=./plugin.so main.c -o withPlugin #&> log
$GCC main.c -o noPlugin
