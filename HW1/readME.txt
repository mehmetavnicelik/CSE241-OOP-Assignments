
Example 1:
----------------------------------------------
  a   b   c   d   e   f   g   h 
1 .   .   .   o   .   .   o   .   
2   x   x   .   o   .   .   o   .   
3     .   x   .   o   .   .   o   .   
4       .   x   x   .   .   o   .   .   
5         .   .   .   .   .   o   .   .   
6           .   .   .   .   .   .   .   .   
7             x   x   x   x   x   x   x   x   
8               .   .   .   .   .   .   .   .   
----------------------------------------------
Example 2:
----------------------------------------------
  a   b   c   d   e   f   g   h 
1 .   .   .   o   .   .   o   .   
2   x   x   .   o   .   .   o   .   
3     .   x   .   o   .   .   o   .   
4       .   x   x   o   .   o   .   .   
5         .   .   o   o   .   o   .   .   
6           .   .   o   .   .   o   .   .   
7             x   x   x   x   x   o   .   .   
8               .   .   .   .   .   o   .   .   
----------------------------------------------
In the scenarios above, program consider only the first indexes of 'x' and 'o' players.

For; example 1, even though 'x' character wins (A7-H7 path),program does not assume that it won. Because it expects to end the game from (A2-B2-B3-...) path.
For; example 2, the scenenario is same. Even though 'o' character wins by going (G1-G2) path, the program expects to end the game by (D1-D2-D3...) path. 

Because those are the first founded coordinates. The game searchs just for the minimum indexes.
*************************************************************************************************
RULES:
X goes from left to right.
O goes from up to down. 
*************************************************************************************************