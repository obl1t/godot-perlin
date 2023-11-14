#ifndef PERLIN_H
#define PERLIN_H

#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_player3d.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/cpu_particles3d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_map.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/sphere_shape3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

namespace godot {

class Perlin : public Node{
    GDCLASS(Perlin, Node)
    private:
        // double fade(double t);
        // double lerp(double t, double a, double b);
        // double grad(int hash, double x, double y, double z);
        Vector2*** random_vectors;
        bool has_random_vectors = false;
    protected:
        static void _bind_methods();
    public:
        Perlin();
        ~Perlin();
        void generate_random_vectors(int seed, Vector2 offset);
        float interpolate(float a, float b, float w);
        float generate_perlin_noise(float x, float y);
        float generate_fractal_noise(float x, float y, int octaves = 3, float persistence = 0.2, float frequency = 1.0);
        float get_dot_product(Vector2* a, float x, float y);

};

}
#endif