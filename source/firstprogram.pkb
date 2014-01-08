print "likelyhood: "
sys "clear"
get #d
#a ~~ #d
#c = 0

label 1
#b ~~ #d
print #b
print "|"
if #a == #b
goto 2
#c += 1
goto 1

label 2
print "done\nduration:"
print #c
