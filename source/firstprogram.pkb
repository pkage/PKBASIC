goto 4
label 3
// subroutine test
//print "likelyhood: "
//sys "clear"
/get #d
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

goto #Z

label 4
#A = 0
print "Repeat: "
get #e
print "likelyhood: "
get #d
#f = 0
label 5
if #f >= #e
goto 6
#Z = 7
goto 3
label 7
#A += #c
#f += 1
goto 5
label 6
print "Ended.\nCycles: "
print #f
print "\nInternal cycles: "
print #A
