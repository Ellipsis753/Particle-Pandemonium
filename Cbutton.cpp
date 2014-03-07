#include "Cbutton.h"

Cbutton::Cbutton(float x, float y, float w, float h): x(x), y(y), w(w), h(h) {
    //empty
}

bool Cbutton::isClicked(float mouseX, float mouseY) {
    if (mouseX >= x && mouseX < x+w && mouseY <= y && mouseY > y-h) {
        return true;
    }
    return false;
}
