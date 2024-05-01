# Cub3D

map error management:
1. Find start and end index;
2. No empty lines, otherwise error;
3. Check if all the border = 1;
4. Check if there are no invalid characters;
5. Update empty spaces to 1;
6. Check if map is the last in the file.
No info should follow after the map.


Plan for 01.05.2024:
I need to make a dynamic minimap, meaning that it should have only 10 tiles visible, and it will change depending on the player movement.

get player direction (N, S, E, W)