# Cub3D

map error management:
1. Find start and end index; -> check_file.c -> done
2. No empty lines, otherwise error; -> check_file.c -> done
3. Check if there are no invalid characters; -> check_File.c -> done
4. Check if map is the last in the file, no info should follow after the map. ->check_file.c -> done
5. Check if all the border = 1; -> check_File.c -> done
6. Update empty spaces to 1; -> get_map


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


27.05:

1. finalize minimap_vis
2. there is a segfaul when the path to textures is wrong, need to fix that. 
3. Add mouse rotation.
4. Norminette. 
