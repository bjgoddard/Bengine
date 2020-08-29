# Description
This is a lightweight, prototypical game engine that enables game construction by parsing textures, animations and tilemaps through TinyXML onto a display created by SDL.

<p align="center">
<img src="./Bengine.png" alt="Picture" width="500" height="400" />
</p>

# Approach
After exposure to modern game engines and C++, the goal with Bengine is to solidify C++ principals and deepen my understanding of the purpose fulfilled by engines such as Unity and Unreal.

# Getting Started
Bengine creates a window and renderer through SDL which can be edited in the Engine header. All new textures can simply be added to the textures.tml file, and will be loaded upon compilation.
After loading the textures, animation sequences can be composed of textures in the animations.aml file. Maps and tilesets created in Tiled can be implemented by changing the
encoding format to csv.

# Prerequisites
The solution must be linked with the SDL, SDL_image, SDL_ttf, and TinyXML libraries.

# Built with
SDL
SDL_image
SDL_ttf
TinyXML
Tiled

As of August 29th 2020, the first version of Bengine is ready for use.

