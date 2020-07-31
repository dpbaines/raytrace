#include "camera.hpp"

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
    Coords toptobot = top_left - bot_left;

    Coords ans = top_left + (lefttoright * ( (float) x / WIDTH )) + (toptobot * ( (float) y / HEIGHT ));

    return ans;
}

Coords Screen::get_camera_pos() {
    // Calculate camera position based on FOV
    // FOV will be assumed to mean horizontal FOV

    // Camera location is calculated by ( |P| / tan(FOV / 2) ) * - N
    // P is half the vector from right to left, N is the normal vector normalized

    Coords P = (top_right - top_left) * 0.5;
    Coords camera_pos = norm * ( -1 * P.mag() / tanf(FOV / 2) );

    return camera_pos;
}

Camera::Camera(Coords cent, Coords normal, Coords vertical, float w, float h) {
    Screen sc(cent, normal, vertical, w, h);
    screen = sc;

    origin = sc.get_camera_pos();
}

void ShapeContainer::register_shape(Shape* shape, const Camera& camera) {
    shape_cont.push_back(shape);
    sort_container(camera);
}

std::vector<Shape*> ShapeContainer::get_shape_list() {
    return shape_cont;
}

void Scene::add_shape(Shape& shape) {
    shape_list.register_shape(&shape, camera);
}

bool ShapeContainer::compare_shape(const Shape* s1, const Shape* s2, const Camera& camera) {
    float distance1 = (s1->get_center() - camera.origin).mag();
    float distance2 = (s2->get_center() - camera.origin).mag();

    return distance1 < distance2;
}

void ShapeContainer::sort_container(const Camera& camera) {
    std::sort(shape_cont.begin(), shape_cont.end(), std::bind(compare_shape, std::placeholders::_1, std::placeholders::_2, camera));
}