#include "../include/CheckersGame.hpp"
#include "../include/CheckersPiece.hpp"
#include "../include/Player.hpp"
#include "../include/Piece.hpp"
#include "../include/Board.hpp"
#include <iostream>

CheckersGame::CheckersGame() 
{
    std::cout << "CheckersGame::CheckersGame()" << std::endl;
}

// boucle du jeu
void CheckersGame::run() 
{
    Player player1{Players::P1};
    Player player2{Players::P2};
    std::vector<Player*> players{&player1, &player2};
    Board board{ GameType::CHECKERS, players};

    std::cout << board << std::endl;

    

    startGame(board,players);
}

void CheckersGame::startGame(Board& board, std::vector<Player*>& players)
{
    bool isRunning = true;
    int turn{0};
    while (isRunning)
    {
        if (turn % 2 == 0) playTurn(board, *(players[0]));
        else playTurn(board, *(players[1]));

        // TODO :check if game is over
            // TODO : if yes, check who won
                // TODO : if yes, display winner
                // TODO : if no, display draw
            // TODO : isRunning = false;

        turn++;
    }
}

void CheckersGame::playTurn(Board& board, Player& player)
{
    // TODO : movement choice

    std::cout << "Player " <<  player.getPlayerId() << "'s turn" << std::endl;
    std::cout << "Entrez les coordonnées de la pièce à déplacer (ligne col)" << std::endl;
    int ligne, col;
    std::cin >> ligne >> col;
    std::cout<<"before isCordValid"<<std::endl;
    isCordValid(ligne,col);
    std::cout<<"after isCordValid"<<std::endl;
    if(board.getPieceAt(ligne,col) == nullptr)
    {
        std::cout << "Pas de pièce à cet endroit" << std::endl;
        return;
    }
    std::cout<<board.getPieceAt(ligne,col)<<std::endl;
    std::cout<<"before getPlayer"<<std::endl;
    if(board.getPieceAt(ligne,col)->getPlayer().getPlayerId() != player.getPlayerId())
    {
        std::cout<<"after getPlayer"<<std::endl;
        std::cout << "Cette pièce ne vous appartient pas" << std::endl;
        return;
    }
    std::cout<<"before demade de Dest"<<std::endl;
    std::cout << "Entrez les coordonnées de la case de destination (ligne col)" << std::endl;
    int ligne2, col2;
    std::cin >> ligne2 >> col2;
    std::cout<<"before isDestValid"<<std::endl;
    if(isDestValid(ligne,col,ligne2,col2,player,board)){
        board.setValueAt(ligne2,col2,board.getPieceAt(ligne,col).release());
        board.setValueAt(ligne,col,nullptr);
    }else if(canPieceBeEaten(ligne,col,ligne2,col2,player,board))
    {
        board.setValueAt(ligne2,col2,board.getPieceAt(ligne,col).release());
        board.setValueAt(ligne,col,nullptr);
    }
    else
    {
        std::cout << "Déplacement impossible" << std::endl;
        return;
    }
    
   
   
    
}

bool CheckersGame::isCordValid(int ligne,int col)
{
    if(ligne < 0 || ligne > 9 || col < 0 || col > 9)
    {
        std::cout << "Coordonnées invalides" << std::endl;
        return false;
    }
    return true;
}

bool CheckersGame::isDestValid(int ligne1,int col1,int ligne2,int col2,
                                                Player& player,Board& board)
{     
    if(isCordValid(ligne1,col1) && isCordValid(ligne2,col2))
    { 
        if(board.getPieceAt(ligne2,col2) == nullptr && (ligne2==ligne1-1) && (col2==col1+1 || col2==col1-1) 
                                                && !board.getPieceAt(ligne1,col1)->IsKing())
        {
            return true;
        }
        else if (board.getPieceAt(ligne2,col2) == nullptr && board.getPieceAt(ligne1,col1)->IsKing())
        {
            return true;
        }
    }
    return false;
}
//TODO : Ajouter le cas ou la piece est une dame
bool CheckersGame::canPieceBeEaten(int ligne1,int col1,int ligne2,int col2,Player& player,Board& board)
{
    if(board.getPieceAt(ligne1,col1)!= nullptr && board.getPieceAt(ligne2,col2)!=nullptr
                                             && board.getPieceAt(ligne2,col2)->getPlayer().getPlayerId() != player.getPlayerId())
    {
        ;
        if(ligne2==ligne1-1 && col2==col1 + 1 && board.getPieceAt(ligne2-1,col2+1)!=nullptr ){
            
            board.setValueAt(ligne2-1,col2+1,board.getPieceAt(ligne1,col1).release());
            board.setValueAt(ligne1,col1,nullptr);
            return true;
        }else if(ligne2==ligne1-1 && col2==col1 - 1 && board.getPieceAt(ligne2-1,col2-1)!=nullptr)
            {
            board.setValueAt(ligne2-1,col2-1,board.getPieceAt(ligne1,col1).release());
            board.setValueAt(ligne1,col1,nullptr);
            return true;
            }
    }else {return false;}
    return false;
}
CheckersGame::~CheckersGame() 
{
    std::cout << "CheckersGame::~CheckersGame()" << std::endl;
}