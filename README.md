# Hyper Wau

This game was made for Larian X 42KL's mini gauntlet with the theme of Malaysia Day.
You play as a Wau Bulan, a traditional kite that is often showcased during national celebrations like Merdeka and Malaysia Day. The kite also serves as a recognisable symbol of Malaysian culture all year round. Your aim is to dodge obstacles that come in the form of helicopters that carry the Malaysian flag reflecting the annual tradition of the military flypast.

What makes this game unique is the dimensional plane you navigate through. Unlike a regular grid, the surface of this game exists on a hyperbolic plane which is a theoretical surface that has constant negative curvature. It leads to bizzare warping and initially unintuitive movements.

## Building and Running

Requires Linux / WSL

1. clone and enter the repository ```git clone https://github.com/ChunkyCheng/GauntletGame && cd GauntletGame```

2. run the Makefile with ```make```.
The required library will be cloned and built automatically. It may take a few minutes.

3. launch the game ```./HyperWau```

## External Libraries
I used raylib (included as a submodule) as it provided ease for window creation, draw functions and keyboard input. It also allowed me to easily load a custom shader that was required for the hyperbolic rendering. The coordinate system along with its navigation, hitboxes, and rendering logic in the shader was written by me.

## Gauntlet Week 1 Lessons
Every function that does not modify any member variable has been correctly labelled as const. I also have a RAII wrapper for the shader object as it provides ease to automatically unload the shader during destruction.

## Future Potential
I had to cut some ideas for other varied obstacles like fireworks and clouds that push you off the map. It would be cool to revisit these ideas as they look and feel unique on a hyperbolic surface. I would also do a lot of refactoring as my code started to get messy towards the end of development as I tried to get a smooth working version ready. One clear example would be moving textures and their relavant information for the shader to use into its own class that can also handle texture unloading. Right now every entity loads a texture even though there are many identical textures. It would be better if they instead used a pointer or a reference to a single loaded texture for entities to share.


