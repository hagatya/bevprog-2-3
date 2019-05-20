#ifndef EXAMPLECHECKBOX_HPP_INCLUDED
#define EXAMPLECHECKBOX_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include <string>
#include <vector>

using namespace genv;
using namespace std;


class ExampleCheckBox : public Widget {
protected:
    bool _checked;
public:
    ExampleCheckBox(int x, int y, int sx, int sy);
    virtual void draw();
    virtual void handle(event ev);
    virtual bool is_checked();
};

void endgame();
void ablak();
void event_loop(vector<Widget*> & widgets);

#endif // EXAMPLECHECKBOX_HPP_INCLUDED
