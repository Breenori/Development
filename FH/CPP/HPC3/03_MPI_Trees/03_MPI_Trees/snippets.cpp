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

// value is reference because for boss it is input, for workers it is output
template <typename T> void broadcast(int const root, T& value) {

}

// Funktion: nimmt 2 T, und liefer 1 T. Addition etc.
template <std::floating_point T> using binary_function_t = std::function <T (T, T)>;

template <typename T> T reduce(int const root, T value, binary_function_t<T> const op) {

}