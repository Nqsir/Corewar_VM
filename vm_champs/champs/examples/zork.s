.name "zork"
.comment "I'M ALIIIIVE"

#l2:		sti r1, %:live, %1

bite:	sti r1, %:live, %1
        ld %-254, r2
        #ld 525, r3
        and -1, -1, r4
        #or r2, r3, r4
        #ldi r3, %2, r4
        sti r4, %20, %0

live:   live %1
		zjmp %:bite
