.name "Frankenstein"
.comment "I'm alive !"

begin_corruption:
	st				r1, :stash
	ld				%151056128,r1	# 09 00 EF 00
	st				r1, :begin_corruption
	ld				%493,r2			# jump
	ld				%100,r3
	live			%1111638594
	fork            %:corruption_second

corruption_first:
	ld				%34144744,r4	; 02 09 01 E8
	st				r4,r5
	ld				%50921567,r6
	st				r6,r7
	st				r6,r12
	st				r6,r13
	st				r6,r14
	st				r6,r15
	st				r4,r8
	st				r4,r9
	st				r4,r10
	ld				%167685120,r11
	ld				%4,r1
	sub             r16, r16, r16
	zjmp            %:tmp

corruption_second:
	ld		%190055681,r4
	ld		%190055937,r5
	ld		%190057473,r6
	ld		%190057729,r12
	ld		%190057985,r13
	ld		%190058241,r14
	ld		%190056193,r15
	ld		%190056449,r7
	ld		%190056705,r8
	ld		%190056961,r9
	ld		%151087617,r10
	ld		%151035392,r11
	ld		%0, r1

	zjmp	%:tmp
	live	%1111638594
	live	%1111638594
	aff		r2
	aff		r2

stash:
	aff		r2
	live	%1111638594
	live	%1111638594
	live	%1111638594

_start:
	ld		:stash,r1
	ld		%507, r6
	ld		%8, r8
	ld		%139, r10
	ld		%-1,r14
	ld		%0,r2
	ld		%16777216,r11
	live	%1111638594
	fork	%:hola
	live	%1111638594
	ld		%0,r16
	fork	%:life_cycle
	live	%1111638594
	fork	%:preserve
	live	%1111638594
	fork	%:apocalypse
	live	%1111638594
	sti		r1,%1,%:h1
	sti		r1,%6,%:h1
	
	st		r16,-9

life_cycle:
	st	r11,10
	st	r1,6
	aff	r0
	aff	r0
	zjmp	%:life_cycle

hola: live %1111638594
	fork	%:c2

c1:
	live	%1111638594
	ld		%4, r2
	ld		%101253622, r3
	ld		%101253622, r5
	ld		%168362119, r7
	ld		%262144, r9
	ld		%0, r16
	zjmp	%:rush

c2:
	live	%1111638594
	ld		%0, r2
	ld		%190055682, r3
	ld		%190056194, r5
	ld		%190056706, r7
	ld		%134443017, r9
	ld		%0, r16
	zjmp	%:rush

tmp:
	zjmp	%:end
rush:
	live	%1111638594
	sti		r3, r2, r6
	zjmp	%502

cycle:
	live	%1111638594

apocalypse:
	fork	%:cycle
	live	%1111638594
    fork    %:salut2
    or      r2, %32, r2

salut2:
    live    %1111638594
    fork    %:salut3
    or      r2, %16, r2

salut3:
    live    %1111638594
    fork    %:salut4
    or      r2, %8, r2

salut4:
    live    %1111638594
    fork    %:salut5
    or      r2, %4, r2

salut5:
    ldi     %:prog, r2, r16
    ld      %0, r15

prog:
    sti     r16, %64, r2
    sti     r16, %122, r2
    sti     r16, %180, r2
    sti     r16, %238, r2
    sti     r16, %296, r2
    sti     r16, %354, r2
h1:
    live    %1111638594
    live    %1111638594
    sti     r16, %402, r2
    sti     r16, %448, r2
    zjmp    %442
    live    %1111638594

preserve:
	live	%1111638594
	sti		r1,%:_start,r14
	zjmp	%:preserve

end:
	sti		r4,r1,%505
	zjmp	%499

