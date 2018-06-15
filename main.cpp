#include <iostream>
#include <string>
#include "chess.h"
#include <cstdlib>
#include <ctime>


using namespace std;

std::string array1[size][size] = {{"--", "--", "--", "--", "--", "--", "WK", "--"},
                                 {"--", "--", "--", "--", "--", "--", "--", "--"},
                                 {"--", "--", "WN", "--", "--", "--", "--", "--"},
                                 {"--", "--", "--", "--", "--", "--", "--", "--"},
                                 {"--", "--", "--", "--", "--", "--", "--", "--"},
                                 {"--", "--", "--", "--", "--", "--", "--", "--"},
                                 {"--", "--", "--", "--", "--", "--", "WR", "--"},
                                 {"--", "BK", "--", "--", "--", "--", "--", "WR"}};


string parseMove(string move) {
    move[1] = '8' - move[1] + '0';
    move[3] = '8' - move[3] + '0';
    move[0] = move[0] - 'a' + '0';
    move[2] = move[2] - 'a' + '0';
    swap(move[0], move[1]);
    swap(move[2], move[3]);
    return move;
}


int main() {


    chess ch;

//    for (int i = 0; i < size; i++) {
//        for (int j = 0; j < size; j++) {
//            ch.setField(i, j, array1[i][j]);
//        }
//    }
    //cout << ch.countBlackMaterial() << endl << ch.countWhiteMaterial() << endl;
    string move = "";
    ch.print();
    srand(static_cast<unsigned int>(time(NULL)));

    //cout << ch.isCheck(true) << endl;

    while (!ch.isMate(false)) {

        cout << endl;
        do{
            cout << "input the move " << endl;
            cin >> move;
            move = parseMove(move);
        }while(!ch.isPossibleMove(move, false));

        //cout << move << endl;
        ch.makeMove(move);
        ch.passMove();


        //cout << ch.possibleMoves(false) << endl;
        if (ch.isMate(true))
            break;
        if (ch.isMate(false))
            break;

        int move1 = rand() % ((((ch.possibleMoves(true)).length()-8))/4) * 4;
        ch.makeMove((ch.possibleMoves(true)).substr(move1, 4));
        system("cls");
        ch.print();
    }
    cout << ch.whoMoves() << " win" << endl;

system("pause");
    return 0;
}