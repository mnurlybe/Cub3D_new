
// #include <stdio.h>

// #define MAP_WIDTH  100 // Define your map width
// #define MAP_HEIGHT 100 // Define your map height
// #define VIEW_WIDTH  20  // Define the visible width
// #define VIEW_HEIGHT 10  // Define the visible height

// typedef struct {
//     int x;
//     int y;
// } Point;

// // Function to print the visible portion of the map
// void printVisibleMap(char map[][MAP_WIDTH], Point player) {
//     int startX = player.x - VIEW_WIDTH / 2;
//     int startY = player.y - VIEW_HEIGHT / 2;

//     // Adjust start positions to ensure they are within the map bounds
//     if (startX < 0) startX = 0;
//     if (startY < 0) startY = 0;

//     int endX = startX + VIEW_WIDTH;
//     int endY = startY + VIEW_HEIGHT;

//     // Adjust end positions to ensure they are within the map bounds
//     if (endX > MAP_WIDTH) endX = MAP_WIDTH;
//     if (endY > MAP_HEIGHT) endY = MAP_HEIGHT;

//     // Print the visible portion of the map
//     for (int y = startY; y < endY; y++) {
//         for (int x = startX; x < endX; x++) {
//             if (x == player.x && y == player.y) {
//                 printf("P "); // Print player
//             } else {
//                 printf("%c ", map[y][x]);
//             }
//         }
//         printf("\n");
//     }
// }

// int main() {
//     char map[MAP_HEIGHT][MAP_WIDTH]; // Your map array

//     // Initialize your map (e.g., fill it with '.' to represent empty spaces)
//     for (int y = 0; y < MAP_HEIGHT; y++) {
//         for (int x = 0; x < MAP_WIDTH; x++) {
//             map[y][x] = '.';
//         }
//     }

//     // Sample player position
//     Point player = {50, 50};

//     // Print the visible portion of the map centered around the player
//     printVisibleMap(map, player);

//     return 0;
// }
