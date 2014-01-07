#a = 0
print "times to spin: "
get #b

label 1
if #a > #b
goto 2

print "["
print #a
print "/"
print #b
print "]\n"

#a += 1
goto 1

label 2
print "\ndone!"
