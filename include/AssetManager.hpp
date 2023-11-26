#pragma once

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

enum AssetID
{
    MAIN_FONT = 0,
    CHECKERS_BLACK_PIECE,
    CHECKERS_WHITE_PIECE
};

namespace Engine
{
    class AssetManager
    {
        private:
            std::map<int, std::unique_ptr<sf::Texture>> m_textures;
            std::map<int, std::unique_ptr<sf::Font>> m_fonts;

        public:
            AssetManager();
            ~AssetManager();

            void AddTexture(int id, const std::string &filePath, bool wantRepeated = false);
            void AddFont(int id, const std::string &filePath);

            bool HasTexture(int id) const;
            bool HasFont(int id) const;

            const sf::Texture &GetTexture(int id) const;
            sf::Font &GetFont(int id);
    };
}