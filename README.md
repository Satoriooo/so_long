*This project has been created as part of the 42 curriculum by shirose.*

# So_long

## Description
### Overview
This project is an implementation of a simple 2D game. For this project we are provided with a simple graphic library MinilibX. With this library we create a game, where the player walks through a map, collects items and eventually reaches to the goal. 

### Goal
Through this project students are expected to deepen understanding in the following topics regarding to game development;
- Load window, images
- Control of player's movement
- Map rendering
- Item collection
- Safe and clean termination on error or after clear

## Instructions
### Installation
For installation, clone the git repo to your work directory.
```bash
git clone https://github.com/Satoriooo/so_long.git
```
MiniLibX is also required. Follow the guide [here](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html) and install it.

### Compilation
By executing make, it compiles the source files. You can also use clean, fclean, and re.
```bash
make
```
### Execution
Example:
```bash
./so_long "map_sample.ber"
```
To move the character, use either arrow keys or WASD keys.

The map has the 5 elements;
>0: Path, 1: Wall, E: Exit, C: Collectible, P: Player

It must follow the conditions below;
- The map is rectangular and is surrended by walls.
- The map has one player, one exit, and at least one collectible.
- There must be a path, which allows the player to collect every collectibles and leads to the exit.
- No letters other than above elements are allowed.
- The last line of the map ends without a new line.
- The maximum size is 1980 x 1080 pixel, which is 61 x 33 tiles.
- File name consists of [a-z], [A-Z], [0-9], '_', '.', and is less than 100 letters.

## Resources
### Documentations
#### MiniLibX
- [42 Docs - MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx)
- [MiniLibX - Simple Graphical Interface Library for students](https://qst0.github.io/ft_libgfx/man_mlx.html)
#### Keysym
- [keysymdef.h source code](https://codebrowser.dev/gtk/include/X11/keysymdef.h.html)
#### Errno
- [【C言語】errnoを利用してエラーの原因を特定する](https://daeudaeu.com/c-errno/) (ENG: Find an error with errno in C)

### AI usage
- Basic usage of MiniLibX
- Explanation of hook, loop, and image loadings
