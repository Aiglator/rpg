#include <iostream>
#include <SFML/Graphics.hpp>
#include "menu.hpp"



// Implémentation temporaire de level1 pour les tests
void level1() {
    std::cout << "Level1 function called" << std::endl;
}

int main() {
    std::cout << "Starting game..." << std::endl;
    
    // Appel de la fonction menu
    viewmenu();
    
    return 0;
}