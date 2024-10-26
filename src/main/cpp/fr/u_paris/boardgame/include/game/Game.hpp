#pragma once

#include <memory>

#include "Board.hpp"
#include "GameState.hpp"
#include "player/Player.hpp"

class Game
{
    private:
        void AddPlayer(std::shared_ptr<Player> player);
    protected: 
        std::vector<std::shared_ptr<Player>> players;
        std::shared_ptr<Board> board;

        std::shared_ptr<GameState> state;

        virtual void Init() = 0;
        virtual void InitPlayers();
    public:
        explicit Game();
        virtual ~Game() = default;

        virtual void Start();
        virtual void Turn() = 0;

        virtual void SelectPiece(const coord_t coord);
        virtual void DeselectPiece();

        void MovePiece(const coord_t to) const;
        bool IsMovePossible(const coord_t to) const;
        
        virtual bool IsGameFinished() = 0;

        std::shared_ptr<Board> GetBoard() const;
        std::vector<std::shared_ptr<Player>> GetPlayers() const;
        std::shared_ptr<Player> GetPlayer(const int id) const;
        std::shared_ptr<GameState> GetState() const;
};