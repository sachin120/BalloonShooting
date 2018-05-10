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
#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder() {
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename) {
    //  Get the reference to m_Texture using m_s_Instance
    auto& m = m_s_Instance->m_Texture;

    //  Create an Iterator to hold key-value-pair
    auto keyValuePair = m.find(filename);

    //  Did we find match?
    if (keyValuePair != m.end()) {
        //  Yes, return the texture. Second part is the texture
        return keyValuePair->second;
    } else {
        //  If file name not found, Create a new Key value pair using filename
        auto& texture = m[filename];

        //  Load the texture from file as usual way
        texture.loadFromFile(filename);

        return texture;
    }
}
