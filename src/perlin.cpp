#include "perlin.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
 
using namespace godot;


Perlin::Perlin()
{
}
Perlin::~Perlin()
{
}


void Perlin::_bind_methods() {
    ClassDB::bind_method(D_METHOD("generate_random_vectors", "seed", "offset"), &Perlin::generate_random_vectors);
    ClassDB::bind_method(D_METHOD("generate_perlin_noise", "x", "y"), &Perlin::generate_perlin_noise);
    ClassDB::bind_method(D_METHOD("generate_fractal_noise", "x", "y", "octaves", "persistence", "frequency"), &Perlin::generate_fractal_noise);
}
// Creates the random vectors for the perlin noise.
void Perlin::generate_random_vectors(int seed, Vector2 offset){
    // Create a 2D array of Vector2s.
    Vector2*** noise = new Vector2**[32];
    for(int i = 0; i < 32; i++){
        noise[i] = new Vector2*[32];
    }

    // Initialize all Vector2s to random values.
    srand(seed + offset.x * 37 + offset.y * 17);
    for(int i = 0; i < 32; i++){
        for(int j = 0; j < 32; j++){
            float x = ((float) rand() / RAND_MAX) - 0.5;
            float y = ((float) rand() / RAND_MAX) - 0.5;
            noise[i][j] = memnew(Vector2(x, y));
            // Normalize the gradient vectors
            if(noise[i][j]->length() != 0){
                noise[i][j]->normalize();
            }
        }
    }
    random_vectors = noise;
}

// Takes a 2d point and uses the weight to interpolate between x and y
float Perlin::interpolate(float a, float b, float w){
    // Use cubic interpolation to smooth noise.
    return (b - a) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a;
}

// Gets the dot product between a vector and a point.
float Perlin::get_dot_product(Vector2* a, float x, float y){
    return a->x * x + a->y * y;
}

// Generates perlin noise at a given point.
float Perlin::generate_perlin_noise(float x, float y){
    if(!has_random_vectors){
        generate_random_vectors(0, Vector2(0, 0));
        has_random_vectors = true;
    }
    // Get the integer coordinates of the point.
    int x0 = ((int) x) % 32;  // Wrap around as needed
    int x1 = (x0 + 1) % 32;
    int y0 = ((int) y) % 32;
    int y1 = (y0 + 1) % 32;


    // Get the vectors at the 4 corners of the cell.
    Vector2* top_left = random_vectors[x0][y0];
    Vector2* top_right = random_vectors[x1][y0];
    Vector2* bottom_left = random_vectors[x0][y1];
    Vector2* bottom_right = random_vectors[x1][y1];
    
    // Get the fractional part of the point.
    float x_frac = x - (int) x;
    float y_frac = y - (int) y;

    

    // Get the dot products of the vectors and the point.
    float dot_top_left = get_dot_product(top_left, x_frac, y_frac);
    float dot_top_right = get_dot_product(top_right, x_frac - 1, y_frac);
    float dot_bottom_left = get_dot_product(bottom_left, x_frac, y_frac - 1);
    float dot_bottom_right = get_dot_product(bottom_right, x_frac - 1, y_frac - 1);



    float x_interpolate_1 = interpolate(dot_top_left, dot_top_right, x_frac);
    float x_interpolate_2 = interpolate(dot_bottom_left, dot_bottom_right, x_frac);

    float value = interpolate(x_interpolate_1, x_interpolate_2, y_frac);
    return value;
}

float Perlin::generate_fractal_noise(float x, float y, int octaves, float persistence, float frequency){
    float total = 0;
    float amplitude = 1;
    float max_value = 0;
    for(int i = 0; i < octaves; i++){
        total += generate_perlin_noise(x * frequency, y * frequency) * amplitude;
        max_value += amplitude;
        amplitude *= persistence;
        frequency *= 2;
    }
    return total / max_value;
}