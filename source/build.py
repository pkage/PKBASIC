#! /usr/bin/env python

import os
import sys
import shutil

str = ""
ntype = 0

comp = ""
args = ""
mfile = ""

f = open("buildconfig.cfg", "r")
for line in f:
	line = line[:-1]
	if ntype == 1:
		comp = line
		ntype = 0
	if ntype == 2:
		args = line
		ntype = 0
	if ntype == 3:
		mfile = line
		ntype = 0
	if "[compiler]" in line:
		ntype = 1
	if "[arguments]" in line:
		ntype = 2
	if "[mainfile]" in line:
		ntype = 3

f.close()

if comp == "":
	print("Could not get compiler info from buildconfig.cfg\nAborting...\n")
	sys.exit(0)

if mfile == "":
	print("Could not find mainfile info from buildconfig.cfg\nAborting...\n")
	sys.exit(0)

print("Compiling...\n")
os.system(comp + " " + mfile + ".cpp -o ../temp/" + mfile + " " + args)
print("\nCompile finished.")
cbt = 0
if os.path.isfile("../temp/" + mfile) == True:
	shutil.move("../temp/" + mfile, "../builds/" + mfile)
	cbt = 1
else:
	cbt_ = raw_input("Build failed. Create run token anyways? [y/n]: ")
	if cbt_ == "y" or cbt_ == "Y":
		cbt = 1

if cbt == 1:
	f = open("run", "w")
	f.write('''#! /usr/bin/env python
import os
os.system("../builds/''' + mfile + '")')
	os.system("chmod +x run")
	print("Created run token.")
else:
	print("Did not create run token. Run token currently points to previous build.")
