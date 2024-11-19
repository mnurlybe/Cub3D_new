# Cub3D

A first-person 3D maze renderer using raycasting technology, inspired by the legendary Wolfenstein 3D - the first true FPS in video game history. This project is part of the 42 school curriculum, focusing on implementing core graphics concepts using ray-casting principles.

## Project Overview

The goal is to create a dynamic view inside a maze using ray-casting techniques, similar to how Wolfenstein 3D revolutionized gaming in 1992. The project emphasizes:
- Rigorous programming practices
- Practical application of mathematics
- Graphics programming fundamentals
- Efficient algorithm implementation

### Mandatory Features
- First-person 3D perspective using ray-casting
- Textured walls with different textures for each direction (N,S,E,W)
- Customizable floor and ceiling colors
- Smooth window management
- Basic controls (WASD movement, arrow key rotation)
- Map parsing from .cub files
- Proper error handling
- Clean exit management

### Bonus Features
- ✅ Wall collisions
- ✅ Minimap system
- ✅ Mouse rotation
- ✅ Animated sprites
- 🔄 Door system (open/close)

## Installation

### Prerequisites

#### For Linux (Ubuntu/Debian):
```bash
# Install required dependencies
sudo apt-get update
sudo apt-get install cmake make xorg libxext-dev zlib1g-dev libbsd-dev libglfw3-dev

# If you encounter any graphics-related issues, try:
sudo ldconfig
```

#### For macOS:
```bash
# Install Homebrew if not installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew update
brew install cmake glfw
```

### Building from Source

1. Clone the repository with submodules:
```bash
git clone --recurse-submodules https://github.com/your-username/cub3d.git
cd cub3d
```

If you've already cloned the repository without submodules:
```bash
git clone https://github.com/your-username/cub3d.git
cd cub3d
git submodule init
git submodule update
```

2. Build the project:
```bash
make
```

## Usage

1. Run the program with a map file:
```bash
./cub3D maps/example.cub
```

2. Controls:
   - W: Move forward
   - S: Move backward
   - A: Strafe left
   - D: Strafe right
   - ←/→: Rotate camera
   - Mouse3: Mouse Rotation
   - ESC: Exit game
   - Red cross: Close window

## Map Format

Maps must be files with the `.cub` extension containing the following elements:

### Texture and Color Configuration
```
NO ./path_to_north_texture.png  # North wall texture
SO ./path_to_south_texture.png  # South wall texture
WE ./path_to_west_texture.png   # West wall texture
EA ./path_to_east_texture.png   # East wall texture

F 220,100,0    # Floor color (RGB)
C 225,30,0     # Ceiling color (RGB)
```

### Map Configuration
- Must be surrounded by walls (1)
- Valid characters:
  - '0': Empty space
  - '1': Wall
  - 'N'/'S'/'E'/'W': Player start position and orientation

Example map:
```
        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Map Rules
- Map must be the last element in the file
- Map must be closed/surrounded by walls
- Empty lines are allowed between elements
- Elements can be in any order (except map must be last)
- Spaces are valid in the map and must be handled

## Project Structure
```
.
├── includes/          # Header files
├── libft/            # Custom C library
├── MLX42/            # Graphics library (submodule)
├── src/              # Source files
├── textures/         # Texture files
├── maps/             # Map files
└── Makefile          # Build system
```

## Development Status

### Phase 1: Setup ✅
- [x] Initialize repository
- [x] Setup MLX42 library
- [x] Create basic window management

### Phase 2: Map Parsing ✅
- [x] Implement .cub file parser
- [x] Validate map format
- [x] Store map data

### Phase 3: Raycasting ✅
- [x] Implement DDA algorithm
- [x] Calculate wall distances
- [x] Render vertical strips

### Phase 4: Texturing ✅
- [x] Load wall textures
- [x] Apply textures to walls
- [x] Implement floor/ceiling colors
- [ ] Implement floor/ceiling textures (not required)

### Phase 5: Player Movement ✅
- [x] Implement WASD movement
- [x] Add rotation controls (Arrow Keys + Mouse)
- [x] Add collision detection

### Phase 6: Optimization ✅
- [x] Improve rendering performance (Image Buffering)
- [x] Memory management 
- [x] Code cleanup
- [ ] Complete Documentation

## Documentation Index
- [Development Plan](DEVELOPMENT.md)

## Error Handling

The program will exit with "Error\n" followed by an explicit error message if:
- Invalid map configuration is detected
- Map is not properly closed
- Invalid texture paths
- Invalid RGB values
- Missing required elements
- Memory allocation failures

## Contributing

1. Fork the repository
2. Create a new branch for your feature
3. Commit your changes
4. Push to your branch
5. Submit a pull request

## Known Issues

- Mac users might need to update GLFW for optimal performance
- Linux users might need to run `sudo ldconfig` after installing dependencies
- Some texture formats might not load properly on different systems

## Authors

- Madi (@mnurlybe)
- Luca Woiton (@lwoiton)

## Acknowledgments

- 42 Prague for the project requirements and evaluation
- John Carmack and John Romero for creating Wolfenstein 3D
- [MLX42](https://github.com/codam-coding-college/MLX42) library