#include "RiverRenderer.h"

using namespace render;
using namespace std;


RiverRenderer::RiverRenderer(std::shared_ptr<state::River> river, sf::Vector2f position){
    this->setPosition(position);

    this->texture.loadFromFile("res/textures/footer_lodyas.png");
}

void RiverRenderer::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    sf::Vector2f _position = this->getPosition();

    sf::Sprite _sprite(this->texture);
    _sprite.setScale(130/_sprite.getLocalBounds().width,900/_sprite.getLocalBounds().height);
    _sprite.setPosition(_position.x,_position.y);

    target.draw(_sprite);
}