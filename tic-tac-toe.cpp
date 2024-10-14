#include<bits/stdc++.h>
using namespace std;

class Player{
    private:
    
    
    public:
    string name;
    int id;
    Player(string _name, int _id){
        this->name = _name;
        this->id = _id;
    }
 
};

class Move{

    public:
    int x;
    int y;
    int symbol;
        Move(int _x, int _y, int _s){
            this->x = _x;
            this->y = _y;
            this->symbol = _s;
        }
};

class Board{
    private:
    vector<vector<int>> board;
    int size;
    vector<int> rowSum;
    vector<int> colSum;
    int diagSum;
    int crossDiagSum;
    bool boardFull = false;
    bool boardWon = false;
    int emptyCells;
    
    public:
    Board(int n){
        board.resize(n, vector<int>(n, 0));
        rowSum.resize(n, 0);
        colSum.resize(n, 0);
        diagSum=0;
        crossDiagSum = 0;
        emptyCells = n*n;
    }
    
    void makeMove(Move* move){
        // check for invalidity
        if(!isValid(move)){
            throw runtime_error("Invalid move");
        }
        int x= move->x;
        int y= move->y;
        int sym= move->symbol;
        int n= board.size();
        board[x][y] = sym;
        emptyCells-=1;
        if(emptyCells == 0){
            this->boardFull = true;
        }
        
        rowSum[x] += sym;
        colSum[y] += sym;
        
        if(x == y){
            diagSum+= sym;
        }
        // cross -> x,y (0, n-1); (1, n-2);...(n-1, 0)
        if(x+y == n-1){
            crossDiagSum += sym;
        }
        
        if(abs(rowSum[x])== n or abs(colSum[y]) == n or abs(crossDiagSum) ==n or abs(diagSum)==n){
            this->boardWon = true;
        }
        
    }
    
    bool isValid(Move* move){
        int x= move->x;
        int y= move->y;
        
        if(x<0 or y<0 or x>=board.size() or y>=board.size() or board[x][y]!=0){
            return false;
        }
        return true;
    }
    
    bool isWon(){
        return this->boardWon;
    }
    
    bool isFull(){
        return this->boardFull;
    }
    
    void print(){
        int n= board.size();
        for(int i=0; i<n; i++){
            cout<<endl;
            for(int j=0; j<n; j++){
                cout<<board[i][j]<<" ";
            }
        }
    }
    
};



class Game{
    private:
    Player* p1;
    Player* p2;
    Board* board;;
    
    vector<Move*> moves;
    public:
    Game(Player* _p1, Player* _p2, Board* _board){
        this->board= _board;
        this->p1 = _p1;
        this->board = _board;
    }
    
    void play(){
        while(!board->isFull() and !board->isWon()){
            // get move
            Move* move;
            int x, y;
            if(moves.size() % 2 == 0){
                // Move move = p1.getMove()
                cout<<"player 1 give inputs: \n";
                cin>>x;
                cin>>y;
                move = new Move(x, y, 1);
            }else{
                // Move move = p2.getMove();
                cout<<"player 2 give inputs: \n";
                cin>>x;
                cin>>y;
                move = new Move(x, y, -1);
            }
            
            moves.push_back(move);
            // make move
            try{
                board->makeMove(move);    
            }
            catch(exception e){
                cerr<<" error making move "<<e.what()<<endl;
            }
            board->print();
        }
        if(board->isWon()){
            string winner = (moves.back()->symbol == 1)? p1->name: p2->name;
            cout<<"game won by "<< winner<<endl;
        }else{
            cout<<"no one won! \n";
        }
        if(board->isFull()){
            cout<<"board full! \n";
        }
    }
};


int main() {
    Player* p1= new Player("hulk", 5);
    Player* p2= new Player("spidey", 10);
    Board* b = new Board(3);
    Game g(p1, p2, b);
    
    g.play();
}