#! /usr/bin/env sh

cd ../build
./build.py ../source/buildconfig/testlib.cfg ../source/buildconfig/varlist.cfg
mv ../source/extensions/varlib.o /usr/local/pkb
mv ../source/extensions/testlib.o /usr/local/pkb
cd ../..
./install.py
cd engine/source

