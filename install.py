#! /usr/bin/env python

import os
import sys
import platform
import ConfigParser


print """ 
Welcome to the PKBASIC installer!
This will install the PKBASIC interpreter onto your system.
"""
while 1==1:
	s = raw_input("Proceed? [y/n]: ").lower()
	if s == "n" or s == "no":
		print "installation aborted\n"
		sys.exit(0)
	if s == "y" or s == "yes":
		break

print("proceeding with installation\n\nDetecting OS...")
print("Detected OS: " + platform.system())
print("OS type: " + os.name)
print("OS release: " + platform.release())
TMPDIR = ""
LIB_LOC = ""
BIN_DIR = ""
COMPILER = ""

if os.name == "posix":
	print("detected posix system, setting variables...")
	TMPDIR = '\\"/tmp/\\"'
	LIB_LOC = '\\"/usr/local/pkb/\\"'
	BIN_DIR = "/usr/local/bin"
	COMPILER = 'g++'
elif os.name == "nt":
	print("detected windows system, setting variables...")
	print(" // I have not tested on windows so things may explode // ") 
	# tons of backslashes because this gets parsed twice - once by python and then by the interpreter
	TMPDIR = '\\"C:\\\\temp\\\\\\"'
	LIB_LOC = '\\"C:\\\\PKB\\\\LIBS\\"'
	BIN_DIR = "C:\\\\PKB\\\\"
	COMPILER = raw_input("Compiler to use: ")
else:
	print("unknown platform detected.\n")
	while 1==1:
	        s = raw_input("Configure manually? [y/n]: ").lower()
	        if s == "n" or s == "no":
       		        print "installation aborted\n"
                	sys.exit(0)
	        if s == "y" or s == "yes":
	                break
	
	print("please only use absolute paths")
	TMPDIR = raw_input("Temporary directory path: ")
	LIB_LOC = raw_input("Folder in which to search for external libraries: ")
	BIN_DIR = raw_input("Folder in which to place interpreter (should be on your path): ")
	COMPILER = raw_input("Compiler to use: ")

cfg = ConfigParser.ConfigParser()

try:
	cfg.read("build/main.cfg")
except:
	print("error opening build/main.cfg\ntry downloading the project again")
	sys.exit(0)
try:
	args = ("-std=c++11 -DLIB_LOC=" + LIB_LOC + " -DTMPDIR=" + TMPDIR)
	cfg.set("CONFIG","additional args", args)
	cfg.set("CONFIG","output dir", BIN_DIR)
	cfg.set("CONFIG","compiler", COMPILER)
except:
	print("error processing the config file")
	sys.exit(0)
try:
	cfg.write(open("build/main.cfg","w"))
except:
	print("error writing config file")
	sys.exit(0)

print(""" 
created config file at build/main.cfg

""")
while 1==1:
        s = raw_input("Proceed to build? [y/n]: ").lower()
        if s == "n" or s == "no":
                print "installation aborted\n"
                sys.exit(0)
        if s == "y" or s == "yes":
                break

os.system("python engine/build/build.py build/main.cfg")
print("Finished build process.")
