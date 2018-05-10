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

class Arrow {
    private:
    //  Where is the arrow?
    Vector2f m_Position;

    //  What each arrow looks like
    RectangleShape m_ArrowShape;

    //  Is the arrow currently wizzing through the air
    bool m_InFlight = false;

    //  How fast does the arrow travel?
    float m_ArrowSpeed = 900;

    //  What fraction of 1 pixel does the arrow travel,
    //  Horizontally and Vertically each frame?
    //  This value will derive from arrow speed
    float m_ArrowDistanceX;
    float m_ArrowDistanceY;

    //  Some boundaries so that arrow doesn't fly over
    float m_MaxX;
    float m_MinX;
    float m_MaxY;
    float m_MinY;
    //  Public function prototype go here
    public:
    Arrow();

    //  Stop the array
    void stop();

    //  Return the value of m_InFlight
    bool isInFlight();

    //  Launch a new arrow
    void shoot(float startX, float startY, float xTarget, float yTarget);

    //  Tale the calling code where the arrow is in the world
    FloatRect getPosition();

    //  Return the actual shap (for drawing)
    RectangleShape getShape();

    //  update the arrow each frame
    void update(float elapedTime);
};
