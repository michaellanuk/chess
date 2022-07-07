# Chess
Implementation of a chess engine in C++.

This program manages and simulates chess games. By default, it simulates a short game played between Alexander Alekhine and Milorad Vasic in 1931.

## Usage:

Compile with `make`.

Run with:

```
./chess
```
Output:

```
========================
Testing the Chess Engine
========================

A new chess game has started!


    A B C D E F G H 
  +-----------------+
8 | ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜ | 8
7 | ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟ | 7
6 | . . . . . . . . | 6
5 | . . . . . . . . | 5
4 | . . . . . . . . | 4
3 | . . . . . . . . | 3
2 | ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙ | 2
1 | ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ | 1
  +-----------------+
    A B C D E F G H 
```

From final output of Alekhine vs Vasic (1931):
```
white's Bishop moves from D3 to G6
black is in checkmate


    A B C D E F G H 
  +-----------------+
8 | ♜ . ♝ ♛ ♚ . . ♜ | 8
7 | ♟ . ♟ ♞ . . ♟ . | 7
6 | . ♟ . . ♟ ♞ ♗ ♟ | 6
5 | . . . . . . . . | 5
4 | . . . ♙ . . . . | 4
3 | ♗ . ♙ . . . . . | 3
2 | ♙ . ♙ . . ♙ ♙ ♙ | 2
1 | ♖ . . . ♔ . ♘ ♖ | 1
  +-----------------+
    A B C D E F G H 
```
