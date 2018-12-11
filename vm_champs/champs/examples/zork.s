.name "zork"
.comment "I'M ALIIIIVE"

#l2:		sti r1, %:live, %1

bite:	sti r1, %:live, %1
        ld  %25, r4
        st r4, 15

live:	live %1
		zjmp %:bite
