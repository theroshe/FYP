#!/bin/bash

GCC=/home/rob/fyp/install/bin/gcc

$GCC -fplugin=./plugin.so main.c -fdump-tree-original-raw
