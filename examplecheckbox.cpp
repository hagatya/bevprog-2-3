#include "examplecheckbox.hpp"
#include "graphics.hpp"
#include <sstream>
#include <iostream>

using namespace genv;
using namespace std;

bool q;
char a[20][20];

void event_loop(vector<ExampleCheckBox*>& widgets)
{
    event ev;
    int focus = -1;
    while(gin >> ev && ev.keycode != key_escape)
    {
        if (ev.type == ev_mouse && ev.button==btn_left)
        {
            for (size_t i=0; i<widgets.size(); i++)
            {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y))
                {
                    focus = i;
                }
            }
        }
        if (focus!=-1)
        {
            widgets[focus]->handle(ev);
        }
        for (size_t i=0; i<widgets.size(); i++)
        {
            widgets[i]->draw();
        }
        gout << refresh;
    }
}

vector<ExampleCheckBox*> w;

void ablak()
{
    gout.open(500,500);
    q=0;
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            ExampleCheckBox * b1 = new ExampleCheckBox(i*25,j*25,24,24);
            w.push_back(b1);
        }
    }
    event_loop(w);
}


ExampleCheckBox::ExampleCheckBox(int x, int y, int sx, int sy) : Widget(x,y,sx,sy)
{
    _checked=false;
}

void ExampleCheckBox::draw()
{
}

void ExampleCheckBox::handle(event ev)
{
    if(ev.pos_x <= _x+_size_x && ev.pos_x >= _x && ev.pos_y <= _y+_size_y && ev.pos_y >= _y && ev.type == ev_mouse && ev.button == btn_left)
    {
        _checked=true;

    }

}

bool ExampleCheckBox::is_checked()
{
    return _checked;
}