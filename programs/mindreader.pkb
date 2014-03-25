print "Mind Reader [demo]\nPick a number 1-100\n"
#l = 0
#h = 100


label 1
print "I guess : "
#a = 0
#a += #l
#a += #h
#a /= 2
<<<<<<< HEAD
// flatten the thingy
floor #a
print #a
=======
print #a
ceil #a
>>>>>>> 07dc474b8bb0b0594d46ad169578e74f26ad2d5b
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

