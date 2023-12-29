#pragma once

#include "../Board.hpp"
#include "../game/GameStatus.hpp"
#include "../game/ModelFlags.hpp"

class Model
{
    protected:
        std::unique_ptr<Board> m_board;
        std::vector<std::shared_ptr<Player>> m_players;

        void SwitchPlayer(GameStatus& status, ModelFlags& flags);
    public:
        Model() = default;
        virtual ~Model() = default;

        /*virtual void Turn(const coord_t coord) = 0;
        virtual void Init() = 0;*/
};