*This project has been created as part of the 42 curriculum by lucinguy, ccauderl.*

# cub3d

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/6ab5028e55f542ecb2dadf9ad09afc1c)](https://app.codacy.com/gh/ColinCauderlier/cub3d/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)

[![Quality gate status](https://sonarcloud.io/api/project_badges/measure?project=ColinCauderlier_cub3d&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=ColinCauderlier_cub3d)

## Description

The **Cub3D** project is about recreating a Doom-like 3D environment, with player movement, collision and textures.

The use of the miniLibX library for the graphic interface was mandatory.

### Parts

We divided the project into several sections :
- Parsing: 
- Raycasting: 
- User interaction: make the player move, collide with walls, close the window ...

## Instructions

The miniLibx for Linux is set with the project. It is also available online for Mac.

You need the textures in .xpm format, they need to be 256*256 pixels.

***Usage***
1) make all
2) ./cub3D + "path_to_map_file"
3) Play  

***Check leaks***  
valgrind --leak-check=full --show-leak-kinds=all ./cub3D map.cub

## Resources
A tutorial on how to raycast :
https://lodev.org/cgtutor/raycasting.html

