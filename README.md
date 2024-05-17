# Cub3D


file error management: 
1. 


map error management:
1. Find start and end index; -> check_file.c -> done
2. No empty lines, otherwise error; -> check_file.c
3. Check if all the border = 1; -> get_map
4. Check if there are no invalid characters; -> check_File.c
5. Update empty spaces to 1; -> get_map
6. Check if map is the last in the file. ->check_file.c
No info should follow after the map.


Plan for 01.05.2024:
I need to make a dynamic minimap, meaning that it should have only 10 tiles visible, and it will change depending on the player movement.

get player direction (N, S, E, W)


// Brainstorming
Player struct: mini_x and mini_y --> are these really needed for a minimap. 
If for minimap it is going to look like the player is always in the center, then we will
probably need to move only the visible part of the map.
Meaning that every pixel is going to be checked if it is: 1.outside of map, 2. wall, 3.nowall. 
Therefore, in move_player function, we can use normal Players coordinates (x and y) to move in the window and in parallel it is going to adjust visible part of the minimap.
Like these we will not duplicate player's coordinate twice in a minimap and normal window.
