#include "window.h"


int main(void)
{
    int input;

    create_window();

    while ((input = getch()) != KEY_F(5)) {
        //Todo: process events
    }
    destroy_window();
}

