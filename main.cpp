#include <iostream>
#include <algorithm>
#include <limits>


int minimax(int size, char tab[9][9], int depth, bool maxPlayer, int win, int alpha, int beta);
int isEnd(int size, char tab[9][9], int win);
int* bestMove(int size, char tab[9][9], int depth, int a, int b, int win);

int* bestMove(int size, char tab[9][9], int depth, int a, int b, int win){
    int bestScore = (-1)*std::numeric_limits<int>::max();
    auto move = new int[2];
    for(int r = 0; r < size; r++){
        for(int c = 0; c < size; c++){
            if(tab[r][c] == ' '){
                tab[r][c] = 'x';
                int score = minimax(size, tab, depth, false, win, a, b);
                tab[r][c] = ' ';
                if(score > bestScore){
                    bestScore = score;
                    move[0] = r;
                    move[1] = c;
                }
            }
        }
    }
    return move; // zmienic
}

int minimax(int size, char tab[9][9], int depth, bool maxPlayer, int win, int alpha, int beta){
    int winner = isEnd(size, tab, win);
    if(winner != 0 || depth == 0) return winner;

    if(maxPlayer) {
        int bestScore = (-1)*std::numeric_limits<int>::max();
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (tab[r][c] == ' ') {
                     tab[r][c] = 'x';
                    int score = minimax(size, tab, depth - 1, false, win, alpha, beta);
                    tab[r][c] = ' ';
                    bestScore = std::max(bestScore, score);
                    alpha = std::max(alpha, score);
                    if(beta <= alpha) break;
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = std::numeric_limits<int>::max();
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (tab[r][c] == ' ') {
                     tab[r][c] = 'o';
                    int score = minimax(size, tab, depth - 1, true, win, alpha, beta);
                    tab[r][c] = ' ';
                    bestScore = std::min(bestScore, score);
                    beta = std::min(beta, score);
                    if(beta <= alpha) break;
                }
            }
        }
        return bestScore;
    }
}


int isEnd(int size, char tab[9][9], int win){
    int ctr = 0;
    int w;
    for(int r = 0; r < size; r++){
        for(int c = 0; c < size; c++){
            if(tab[r][c] == 'x' || tab[r][c] == 'o'){
                for(w = 0; w < win; w++){
                    if(tab[r][c] == tab[r+w][c] && r+w < size) {
                        ctr++;
                    }
                    else {
                        ctr = 0;
                        break;
                    }
                }
                if(ctr == win){
                    if(tab[r][c] == 'x') return 1;
                    if(tab[r][c] == 'o') return -1;
                }
                for(w = 0; w < win; w++){
                    if(tab[r][c] == tab[r][c+w] && c+w < size) {
                        ctr++;
                    }
                    else {
                        ctr = 0;
                        break;
                    }
                }
                if(ctr == win){
                    if(tab[r][c] == 'x') return 1;
                    if(tab[r][c] == 'o') return -1;
                }
                for(w = 0; w < win; w++){
                    if(tab[r][c] == tab[r+w][c+w] && r+w < size){
                        ctr++;
                    }
                    else {
                        ctr = 0;
                        break;
                    }
                }
                if(ctr == win){
                    if(tab[r][c] == 'x') return 1;
                    if(tab[r][c] == 'o') return -1;
                }
                for(w = 0; w < win; w++){
                    if(tab[r][c] == tab[r-w][c+w] && r-w >= 0 && c+w < size){
                        ctr++;
                    }
                    else {
                        ctr = 0;
                        break;
                    }
                }
                if(ctr == win){
                    if(tab[r][c] == 'x') return 1;
                    if(tab[r][c] == 'o') return -1;
                }
            }
        }
    }
    return 0;
}



int main() {
    int size, match;
    char board [9][9];

//--------------introduction------------------
    std::cout<<"\nWelcome to the tic-tac-toe game.\n\nFirst please type the preferred size of the board (3 - 9): ";
    std::cin>>size;
    std::cout<<"\nNow decide how many symbols standing one by one win: ";
    std::cin>>match;
    while(match > size){
        std::cout<<"\nNumber of winning symbols cannot be bigger than size of the board.\nTry again: ";
        std::cin>>match;
    }
    std::cout<<"\nThank you. Here are some things you need to know: \n1. You are playing with an \'o\', AI is playing with an \'x\'\n"
               "2. You will be asked where to place your symbol: row is horizontal, column is vertical.\n"
               "3. Rows' and columns' indexes starts from 0.\n"
               "4. It is a console game, so the interface is not as beautiful as the inside :)\n"
               "5. Your board looks like this: \n";
    for(int r = 0; r<size; r++)
    {
        for(int c=0; c<size;c++){
            board[r][c] = ' ';
        }
    }
    for(int r = 0; r<size; r++)
    {
        std::cout<<"|";
        for(int c=0; c<size;c++){
            std::cout<<board[r][c]<<"|";
        }
        std::cout<<"\n------------\n";
    }
std::cout<<"\n 6. Good luck in beating the game!\n";


//----------------------------------------------


int col=10, row=10;
    std::cout<<"---------------------------------\n x starts\n \n";
    for(int i = 0; i < size*size; i++){
        if(i%2){
            std::cout<<"your row: ";
            std::cin>>row;
            while(row >= size){
                if(row >= size) std::cout<<"Index too high.";
                std::cout<<"your row: ";
                std::cin>>row;
            }
            std::cout<<"your column: ";
            std::cin>>col;
            while(col >= size){
                if(col >= size) std::cout<<"Index too high.";
                std::cout<<"your column: ";
                std::cin>>col;
            }

            if(board[row][col] == ' ') board[row][col] = 'o';
            else {
                std::cout<<"\nThis place is taken. Try another one.\n";
                i--;
            }
        }
        else {
            std::cout<<"AI's move: \n";
            row = bestMove(size, board, 12, std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), match)[0];
            col = bestMove(size, board, 12, std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), match)[1];
            board[row][col] = 'x';
        }

        for(int r = 0; r<size; r++)
        {
            std::cout<<"|";
            for(int c=0; c<size;c++){
                std::cout<<board[r][c]<<"|";
            }
            std::cout<<"\n------------\n";
        }
        int result = isEnd(size, board, match);
        if(result == 1) {
            std::cout<<"AI won! Better luck next time.\n";
            break;
        }
        else if(result == -1) {
            std::cout<<"You won! Congratulations.\n";
            break;
        }
    }
    if(isEnd(size, board, match)==0) std::cout<<"Tie! Good job.\n";


    //---------------------------------

    return 0;
}
