#include "Background.hpp"

Background::Background() {
}

Background::Background(std::string lvlDesc) {
    init(lvlDesc);
}

Background::~Background() {

}

void Background::init(std::string lvlDesc) {
    readLevel(lvlDesc);
    _doors.setPosition(0,0);
    _background.setPosition(0,0);
    _background.setTexture(_bTexture);
}

bool Background::colision(float x, float y){
    return colision(sf::Vector2f(x,y));
}

bool Background::colision(sf::Vector2f pos) {
    for(int i = 0; i < _boundaries.size(); ++i){
        if(_boundaries[i].contains(pos)) return true;
    }
    return false;
}

void Background::draw(sf::RenderTarget *target){
    target->draw(_background);

    if(_doorOpenedL && _doorOpenedR){
        _doors.setTexture(Resources::doors_OO);
    }
    else if( _doorOpenedL && ! _doorOpenedR){
        _doors.setTexture(Resources::doors_OX);
    }
    else if(! _doorOpenedL && ! _doorOpenedR){
        _doors.setTexture(Resources::doors_XX);
    }
    target->draw(_doors);

    //DEBUG DRAW RED RECTANGLES
   if(DEBUGDRAW) {
   for(int i = 0; i < _boundaries.size(); ++i){
        sf::RectangleShape RS(sf::Vector2f(_boundaries[i].width,_boundaries[i].height));
        RS.setPosition(sf::Vector2f(_boundaries[i].left,_boundaries[i].top));
        RS.setOutlineColor(sf::Color(i*10+10,i*20+20,i*30+30));
        RS.setFillColor(sf::Color(i*10+10,i*20+20,i*30+30,100));
        RS.setOutlineThickness(2);
        target->draw(RS);
    }
}

}

bool Background::circleColision(sf::Vector2f pos, float rad) {
    for(int i = 0; i < _boundaries.size(); ++i){

        if(    _boundaries[i].contains(pos.x+rad, pos.y)
            || _boundaries[i].contains(pos.x-rad, pos.y)
            || _boundaries[i].contains(pos.x, pos.y+rad)
            || _boundaries[i].contains(pos.x, pos.y-rad) ){
            return true;
        }
        else if(    getModule(pos, sf::Vector2f(_boundaries[i].left,_boundaries[i].top)) < rad
                 || getModule(pos, sf::Vector2f(_boundaries[i].left+_boundaries[i].width,_boundaries[i].top)) < rad
                 || getModule(pos, sf::Vector2f(_boundaries[i].left,_boundaries[i].top+_boundaries[i].height)) < rad
                 || getModule(pos, sf::Vector2f(_boundaries[i].left+_boundaries[i].width,_boundaries[i].top+_boundaries[i].height)) < rad ){
            return true;
        }
    }
    return false;
}


bool Background::rectangleColision(sf::FloatRect rect){
    for(int i = 0; i < _boundaries.size(); ++i){
        if(   _boundaries[i].contains(rect.left, rect.top)
           || _boundaries[i].contains(rect.left+rect.width, rect.top)
           || _boundaries[i].contains(rect.left, rect.top+rect.height)
           || _boundaries[i].contains(rect.left+rect.width, rect.top+rect.height))
            return true;
        if(   rect.contains(_boundaries[i].left, _boundaries[i].top)
              || rect.contains(_boundaries[i].left+_boundaries[i].width, _boundaries[i].top)
              || rect.contains(_boundaries[i].left, _boundaries[i].top+_boundaries[i].height)
              || rect.contains(_boundaries[i].left+_boundaries[i].width, _boundaries[i].top+_boundaries[i].height))
               return true;
    }
    return false;
}

#include <complex>
using namespace std;

typedef complex<double> point;

double error=1e-7;

double prodesc(point p1,point p2)
{
  return real(conj(p1)*p2);
}

double prodvec(point p1,point p2)
{
  return imag(conj(p1)*p2);
}

point calculainterseccio(point p1,point v1,point p2,point v2)
{
  return p1+(prodvec(p2-p1,v2)/prodvec(v1,v2))*v1;
}

pair<bool,point> intersecciosemirectasegment(point p1,point v1,point a,point b)
{
  point p2=a;
  point v2=b-a;

  if (abs(prodvec(v1,v2))<error) return pair<bool,point> (false,0.0);

  point interseccio=calculainterseccio(p1,v1,p2,v2);

  if (prodesc(interseccio-p1,v1)<-error) return pair<bool,point> (false,0.0);
  if (prodesc(interseccio-p2,v2)<-error) return pair<bool,point> (false,0.0);
  if (prodesc(interseccio-b,v2)>error) return pair<bool,point> (false,0.0);
  return pair<bool,point> (true,interseccio);
}



sf::Vector2i Background::getIntersection(sf::Vector2i position, sf::Vector2i mousePos){

    sf::Vector2i ret(-1337,-1337);

    pair <bool,point> result;
    result.second.real(0);
    result.second.imag(0);
    result.first = false;

    point pos(position.x, position.y);
    point vec(mousePos.x - position.x, mousePos.y - position.y);
    for(int i = 0; i < _boundaries.size(); ++i){

        point a, b;

        //TOP
        result.first = false;
        a.real( double( _boundaries[i].left));
        a.imag( double( _boundaries[i].top));
        b.real( double( _boundaries[i].left + _boundaries[i].width));
        b.imag( double( _boundaries[i].top));
        result = intersecciosemirectasegment(pos, vec, a, b);
        if(result.first &&
                (abs(pos-result.second) < abs(pos- point(ret.x, ret.y))))
                    ret = sf::Vector2i(result.second.real(),result.second.imag());

        //LEFT
        result.first = false;
        a.real( double( _boundaries[i].left));
        a.imag( double( _boundaries[i].top));
        b.real( double( _boundaries[i].left));
        b.imag( double( _boundaries[i].top + _boundaries[i].height));
        result = intersecciosemirectasegment(pos, vec, a, b);
        if(result.first &&
                (abs(pos-result.second) < abs(pos- point(ret.x, ret.y))))
                    ret = sf::Vector2i(result.second.real(),result.second.imag());

        //BOT
        result.first = false;
        a.real( double( _boundaries[i].left));
        a.imag( double( _boundaries[i].top + _boundaries[i].height));
        b.real( double( _boundaries[i].left+ _boundaries[i].width));
        b.imag( double( _boundaries[i].top + _boundaries[i].height));
        result = intersecciosemirectasegment(pos, vec, a, b);
        if(result.first &&
                (abs(pos-result.second) < abs(pos- point(ret.x, ret.y))))
                    ret = sf::Vector2i(result.second.real(),result.second.imag());

        //RIGHT
        result.first = false;
        a.real( double( _boundaries[i].left+ _boundaries[i].width));
        a.imag( double( _boundaries[i].top ));
        b.real( double( _boundaries[i].left+ _boundaries[i].width));
        b.imag( double( _boundaries[i].top + _boundaries[i].height));
        result = intersecciosemirectasegment(pos, vec, a, b);
        if(result.first &&
                (abs(pos-result.second) < abs(pos- point(ret.x, ret.y))))
                    ret = sf::Vector2i(result.second.real(),result.second.imag());


    }

//    if(ret.x != 0) ret.x = mousePos.x;
  //  if(ret.y != 0) ret.y = mousePos.y;
    //retorna minim
    return ret;

}

sf::Vector2f Background::getVectorFromCircleColision(sf::Vector2f &direction, sf::Vector2f pos, float rad) {
    sf::Vector2f ret(0,0);
    direction.x = direction.x / getModule(sf::Vector2f(0,0), direction);
    direction.y = direction.y / getModule(sf::Vector2f(0,0), direction);

    for(int i = 0; i < _boundaries.size(); ++i){
        float left, right, top, bot;
        top = _boundaries[i].top;
        left = _boundaries[i].left;
        bot = _boundaries[i].top + _boundaries[i].height;
        right = _boundaries[i].left + _boundaries[i].width;

        log("0");
        // )|
        if( _boundaries[i].contains(pos.x+rad, pos.y)) { ret.x = min(left - pos.x+rad, ret.x);}
        // |(
        if( _boundaries[i].contains(pos.x-rad, pos.y)) { ret.x = max(pos.x-rad - right, ret.x);}
        // _U_
        if( _boundaries[i].contains(pos.x, pos.y+rad)) { ret.y = max(pos.y+rad - top, ret.y); }
        //  ^
        if( _boundaries[i].contains(pos.x, pos.y-rad)) { ret.y = min(bot - pos.y-rad, ret.y); }

/*
        if( getModule(pos, sf::Vector2f(left,top)) < rad ) {
            sf::Vector2f origin(left,top);
            sf::Vector2f center = pos;
            sf::Vector2f d = origin - center;
            sf::Vector2f point;
            float a = direction.x*direction.x + direction.y*direction.y;
            float b = d.x*direction.x + d.y*direction.y;
            float c = d.x*d.x + d.y*d.y - rad * rad;
            float disc = b*b-a*c;

            float sqrtDisc = std::sqrt(disc);
            float invA = 1.0/a;

            float t0 = (-b - sqrtDisc) *invA;
            float t1 = (-b + sqrtDisc) *invA;

            point.x = origin.x + t0 * direction.x;
            point.y = origin.y + t1 * direction.y;

            ret.y = min(ret.y, abs(top - point.y));
            ret.x = min(ret.x, abs(left - point.x));

        }

        if( getModule(pos, sf::Vector2f(right,top)) < rad ) {
            sf::Vector2f origin(right,top);
            sf::Vector2f center = pos;
            sf::Vector2f d = origin - center;
            sf::Vector2f point;
            float a = direction.x*direction.x + direction.y*direction.y;
            float b = d.x*direction.x + d.y*direction.y;
            float c = d.x*d.x + d.y*d.y - rad * rad;
            float disc = b*b-a*c;

            float sqrtDisc = std::sqrt(disc);
            float invA = 1.0/a;

            float t0 = (-b - sqrtDisc) *invA;
            float t1 = (-b + sqrtDisc) *invA;

            point.x = origin.x + t0 * direction.x;
            point.y = origin.y + t1 * direction.y;

            ret.y = min(ret.y, abs(top - point.y));
            ret.x = max(ret.x, abs(right - point.x));

        }

        if( getModule(pos, sf::Vector2f(right,bot)) < rad ) {
            sf::Vector2f origin(right,bot);
            sf::Vector2f center = pos;
            sf::Vector2f d = origin - center;
            sf::Vector2f point;
            float a = direction.x*direction.x + direction.y*direction.y;
            float b = d.x*direction.x + d.y*direction.y;
            float c = d.x*d.x + d.y*d.y - rad * rad;
            float disc = b*b-a*c;

            float sqrtDisc = std::sqrt(disc);
            float invA = 1.0/a;

            float t0 = (-b - sqrtDisc) *invA;
            float t1 = (-b + sqrtDisc) *invA;

            point.x = origin.x + t0 * direction.x;
            point.y = origin.y + t1 * direction.y;

            ret.y = max(ret.y, abs(bot - point.y));
            ret.x = max(ret.x, abs(right - point.x));

        }

        if( getModule(pos, sf::Vector2f(left,bot)) < rad ) {
            sf::Vector2f origin(left,bot);
            sf::Vector2f center = pos;
            sf::Vector2f d = origin - center;
            sf::Vector2f point;
            float a = direction.x*direction.x + direction.y*direction.y;
            float b = d.x*direction.x + d.y*direction.y;
            float c = d.x*d.x + d.y*d.y - rad * rad;
            float disc = b*b-a*c;

            float sqrtDisc = std::sqrt(disc);
            float invA = 1.0/a;

            float t0 = (-b - sqrtDisc) *invA;
            float t1 = (-b + sqrtDisc) *invA;

            point.x = origin.x + t0 * direction.x;
            point.y = origin.y + t1 * direction.y;

            ret.y = max(ret.y, abs(bot - point.y));
            ret.x = min(ret.x, abs(left - point.x));

        }
*/
    }
    return ret;

}

sf::Vector2i Background::getIntersection(sf::Vector2i mousePos){

    sf::Vector2i ret(1,1);

    for(int i = 0; i < _boundaries.size(); ++i){
        if(_boundaries[i].contains(sf::Vector2f(mousePos.x,mousePos.y))){
            ret.x = _boundaries[i].left;
            ret.y = _boundaries[i].top;
      //      ret.x = mousePos.x;
      //      ret.y = mousePos.y;
        }

    }

    return ret;

}

sf::Vector2f Background::getCircleColisionOffset(sf::Vector2f pos, float rad){
    sf::Vector2f ret(0,0);

    for(int i = 0; i < _boundaries.size(); ++i){

        if( _boundaries[i].contains(pos.x+rad, pos.y)) ret.x = std::max(pos.x+rad - _boundaries[i].left, ret.x);
        if( _boundaries[i].contains(pos.x-rad, pos.y)) ret.x = std::max(_boundaries[i].left + _boundaries[i].width - pos.x-rad, pos.x);
        if( _boundaries[i].contains(pos.x, pos.y+rad)) ret.y = std::max(pos.y+rad - _boundaries[i].top, ret.y);
        if( _boundaries[i].contains(pos.x, pos.y-rad)) ret.y = std::max(_boundaries[i].top + _boundaries[i].height - pos.y+rad, ret.y);

        if( getModule(pos, sf::Vector2f(_boundaries[i].left,_boundaries[i].top)) < rad ) {
            float ratio = rad / getModule(pos, sf::Vector2f(_boundaries[i].left,_boundaries[i].top));
            ret.x = std::max(ret.x, (_boundaries[i].left - pos.x)*ratio);
            ret.y = std::max(ret.y, (_boundaries[i].top - pos.y)*ratio);
        }
        if( getModule(pos, sf::Vector2f(_boundaries[i].left+_boundaries[i].width,_boundaries[i].top)) < rad ){
            float ratio = rad / getModule(pos, sf::Vector2f(_boundaries[i].left+_boundaries[i].width,_boundaries[i].top));
            ret.x = std::max(ret.x, (pos.x - _boundaries[i].left+_boundaries[i].width)*ratio);
            ret.y = std::max(ret.y, (_boundaries[i].top - pos.y)*ratio);
        }
        if( getModule(pos, sf::Vector2f(_boundaries[i].left,_boundaries[i].top+_boundaries[i].height)) < rad ){
            float ratio = rad / getModule(pos, sf::Vector2f(_boundaries[i].left,_boundaries[i].top+_boundaries[i].height));
            ret.x = std::max(ret.x, (_boundaries[i].left - pos.x)*ratio);
            ret.y = std::max(ret.y, (pos.y - _boundaries[i].top+_boundaries[i].height)*ratio);
        }
        if( getModule(pos, sf::Vector2f(_boundaries[i].left+_boundaries[i].width,_boundaries[i].top+_boundaries[i].height)) < rad ){
            float ratio = rad / getModule(pos, sf::Vector2f(_boundaries[i].left+_boundaries[i].width,_boundaries[i].top+_boundaries[i].height));
            ret.x = std::max(ret.x, (pos.x - _boundaries[i].left+_boundaries[i].width)*ratio);
            ret.y = std::max(ret.y, (pos.y - _boundaries[i].top+_boundaries[i].height)*ratio);
        }

    }
    return ret;

}




void Background::readLevel(std::string lvlDesc) {
    std::string line;
    std::ifstream myfile (LVLDESCIPTPATH+lvlDesc+".txt");
    //std::cout << (LVLDESCIPTPATH+lvlDesc+".txt") << std::endl;

    if (myfile.is_open()) {

        std::getline (myfile,line);
        while(line[0] == '#') std::getline (myfile,line);
        if(! _bTexture.loadFromFile(TEXTURETPATH+line) ) std::cout << "error on loading bacground texture" << std::endl;

        std::getline (myfile,line);
        while (line[0] != '$') {
            if(line[0] != '#'){
                if(line == "doors"){
                    std::getline (myfile,line);
                    while(line[0] == '#') std::getline (myfile,line);
                    if(line == "OO"){
                        _doorOpenedL = _doorOpenedR = true;
                    }
                    else if(line == "OX"){
                        _doorOpenedL = true;
                        _doorOpenedR = false;
                    }
                    else if(line == "XX"){
                        _doorOpenedL = _doorOpenedR = false;
                    }

                }

                if(line == "boundaries"){
                    //log("boundaries");

                    std::getline (myfile,line);
                    while(line[0] == '#') std::getline (myfile,line);

                    while(line == "next"){

                        sf::FloatRect fr;
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);
                        fr.left = myStoi(line);
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);
                        fr.top = myStoi(line);
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);
                        fr.width = myStoi(line);
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);
                        fr.height = myStoi(line);

                        _boundaries.push_back(fr);

                        //read next that would be next if ther are more or end (or something else ) if it is done
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);

                    }

                }
            }
            std::getline (myfile,line);
            while(line[0] == '#') std::getline (myfile,line);
        }
        //std::cout << "bg finishes with line  " << line << std::endl;
        myfile.close();
    } else std::cout << "not oppened backgroound file " << lvlDesc << std::endl;
}
