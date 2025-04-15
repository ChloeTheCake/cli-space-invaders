# cli-space-invaders

#### Maintained by CaylaTheCake, so me

There are multiple ways to build this, at the moment it requires that you have a directory
called 'obj' in src, which git won't keep track of if it's empty so make sure you make that
directory before building. The shell.nix file is a dev shell which you need for ncurses on
NixOS, then create the directory 'obj' in the src directory and run make to build

### TODO:
- ~~Fix a bug where it gets stuck in a loop in the function checkIfProjectilesHitEnemy~~
- ~~Fix a bug where enemies not hit by projectiles die~~
- ~~Fix a bug where it segment faults and I'm not sure why (I know why now)~~
- ~~Refactor the checkIfProjectilesHitEnemy function in update.c to nest less~~
- ~~Add barriers~~
- Make the enemies move
- Make the enemies shoot
- Title screen
- Option screen?
- Difficulty choice?
