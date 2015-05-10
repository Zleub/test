#!/bin/sh

cd lib/lua ;
git submodule init ;
git submodule update ;
cmake . ;
make ;
