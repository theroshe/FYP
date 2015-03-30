#!/bin/bash

VER=1.20.0
INSTALL=$(pwd)/crosstool-ng

if [ ! -d $INSTALL ]; then
	mkdir $INSTALL
fi

if [ ! -f crosstool-ng-$VER.tar.bz2 ]; then
	wget http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-$VER.tar.bz2
fi

if [ ! -d crosstool-ng-$VER ]; then
	tar -xvf crosstool-ng-$VER.tar.bz2
fi

cd crosstool-ng-$VER

./configure --prefix=$INSTALL
make
make install

