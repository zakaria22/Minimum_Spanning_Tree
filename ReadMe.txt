========================Compilation========================

1) gcc -g  tp1.c -o tp1
	=> ./tp1

2) gcc -g  tp2.c -o tp2
	=> ./tp2


========================Dynamic programming================================

i think that the dynamic programming is easy to implement comparing 
with the branch & bound algorithm, because it doeas not require the use
of any additional structures. and also, it's exact and faster then the 
branch and bound. it's a recursive algorithm with a polynomial complexity.



========================Branch and bound====================================

the branch and bound algorithm have an exponential complexity, it's generate 
a lot of intermidiate stages and all leaves, so to construct the tree, 
it requieres alot of memory which dependce on the lenght of the priority queue.




========================linear programming (GLPK=============================

it's easy to implement comparing with branch and bound algorithm, even thow,
it's still more complex to make it run then the dynamic programming. but it's
get the exact optimal solution. ( its result is equal to dynamic programming
result's).


