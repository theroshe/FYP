#!/bin/bash

wget http://sourceforge.net/projects/openocd/files/openocd/0.8.0/openocd-0.8.0.tar.bz2
tar -xvf openocd-0.8.0.tar.bz2
cd openocd-0.8.0 
./configure --enable-maintainer--mode --enable-legacy-ft2232_libftdi
#--enable-armjtagew --enable-ftdi 
#--enable-legacy-ft2232-ftd2xx
make
