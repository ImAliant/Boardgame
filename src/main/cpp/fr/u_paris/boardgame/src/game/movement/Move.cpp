#include "game/movement/Move.hpp"

Move::Move(const coord_t t, const std::shared_ptr<Piece> p): to{t}, piece{p} {
    if (p == nullptr) is_jump = false;
    else is_jump = true;
}

bool Move::IsJump() const {
    return is_jump;
}

coord_t Move::GetTo() const {
    return to;
}

std::shared_ptr<Piece> Move::GetPiece() const {
    return piece;
}

std::ostream& operator<<(std::ostream& os, const Move& m) {
    os << "Move to " << m.GetTo().first << ", " << m.GetTo().second;
    if (m.IsJump()) {
        std::shared_ptr<Piece> p = m.GetPiece();
        os << " jump over piece at " << *p;
    }
    else os << std::endl;

    return os;
}