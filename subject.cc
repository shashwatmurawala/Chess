#include "subject.h"

void Subject::attach (Observer *ob) {
    observers.push_back(ob);
}

void Subject::detach (Observer *ob) {
    int i = 0;
    for (auto o : observers) {
        if (ob == o) break;
        i++;
    }
    observers.erase(observers.begin() + i);
}

void Subject::displayBoard () {
    for (auto o : observers) {
        o->display();
    }
}

Subject::~Subject () {
    for (auto o : observers) {
        delete o;
    }
}
