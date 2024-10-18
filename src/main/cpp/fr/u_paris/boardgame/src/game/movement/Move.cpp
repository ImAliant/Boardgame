#include "game/movement/Move.hpp"

Move::Move(const coord_t f, const coord_t t, const std::shared_ptr<Piece> p): from{f}, to{t}, piece{p} {
    if (p == nullptr) is_jump = false;
    else is_jump = true;
}

bool Move::IsJump() const {
    return is_jump;
}

coord_t Move::GetFrom() const {
    return from;
}

coord_t Move::GetTo() const {
    return to;
}

std::shared_ptr<Piece> Move::GetPiece() const {
    return piece;
}