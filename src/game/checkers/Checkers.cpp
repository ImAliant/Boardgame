#include "../../../include/game/checkers/Checkers.hpp"
#include "../../include/GameType.hpp"
#include "../../include/exception/InvalidUsageException.hpp"
#include "../../include/exception/InvalidCoordinatesException.hpp"

#include <algorithm>

Checkers::Checkers() {}

Checkers::~Checkers() {}

void Checkers::SwitchPlayer() {
    if (m_currentPlayer == m_players[static_cast<int>(Players::PLAYER_ONE)]) {
        m_currentPlayer = m_players[static_cast<int>(Players::PLAYER_TWO)];
    }
    else {
        m_currentPlayer = m_players[static_cast<int>(Players::PLAYER_ONE)];
    }
}

void Checkers::Turn(std::pair<int, int> coord) {
    std::cout << "Turn" << std::endl;
    // On teste si la partie est déjà terminée
    if (m_isGameFinished) {
        throw InvalidUsageException("Checkers::Turn() : m_isGameFinished is true");
    }
    // On teste si la partie n'est pas encore commencée
    if (!m_isGameStarted) {
        throw InvalidUsageException("Checkers::Turn() : m_isGameStarted is false");
    }
    // On teste si les coordonnées sont valides
    if (!AreCoordinatesValid(coord)) {
        throw InvalidCoordinatesException("Checkers::Turn() : coord are invalid");
    }

    std::cout << "coord: " << coord.first << ", " << coord.second << std::endl;

    // Si la coordonnée est une piece du joueur courant
    if (IsPieceOfCurrentPlayer(coord)) {
        SelectPiece(coord);
    }
    else if (IsMovePossible(coord))
    {
        // Si le mouvement est possible alors on déplace la piece
        ApplyMove(coord);
    }
    else {
        if (m_isPieceSelected)
            DeselectPiece();
    }
}

bool Checkers::IsPieceOfCurrentPlayer(std::pair<int, int> coord) const
{
    auto currentPlayer = m_currentPlayer->getPlayer();
    auto piece = m_board->getValueAt(coord.first, coord.second);

    if (piece->getOwner().getPlayer() == currentPlayer) return true;
    
    return false;
}

bool Checkers::IsMovePossible(std::pair<int, int> coord) const
{
    std::cout << "IsMovePossible" << std::endl;
    // On teste si la piece est selectionnée
    if (!IsPieceSelected()) {
        throw InvalidCoordinatesException("Checkers::IsMovePossible() : m_selectedPiece is invalid");
    }

    // On teste si la piece peut se déplacer à la coordonnée
    auto possibleMoves = GetPossibleMoves(m_selectedPiece.first, m_selectedPiece.second);
    return std::find(possibleMoves.begin(), possibleMoves.end(), coord) != possibleMoves.end();
}

void Checkers::CheckForWin() {
    // TODO
}

void Checkers::SelectPiece(std::pair<int, int> coord)
{
    std::cout << "SelectPiece: " << coord.first << ", " << coord.second << std::endl;
    // On teste si la piece est selectionnée
    if (m_isPieceSelected) {
        DeselectPiece();
    }

    m_selectedPiece = coord;
    m_isPieceSelected = true;
}
void Checkers::DeselectPiece()
{
    std::cout << "DeselectPiece" << std::endl;
    m_lastPossibleMoves = GetPossibleMoves(m_selectedPiece.first, m_selectedPiece.second);
    m_selectedPieceChanged = true;
    m_lastSelectedPiece = m_selectedPiece;
    m_isPieceSelected = false;
    m_selectedPiece = {-1, -1};
}
void Checkers::ApplyMove(std::pair<int, int> coord)
{
    // On teste si la piece est selectionnée
    if (!IsPieceSelected())
    {
        throw InvalidCoordinatesException("Checkers::ApplyMove() : m_selectedPiece is invalid");
    }
    
    // On teste si le mouvement est possible
    if (!IsMovePossible(coord))
    {
        return;
    }

    // Si la piece est un pion, on teste si elle peut se promouvoir
    if (GetPieceType(m_selectedPiece.first, m_selectedPiece.second) == PieceType::PAWN)
    {
        if (CanPromotePiece(coord))
        {
            PromotePiece();
        }
    }

    // On déplace la piece
    auto piece = m_board->getValueAt(m_selectedPiece.first, m_selectedPiece.second);
    m_board->movePiece(m_selectedPiece.first, m_selectedPiece.second, coord.first, coord.second);
}
void Checkers::PromotePiece(/**/)
{

}
void Checkers::CapturePiece(int x, int y)
{

}
void Checkers::RemovePiece(int x, int y)
{

}

void Checkers::InitPlayers() {
    // On teste si les joueurs sont déjà initialisés
    if (!m_players.empty()) {
        m_players.clear();
    }

    // On crée les joueurs
    m_players.push_back(std::make_shared<Player>(Players::PLAYER_ONE));
    m_players.push_back(std::make_shared<Player>(Players::PLAYER_TWO));
    m_players.push_back(std::make_shared<Player>(Players::NONE));

    // On définit le joueur courant
    m_currentPlayer = m_players[static_cast<int>(Players::PLAYER_ONE)];
}

void Checkers::InitBoard() {
    // On teste si le board est déjà initialisé
    if (m_board != nullptr) {
        m_board.reset();
    }
    // On teste si les joueurs sont bien initialisés
    if (m_players.empty()) {
        throw std::runtime_error("Checkers::InitBoard() : m_players is empty");
    }

    m_board = std::make_unique<Board>(GameType::CHECKERS, m_players);

    int row = m_board->getRows();
    int col = m_board->getCols();

    if (row != 10 || col != 10) {
        throw std::runtime_error("Checkers::InitBoard() : row and col have incorrect values");
    }
}

void Checkers::UpdatePossibleMoves() const
{
    auto rows = m_board->getRows();
    auto cols = m_board->getCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            m_board->getValueAt(i, j)->findPossibleMoves(*m_board);
        }
    }
}

void Checkers::GameStart()
{
    m_isGameStarted = true;
}

void Checkers::ResetSelectedPieceFlag()
{
    m_selectedPieceChanged = false;
}

bool Checkers::AreCoordinatesValid(std::pair<int, int> coord) const
{
    return coord.first >= 0 && coord.first < 10 && coord.second >= 0 && coord.second < 10;
}

// getters
std::shared_ptr<Player> Checkers::GetCurrentPlayer() const
{
    return m_currentPlayer;
}
std::shared_ptr<Player> Checkers::GetPlayer(Players player) const
{
    return m_players[static_cast<int>(player)];
}
Piece& Checkers::GetPiece(int x, int y) const
{
    return *m_board->getValueAt(x, y);
}
std::vector<std::pair<int, int>> Checkers::GetPossibleMoves(int x, int y) const
{
    //
    std::cout << "GetPossibleMoves" << std::endl;
    std::cout << "x: " << x << ", y: " << y << std::endl;

    return m_board->getValueAt(x, y)->getPossibleMoves();
}
/*std::vector<std::pair<int, int>> Checkers::GetPossibleCaptures(int x, int y) const
{
    // TODO
}*/
std::unique_ptr<Board>& Checkers::GetBoard()
{
    return m_board;
}
bool& Checkers::IsGameStarted()
{
    return m_isGameStarted;
}
std::pair<int, int> Checkers::GetSelectedPiece() const
{
    return m_selectedPiece;
}
std::pair<int, int> Checkers::GetLastSelectedPiece() const
{
    return m_lastSelectedPiece;
}
bool Checkers::IsPieceSelected() const
{
    return m_isPieceSelected;
}
bool Checkers::IsSelectedPieceChanged() const
{
    return m_selectedPieceChanged;
}
std::vector<std::pair<int, int>> Checkers::GetLastPossibleMoves() const
{
    return m_lastPossibleMoves;
}