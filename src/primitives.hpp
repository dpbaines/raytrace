#include "renderer.hpp"
#include "math.h"

#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

enum class ShapeType {
    NONE,
    SPHERE,
    PLANE
};

struct Coords {
    float x;
    float y;
    float z;

    Coords() {valid = true;}
    Coords(float x1, float y1, float z1) : x(x1), y(y1), z(z1) {valid = true;}

    // Treat as dot product
    float operator*(const Coords& rhs);

    // Treat as cross product
    Coords operator%(const Coords& rhs);
    
    // Returns the magnitude of the vector
    float mag();

    // Normalize all components, ie divide each by the magnitude
    void normalize();
    Coords& invalidate();

    Coords operator*(float rhs);
    Coords operator+(const Coords& rhs);
    Coords operator-(const Coords& rhs);

    bool valid;
};

class Ray {
    public:
    Ray() {}
    Ray(Coords org, Coords direction) : origin(org), dir(direction) {}

    Coords direction();
    Coords u();
    Coords point();

    Coords X(float d);

    // Return magnitude of the direction component of the ray
    float mag();

    // Add two rays, ie add the direction vectors, using the lhs origin
    Ray operator+(const Ray& rhs);

    private:

    Coords origin;
    Coords dir;
};

class Shape {
    public:

    // Get the intersection point of a ray and whatever shape
    virtual bool intersects(Ray incoming);

    // Get the intersection point of a ray and whatever shape
    virtual std::pair<Coords, int> intersection_point(Ray incoming);

    // Return the reflected ray to an incoming ray hitting this shape
    virtual Ray get_reflected_ray(Ray incoming);

    // Return normal to a point on the surface
    virtual Coords normal(Coords point);

    virtual Coords get_center();
    virtual Coords get_center() const;

    int id_;
    float emissivity;
    pixel colour;
    float reflectivity;
    float matte;

    ShapeType type;
};

class Sphere : public Shape {
    public:

    Sphere();
    Sphere(float r, Coords orig) : radius(r), origin(orig) { type = ShapeType::SPHERE; }

    bool intersects(Ray incoming) override;
    std::pair<Coords, int> intersection_point(Ray incoming) override;
    Ray get_reflected_ray(Ray incoming) override;

    void set_radius(float r);
    float get_radius();

    void set_colour(pixel col);
    pixel get_colour();

    void set_origin(Coords coord);
    Coords get_origin();

    Coords normal(Coords point) override;

    // Same as get_origin in this case
    Coords get_center() override;
    Coords get_center() const override;

    private:

    float radius;
    Coords origin;
};

class Plane : public Shape {
    public:

    Plane();
    Plane(Coords norm, Coords orig) : norm(norm), origin(orig) {}

    bool intersects(Ray incoming) override;
    std::pair<Coords, int> intersection_point(Ray incoming) override;
    Ray get_reflected_ray(Ray incoming) override;

    void set_colour(pixel col);
    pixel get_colour();

    void set_origin(Coords coord);
    Coords get_origin();

    Coords normal(Coords point) override;

    // Same as get_origin in this case
    Coords get_center() override;
    Coords get_center() const override;

    private:

    Coords norm;
    Coords origin;
};

#endif