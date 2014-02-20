#! /usr/bin/env sh

cd ../build
./build.py ../source/buildconfig/testlib.cfg ../source/buildconfig/varlist.cfg
cd ../..
./install.py
cd engine/source

