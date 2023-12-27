#include "../../../include/game/butin/Butin.hpp"
#include "../../../include/exception/InvalidUsageException.hpp"
#include "../../../include/exception/InvalidCoordinatesException.hpp"

#include <algorithm>

Butin::Butin() {}

Butin::~Butin() {}

bool Butin::IsFirstRound() const 
{
    return m_flags.m_isFirstRound;
}
void Butin::EndFirstRound() 
{
    m_flags.m_isFirstRound = false;
}

void Butin::SwitchPlayer() 
{
    if (m_status.m_currentPlayer == m_players[GameConstants::PLAYER_ONEID])
        m_status.m_currentPlayer = m_players[GameConstants::PLAYER_TWOID];
    else m_status.m_currentPlayer = m_players[GameConstants::PLAYER_ONEID];
    
    m_flags.CurrentPlayerChanged();
}


void Butin::Turn(coord_t coord) 
{
    if (IsGameFinished()) 
    {
        throw InvalidUsageException("Butin::Turn() : m_isGameFinished is true");
    }
    if (!IsGameStarted() ) 
    {
        throw InvalidUsageException("Butin::Turn() : m_isGameStarted is false");
    }
    if (!AreCoordinatesValid(coord)) 
    {
        throw InvalidCoordinatesException("Butin::Turn() : coord are invalid");
    }

    /*if (IsFirstRound())
        HandleFirstRoundSelection(coord);
    else {    
        if(IsMovePossible(coord) && IsPieceSelected())
        {
            ApplyMove(coord);
            if(CheckForWinner())
            {  
                m_flags.GameFinished();
                
            }
        }
        
        if (m_flags.m_isPieceSelected)
            DeselectPiece();
        else{
            SelectPiece(coord);
            
            m_board->GetValueAt(coord)->FindPossibleMoves(*m_board);
        }
    }*/

    if (IsFirstRound()) HandleFirstRoundSelection(coord);
    else 
    {
        if (IsMovePossible(coord) && IsPieceSelected())
        {
            PerformMove(coord);

            if (CheckForWinner())
            {
                m_flags.GameFinished();
            }
        }

        if (m_flags.m_isPieceSelected)
            DeselectPiece();
        else
        {
            SelectPiece(coord);
            m_board->GetValueAt(coord)->FindPossibleMoves(*m_board);
        }
    }
}

void Butin::Init()
{
    InitPlayers();
    InitBoard();
    UpdatePossibleMoves();
}

void Butin::UpdatePossibleMoves() const
{
    auto rows = m_board->GetRows();
    auto cols = m_board->GetCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) 
        {
            const auto& coord = std::make_pair(i, j);
            const auto& piece = GetPiece(coord);
            if (piece == nullptr) continue;

            piece->FindPossibleMoves(*m_board);
        }
    }
}



void Butin::InitPlayers() 
{
    // On teste si les joueurs sont déjà initialisés
    if (!m_players.empty()) {
        m_players.clear();
    }

    // On crée les joueurs
    m_players.push_back(std::make_shared<Player>());
    m_players.push_back(std::make_shared<Player>());
    m_players.push_back(std::make_shared<Player>());

    // On définit le joueur courant
    m_status.m_currentPlayer = m_players[GameConstants::PLAYER_ONEID];
}

void Butin::InitBoard() 
{
    // On teste si le board est déjà initialisé
    if (m_board != nullptr) {
        m_board.reset();
    }
    // On teste si les joueurs sont bien initialisés
    if (m_players.empty()) {
        throw std::runtime_error("Butin::InitBoard() : m_players is empty");
    }

    m_board = std::make_unique<ButinBoard>(m_players);

    int row = m_board->GetRows();
    int col = m_board->GetCols();

    if (row != 8 || col != 8) {
        throw std::runtime_error("Butin::InitBoard() : row and col have incorrect values");
    }
}

void Butin::GameStart()
{
    m_flags.m_isGameStarted = true;
}

void Butin_flagsmodel_t::BoardNeedUpdate()
{
    m_boardNeedUpdate = true;
}

void Butin::ResetBoardNeedUpdateFlag()
{
    m_flags.m_boardNeedUpdate = false;
}

std::shared_ptr<Player> Butin::GetCurrentPlayer() const
{
    return m_status.m_currentPlayer;
}

ButinPiece* Butin::GetPiece(coord_t coord) const
{
    if (!AreCoordinatesValid(coord))
        throw InvalidCoordinatesException("Butin::GetPiece(): coord are invalid");

    auto x = coord.first;
    auto y = coord.second;

    return m_board->GetValueAt(coord);
}


std::unique_ptr<ButinBoard>& Butin::GetBoard()
{
    return m_board;
}

bool& Butin::IsGameStarted()
{
    return m_flags.m_isGameStarted;
}
void Butin_flagsmodel_t::GameFinished()
{
    m_isGameFinished = true;

}
bool& Butin::IsGameFinished()
{
    return m_flags.m_isGameFinished;
}

bool Butin::IsBoardNeedUpdate() const
{
    return m_flags.m_boardNeedUpdate;
}

bool Butin::IsCurrentPlayerChanged() const
{
    return m_flags.m_currentPlayerChanged;
}


bool Butin::AreCoordinatesValid(coord_t coord) const
{
    return coord.first >= 0 && coord.first < 10 && coord.second >= 0 && coord.second < 10;
}

void Butin::HandleFirstRoundSelection(coord_t coord) 
{    
    //char pieceColor = m_board->GetValueAt(coords.first,coords.second)->GetSymbol();
    const auto& piece = GetPiece(coord);
    if (piece == nullptr) return;

    char color = piece->GetSymbol();

    if (color == GameConstants::ButinConstants::BUTIN_YELLOW) { // 'Y' represents a yellow piece
        m_board->RemovePiece(coord); // Remove the piece from the board
        m_status.m_currentPlayerIndex++; // Increment the current player index
        SwitchPlayer(); // Switch to the next player
        m_flags.BoardNeedUpdate();
        EndFirstRoundIfNeeded(); // Check if the first round should end
    }
}

void Butin::EndFirstRoundIfNeeded() 
{   
    int numberOfPlayers=m_players.size();
   
   if(m_status.m_currentPlayerIndex >= numberOfPlayers){
        EndFirstRound();
        m_status.m_currentPlayerIndex = 1;
        
    }    
}
    

std::vector<std::pair<int, int>> Butin::GetPossibleMoves(coord_t coord) const
{       
    return m_board->GetValueAt(coord)->GetPossibleMoves();
}


void Butin::SelectPiece(coord_t coord) 
{
    // Check if a piece is already selected
    if (m_flags.m_isPieceSelected) {
        DeselectPiece();
    }
   
    auto piece = GetPiece(coord);
    if (piece == nullptr) return;

    if (piece->GetSymbol() != GameConstants::ButinConstants::BUTIN_YELLOW) return;
    
    m_status.m_currentPossibleMoves = GetPossibleMoves(coord);
    SetSelectedPiece(coord);
    m_flags.PieceIsSelected();   
}

void Butin::DeselectPiece() {
    m_status.SaveLastPossibleMoves();
    m_flags.SelectPieceChanged();
    m_status.SaveLastSelectedPiece();
    m_flags.PieceIsNotSelected();
    SetSelectedPiece(std::make_pair(-1, -1));
}

bool Butin::IsMovePossible(coord_t coord) const
{
    // On teste si la piece est selectionnée
    if (!IsPieceSelected()) {
        return false;
    }
    
    /*if(m_board->GetValueAt(m_status.m_selectedPiece.first, m_status.m_selectedPiece.second)->GetSymbol() != 'Y'){
        return false;
    }*/

    auto piece = GetPiece(m_status.m_selectedPiece);
    if (piece == nullptr) return false;

    if (piece->GetSymbol() != GameConstants::ButinConstants::BUTIN_YELLOW) return false;

    // On teste si la piece peut se déplacer à la coordonnée
    auto possibleMoves = GetPossibleMoves(m_status.m_selectedPiece);
    return std::find(possibleMoves.begin(), possibleMoves.end(), coord) != possibleMoves.end();
}




// Helper methods to manage selected piece
void Butin::SetSelectedPiece(coord_t coord) {
    m_status.m_selectedPiece = coord;
}


bool Butin::IsPieceSelected() const
{
    return m_flags.m_isPieceSelected;
}

bool Butin::IsSelectedPieceChanged() const
{
    return m_flags.m_selectedPieceChanged;
}


std::pair<int, int> Butin::GetSelectedPiece() const
{
    return m_status.m_selectedPiece;
}

void Butin_flagsmodel_t::PieceIsSelected()
{
    m_isPieceSelected = true;
}
void Butin_flagsmodel_t::PieceIsNotSelected()
{
    m_isPieceSelected = false;
}
void Butin_flagsmodel_t::CurrentPlayerChanged()
{
    m_currentPlayerChanged = true;
}
void Butin_flagsmodel_t::SelectPieceChanged()
{
    m_selectedPieceChanged = true;
}
void Butin_flagsmodel_t::PieceMoved() 
{
    m_pieceMoved = true;
}
bool Butin::hasPieceMoved() const
{
    return m_flags.m_pieceMoved;
}
std::pair<int, int> Butin::GetLastSelectedPiece() const
{
    return m_status.m_lastSelectedPiece;
}

std::vector<std::pair<int, int>> Butin::GetLastPossibleMoves() const
{
    return m_status.m_lastPossibleMoves;
}

void Butin::ResetSelectedPieceFlag()
{
    m_flags.m_selectedPieceChanged = false;
}



void Butin::PerformMove(coord_t coord)
{
    // On teste si la piece est selectionnée
    if (!IsPieceSelected())
    {
        throw InvalidCoordinatesException("Butin::ApplyMove() : m_selectedPiece is invalid");
    }
    
    // On teste si le mouvement est possible
    if (!IsMovePossible(coord))
    {
        return;
    }

    // On déplace la piece
    int jumpedX = (m_status.m_selectedPiece.first + coord.first) / 2;
    int jumpedY = (m_status.m_selectedPiece.second + coord.second) / 2;
    const auto& jump = std::make_pair(jumpedX, jumpedY);
    UpdatePlayerScore(m_board->GetValueAt(jump)->GetSymbol());
    m_board->MovePiece(m_status.m_selectedPiece, coord);
    
    m_flags.m_pieceMoved = true;
     
    DeselectPiece();
    
    // On met à jour les mouvements possibles
    UpdatePossibleMoves();

    m_flags.BoardNeedUpdate();
}


void Butin::UpdatePlayerScore(char pieceType) 
{
    int scoreIncrement = 0;
    switch (pieceType) {
        case GameConstants::ButinConstants::BUTIN_YELLOW:
            scoreIncrement = 1; // Yellow piece is 1 point
            break;
        case GameConstants::ButinConstants::BUTIN_RED:
            scoreIncrement = 2; // Red piece is 2 points
            break;
        case GameConstants::ButinConstants::BUTIN_BLACK:
            scoreIncrement = 3; // Black piece is 3 points
            break;
        default:
            return; 
    }
    m_status.m_currentPlayer->AddScore(scoreIncrement);
    std::cout << "Score: " << m_status.m_currentPlayer->GetScore() << std::endl;
}

bool Butin::CheckForWinner() const 
{
    //Check if there is no possible move in the board
    auto rows = m_board->GetRows();
    auto cols = m_board->GetCols();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            const auto& piece = GetPiece(std::make_pair(i, j));
            if (piece == nullptr) continue;

            if (piece->GetSymbol() == GameConstants::ButinConstants::BUTIN_YELLOW) 
            {
                if (!piece->GetPossibleMoves().empty()) 
                {
                    return false;
                }
            }
        }
    
    }
    return true;
}


Player* Butin::DetermineWinner()  
{
    Player* winner = nullptr;
    if (m_players[GameConstants::PLAYER_ONEID]->GetScore() > m_players[GameConstants::PLAYER_TWOID]->GetScore()) {
        winner = m_players[GameConstants::PLAYER_ONEID].get();
        
    }
    else if (m_players[GameConstants::PLAYER_ONEID]->GetScore() < m_players[GameConstants::PLAYER_TWOID]->GetScore()) {
        winner = m_players[GameConstants::PLAYER_TWOID].get();
    }

    setWinner(winner);
    setWinnerScore(winner->GetScore());
    return winner;
}

Player* Butin::GetWinner() const 
{
    return m_status.m_winner;
}

void Butin::setWinner(Player* winner) 
{
    m_status.m_winner = winner;
}

void Butin::setWinnerScore(int score) 
{
    m_status.m_winnerScore = score;
}

int Butin::getWinnerScore() const 
{
return m_status.m_winnerScore;
}