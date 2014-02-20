print "Mind Reader [demo]\nPick a number 1-100\n"
#l = 0
#h = 100


label 1
print "I guess : "
#a = 0
#a += #l
#a += #h
#a /= 2
print #a
ceil #a
label 2
print "\n[H/L/C]: "
get $t
if $t == "c"
goto q
if $t == "l"
#h = #a
if $t == "h"
#l = #a
goto 1

label q
print "\nyay!"
exit

