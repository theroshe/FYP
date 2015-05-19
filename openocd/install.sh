#!/bin/bash

if [ "$UID" -ne 0 ]; then
	echo Must be run as root
	exit
fi
	

cd openocd-0.7.0
make install
