#include <FL/Fl.H>
#include "LibraryGUI.h"

int main(int argc, char **argv)
{
    LibraryGUI *gui = new LibraryGUI(900, 650, "Optimized Library Lookup System");
    gui->show(argc, argv);
    return Fl::run();
}