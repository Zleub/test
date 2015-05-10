#!/bin/sh

cd lua ;
git submodule init ;
git submodule update ;
cmake . ;
make ;
mv luaconf.h src\ ;
