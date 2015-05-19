#!/bin/bash

GCC=../../gcc-native/bin/gcc

$GCC -fplugin=./plugin.so main.c -fdump-tree-original-raw
