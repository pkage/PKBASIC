print "Mind Reader [demo]\nPick a number 1-100\n"
#l = 1
#h = 100


label 1
print "I guess : "
#a = 0
#a += #l
#a += #h
#a /= 2
print #a
label 2
print "\n[H/L/C]: "
get #t
if #t == 1
goto q


goto 1

label q
print "\nyay!"
exit

