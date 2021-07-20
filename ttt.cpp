#include <iostream>
#include <stdlib.h>
#include <vector>

class Game{
        char value; // For object attack name / Name
        static std::vector<std::vector<char>> board;
    public:
        Game(char _value): value(_value){} // basic constructor member initializer
        char return_value(void){
            return value;
        }
        static void print(void){
            for(uint8_t y = 0; y < board.size(); y++){
                std::cout<<"\t\t\t"<<y+1<<" ";
                for(char x: board.at(y)){
                    std::cout<<x<<" ";
                }
                std::cout<<"\n";
            }
            std::cout<<"\t\t\t  1 2 3\n";
        }
        void place(void){
            int y, x;
            std::cout<<value<<": ";
            if(!(std::cin >> y >> x)) exit(1);
            if(y <= 0 || x <= 0 || y >= 4 || x >= 4 || board.at(y-1).at(x-1) != '_'){
                place();
                return;
            }
            board.at(y-1).at(x-1) = value;
        }
        bool check(void){
            // Horizontally
            int c=0;
            for(std::vector<char> y: board){
                for(char x: y){
                    if(c >= 1){
                        if(x == value) c++;
                        else break;
                        if(c==3) return true;
                        continue;
                    }
                    c += (x == value);
                }
                c=0;
            }
            // Vertically
            for(uint8_t y = 0; y < board.size(); y++){
                for(uint8_t x = 0; x < board.at(y).size(); x++){
                    if(c >= 1){
                        if(board.at(x).at(y) == this->value)c++;
                        else break;
                        if(c==3) return true;
                        continue;
                    }
                    c += (board.at(x).at(y) == this->value);
                }
                c=0;
            }
            // Diaganolly
            // North-West - South-East
            for(uint8_t y = 0; y < board.size(); y++){
                if(c >= 1){
                    if(board.at(y).at(y) == this->value) c++;
                    else break;
                    if(c==3) return true;
                    continue;
                }
                c += (board.at(y).at(y) == this->value);
            }
            c=0;
            // North-East - South-West
            for(uint8_t y=0, x=board.size()-1; y < board.size(); y++, x--){
                if(c >= 1){
                    if(board.at(y).at(x) == this->value)c++;
                    else break;
                    if(c==3) return true;
                    continue;
                }
                c += (board.at(y).at(x) == this->value);
            }
            return false;
        }

        static bool end_if_filled(void){
            for(std::vector<char> y: board) for(char x: y) if(x == '_') return false;
            return true;
        }
};

std::vector<std::vector<char>> Game::board = {
    {'_', '_', '_'},
    {'_', '_', '_'},
    {'_', '_', '_'}
};

int main(){
    Game player_1('x');
    Game player_2('o');
    while(true){
        // Player 1
        player_1.place();
        Game::print();
        if(player_1.check()){
            std::cout<<player_1.return_value()<<" has won!\n";
            return 1;
        }
        if(Game::end_if_filled()){
            std::cout<<"Draw.\n";
            return 0;
        }
        // Player 2
        player_2.place();
        Game::print();
        if(player_2.check()){
            std::cout<<player_2.return_value()<<" has won!\n";
            return 1;
        }
        if(Game::end_if_filled()){
            std::cout<<"Draw.\n";
            return 0;
        }
    }
}