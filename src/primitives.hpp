#include "renderer.hpp"

#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

struct Coords {
    float x;
    float y;
    float z;

    Coords() {valid = true;};
    Coords(float x1, float y1, float z1) : x(x1), y(y1), z(z1) {valid = true;}; 

    // Treat as dot product
    float operator*(const Coords& rhs);
    
    float mag();

    void normalize();

    Coords operator*(float rhs);
    Coords operator+(const Coords& rhs);
    Coords operator-(const Coords& rhs);

    bool valid;
};

class Ray {
    public:
    Ray() {};
    Ray(Coords org, Coords direction) : origin(org), dir(direction) {};

    Coords direction();
    Coords u();
    Coords point();

    float mag();

    Ray operator+(const Ray& rhs);

    private:

    Coords origin;
    Coords dir;
};

class Shape {
    public:

    virtual Coords intersection_point(Ray incoming) = 0;
    virtual Ray get_reflected_ray(Ray incoming) = 0;
    virtual Coords normal(Coords point) = 0;

    protected:

    float emissivity;
    float reflectivity;
    float matte;
};

class Sphere : Shape {
    public:

    Sphere();
    Sphere(float r, Coords orig, pixel col) : radius(r), origin(orig), colour(col) {};

    Coords intersection_point(Ray incoming) override;
    Ray get_reflected_ray(Ray incoming) override;

    void set_radius(float r);
    float get_radius();

    void set_colour(pixel col);
    pixel get_colour();

    void set_origin(Coords coord);
    Coords get_origin();

    Coords normal(Coords point) override;

    private:

    float radius;
    Coords origin;
    pixel colour;
};

#endif