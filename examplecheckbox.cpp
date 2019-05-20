#include "examplecheckbox.hpp"
#include "graphics.hpp"
#include <sstream>
#include <iostream>

using namespace genv;
using namespace std;

bool q, win;
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
    win=false;
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            ExampleCheckBox * b1 = new ExampleCheckBox(i*25,j*25,24,24);
            w.push_back(b1);
            a[i][j] = w[i*20+j]->t;
        }
    }
    event_loop(w);
}

int REDWin()
{
    gout << color(255,0,0) << move_to(150, 200) << box(200, 100) << color(0, 0, 0) << move_to(150, 250) << text("Piros nyert");
    gout << move_to(150, 250+gout.cascent()) << text("Nyomj esc-et a kilépéshez");
    return 0;
}

int GREENWin()
{
    gout << color(0,255,0) << move_to(150, 200) << box(200, 100) << color(0, 0, 0) << move_to(150, 250) << text("Zöld nyert");
    gout << move_to(150, 250+gout.cascent()) << text("Nyomj esc-et a kilépéshez");
    return 0;
}
void endgame()
{
    gout << color(255,255,255) << move_to(150, 200) << box(200, 100) << color(0, 0, 0) << move_to(150, 250) << text("Döntetlen");
    gout << move_to(150, 250+gout.cascent()) << text("Nyomj esc-et a kilépéshez");
}

ExampleCheckBox::ExampleCheckBox(int x, int y, int sx, int sy) : Widget(x,y,sx,sy)
{
    _checked=false;
    t=0;
}

void ExampleCheckBox::draw()
{
    if(t==0)
    {
        gout << move_to(_x, _y) << color(255,255,255) << box(_size_x, _size_y);
    }
    if(t==1)
    {
        gout << move_to(_x, _y) << color(0,255,0) << box(_size_x, _size_y);
    }
    if(t==2)
    {
        gout << move_to(_x, _y) << color(255,0,0) << box(_size_x, _size_y);
    }
    if(win==true && q==1)
    {
        GREENWin();
        return;
    }
    if(win==true && q==0)
    {
        REDWin();
        return;
    }
}

void ExampleCheckBox::handle(event ev)
{
    if(ev.pos_x <= _x+_size_x && ev.pos_x >= _x && ev.pos_y <= _y+_size_y && ev.pos_y >= _y && ev.type == ev_mouse && ev.button == btn_left && !win)
    {
        _checked=true;
        if(_checked && t==0)
        {
            t=(unsigned)q+1;
            q=!q;
            for(int i=0; i<20; i++)
            {
                for(int j=0; j<20; j++)
                {
                    a[i][j] = w[i*20+j]->t;
                }
            }
        }
    }
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            if(a[i][j] == a[i+1][j] && a[i][j] == a[i+2][j] && a[i][j] == a[i+3][j] && a[i][j] == a[i+4][j] && a[i][j] >0)
                win=true;
            if(a[i][j] == a[i][j+1] && a[i][j] == a[i][j+2] && a[i][j] == a[i][j+3] && a[i][j] == a[i][j+4] && a[i][j] >0)
                win=true;
            if(a[i][j] == a[i+1][j+1] && a[i][j] == a[i+2][j+2] && a[i][j] == a[i+3][j+3] && a[i][j] == a[i+4][j+4] && a[i][j] >0)
                win=true;
            if(a[i][j] == a[i+1][j-1] && a[i][j] == a[i+2][j-2] && a[i][j] == a[i+3][j-3] && a[i][j] == a[i+4][j-4] && a[i][j] >0)
                win=true;
            if(a[i][j] > 0 && a[i+1][j] > 0 && a[i+2][j] > 0 && a[i+3][j] > 0 && a[i+4][j] > 0 && a[i][j] != a[i+1][j] && a[i][j] != a[i+2][j] && a[i][j] != a[i+3][j] && a[i][j] != a[i+4][j])
             {
                endgame();
                win=true;
             }
        }
    }
}

bool ExampleCheckBox::is_checked()
{
    return _checked;
}
