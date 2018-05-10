/*
    BalloonShooting is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    BalloonShooting is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BalloonShooting.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <SFML/Graphics.hpp>
#include "Bow.h"
#include "TextureHolder.h"

Bow::Bow() {
    m_Sprite = Sprite(TextureHolder::GetTexture("../assets/graphics/player.png"));

    //  Set origin of the sprite to center for a smooth rotation
    m_Position.x = 250;
    m_Position.y = 500;
    m_Sprite.setPosition(m_Position.x, m_Position.y);
    m_Sprite.setOrigin(25, 25);
}

void Bow::spawn(IntRect arena, Vector2f resolution) {
    //m_Position.x = arena.width / 3;
    //m_Position.y = arena.height / 4;
    m_Position.x = arena.width;
    m_Position.y = arena.height;

    //  Store for futur use
    m_Resolution.x = resolution.x;
    m_Resolution.y = resolution.y;
}

FloatRect Bow::getPosition() {
    return m_Sprite.getGlobalBounds();
}

Vector2f Bow::getCenter() {
    return m_Position;
}

float Bow::getRotation() {
    return m_Sprite.getRotation();
}

Sprite Bow::getSprite() {
    return m_Sprite;
}

void Bow::update(float elapsedTime, Vector2i mousePosition) {
    //  Here elapsedTime is for future use, for movement
    int adj_lenght = mousePosition.x - m_Sprite.getPosition().x;  
    int opp_lenght = m_Sprite.getPosition().y - mousePosition.y;

    float angle = opp_lenght / (sqrt(adj_lenght * adj_lenght  + opp_lenght * opp_lenght));

    //  This is just to avoid pointing back visually
    if (angle < 0.70) {
        m_Sprite.setRotation(-sin(angle)*180/3.1415);
    }
}

