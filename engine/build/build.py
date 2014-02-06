#! /usr/bin/env python

import os
import sys
import shutil
from ConfigParser import ConfigParser

# get rid of the first arg (invocation)
args = sys.argv
args.pop(0)

# spin
count = 0
for arg in args:
	
	print("loading config [" + arg + "]")
	try:
		cfg = ConfigParser()
		cfg.read(arg)
	except:
		print("unable to open config file\n")
		sys.exit(0)
	# get configuration
	try:
		cm = cfg.get("CONFIG", "compiler")
		mf = cfg.get("CONFIG", "input name")
		ml = cfg.get("CONFIG", "input dir")
		on = cfg.get("CONFIG", "output name")
		od = cfg.get("CONFIG", "output dir")
		ls = cfg.get("CONFIG", "lib search dirs")
		lb = cfg.get("CONFIG", "libraries")
		id = cfg.get("CONFIG", "include dirs")
		aa = cfg.get("CONFIG", "additional args")
		ln = cfg.get("CONFIG", "add hardlink")
		ll = cfg.get("CONFIG", "hardlink location")
	except:
		print("invalid config file\n")
		sys.exit(0)
	
	# stick together all the basic stuffs
	command = cm + " " + ml + mf + " -o " + on + " " + aa + " "
	
	# manage external libdirs
	for libd in ls:
		command = command + " -L" + libd
	command += " "
	
	# manage libraries
	for lib in lb:
		command += " -l" + lib
	command += " "
	
	# manage includes
	for inc in id:
		command += " -I" + inc

	# invoke
	print("step 1: build")
	print("\tinvoking [" + command + "]\n")
	os.system(command)

	# detect build failure
	if os.path.isfile(on):
		print "\n\tbuild succeeded."
	else:
		print("\n\n\tbuild failed.\nAborting...")
		sys.exit(0)

	# move build
	print("\nstep 2: file organization\n\tmoving output to desired location")
	try:
		shutil.move(on, od)
	except:
		print("\t\tfile exists, overwriting...")
		os.system("mv " + on + " " + od)
	
	# make a hardlink if desired
	if ln == "yes":
		print("\nstep 3: hardlink\n\thardlinking from location to desired locations...")
		cmd = "ln " + od + on + " " + ll
		print("\t\tinvoking [" + cmd + "]")
		os.system(cmd)
	
	print("finished build of [" + arg + "]")
	count += 1

print("processed " + str(count) + " config files")
