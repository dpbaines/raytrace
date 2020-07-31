#include "primitives.hpp"

Ray Ray::operator+(const Ray& rhs) {
    Ray newray;

    newray.origin.x = origin.x;
    newray.origin.y = origin.y;
    newray.origin.z = origin.z;

    newray.dir.x = origin.x + rhs.origin.x;
    newray.dir.y = origin.y + rhs.origin.y;
    newray.dir.z = origin.z + rhs.origin.z;

    return newray;
}

Coords Coords::operator%(const Coords& rhs) {
    Coords cross;

    cross.x = (y * rhs.z) - (z * rhs.y);
    cross.y = (z * rhs.x) - (x * rhs.z);
    cross.z = (x * rhs.y) - (y * rhs.x);

    return cross;
}

Coords Coords::operator+(const Coords& rhs) {
    Coords dot;

    dot.x = x + rhs.x;
    dot.y = y + rhs.y;
    dot.z = z + rhs.z;

    return dot;
}

Coords Coords::operator-(const Coords& rhs) {
    Coords dot;

    dot.x = x - rhs.x;
    dot.y = y - rhs.y;
    dot.z = z - rhs.z;

    return dot;
}

Coords Coords::operator*(float rhs) {
    Coords dot;

    dot.x = x * rhs;
    dot.y = y * rhs;
    dot.z = z * rhs;

    return dot;
}

float Coords::operator*(const Coords& rhs) {
    return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}

Coords Ray::direction() {
    return dir;
}

Coords Ray::u() {
    float magnitude = std::sqrt( std::pow(dir.x, 2) + std::pow(dir.y, 2) + std::pow(dir.z, 2) );
    return Coords(dir.x / magnitude, dir.y / magnitude, dir.z / magnitude);
}

Coords Ray::point() {
    return origin;
}

float Ray::mag() {
    return std::sqrt( std::pow(dir.x, 2) + std::pow(dir.y, 2) + std::pow(dir.z, 2) );
}

Coords Ray::X(float d) {
    return origin + (dir * d);
}

float Coords::mag() {
    return std::sqrt( std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) );
}

void Coords::normalize() {
    float magnitude = mag();

    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

Coords Sphere::intersection_point(Ray incoming) {
    // https://en.wikipedia.org/wiki/Line–sphere_intersection
    // Det < 0 means no intersection
    // Det = 0 means one intersection
    // Det > 0 means two intersections
    float determinant = std::pow( (incoming.u() * (incoming.point() - origin)) , 2) 
                        - ( (incoming.point() - origin) * (incoming.point() - origin) - radius);

    if (determinant < 0) {
        // No intersection
        Coords invalid;
        invalid.valid = false;
        return invalid;
    } else if (determinant == 0) {
        // A single intersection, ie a tangent
        float d = - (incoming.u() * (incoming.point() - origin)) + std::sqrt(determinant);

        return incoming.point() + (incoming.u() * d);

    } else {
        // Ray passes through sphere at points
        float dpos = - (incoming.u() * (incoming.point() - origin)) + std::sqrt(determinant);
        float dneg = - (incoming.u() * (incoming.point() - origin)) - std::sqrt(determinant);

        Coords point1 = incoming.point() + (incoming.u() * dpos);
        Coords point2 = incoming.point() + (incoming.u() * dneg);

        // Return coordinate closer to ray casting point
        return (point1 - incoming.point()).mag() < (point2 - incoming.point()).mag() ? point1 : point2;
    }

}

Ray Sphere::get_reflected_ray(Ray incoming) {
    Coords intersect = intersection_point(incoming);

    if (!intersect.valid) return Ray();

    Coords norm = normal(intersect);

    Coords r = incoming.u() - (norm * (2 * (incoming.u() * norm)));

    return Ray(intersect, r);
}

Coords Sphere::normal(Coords point) {
    Coords norm = point - origin;
    norm.normalize();
    
    return norm;
}

void Sphere::set_radius(float r) {
    radius = r;
}

float Sphere::get_radius() {
    return radius;
}

void Sphere::set_colour(pixel col) {
    colour = col;
}

pixel Sphere::get_colour() {
    return colour;
}

void Sphere::set_origin(Coords coord) {
    origin = coord;
}

Coords Sphere::get_origin() {
    return origin;
}