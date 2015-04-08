#!/bin/bash

GCC=/home/rob/fyp/native/bin/gcc

$GCC -fplugin=./plugin.so main.c -fdump-tree-original-raw
