#!/bin/bash

#rm dump/*

#/home/rob/build/output/bin/g++ -fplugin=./plugin.so main.c 
#-fdump-tree-gimple-raw-details

GCC=/home/rob/fyp/gcc/output/bin/gcc 

$GCC -fplugin=./plugin.so main.c -fdump-tree-original-raw


#mv main.c.* dump
