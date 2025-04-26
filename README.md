# TankBattleGame
HW 1 for Adv Coding Topics in C++

Collaborators:
Hagar Paytan, ID: 206825176
Omri Kaplan, ID: <insert ID!!>

Our Makefile automatically detects all .cpp files in the folder and compiles them - beware!

To compile, run:
make       

To run the game, run:
./TankGame <textfile>

To clean up after running, run:
make clean 


Example input files explaination:
Setting - player 1 is the chasing algo, player 2 is the shooting. 2 aims at 1, while 1 aims towards the shortest path. 2 then shoots at 1, while 1 starts moving. By the time 2 gets close enough to aim and shoot at 2, 1's initial shell warps around and hits 1 before it can react. 
