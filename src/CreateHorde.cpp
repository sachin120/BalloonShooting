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
#include "Balloon.h"

Balloon* createHorde(int numBalloons, IntRect arena) {
    Balloon* ballons = new Balloon[numBalloons];

    int maxY = arena.height;
    int minY = arena.top;
    int maxX = arena.width;
    int minX = arena.left;

    //  This is the range or the time interval for balloons
    int minHeightRand = maxY;
    //  This multiplication depents on level
    int maxHeightRand = arena.height * 2;

    float x, y;

    for (int i = 0; i < numBalloons; i++) {
        srand((int)time(0) * i);
        y = (rand() % maxHeightRand) + minHeightRand;
        x = (rand() % maxX) + minX; 

        //  Heady, jupiter, shankarpali, tenali, stripy
        srand((int)time(0) * i * 2);
        int type = (rand() % 5);    //  As there are 5 types of balloons

        //  Spawn the new balloon
        ballons[i].spawn(arena, x, y, type, i);
    }
    return ballons;
}
