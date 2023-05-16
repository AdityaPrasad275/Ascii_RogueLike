# Ascii RogueLike

A simple dungeon adventure/battle game based on preconfigured map (level.txt)

Has WASD movements, collision (most elementary form of it), battle system. 

Only supports goblin ('g'), dragon ('d') and ofcourse player ('@'). This can be changed in Level::setupLevel() in level.cpp which entails reading the map and well, setting it up.

# Instructions 
 Go to the directory where files are stored and use this command
`g++ main.cpp level.cpp -o main.exe`
