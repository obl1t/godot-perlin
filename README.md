## Perlin and Fractal Noise Generator

This repository contains GDExtension C++ scripts for a 2D perlin noise generator and an example Godot Project that uses the GDExtension node.

### Usage:
generate_random_vectors(int seed, Vector2 offset) to set a seed.\
generate_perlin_noise(float x, float y) to get the perlin noise for a 2D point. \
generate_fractal_noise(float x, float y, int octaves, float persistence, float frequency) to get the fractal noise for a 2D point. 
The fractal noise is a layering of perlin noises at different octaves.
Persistence controls how much higher-frequency octaves show up in the noise value (e.g., a persistence of 0.5 means that the second octave 
contributes 0.5 as much to the noise value and the third octave contributes 0.5 * 0.5 as much.). 
