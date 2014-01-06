#! /usr/bin/env python
import os
name = raw_input("Name for tarred sources [omit .tar.gz]: ")
os.system("cd ..")
os.system("tar -zcvf backups/" + name + ".tar.gz source")
os.system("cd tools")
