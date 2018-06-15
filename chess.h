#include <string>
#include <iostream>

#define size 8
#define field "--"
#define fight "xx"
#define or ||
#define and &&
//#define print_isCheck


using namespace std;


bool in_range(int n) {
    return (n >= 0 && n < 8);
}


class chess {

private:
    string arr[size][size];

    bool is_black_move = false;

    string previousMove[size][size];

    bool kings_not_near(int i1, int j1, int i2, int j2) {
        return !(abs(i2 - i1) < 2 and abs(j2 - j1) < 2);
    }

    double spaceControl() {
        int a = possibleMoves(true).length();
        int b = possibleMoves(false).length();

    }

public:
    string whoMoves() {
        if (is_black_move)
            return "B";
        return "W";
    }

    void passMove() {
        is_black_move = !is_black_move;
    }

    chess() {
        for (int i = 0; i < size; i++) {
            //arr[i] = new char*;
            for (int j = 0; j < size; j++) {
                arr[i][j] = const_cast<char *>(field);
            }
        }
        for (int i = 0; i < size; i++) {
            arr[6][i] = const_cast<char *>("WP");
            arr[1][i] = const_cast<char *>("BP");
        }
        arr[7][0] = const_cast<char *>("WR");
        arr[7][1] = const_cast<char *>("WN");
        arr[7][2] = const_cast<char *>("WB");
        arr[7][3] = const_cast<char *>("WQ");
        arr[7][4] = const_cast<char *>("WK");
        arr[7][5] = const_cast<char *>("WB");
        arr[7][6] = const_cast<char *>("WN");
        arr[7][7] = const_cast<char *>("WR");
        arr[0][0] = const_cast<char *>("BR");
        arr[0][1] = const_cast<char *>("BN");
        arr[0][2] = const_cast<char *>("BB");
        arr[0][3] = const_cast<char *>("BQ");
        arr[0][4] = const_cast<char *>("BK");
        arr[0][5] = const_cast<char *>("BB");
        arr[0][6] = const_cast<char *>("BN");
        arr[0][7] = const_cast<char *>("BR");
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << size - i << " ";
            for (int j = 0; j < size; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        cout << "  ";
        for (int i = 0; i < size; i++) {
            cout << char('a' + i) << "  ";
        }
        cout << endl << endl;
    }

    string getField(int a, int b) {
        return arr[a][b];
    }

    void setField(int a, int b, string val) {
        arr[a][b] = val;
    }

    bool isCheck(bool is_black_move) {

        bool bo = false;
        //string arr1[8][8];
        string arr1[size][size];
        for (int i = 0; i < size; i++) {
            //arr1[i] = new char *[size];
            for (int j = 0; j < size; j++) {
                arr1[i][j] = arr[i][j];
            }
        }

        char attacker_color = 'B';
        char protector_color = 'W';
        if (is_black_move) {
            attacker_color = 'W';
            protector_color = 'B';
        }

        int protector_i = 0;
        int protector_j = 0;
        string protector_king = " K";
        protector_king[0] = protector_color;
        //cout << protector_king;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (arr1[i][j] == protector_king) {
                    protector_i = i;
                    protector_j = j;
                }
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if ((arr1[i][j])[0] == attacker_color) {
                    int i1;
                    int j1;
                    // for rook
                    if ((arr1[i][j])[1] == 'R') {
                        i1 = i;
                        j1 = j;

                        while (i1 >= 0 &&
                               (arr1[i1][j] == field || arr1[i1][j] == protector_king || arr1[i1][j] == fight ||
                                i1 == i)) {
                            arr1[i1][j] = (fight);
                            i1 = i1 - 1;
                        }
                        while (j1 >= 0 &&
                               (arr1[i][j1] == field || arr1[i][j1] == protector_king || arr1[i][j1] == fight ||
                                j1 == j)) {
                            arr1[i][j1] = (fight);
                            j1 = j1 - 1;
                        }
                        i1 = i;
                        j1 = j;

                        while (i1 < size &&
                               (arr1[i1][j] == field || arr1[i1][j] == protector_king || arr1[i1][j] == fight ||
                                i1 == i)) {
                            arr1[i1][j] = (fight);
                            i1 = i1 + 1;
                        }
                        while (j1 < size &&
                               (arr1[i][j1] == field || arr1[i][j1] == protector_king || arr1[i][j1] == fight ||
                                j1 == j)) {
                            arr1[i][j1] = (fight);
                            j1 = j1 + 1;
                        }
                        arr1[i][j][0] = attacker_color;
                        arr1[i][j][1] = 'R';

                        continue;
                    }

                    // for knight
                    if ((arr1[i][j])[1] == 'N') {
                        if (in_range(i - 1) && in_range(j - 2)) {
                            if (arr1[i - 1][j - 2] == field || arr1[i - 1][j - 2] == protector_king) {
                                arr1[i - 1][j - 2] = (fight);
                            }
                        }

                        if (in_range(i - 2) && in_range(j - 1))
                            if (arr1[i - 2][j - 1] == field || arr1[i - 2][j - 1] == protector_king)
                                arr1[i - 2][j - 1] = (fight);
                        if (in_range(i + 2) && in_range(j + 1))
                            if (arr1[i + 2][j + 1] == field || arr1[i + 2][j + 1] == protector_king) {
                                arr1[i + 2][j + 1] = (fight);
                            }
                        if (in_range(i + 1) && in_range(j + 2))
                            if (arr1[i + 1][j + 2] == field || arr1[i + 1][j + 2] == protector_king) {
                                arr1[i + 1][j + 2] = (fight);
                            }

                        if (in_range(i - 2) && in_range(j + 1))
                            if (arr1[i - 2][j + 1] == field || arr1[i - 2][j + 1] == protector_king)
                                arr1[i - 2][j + 1] = (fight);

                        if (in_range(i - 1) && in_range(j + 2))
                            if (arr1[i - 1][j + 2] == field || arr1[i - 1][j + 2] == protector_king)
                                arr1[i - 1][j + 2] = (fight);
                        if (in_range(i + 1) && in_range(j - 2))

                            if (arr1[i + 1][j - 2] == field || arr1[i + 1][j - 2] == protector_king)
                                arr1[i + 1][j - 2] = (fight);
                        if (in_range(i + 2) && in_range(j - 1))

                            if (arr1[i + 2][j - 1] == field || arr1[i + 2][j - 1] == protector_king)
                                arr1[i + 2][j - 1] = (fight);
                        continue;
                    }
                    // for bishop
                    if ((arr1[i][j])[1] == 'B') {
                        i1 = i;
                        j1 = j;
                        while (i1 >= 0 && j1 >= 0 &&
                               (arr1[i1][j1] == field || arr1[i1][j1] == protector_king || arr1[i1][j1] == fight ||
                                j1 == j)) {
                            arr1[i1][j1] = const_cast<char *>(fight);
                            i1 = i1 - 1;
                            j1 = j1 - 1;
                        }
                        i1 = i;
                        j1 = j;
                        while (i1 >= 0 && j1 < size &&
                               (arr1[i1][j1] == field || arr1[i1][j1] == protector_king || arr1[i1][j1] == fight ||
                                j1 == j)) {
                            arr1[i1][j1] = const_cast<char *>(fight);
                            i1 = i1 - 1;
                            j1 = j1 + 1;
                        }
                        i1 = i;
                        j1 = j;
                        while (i1 < size && j1 >= 0 &&
                               (arr1[i1][j1] == field || arr1[i1][j1] == protector_king || arr1[i1][j1] == fight ||
                                j1 == j)) {
                            arr1[i1][j1] = const_cast<char *>(fight);
                            i1 = i1 + 1;
                            j1 = j1 - 1;
                        }
                        i1 = i;
                        j1 = j;
                        while (i1 < size && j1 < size &&
                               (arr1[i1][j1] == field || arr1[i1][j1] == protector_king || arr1[i1][j1] == fight ||
                                j1 == j)) {
                            arr1[i1][j1] = const_cast<char *>(fight);
                            i1 = i1 + 1;
                            j1 = j1 + 1;
                        }


                        arr1[i][j][0] = attacker_color;
                        arr1[i][j][1] = 'B';
                        continue;
                    }
// for queen
                    if ((arr1[i][j])[1] == 'Q') {
                        // diagonals
                        i1 = i;
                        j1 = j;
                        while (i1 >= 0 && j1 >= 0 &&
                               (arr1[i1][j1] == field || arr1[i1][j1] == protector_king || arr1[i1][j1] == fight ||
                                j1 == j)) {
                            arr1[i1][j1] = const_cast<char *>(fight);
                            i1 = i1 - 1;
                            j1 = j1 - 1;
                        }
                        i1 = i;
                        j1 = j;
                        while (i1 >= 0 && j1 < size &&
                               (arr1[i1][j1] == field || arr1[i1][j1] == protector_king || arr1[i1][j1] == fight ||
                                j1 == j)) {
                            arr1[i1][j1] = const_cast<char *>(fight);
                            i1 = i1 - 1;
                            j1 = j1 + 1;
                        }
                        i1 = i;
                        j1 = j;
                        while (i1 < size && j1 >= 0 &&
                               (arr1[i1][j1] == field || arr1[i1][j1] == protector_king || arr1[i1][j1] == fight ||
                                j1 == j)) {
                            arr1[i1][j1] = const_cast<char *>(fight);
                            i1 = i1 + 1;
                            j1 = j1 - 1;
                        }
                        i1 = i;
                        j1 = j;
                        while (i1 < size && j1 < size &&
                               (arr1[i1][j1] == field || arr1[i1][j1] == protector_king || arr1[i1][j1] == fight ||
                                j1 == j)) {
                            arr1[i1][j1] = fight;
                            i1 = i1 + 1;
                            j1 = j1 + 1;
                        }
                        // for lines
                        i1 = i;
                        j1 = j;

                        while (i1 >= 0 &&
                               (arr1[i1][j] == field || arr1[i1][j] == protector_king || arr1[i1][j] == fight ||
                                i1 == i)) {
                            arr1[i1][j] = const_cast<char *>(fight);
                            i1 = i1 - 1;
                        }
                        while (j1 >= 0 &&
                               (arr1[i][j1] == field || arr1[i][j1] == protector_king || arr1[i][j1] == fight ||
                                j1 == j)) {
                            arr1[i][j1] = const_cast<char *>(fight);
                            j1 = j1 - 1;
                        }
                        i1 = i;
                        j1 = j;

                        while (i1 < size &&
                               (arr1[i1][j] == field || arr1[i1][j] == protector_king || arr1[i1][j] == fight ||
                                i1 == i)) {
                            arr1[i1][j] = const_cast<char *>(fight);
                            i1 = i1 + 1;
                        }
                        while (j1 < size &&
                               (arr1[i][j1] == field || arr1[i][j1] == protector_king || arr1[i][j1] == fight ||
                                j1 == j)) {
                            arr1[i][j1] = const_cast<char *>(fight);
                            j1 = j1 + 1;
                        }


                        arr1[i][j][0] = attacker_color;
                        arr1[i][j][1] = 'Q';
                        continue;

                    }

                    // for pawn
                    if ((arr1[i][j])[1] == 'P') {
                        if (i + 1 < size && attacker_color == 'B') {
                            if (j + 1 < size && (arr1[i + 1][j + 1] == field || arr1[i + 1][j + 1] == protector_king))
                                arr1[i + 1][j + 1] = const_cast<char *>(fight);
                            if (j - 1 > 0 && (arr1[i + 1][j - 1] == field || arr1[i + 1][j - 1] == protector_king))
                                arr1[i + 1][j - 1] = const_cast<char *>(fight);
                        }
                        if (i - 1 > 0 && attacker_color == 'W') {
                            if (j + 1 < size && (arr1[i - 1][j + 1] == field || arr1[i - 1][j + 1] == protector_king))
                                arr1[i - 1][j + 1] = const_cast<char *>(fight);
                            if (j - 1 > 0 && (arr1[i - 1][j - 1] == field || arr1[i - 1][j - 1] == protector_king))
                                arr1[i - 1][j - 1] = const_cast<char *>(fight);
                        }
                    }
                }
            }
        }

        if (arr1[protector_i][protector_j] == fight)
            bo = true;


#ifdef print_isCheck
        for (int i = 0; i < size; i++) {
            cout << size - i << " ";
            for (int j = 0; j < size; j++) {
                cout << arr1[i][j] << " ";
            }
            cout << endl;
        }
        cout << "  ";
        for (int i = 0; i < size; i++) {
            cout << char('a' + i) << "  ";
        }
        cout << endl << endl;

#endif

//        for (int i = 0; i, size; i++) {
//
//            delete[] arr1[i];
//        }
//        delete[] arr1;

        return bo;
    }

    bool isMate(bool is_black_move) {
        string a = possibleMoves(is_black_move);
        if (a == "stop")
            return true;
        return false;
    }

    void makeMove(string m) {
        if (m.length() == 4) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    previousMove[i][j] = arr[i][j];
                }
            }
            arr[int(m[2] - '0')][int(m[3] - '0')] = arr[int(m[0] - '0')][int(m[1] - '0')];
            arr[int(m[0] - '0')][int(m[1] - '0')] = field;
            is_black_move = !is_black_move;
        }
    }

    void makeMove(int a1, int b1, int a2, int b2) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                previousMove[i][j] = arr[i][j];
            }
        }
        arr[a2][b2] = arr[a1][b1];
        arr[a1][b1] = field;
        is_black_move = !is_black_move;

    }

    void moveBack() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                arr[i][j] = previousMove[i][j];
            }
        }
    }

    string possibleMoves(bool is_black_move) {
        string moves[140];
        int k = 0;
        string arr1[size][size];
        for (int i = 0; i < size; i++) {
            //arr1[i] = new char *[size];
            for (int j = 0; j < size; j++) {
                arr1[i][j] = arr[i][j];
            }
        }

        string mover_color = "W";
        string not_mover_color = "B";
        if (is_black_move) {
            not_mover_color = "W";
            mover_color = "B";
        }

        int nmk_i = 0;  // not mover king i
        int nmk_j = 0;  // not mover king j

        string not_mover_king = (not_mover_color + "K");

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (arr1[i][j] == not_mover_king) {
                    nmk_i = i;
                    nmk_j = j;
                }
            }
        }


// moves by figure
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int i1 = i;
                int j1 = j;
// for rook
                if (arr1[i][j] == mover_color + "R") {
                    i1 = i;
                    j1 = j;
                    while (i1 >= 0 and arr1[i1][j] != not_mover_king and
                           (arr1[i1][j] == field or ((arr1[i1][j])[0] == not_mover_color[0] or i1 == i))) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i1) + to_string(j));
                        if ((arr1[i1][j])[0] == not_mover_color[0]) {
                            break;
                        }
                        i1 = i1 - 1;
                    }
                    while (j1 >= 0 and arr1[i][j1] != not_mover_king and (
                            arr1[i][j1] == field or (arr1[i][j1])[0] == not_mover_color[0] or i1 == i)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i) + to_string(j1));
                        if ((arr1[i][j1])[0] == not_mover_color[0]) {
                            break;
                        }
                        j1 = j1 - 1;
                    }
                    i1 = i;
                    j1 = j;
                    while (i1 < size and arr1[i1][j] != not_mover_king and (
                            arr1[i1][j] == field or (arr1[i1][j])[0] == not_mover_color[0] or i1 == i)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i1) + to_string(j));
                        if ((arr1[i1][j])[0] == not_mover_color[0]) {
                            break;
                        }
                        i1 = i1 + 1;
                    }
                    while (j1 < size and arr1[i][j1] != not_mover_king and (
                            arr1[i][j1] == field or (arr1[i][j1])[0] == not_mover_color[0] or arr1[i][j1] == fight or
                            j1 == j)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i) + to_string(j1));
                        if ((arr1[i][j1])[0] == not_mover_color[0]) {
                            break;
                        }
                        j1 = j1 + 1;
                    }
                    arr1[i][j] = mover_color + 'R';
                    continue;
                }

// for knight
                if (arr1[i][j] == (mover_color + 'N')) {
                    if (in_range(i - 1) and in_range(j - 2))
                        if (arr1[i - 1][j - 2] != not_mover_king and (
                                arr1[i - 1][j - 2] == field or (arr1[i - 1][j - 2])[0] == not_mover_color[0]))
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i - 1) + to_string(j - 2));


                    if (in_range(i - 2) and in_range(j - 1))
                        if (arr1[i - 2][j - 1] != not_mover_king and (
                                arr1[i - 2][j - 1] == field or (arr1[i - 2][j - 1])[0] == not_mover_color[0]))
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i - 2) + to_string(j - 1));

                    if (in_range(i + 2) and in_range(j + 1))
                        if (arr1[i + 2][j + 1] != not_mover_king and (
                                arr1[i + 2][j + 1] == field or (arr1[i + 2][j + 1])[0] == not_mover_color[0]))
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i + 2) + to_string(j + 1));

                    if (in_range(i + 1) and in_range(j + 2))
                        if (arr1[i + 1][j + 2] != not_mover_king and (
                                arr1[i + 1][j + 2] == field or (arr1[i + 1][j + 2])[0] == not_mover_color[0]))
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i + 1) + to_string(j + 2));


                    if (in_range(i - 2) and in_range(j + 1))
                        if (arr1[i - 2][j + 1] != not_mover_king and (
                                arr1[i - 2][j + 1] == field or (arr1[i - 2][j + 1])[0] == not_mover_color[0]))
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i - 2) + to_string(j + 1));

                    if (in_range(i - 1) and in_range(j + 2))
                        if (arr1[i - 1][j + 2] != not_mover_king and (
                                arr1[i - 1][j + 2] == field or (arr1[i - 1][j + 2])[0] == not_mover_color[0]))
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i - 1) + to_string(j + 2));

                    if (in_range(i + 1) and in_range(j - 2))
                        if (arr1[i + 1][j - 2] != not_mover_king and (
                                arr1[i + 1][j - 2] == field or (arr1[i + 1][j - 2])[0] == not_mover_color[0]))
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i + 1) + to_string(j - 2));

                    if (in_range(i + 2) and in_range(j - 1))
                        if (arr1[i + 2][j - 1] != not_mover_king and (
                                arr1[i + 2][j - 1] == field or (arr1[i + 2][j - 1])[0] == not_mover_color[0]))
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i + 2) + to_string(j - 1));
                    continue;
                }

// for bishop
                if (arr1[i][j] == (mover_color + 'B')) {
                    i1 = i;
                    j1 = j;
                    while (i1 >= 0 and j1 >= 0 and arr1[i1][j1] != not_mover_king and (
                            arr1[i1][j1] == field or (arr1[i1][j1])[0] == not_mover_color[0] or j1 == j)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i1) + to_string(j1));
                        if ((arr1[i1][j1])[0] == not_mover_color[0]) {
                            break;
                        }
                        i1 = i1 - 1;
                        j1 = j1 - 1;
                    }
                    i1 = i;
                    j1 = j;
                    while (i1 >= 0 and j1 < size and arr1[i1][j1] != not_mover_king and (
                            arr1[i1][j1] == field or (arr1[i1][j1])[0] == not_mover_color[0] or j1 == j)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i1) + to_string(j1));
                        if ((arr1[i1][j1])[0] == not_mover_color[0]) {
                            break;
                        }
                        i1 = i1 - 1;
                        j1 = j1 + 1;
                    }
                    i1 = i;
                    j1 = j;
                    while (i1 < size and j1 >= 0 and arr1[i1][j1] != not_mover_king and (
                            arr1[i1][j1] == field or (arr1[i1][j1])[0] == not_mover_color[0] or j1 == j)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i1) + to_string(j1));
                        if ((arr1[i1][j1])[0] == not_mover_color[0]) {
                            break;
                        }
                        i1 = i1 + 1;
                        j1 = j1 - 1;
                    }
                    i1 = i;
                    j1 = j;
                    while (i1 < size and j1 < size and arr1[i1][j1] != not_mover_king and (
                            arr1[i1][j1] == field or (arr1[i1][j1])[0] == not_mover_color[0] or j1 == j)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i1) + to_string(j1));
                        if ((arr1[i1][j1])[0] == not_mover_color[0]) {
                            break;
                        }
                        i1 = i1 + 1;
                        j1 = j1 + 1;
                    }

                    arr1[i][j] = (mover_color + "B");
                    continue;
                }

// for queen
                if (arr1[i][j] == (mover_color + 'Q')) {
// diagonals
                    i1 = i;
                    j1 = j;
                    while (i1 >= 0 and j1 >= 0 and arr1[i1][j1] != not_mover_king and (
                            arr1[i1][j1] == field or (arr1[i1][j1])[0] == not_mover_color[0] or j1 == j)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i1) + to_string(j1));
                        if ((arr1[i1][j1])[0] == not_mover_color[0]) {
                            break;
                        }
                        i1 = i1 - 1;
                        j1 = j1 - 1;
                    }
                    i1 = i;
                    j1 = j;
                    while (i1 >= 0 and j1 < size and arr1[i1][j1] != not_mover_king and (
                            arr1[i1][j1] == field or (arr1[i1][j1])[0] == not_mover_color[0] or j1 == j)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i1) + to_string(j1));
                        if ((arr1[i1][j1])[0] == not_mover_color[0]) {
                            break;
                        }
                        i1 = i1 - 1;
                        j1 = j1 + 1;
                    }
                    i1 = i;
                    j1 = j;
                    while (i1 < size and j1 >= 0 and arr1[i1][j1] != not_mover_king and (
                            arr1[i1][j1] == field or (arr1[i1][j1])[0] == not_mover_color[0] or j1 == j)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i1) + to_string(j1));
                        if ((arr1[i1][j1])[0] == not_mover_color[0]) {
                            break;
                        }
                        i1 = i1 + 1;
                        j1 = j1 - 1;
                    }
                    i1 = i;
                    j1 = j;
                    while (i1 < size and j1 < size and arr1[i1][j1] != not_mover_king and (
                            arr1[i1][j1] == field or (arr1[i1][j1])[0] == not_mover_color[0] or j1 == j)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i1) + to_string(j1));
                        if ((arr1[i1][j1])[0] == not_mover_color[0]) {
                            break;
                        }
                        i1 = i1 + 1;
                        j1 = j1 + 1;
                    }

// for lines
                    i1 = i;
                    j1 = j;

                    while (i1 >= 0 and arr1[i1][j] != not_mover_king and
                           (arr1[i1][j] == field or (arr1[i1][j])[0] == not_mover_color[0] or arr1[i1][j] == fight or
                            i1 == i)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i1) + to_string(j));
                        if ((arr1[i1][j])[0] == not_mover_color[0]) {
                            break;
                        }
                        i1 = i1 - 1;
                    }
                    while (j1 >= 0 and arr1[i][j1] != not_mover_king and (
                            arr1[i][j1] == field or (arr1[i][j1])[0] == not_mover_color[0] or arr1[i][j1] == fight or
                            i1 == i)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i) + to_string(j1));
                        if ((arr1[i][j1])[0] == not_mover_color[0]) {
                            break;
                        }
                        j1 = j1 - 1;
                    }
                    i1 = i;
                    j1 = j;
                    while (i1 < size and arr1[i1][j] != not_mover_king and (
                            arr1[i1][j] == field or (arr1[i1][j])[0] == not_mover_color[0] or arr1[i1][j] == fight or
                            i1 == i)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i1) + to_string(j));
                        if ((arr1[i1][j])[0] == not_mover_color[0]) {
                            break;
                        }
                        i1 = i1 + 1;
                    }
                    while (j1 < size and arr1[i][j1] != not_mover_king and (
                            arr1[i][j1] == field or (arr1[i][j1])[0] == not_mover_color[0] or arr1[i][j1] == fight or
                            j1 == j)) {
                        moves[k++] = (to_string(i) + to_string(j) + to_string(i) + to_string(j1));
                        if ((arr1[i][j1])[0] == not_mover_color[0]) {
                            break;
                        }
                        j1 = j1 + 1;
                    }

                    arr1[i][j] = (mover_color + "Q");
                    continue;

                }
// for pawn
                if (arr1[i][j] == (mover_color + 'P')) {
                    if (i + 1 < size and mover_color == "B") {
                        if ((j + 1 < size and arr1[i + 1][j + 1] != not_mover_king
                             and (arr1[i + 1][j + 1])[0] == not_mover_color[0]))
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i + 1) + to_string(j + 1));

                        if (j - 1 > 0 and arr1[i + 1][j - 1] != not_mover_king and
                            (arr1[i + 1][j - 1])[0] == not_mover_color[0])
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i + 1) + to_string(j - 1));

                        if (i == 1 and arr1[i + 1][j] == field and arr1[i + 2][j] == field)
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i + 2) + to_string(j));

                        if (arr1[i + 1][j] == field)
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i + 1) + to_string(j));
                    }
                    if (i - 1 > 0 and mover_color == "W") {
                        if ((j + 1 < size and arr1[i - 1][j + 1] != not_mover_king
                             and (arr1[i - 1][j + 1])[0] == not_mover_color[0]))
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i - 1) + to_string(j + 1));

                        if (j - 1 > 0 and arr1[i - 1][j - 1] != not_mover_king and
                            (arr1[i - 1][j - 1])[0] == not_mover_color[0])
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i - 1) + to_string(j - 1));

                        if (i == 6 and arr1[i - 1][j] == field and arr1[i - 2][j] == field)
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i - 2) + to_string(j));

                        if (arr1[i - 1][j] == field)
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i - 1) + to_string(j));

                    }
                    continue;
                }

// for king
                if (arr1[i][j] == (mover_color + 'K')) {

                    if (in_range(i + 1)) {
                        if (in_range(j + 1))
                            if ((kings_not_near(i + 1, j + 1, nmk_i, nmk_j) and
                                 ((arr1[i + 1][j + 1])[0] == not_mover_color[0]
                                  or arr1[i + 1][j + 1] == field)))
                                moves[k++] = (to_string(i) + to_string(j) + to_string(i + 1) + to_string(j + 1));

                        if (in_range(j - 1))
                            if ((kings_not_near(i + 1, j - 1, nmk_i, nmk_j) and
                                 ((arr1[i + 1][j - 1])[0] == not_mover_color[0]
                                  or arr1[i + 1][j - 1] == field)))
                                moves[k++] = (to_string(i) + to_string(j) + to_string(i + 1) + to_string(j - 1));

                        if ((kings_not_near(i + 1, j, nmk_i, nmk_j) and ((arr1[i + 1][j])[0] == not_mover_color[0]
                                                                         or arr1[i + 1][j] == field)))
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i + 1) + to_string(j));
                    }

                    if (in_range(i - 1)) {
                        if (in_range(j + 1))
                            if ((kings_not_near(i - 1, j + 1, nmk_i, nmk_j) and
                                 ((arr1[i - 1][j + 1])[0] == not_mover_color[0]
                                  or arr1[i - 1][j + 1] == field)))
                                moves[k++] = (to_string(i) + to_string(j) + to_string(i - 1) + to_string(j + 1));

                        if (in_range(j - 1))
                            if ((kings_not_near(i - 1, j - 1, nmk_i, nmk_j) and
                                 ((arr1[i - 1][j - 1])[0] == not_mover_color[0]
                                  or arr1[i - 1][j - 1] == field)))
                                moves[k++] = (to_string(i) + to_string(j) + to_string(i - 1) + to_string(j - 1));

                        if ((kings_not_near(i - 1, j, nmk_i, nmk_j) and ((arr1[i - 1][j])[0] == not_mover_color[0]
                                                                         or arr1[i - 1][j] == field)))
                            moves[k++] = (to_string(i) + to_string(j) + to_string(i - 1) + to_string(j));

                        if (in_range(j + 1))
                            if ((kings_not_near(i, j + 1, nmk_i, nmk_j) and ((arr1[i][j + 1])[0] == not_mover_color[0]
                                                                             or arr1[i][j + 1] == field)))
                                moves[k++] = (to_string(i) + to_string(j) + to_string(i) + to_string(j + 1));

                        if (in_range(j - 1))
                            if ((kings_not_near(i, j - 1, nmk_i, nmk_j) and ((arr1[i][j - 1])[0] == not_mover_color[0]
                                                                             or arr1[i][j - 1] == field)))
                                moves[k++] = (to_string(i) + to_string(j) + to_string(i) + to_string(j - 1));
                    }

                }
            }
        }
        string possible_moves;
        for (int i = 0; i < k; i++) {
            if (moves[i][0] != moves[i][2] or moves[i][1] != moves[i][3]) {
                makeMove(moves[i]);
                if (!isCheck(is_black_move)) {
                    possible_moves = possible_moves + (moves[i]);
                }
                moveBack();
            }
        }
        possible_moves += "stop";
        return possible_moves;

    }

    double countWhiteMaterial() {
        double white = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (arr[i][j] == "WP")
                    white += 1;
                if (arr[i][j] == "WN")
                    white += 3;
                if (arr[i][j] == "WB")
                    white += 3;
                if (arr[i][j] == "WR")
                    white += 5;
                if (arr[i][j] == "WQ")
                    white += 9;
            }
        }
        return white;
    }

    double countBlackMaterial() {
        double black = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (arr[i][j] == "BP")
                    black += 1;
                if (arr[i][j] == "BN")
                    black += 3;
                if (arr[i][j] == "BB")
                    black += 3;
                if (arr[i][j] == "BR")
                    black += 5;
                if (arr[i][j] == "BQ")
                    black += 9;
            }
        }
        return black;
    }

    double countAdvantage() {
        if (countWhiteMaterial() >= countBlackMaterial())
            return countWhiteMaterial() / countBlackMaterial();
        else
            return -countBlackMaterial() / countWhiteMaterial();
    }

    bool isPossibleMove(string move, bool is_black_move) {
        string a = possibleMoves(is_black_move);
        for (int i = 0; i <= a.length() - 4; i = i + 4) {
            if (a.substr(i, 4) == move) {
                return true;
            }
        }
        return false;
    }


};



