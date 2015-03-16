#!/bin/bash

INSTALL=/home/rob/fyp/crosstool-ng
BUILD=/home/rob/fyp/crosstool-ng-1.20.0

export PATH=$PATH:$INSTALL/bin

if [ ! -d $BUILD ]; then
	mkdir $BUILD
fi

cd $BUILD

#Set up symlinks to force use of python 2 rather than 3
mkdir /home/rob/fyp/temp
ln -s /bin/python2 /home/rob/fyp/temp/python
ln -s /bin/python2-config /home/rob/fyp/temp/python-config

./ct-ng clean
PATH=/home/rob/fyp/temp:$PATH ./ct-ng build

rm -rf /home/rob/fyp/temp
