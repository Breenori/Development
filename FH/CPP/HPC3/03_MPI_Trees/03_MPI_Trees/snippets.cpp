#include <concepts>
#include <functional>

/*
funktionen parallel amchen --> serial reduce/map, parallel reduce/map

0 1 2 3 4 5 6 7

0:
0
1		2^(0)

1:
0 1		x < 2^(1)
2 3		2^(1) <= x < 2^(2)

2:
0 1 2 3 	x < 2^(2)
4 5 6 7 	2^(2) <= x < 2(3)

Send to = rank + 2^step
Receive from = rank - 2^step
*/


