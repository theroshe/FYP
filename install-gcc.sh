#!/bin/bash

GCCVER=4.9.1

BUILD="$(pwd)/gcc/output"
INSTALL="$(pwd)/native"

if [ ! -d gcc ]; then
	mkdir gcc
fi

cd gcc

if [ ! -f gcc-$GCCVER.tar.gz ]; then
	wget ftp://ftp.gnu.org/gnu/gcc/gcc-$GCCVER/gcc-$GCCVER.tar.gz
fi

if [ ! -d gcc-$GCCVER ]; then
	tar -xvf gcc-$GCCVER.tar.gz
fi

if [ ! -d $BUILD ]; then
	mkdir $BUILD
fi

if [ ! -f gcc-$GCCVER/mpfr ]; then
	cd gcc-$GCCVER
	./contrib/download_prerequisites
	cd ..
fi

cd $BUILD

../gcc-$GCCVER/configure --prefix=$INSTALL --enable-plugin --enable-languages=c,c++ --disable-multilib --disable-nls

make
make install
