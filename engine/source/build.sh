#! /usr/bin/env sh

cd ../build
<<<<<<< HEAD
./build.py ../source/buildconfig/testlib.cfg ../source/buildconfig/varlist.cfg ../source/buildconfig/floor.cfg ../source/buildconfig/ceil.cfg
mv ../source/extensions/varlib.o /usr/local/pkb
mv ../source/extensions/testlib.o /usr/local/pkb
mv ../source/extensions/floor.o /usr/local/pkb
mv ../source/extensions/ceil.o /usr/local/pkb
=======
./build.py ../source/buildconfig/testlib.cfg ../source/buildconfig/varlist.cfg
mv ../source/extensions/varlib.o /usr/local/pkb
mv ../source/extensions/testlib.o /usr/local/pkb
>>>>>>> 07dc474b8bb0b0594d46ad169578e74f26ad2d5b
cd ../..
./install.py
cd engine/source

