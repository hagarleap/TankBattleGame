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
Setting - Player 1 is the chasing algo, Player 2 is the shooting algo

Input a:
    - 2 aims at 1, while 1 turns towards the shortest path
    - 2 then shoots at 1, while 1 starts moving
    - By the time 2 gets close enough to aim and shoot at 2, 1's initial shell warps around and hits 1 before it can react

Input b:
    - 1 is totally encased in walls, just far away from 2. This means that chasing algo will tell it do do nothing, since there is no path, and common sense won't prompt it to shoot at 2.
    - 2 will keep shooting towards 1, eventually breaking a wall.
    - Now that the map changed, 1 will start to move towards 2
    - by then, 2 has stopped cooldown and shoots 1.

Input c:
 - there is a single diagonal wall between both tanks
 - beacuse of the short distance, they both aim at each other and shoot simultaneously
 - beacuse of the double shot, the wall is now gone
 - both tanks are in cooldown. 1 prefers to chase 2, while 2 will do nothing until it can shoot
 - 1 has enough time to run over 2, and so they end in a tie (mutual destruction)
 - This happens because of the nature of the common sense and chasing algorithms:
    - Chasing's instruction is to simply get to the other tank.
    - Common sense algorithm will override this choice both 
        1. The enemy tank is at most 2 spots away
        2. The tank is able to shoot
    - Since 1 was still in cooldown from shooting, nothing was there to override them from running into 2 and ending in a tie.

