// Author: Jake Rieger
// Created: 7/12/2024.
//

#include <cstdlib>
#include "X11Parent.h"
#include "Platform/X11PluginView.h"

int main() {
    X11Parent::CreateParentWindow();
    X11Parent::Run();
    X11Parent::DestroyParentWindow();

    return EXIT_SUCCESS;
}