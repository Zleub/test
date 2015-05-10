#!/bin/sh

if [ ! -s "lua/liblua.dylib" ]; then (
	cd lua ;
	git submodule init ;
	git submodule update ;
	cmake . ;
	make ;
) fi ;
