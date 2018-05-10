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

class Bow {
    private:
    //  Where is the Bow
    Vector2f m_Position;

    //  Sprite
    Sprite m_Sprite;

    //  Texture
    Texture m_Texture;

    //  What is the screen resolution
    Vector2f m_Resolution;
    
    public:
    //  All the public function come here
    Bow();

    //  position the bow
    void spawn(IntRect arena, Vector2f resolution);

    //  Where is bow
    FloatRect getPosition();

    //  Where is the center of the Bow
    Vector2f getCenter();

    //  Get rotation
    float getRotation();

    //  Send copy of sprite to main
    Sprite getSprite();

    //  Rotate along the mouse position
    void update(float elapsedTime, Vector2i mousePosition);
};
