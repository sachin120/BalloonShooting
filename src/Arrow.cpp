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
#include "Arrow.h"

Arrow::Arrow() {
    m_ArrowShape.setSize(sf::Vector2f(30, 2));
}
    
void Arrow::shoot(float startX, float startY, float targetX, float targetY) {

    int adj_lenght = targetX - startX;  
    int opp_lenght = startY - targetY;

    float angle = opp_lenght / (sqrt(adj_lenght * adj_lenght  + opp_lenght * opp_lenght));

    //  This is just to avoid pointing back visually
    //  shoud not shoot if not valid
    if (angle < 0.70) {
        //  Keep track of Arrow
        m_InFlight = true;
        m_Position.x = startX; 
        m_Position.y = startY; 

        //  Calculate the gradient of the flight path   (Slop of line)
        float gradient = (startX - targetX) / (startY - targetY);

        m_ArrowShape.setRotation(-sin(angle)*180/3.1415);
        m_ArrowDistanceX = m_ArrowSpeed * (cos(angle));
        m_ArrowDistanceY = m_ArrowSpeed * (-sin(angle)); 
    }

//    //  Keep track of Arrow
//    m_InFlight = true;
//    m_Position.x = startX; 
//    m_Position.y = startY; 
//    
//    //  Calculate the gradient of the flight path   (Slop of line)
//    float gradient = (startX - targetX) / (startY - targetY);
//
//    if (gradient < 0) {
//        gradient *= -1;
//    }
//
//    //  Calculate the ratio between x and t
//    float ratioXY = m_ArrowSpeed / (1 + gradient);
//
//    //  Set the speed horizontally and vertically
//    m_ArrowDistanceY = ratioXY;
//    m_ArrowDistanceX = ratioXY * gradient;
//
//    //  Point the arrow in right direction
//    if (targetX < startX) {
//        m_ArrowDistanceX *= -1;
//    }
//
//    if (targetY < startY) {
//        m_ArrowDistanceY *= -1;
//    }
//
    //  Set the maximum range of 1200 pixel
    float range = 1200;
    m_MinX = startX - range;
    m_MaxX = startX + range;
    m_MinY = startY - range;
    m_MaxY = startY + range;

    //  Position the arrow ready to be drawn
    m_ArrowShape.setPosition(m_Position);
}

void Arrow::stop() {
    m_InFlight = false;
}

bool Arrow::isInFlight() {
    return m_InFlight;
}

FloatRect Arrow::getPosition() {
    return m_ArrowShape.getGlobalBounds();
}

RectangleShape Arrow::getShape() {
    return m_ArrowShape;
}

void Arrow::update(float elapsedTime) {
    //  update the arrow position variables
    m_Position.x +=  m_ArrowDistanceX * elapsedTime; 
    m_Position.y +=  m_ArrowDistanceY * elapsedTime;

    //  move the arrow
    m_ArrowShape.setPosition(m_Position);

    //  Has the Arrow gone out of range?
    if (m_Position.x < m_MinX || m_Position.x > m_MaxX || 
        m_Position.y < m_MinY || m_Position.y > m_MaxY) {

        m_InFlight = false;
    }
}
