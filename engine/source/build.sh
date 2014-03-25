#! /usr/bin/env sh

cd ../build
./build.py ../source/buildconfig/testlib.cfg ../source/buildconfig/varlist.cfg ../source/buildconfig/floor.cfg ../source/buildconfig/ceil.cfg
mv ../source/extensions/varlib.o /usr/local/pkb
mv ../source/extensions/testlib.o /usr/local/pkb
mv ../source/extensions/floor.o /usr/local/pkb
mv ../source/extensions/ceil.o /usr/local/pkb
cd ../..
./install.py
cd engine/source

