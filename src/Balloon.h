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
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Balloon {
    private:
    //  How fast is each balloon type
    const float HEADY_SPEED = 50;
    const float JUPITER_SPEED = 20;
    const float SHANKARPALI_SPEED = 70;
    const float TENALI_SPEED = 80;
    const float STRIPY_SPEED = 60;

    //  How tough is each balloon type
    const float HEADY_HEALTH = 1;
    const float JUPITER_HEALTH = 1;
    const float SHANKARPALI_HEALTH = 2;
    const float TENALI_HEALTH = 2;
    const float STRIPY_HEALTH = 3;

    //  How much point Each give
    const float HEADY_POINTS = 50;
    const float JUPITER_POINTS = 20;
    const float SHANKARPALI_POINTS = 70;
    const float TENALI_POINTS = 80;
    const float STRIPY_POINTS = 60;

    //  Make each balloon vary its speed
    const int MAX_VARRIANCE = 20;
    const int OFFSET = 101 - MAX_VARRIANCE;

    //  Where is this balloon?
    Vector2f m_Position;

    //  A sprite for the balloon
    Sprite m_Sprite;

    //  Get the size of current arena
    IntRect m_Arena;

    //  How fast can this one fly?
    float m_Speed;

    //  How much health has he got?
    float m_Health;

    //  How much point it has
    int m_Points;

    //  Is it still alive?
    bool m_Alive;

    //  Public prototype goes here
    public:
    //  Handle when arrow hits a balloon
    bool hit();

    //  Find out if balloon is alive
    bool isAlive();

    // Gained points
    int gainedPoints();

    //  Spawn a new balloon
    void spawn(IntRect arena, float startX, float startY, int type, int seed);

    //  Return a rectangle that is the position in the world
    FloatRect getPosition();

    //  Return earn points
    int getEarnPoints();

    //  Get copy of the sprite to draw
    Sprite getSprite();

    //  Update the balloon each frame
    void update(float elapsedTime, Vector2f maxHeight);
};
