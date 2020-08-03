#include "camera.hpp"
#include <stdio.h>

Screen::Screen(Coords cent, Coords normal, Coords vertical, float w, float h) : center(cent), norm(normal), vert(vertical), height(h), width(w) {
    // First lets calculate the corners using some !!LINEAR ALGEBRA!!

    norm.normalize();
    vert.normalize();

    // Cross product will give vector in direction of right
    Coords perp = norm % vert;
    
    // Redundant but make sure
    perp.normalize();

    top_right = center + (perp * (width / 2)) + (vert * (height / 2));
    top_left  = center + (perp * (-width / 2)) + (vert * (height / 2));

    bot_right = center + (perp * (width / 2)) + (vert * (-height / 2));
    bot_left  = center + (perp * (-width / 2)) + (vert * (-height / 2));
}

// Can't be fucked to learn about quaternions, maybe someday I can redo this to use those bad boys
// Index (0,0) is the top left
Coords Screen::get_coord(int x, int y) {
    Coords lefttoright = top_right - top_left;
    Coords toptobot = bot_left - top_left;

    Coords ans = top_left + (lefttoright * ( (float) x / WIDTH )) + (toptobot * ( (float) y / HEIGHT ));

    return ans;
}

Coords Screen::get_camera_pos() {
    // Calculate camera position based on FOV
    // FOV will be assumed to mean horizontal FOV

    // Camera location is calculated by ( |P| / tan(FOV / 2) ) * - N
    // P is half the vector from right to left, N is the normal vector normalized

    Coords P = (top_right - top_left) * 0.5;
    Coords camera_pos = norm * ( -1 * P.mag() / tanf(FOV * M_PI / (2*180) ) );

    // printf("top_left <%f %f %f> top_right <%f %f %f> bot_left <%f %f %f> bot_right <%f %f %f>\n", top_left.x, top_left.y, top_left.z, top_right.x, top_right.y, top_right.z, bot_left.x, bot_left.y, bot_left.z, bot_right.x, bot_right.y, bot_right.z);

    return camera_pos;
}

Camera::Camera(Coords cent, Coords normal, Coords vertical, float w, float h) : screen(cent, normal, vertical, w, h) {
    origin = screen.get_camera_pos();
}

void ShapeContainer::register_shape(Shape* shape, const Camera& camera) {
    shape_cont.push_back(shape);
    sort_container(camera);
}

std::vector<Shape*> ShapeContainer::get_shape_list() {
    return shape_cont;
}

void Scene::add_shape(Shape* shape) {
    shape->id_ = shape_list.get_unique_id();
    shape_list.register_shape(shape, camera);
}

void Scene::add_light(Shape* shape) {
    shape->id_ = light_list.get_unique_id();
    light_list.register_shape(shape, camera);
}

bool compare_shape(const Shape* s1, const Shape* s2, const Camera& camera) {
    float distance1 = (s1->get_center() - camera.origin).mag();
    float distance2 = (s2->get_center() - camera.origin).mag();

    return distance1 > distance2;
}

void ShapeContainer::sort_container(const Camera& camera) {
    std::sort(shape_cont.begin(), shape_cont.end(), std::bind(compare_shape, std::placeholders::_1, std::placeholders::_2, camera));
}

// Lets make this recursive
pixel Scene::cast_ray(Ray direction, int this_id) {

    // Check for collision
    for (int i = 0; i < shape_list.size(); i++) {
        if (shape_list[i]->id_ == this_id) continue;

        if (shape_list[i]->intersects(direction)) {
            // printf("1");

            // if (shape_list[i]->emissivity > 0) {
            Coords inter_point;
            int temp;
            std::tie(inter_point, temp) = shape_list[i]->intersection_point(direction);

            return get_brightness(direction, light_list[0], pixel(255, 255, 0, 255), inter_point);
            // }

            // Ray refl = shape_list[i]->get_reflected_ray(direction);

            // return cast_ray(refl, shape_list[i]->id_);
        }
    }

    // printf("0");

    return pixel(200, 200, 200, 200);
}

// Render the scene
void Scene::render(Renderer& renderer) {

    printf("Camera coord <%f %f %f>\n", camera.origin.x, camera.origin.y, camera.origin.z);

    for (int y = 0; y < HEIGHT; y++) {
        // printf("\n");

        for (int x = 0; x < WIDTH; x++) {
            Coords screenvec = camera.screen.get_coord(x, y);
            Coords raydir = screenvec - camera.origin;
            
            Ray raycast(camera.origin, raydir);

            pixel castray = cast_ray(raycast);
            renderer.set_pixel(castray, x, y);

            // if (x % 100 == 0) printf("<%f %f %f> ", raydir.x, raydir.y, raydir.z);
        }
    }
}

int ShapeContainer::get_unique_id() {
    // Make this better once you can delete objects from the list
    return shape_cont.size();
}

Shape* ShapeContainer::operator[](int id) {
    return shape_cont[id];
}

int ShapeContainer::size() {
    return shape_cont.size();
}

Scene::Scene(Coords cent, Coords normal, Coords vertical, float w, float h) : camera(cent, normal, vertical, w, h) {
    
}

pixel Scene::get_brightness(Ray dir, Shape* light, pixel colour, Coords intersect_point) {
    float distance = dir.mag();

    pixel brightness;

    // brightness.r = (sf::Uint8) std::min(colour.r / (std::pow(distance + 1, 2.) * 4 * M_PI), (double) colour.r);
    // brightness.g = (sf::Uint8) std::min(colour.g / (std::pow(distance + 1, 2.) * 4 * M_PI), (double) colour.g);
    // brightness.b = (sf::Uint8) std::min(colour.b / (std::pow(distance + 1, 2.) * 4 * M_PI), (double) colour.b);

    Coords normal = light->normal(intersect_point);
    float cosangle = (dir.direction() * normal) / (normal.mag() * dir.direction().mag());

    brightness.r = (sf::Uint8) std::max(colour.r * cosangle, 0.f);
    brightness.g = (sf::Uint8) std::max(colour.g * cosangle, 0.f);
    brightness.b = (sf::Uint8) std::max(colour.b * cosangle, 0.f);
    brightness.a = 255;

    return brightness;
}