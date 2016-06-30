#include "utils.hpp"

int hardmode = 0;
std::string LANGUAGE = "CAT";

bool isInt(std::string s) {
    for(int i = 0; i < int(s.size()); ++i)
        if (!(s[i]>='0' && s[i]<='9'))
            return false;
    return true;
}

int myStoi(std::string s) {
    int x = 0;
    for (size_t i = 0; i < s.size(); ++i)
        x = 10*x+(s[i]-'0');
    return x;
}

float myStof(std::string s){
    float x = 0;
    size_t i;
    for (i = 0; i < s.size() && s[i]!='.'; ++i) {
        x = 10*x+(s[i]-'0');
    }
    ++i;
    float fract = 0;
    float j = 0;
    while(i < s.size()) {
        fract = 10*fract+(s[i]-'0');
        ++j;
        ++i;
    }
    x += fract/std::pow(10,j);
    return x;
}

bool myStob(std::string s) {
    return (s != "0");
}

void print(std::string s){
    std::cout << s << std::endl;
}

float difference(float a, float b){
    float c = a-b;
    if(c > 0) return c;
    else return c*-1;
}

float getAngle(const sf::Vector2f &orig,const sf::Vector2f &des) {
    return std::atan2(des.y - orig.y, des.x - orig.x)*180/(M_PI);
}

float getModule(const sf::Vector2f &orig, const sf::Vector2f &des) {
    return std::sqrt(std::pow(std::abs(des.x-orig.x), 2) + std::pow(std::abs(des.y-orig.y), 2));
}

bool isCollisioning(sf::Vector2f point1, float radius1, sf::Vector2f point2, float radius2) {
    return (getModule(point1,point2) < radius1+radius2);
}

/*
 * bool RectangleColision(Rectangle r1, Rectangle r2) {
    if (r1.lowerLeft.x < r2.lowerLeft.x + r2.width &&
       r1.lowerLeft.x + r1.width > r2.lowerLeft.x &&
       r1.lowerLeft.y < r2.lowerLeft.y + r2.height &&
       r1.lowerLeft.y + r1.height > r2.lowerLeft.y)
        return true ;
    else
        return false ;
}
bool colisionCircleRectangle(Circle c, Rectangle r) {
    float closestX = c.center.x;
    float closestY = c.center.y;

    if (c.center.x < r.lowerLeft.x) {
        closestX = r.lowerLeft.x;
    }

    else if (c.center.x > r.lowerLeft.x + r.width) {
        closestX = r.lowerLeft.x + r.width;
    }

    if (c.center.y < r.lowerLeft.y) {
        closestY = r.lowerLeft.y;
    }

    else if (c.center.y > r.lowerLeft.y + r.height) {
        closestY = r.lowerLeft.y + r.height;
    }

    return c.center.distSquared(closestX, closestY) < c.radius * c.radius;
}
*/

directions pointsToDirection8(sf::Vector2f pos1, sf::Vector2f pos2, float rotation) {
    float angle = getAngle(pos1,pos2);
    angle -= rotation;

    while (angle < 0) angle += 360;

    if (angle < 22.5 || angle > 360-22.5)    return directions::right;

    else if (angle < 67.5 && angle > 22.5)   return directions::botRight;
    else if (angle < 112.5 && angle > 67.5)  return directions::down;
    else if (angle < 157.5 && angle > 112.5) return directions::botLeft;

    else if (angle > 360-67.5 && angle < 360-22.5)   return directions::topRight;
    else if (angle > 360-112.5 && angle < 360-67.5)  return directions::up;
    else if (angle > 360-157.5 && angle < 360-112.5) return directions::topLeft;

    else return directions::left;
}

directions pointsToDirection4(sf::Vector2f pos1, sf::Vector2f pos2) {
    float angle = getAngle(pos1,pos2);
    while (angle < 0) angle += 360;
    if (angle <= 45 || angle >= 360-45)          return directions::right;
    else if (angle < 135 && angle > 45)          return directions::down;
    else if (angle > 360-135 && angle < 360-45)  return directions::up;
    else                                         return directions::left;
}

float directionsToAngle(directions dir) {
    switch (dir) {
        case directions::right:
            return 0;
        case directions::up:
            return 90;
        case directions::left:
            return 180;
        case directions::down:
            return 270;
        default:
            std::cout << "CAREFULL!!! Not Implemented to that direction." << std::endl;
            return -1;
    }
}

sf::Vector2f getRelativeCenter(sf::Vector2f origen, sf::IntRect boundOr, sf::IntRect boundDest) {
    sf::Vector2f final;

    final.x = boundOr.left + boundOr.width/2 - boundDest.width/2 - boundDest.left + origen.x;
    final.y = boundOr.top + boundOr.height/2 - boundDest.height/2 - boundDest.top + origen.y;

    return final;
}

bool counterDirection(directions d1, directions d2) {
    switch (d1) {
        case directions::down:
            return d2 == directions::up;
        case directions::up:
            return d2 == directions::down;
        case directions::left:
            return d2 == directions::right;
        case directions::right:
            return d2 == directions::left;
        default:
            return false;
    }
}

int getHorizontal(directions dir) {
    return (dir == directions::left ? -1 : (dir == directions::right ? 1 : 0));   
}
int getVertical(directions dir) {
    return (dir == directions::up   ? -1 : (dir == directions::down  ? 1 : 0));
}

sf::Vector2f getRandBounce(float speed, directions dir) {
    float angle = directionsToAngle(dir);
    angle += (std::rand()%90 + 135);
    angle = (int)angle%360;
    return sf::Vector2f(std::cos(angle*TO_RADIANS)*speed, -std::sin(angle*TO_RADIANS)*speed); // (cos angle, -sin angle) because the 0 of the Y is on the top corner
}

int getSign(float n) {
    if (n>0) return 1;
    else if (n<0) return -1;
    else return 0;
}

/*void log(std::string s){
    std::cout << s << std::endl;
}*/

void mlog(std::string s){
    std::cout << s << std::endl;
}
