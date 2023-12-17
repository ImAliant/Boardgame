#include "../../../include/game/checkers/Checkers.hpp"
#include "../../../include/GameType.hpp"
#include "../../../include/exception/InvalidUsageException.hpp"
#include "../../../include/exception/InvalidCoordinatesException.hpp"

#include <algorithm>

Checkers::Checkers() {}

Checkers::~Checkers() {}

void Checkers::SwitchPlayer() {
    if (m_currentPlayer == m_players[static_cast<int>(Players::PLAYER_ONE)])
        m_currentPlayer = m_players[static_cast<int>(Players::PLAYER_TWO)];
    else m_currentPlayer = m_players[static_cast<int>(Players::PLAYER_ONE)];

    CurrentPlayerChanged();
}

void Checkers::Turn(std::pair<int, int> coord) {
    // On teste si la partie est déjà terminée
    if (IsGameFinished()) {
        throw InvalidUsageException("Checkers::Turn() : m_isGameFinished is true");
    }
    // On teste si la partie n'est pas encore commencée
    if (!IsGameStarted()) {
        throw InvalidUsageException("Checkers::Turn() : m_isGameStarted is false");
    }
    // On teste si les coordonnées sont valides
    if (!AreCoordinatesValid(coord)) {
        throw InvalidCoordinatesException("Checkers::Turn() : coord are invalid");
    }

    // Si la coordonnée est une piece du joueur courant
    if (IsPieceOfCurrentPlayer(coord)) {
        SelectPiece(coord);
    }
    else if (IsMovePossible(coord) && IsPieceSelected())
    {
        // Si le mouvement est possible alors on déplace la piece
        ApplyMove(coord);

        // On teste si la partie est terminée
        CheckForWin();

        // On change de joueur si aucune piece n'a été capturée
        if (!m_flags.m_isPieceCaptured)
            SwitchPlayer();

        // On reset le flag de piece capturée
        ResetPieceCapturedFlag();
    }
    else {
        if (m_flags.m_isPieceSelected)
            DeselectPiece();
    }
}

bool Checkers::IsPieceOfCurrentPlayer(std::pair<int, int> coord) const
{
    auto currentPlayer = m_currentPlayer->getPlayer();
    auto piece = GetPiece(coord);

    return piece.GetOwner().getPlayer() == currentPlayer;
}

bool Checkers::IsMovePossible(std::pair<int, int> coord) const
{
    // On teste si la piece est selectionnée
    if (!IsPieceSelected()) {
        return false;
    }

    // On teste si la piece peut se déplacer à la coordonnée
    auto possibleMoves = GetPossibleMoves(m_status.m_selectedPiece.first, m_status.m_selectedPiece.second);
    return std::find(possibleMoves.begin(), possibleMoves.end(), coord) != possibleMoves.end();
}

void Checkers::CheckForWin() {
    // TODO
}

void Checkers::SelectPiece(std::pair<int, int> coord)
{
    std::cout << "SelectPiece: " << coord.first << ", " << coord.second << std::endl;

    // On teste si la piece est selectionnée
    if (m_flags.m_isPieceSelected) {
        DeselectPiece();
    }

    m_status.m_currentPossibleMoves = GetPossibleMoves(coord.first, coord.second);

    SetSelectedPiece(coord);
    PieceIsSelected();
}
void Checkers::DeselectPiece()
{
    std::cout << "DeselectPiece" << std::endl;

    SaveLastPossibleMoves();
    SelectPieceChanged();
    SaveLastSelectedPiece();
    PieceIsNotSelected();
    SetSelectedPiece(std::make_pair<int, int>(-1, -1));
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

    // On déplace la piece
    m_board->MovePiece(m_status.m_selectedPiece.first, m_status.m_selectedPiece.second, coord.first, coord.second);
    BoardNeedUpdate();

    // Si il y a une capture, on supprime la piece capturée
    // Le joueur courant peut rejouer avec la meme piece
    if (CheckCapture(coord))
    {
        m_flags.m_isPieceCaptured = true;
    }

    // Si la piece est un pion, on teste si elle peut se promouvoir
    if (CanPromotePiece(coord))
    {
        std::cout << "debug 2" << std::endl;
        PromotePiece(coord);
    }
    
    DeselectPiece();
    
    // On met à jour les mouvements possibles
    UpdatePossibleMoves();
}
bool Checkers::CheckCapture(std::pair<int, int> coord)
{
    bool capt = false;

    auto piece = m_board->GetValueAt(coord.first, coord.second);
    auto possibleCaptures = piece->GetPossibleCaptures();
    if (possibleCaptures.empty())
    {
        return false;
    }

    for (const auto& capture: possibleCaptures)
    {
        int x = coord.first - capture.first;
        int y = coord.second - capture.second;

        auto c = std::make_pair(x, y);
        if (!AreCoordinatesValid(c)) continue;

        if (m_board->GetValueAt(x, y)->GetSymbol() != 'T')
        {
            CapturePiece(c);
            capt = true;
        }
    }

    return capt;
}
void Checkers::CapturePiece(std::pair<int, int> coord)
{
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::CapturePiece() : coord are invalid");

    auto x = coord.first;
    auto y = coord.second;

    m_board->RemovePiece(x, y);
}

bool Checkers::CanPromotePiece(std::pair<int, int> coord) const
{  
    std::cout << "debug 1" << std::endl;

    // Un pion devient une dame si il atteint la dernière ligne du plateau adverse
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::CanPromotePiece() : coord are invalid");

    auto piece = GetPiece(coord);

    //
    std::cout << piece.IsPromoted() << std::endl;
    std::cout << piece.GetSymbol() << std::endl;
    //

    if (piece.IsPromoted()) return false;
    if (piece.GetSymbol() == 'T') return false;

    auto x = piece.GetX();
    //
    std::cout << x << std::endl;
    //

    if (piece.GetSymbol() == 'W') return (x == CheckersConstants::BOARD_UPPER_LIMIT);
    else return (x == CheckersConstants::BOARD_LOWER_LIMIT);
}

void Checkers::PromotePiece(std::pair<int, int> coord)
{
    std::cout << "debug 3" << std::endl;

    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::PromotePiece() : coord are invalid");

    auto piece = GetPiece(coord);

    piece.Promote();

    BoardNeedUpdate();
}

void Checkers::Init()
{
    InitPlayers();
    InitBoard();
    UpdatePossibleMoves();
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

    m_board = std::make_unique<CheckersBoard>(m_players);

    int row = m_board->GetRows();
    int col = m_board->GetCols();

    if (row != 10 || col != 10) {
        throw std::runtime_error("Checkers::InitBoard() : row and col have incorrect values");
    }
}

void Checkers::UpdatePossibleMoves() const
{
    auto rows = m_board->GetRows();
    auto cols = m_board->GetCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            m_board->GetValueAt(i, j)->FindPossibleMoves(*m_board);
        }
    }
}

void Checkers::SaveLastPossibleMoves()
{
    m_status.m_lastPossibleMoves = m_status.m_currentPossibleMoves;
}
void Checkers::SaveLastSelectedPiece()
{
    m_status.m_lastSelectedPiece = m_status.m_selectedPiece;
}

void Checkers::GameStart()
{
    m_flags.m_isGameStarted = true;
}

void Checkers::PieceIsSelected()
{
    m_flags.m_isPieceSelected = true;
}
void Checkers::PieceIsNotSelected()
{
    m_flags.m_isPieceSelected = false;
}
void Checkers::CurrentPlayerChanged()
{
    m_flags.m_currentPlayerChanged = true;
}
void Checkers::SelectPieceChanged()
{
    m_flags.m_selectedPieceChanged = true;
}
void Checkers::BoardNeedUpdate()
{
    m_flags.m_boardNeedUpdate = true;
}

void Checkers::ResetCurrentPlayerChangedFlag()
{
    m_flags.m_currentPlayerChanged = false;
}
void Checkers::ResetPieceCapturedFlag()
{
    m_flags.m_isPieceCaptured = false;
}
void Checkers::ResetSelectedPieceFlag()
{
    m_flags.m_selectedPieceChanged = false;
}
void Checkers::ResetBoardNeedUpdateFlag()
{
    m_flags.m_boardNeedUpdate = false;
}

bool Checkers::AreCoordinatesValid(std::pair<int, int> coord) const
{
    return coord.first >= 0 && coord.first < 10 && coord.second >= 0 && coord.second < 10;
}

void Checkers::SetSelectedPiece(std::pair<int, int> coord)
{
    m_status.m_selectedPiece = coord;
}

std::shared_ptr<Player> Checkers::GetCurrentPlayer() const
{
    return m_currentPlayer;
}
CheckersPiece& Checkers::GetPiece(std::pair<int, int> coord) const
{   
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::GetPiece() : coord are invalid");

    auto x = coord.first;
    auto y = coord.second;

    return *m_board->GetValueAt(x, y);
}
std::vector<std::pair<int, int>> Checkers::GetPossibleMoves(int x, int y) const
{
    return m_board->GetValueAt(x, y)->GetPossibleMoves();
}
std::unique_ptr<CheckersBoard>& Checkers::GetBoard()
{
    return m_board;
}
bool& Checkers::IsGameStarted()
{
    return m_flags.m_isGameStarted;
}
std::pair<int, int> Checkers::GetSelectedPiece() const
{
    return m_status.m_selectedPiece;
}
std::pair<int, int> Checkers::GetLastSelectedPiece() const
{
    return m_status.m_lastSelectedPiece;
}
bool Checkers::IsPieceSelected() const
{
    return m_flags.m_isPieceSelected;
}
bool Checkers::IsSelectedPieceChanged() const
{
    return m_flags.m_selectedPieceChanged;
}
std::vector<std::pair<int, int>> Checkers::GetLastPossibleMoves() const
{
    return m_status.m_lastPossibleMoves;
}
bool& Checkers::IsGameFinished()
{
    return m_flags.m_isGameFinished;
}
bool Checkers::IsBoardNeedUpdate() const
{
    return m_flags.m_boardNeedUpdate;
}
bool Checkers::IsCurrentPlayerChanged() const
{
    return m_flags.m_currentPlayerChanged;
}