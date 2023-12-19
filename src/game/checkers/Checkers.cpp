#include "../../../include/game/checkers/Checkers.hpp"
#include "../../../include/GameType.hpp"
#include "../../../include/exception/InvalidUsageException.hpp"
#include "../../../include/exception/InvalidCoordinatesException.hpp"

#include <algorithm>
#include <random>

Checkers::Checkers() {}

Checkers::~Checkers() {}

void Checkers::SwitchPlayer() {
    if (m_currentPlayer == m_players[CheckersConstants::PLAYER_ONEID])
        m_currentPlayer = m_players[CheckersConstants::PLAYER_TWOID];
    else m_currentPlayer = m_players[CheckersConstants::PLAYER_ONEID];

    m_flags.CurrentPlayerChanged();
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
        m_flags.ResetPieceCapturedFlag();
    }
    else {
        if (m_flags.m_isPieceSelected)
            DeselectPiece();
    }
}

bool Checkers::IsPieceOfCurrentPlayer(std::pair<int, int> coord) const
{
    auto piece = GetPiece(coord);
    auto idCurrentPlayer = m_currentPlayer->GetId();

    auto pieceOwner = piece->GetOwner();
    if (pieceOwner == nullptr) return false;
    auto idPieceOwner = pieceOwner->GetId();

    return idCurrentPlayer == idPieceOwner;
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

    m_status.SetSelectedPiece(coord);
    auto possibleMoves = GetPossibleMoves(coord.first, coord.second);
    m_status.SetPossibleMoves(possibleMoves);
    m_flags.PieceIsSelected();
}
void Checkers::DeselectPiece()
{
    std::cout << "DeselectPiece" << std::endl;

    m_status.SaveLastPossibleMoves();
    m_status.SaveLastSelectedPiece();
    m_flags.SelectPieceChanged();
    m_flags.PieceIsNotSelected();
    m_status.ResetSelectedPiece();
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

    // Si il y a une capture, on supprime la piece capturée
    // Le joueur courant peut rejouer avec la meme piece
    if (CheckCapture(coord))
    {
        m_flags.m_isPieceCaptured = true;
    }

    // Si la piece est un pion, on teste si elle peut se promouvoir
    if (CanPromotePiece(coord))
    {
        PromotePiece(coord);
    }
    
    DeselectPiece();
    
    // On met à jour les mouvements possibles
    UpdatePossibleMoves();

    m_flags.BoardNeedUpdate();
}
bool Checkers::CheckCapture(std::pair<int, int> coord)
{
    bool capt = false;

    auto piece = GetPiece(coord);
    auto possibleCaptures = piece->GetPossibleCaptures();
    
    if (possibleCaptures.empty()) return false;

    for (const auto& [captx, capty]: possibleCaptures)
    {
        int x = coord.first - captx;
        int y = coord.second - capty;

        auto c = std::make_pair(x, y);
        if (!AreCoordinatesValid(c)) continue;

        auto pieceCapture = GetPiece(c);

        if (pieceCapture->GetSymbol() != CheckersConstants::TRANSPARENT
            && piece->GetSymbol() != pieceCapture->GetSymbol())
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
    // Un pion devient une dame si il atteint la dernière ligne du plateau adverse
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::CanPromotePiece() : coord are invalid");

    auto piece = GetPiece(coord);

    if (piece->IsPromoted()) return false;
    if (piece->GetSymbol() == CheckersConstants::TRANSPARENT) return false;

    auto x = piece->GetX();

    if (piece->GetSymbol() == CheckersConstants::WHITE) return (x == CheckersConstants::BOARD_UPPER_LIMIT);
    else return (x == CheckersConstants::BOARD_LOWER_LIMIT);
}

void Checkers::PromotePiece(std::pair<int, int> coord)
{
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::PromotePiece() : coord are invalid");

    auto piece = GetPiece(coord);

    piece->Promote();

    m_flags.BoardNeedUpdate();
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
    m_players.push_back(std::make_shared<Player>());
    m_players.push_back(std::make_shared<Player>());

    // On définit le joueur courant
    m_currentPlayer = m_players[CheckersConstants::PLAYER_ONEID];

    // Solution pour choisir un joueur au hasard
    /*std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dis(0, 1);
    int random = dis(g);

    m_currentPlayer = m_players[random];*/
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

void Checkers::GameStart()
{
    m_flags.m_isGameStarted = true;
}

void flagsmodel_t::PieceIsSelected()
{
    m_isPieceSelected = true;
}
void flagsmodel_t::PieceIsNotSelected()
{
    m_isPieceSelected = false;
}
void flagsmodel_t::CurrentPlayerChanged()
{
    m_currentPlayerChanged = true;
}
void flagsmodel_t::SelectPieceChanged()
{
    m_selectedPieceChanged = true;
}
void flagsmodel_t::BoardNeedUpdate()
{
    m_boardNeedUpdate = true;
}

void Checkers::ResetCurrentPlayerChangedFlag()
{
    m_flags.m_currentPlayerChanged = false;
}
void flagsmodel_t::ResetPieceCapturedFlag()
{
    m_isPieceCaptured = false;
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

std::shared_ptr<Player> Checkers::GetCurrentPlayer() const
{
    return m_currentPlayer;
}
CheckersPiece* Checkers::GetPiece(std::pair<int, int> coord) const
{
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Checkers::GetPiece(): coord are invalid");

    auto x = coord.first;
    auto y = coord.second;

    return m_board->GetValueAt(x, y);
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