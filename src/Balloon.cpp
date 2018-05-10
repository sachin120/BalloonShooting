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
#include "Balloon.h"
#include "TextureHolder.h"
#include <ctime>
#include <iostream>

using namespace std;

void Balloon::spawn(IntRect arena, float startX, float startY, int type, int seed) {

    //  Copy the details of Balloon game Arena
    m_Arena.left = arena.left; 
    m_Arena.width = arena.width;
    m_Arena.top = arena.top;
    m_Arena.height = arena.height;

    // This might not required
    m_Alive = true;

    switch (type) {
        case 0:
            //  HEADY
            m_Sprite = Sprite(TextureHolder::GetTexture("../assets/graphics/bln4.png"));
            m_Speed = HEADY_SPEED;
            m_Health = HEADY_HEALTH;
            m_Points = HEADY_POINTS;
            break;

        case 1:
            //  JUPITER
            m_Sprite = Sprite(TextureHolder::GetTexture("../assets/graphics/bln2.png"));
            m_Speed = JUPITER_SPEED;
            m_Health = JUPITER_HEALTH;
            m_Points = JUPITER_POINTS;
            break;

        case 2:
            //  SHANKARPALI 
            m_Sprite = Sprite(TextureHolder::GetTexture("../assets/graphics/bln5.png"));
            m_Speed = SHANKARPALI_SPEED;
            m_Health = SHANKARPALI_HEALTH;
            m_Points = SHANKARPALI_POINTS;
            break;

        case 3:
            //  TENALI 
            m_Sprite = Sprite(TextureHolder::GetTexture("../assets/graphics/bln1.png"));
            m_Speed = TENALI_SPEED;
            m_Health = TENALI_HEALTH;
            m_Points = TENALI_POINTS;
            break;

        case 4:
            //  STIPY 
            m_Sprite = Sprite(TextureHolder::GetTexture("../assets/graphics/bln3.png"));
            m_Speed = STRIPY_SPEED;
            m_Health = STRIPY_HEALTH;
            m_Points = STRIPY_POINTS;
            break;
    }

    //  Modify the speeds to make them unique
    srand((int)time(0) * seed);
    //  some where between 80 to 100
    float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
    //  Express as fraction of 1
    modifier /= 100; // Now equal between .7 and 1
    m_Speed *= modifier;

    //  Speed must not be less than 20
    if (m_Speed <= 20) {
        m_Speed = 20;
    }

    m_Position.x = startX;
    m_Position.y = startY;

    m_Sprite.setOrigin(25, 25);
    m_Sprite.setPosition(m_Position);
}

bool Balloon::hit() {
    m_Health -= 1;

    if (m_Health <= 0) {
        //  dead
        m_Alive = false;
        m_Sprite.setTexture(TextureHolder::GetTexture("../assets/graphics/none.png"));    //  Make it disappiare
        return true;
    }
    //  injured but not dead
    return false;
}

bool Balloon::isAlive() {
    return m_Alive;
}

FloatRect Balloon::getPosition() {
    return m_Sprite.getGlobalBounds();
}

Sprite Balloon::getSprite() {
    return m_Sprite;
}

int Balloon::getEarnPoints() {
    return m_Points;
}

void Balloon::update(float elapsedTime, Vector2f maxHeight) {
    float maxX = maxHeight.x;
    float maxY = maxHeight.y;

    //  Update the balloon position
    if (maxHeight.y < m_Position.y) {
        m_Position.y = m_Position.y - m_Speed * elapsedTime;
    }

    //  Move the sprite
    m_Sprite.setPosition(m_Position);
}
