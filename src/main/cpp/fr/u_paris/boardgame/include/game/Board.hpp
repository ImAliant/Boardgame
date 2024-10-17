#pragma once

#include <vector>
#include <memory>

#include "Piece.hpp"
#include "Types.hpp"

class Board
{
    private:
        const int width;
        const int height;
        std::vector<std::vector<std::shared_ptr<Piece>>> pieces;

        void Init();
    protected:
        virtual void FillBoard() = 0;

        virtual void CreatePiece(const coord_t coord, const char symbol) = 0;
    public:
        explicit Board(const int w, const int h);
        virtual ~Board() = default;

        void MovePiece(const coord_t from, const coord_t to);
        void RemovePiece(const coord_t coord);

        void SetPiece(const coord_t coord, std::shared_ptr<Piece> p);
        std::shared_ptr<Piece> GetPiece(const coord_t coord) const;

        bool IsEmpty(const coord_t coord) const;
        bool IsInBoard(const coord_t coord) const;

        int GetWidth() const;
        int GetHeight() const;
        std::vector<std::vector<std::shared_ptr<Piece>>> GetPieces() const;

        friend std::ostream& operator<<(std::ostream& os, const Board& b);
};