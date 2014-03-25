sys "clear"
print "Think of a number 1-100\n"
#a ~~ 99
#a += 1

label 1
print "Guess: "
get #b
if #a > #b
print "higher!\n"
if #a < #b
print "lower!\n"
if #a == #b
goto 2
goto 1

label 2
print "\nyou win!\n"
exit
