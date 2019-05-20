#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"
#include <vector>
#include <string>

using namespace genv;
using namespace std;

class Widget {
protected:
    int _x, _y, _size_x, _size_y;
public:
    Widget();
    Widget(int x, int y, int sx, int sy);
    virtual bool is_selected(int mouse_x, int mouse_y) const;
    virtual void draw();
    virtual void handle(event ev);
};


#endif // WIDGETS_HPP_INCLUDED
