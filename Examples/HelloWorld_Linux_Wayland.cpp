// Author: Jake Rieger
// Created: 7/12/2024.
//

#include "WaylandParent.h"

int main() {
    WaylandParent::CreateParentWindow();
    WaylandParent::Run();
    WaylandParent::DestroyParentWindow();

    return 0;
}