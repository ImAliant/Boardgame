#pragma once

#include <memory>

#include "Board.hpp"
#include "player/Player.hpp"

class Game
{
    private:
        void AddPlayer(std::shared_ptr<Player> player);
    protected: 
        std::vector<std::shared_ptr<Player>> players;
        std::shared_ptr<Board> board;
        virtual void Init() = 0;
        virtual void InitPlayers();
    public:
        explicit Game();
        virtual ~Game() = default;

        virtual void Start() = 0;

        void MovePiece(const coord_t from, const coord_t to) const;

        std::shared_ptr<Board> GetBoard() const;
        std::vector<std::shared_ptr<Player>> GetPlayers() const;
        std::shared_ptr<Player> GetPlayer(const int id) const;
};