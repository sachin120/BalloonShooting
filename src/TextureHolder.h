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
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace std;
using namespace sf;

class TextureHolder {
    private:
    //  A map container from STL, that holds related pair of string and Texture
    map<string, Texture> m_Texture;

    //  A pointer of the same type as the class itself
    //  the one and only instance
    static TextureHolder* m_s_Instance;
    public:
    TextureHolder();
    static Texture& GetTexture(string const& filename);
};
#endif
