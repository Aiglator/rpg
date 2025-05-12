#ifndef WORLD_HPP
#define WORLD_HPP

#include "background.hpp" // tu inclues la classe Background ici

class world {
public:
    world();
    void draw(sf::RenderWindow& window);

private:
    background bg;
};

#endif
