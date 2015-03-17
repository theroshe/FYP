#!/bin/bash

GCCVER=4.9.1

PREFIX="$(pwd)/gcc/output"

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

if [ ! -d $PREFIX ]; then
	mkdir $PREFIX
fi

if [ ! -f gcc-$GCCVER/mpfr ]; then
	cd gcc-$GCCVER
#	./contrib/download_prerequisites
	cd ..
fi

cd $PREFIX
pwd

../gcc-$GCCVER/configure --prefix=$PREFIX --enable-plugin --enable-languages=c,c++ --disable-multilib --disable-nls

make
