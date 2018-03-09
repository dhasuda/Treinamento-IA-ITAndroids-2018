#include <iostream>
#include "Table.h"

using namespace std;

Table::Table(vector<vector<int>> values) {
    this->values = values;
}

int Table::getHValue() {

    int h = 0;
    int i = 0;

    for (int row=0; row<3; row++) {
        for (int column=0; column<3; column++) {
            if (values[row][column] != i && i != 0) {
                h++;
            }
            i++;
        }
    }

    return h;
}

void Table::printTable() {

    for (int row=0; row<3; row++) {
        for (int column=0; column<3; column++) {
            cout << values[row][column] << "  ";
        }
        cout << endl;
    }

}

pair<int, int> Table::getZero() {

    for (int row=0; row<3; row++) {
        for (int column=0; column<3; column++) {
            if(values[row][column] == 0)
                return pair<int, int>(row, column);
        }
    }
}

void Table::betterTable() {

    pair<int, int> positionZero = this->getZero();

    int numeroCerto = 3*positionZero.first + positionZero.second;

    if((positionZero.first + 1 < 3)&&((*this).values[positionZero.first + 1][positionZero.second] == numeroCerto))
        changePositions(positionZero, pair<int, int>(positionZero.first+1, positionZero.second));
    else if((positionZero.first - 1 >= 0)&&((*this).values[positionZero.first - 1][positionZero.second] == numeroCerto))
        changePositions(positionZero, pair<int, int>(positionZero.first - 1, positionZero.second));
    else if((positionZero.second + 1 < 3)&&((*this).values[positionZero.first][positionZero.second+1] == numeroCerto))
        changePositions(positionZero, pair<int, int>(positionZero.first, positionZero.second+1));
    else if((positionZero.second - 1 >= 0)&&((*this).values[positionZero.first][positionZero.second-1] == numeroCerto))
        changePositions(positionZero, pair<int, int>(positionZero.first, positionZero.second-1));


}

void Table::changePositions(pair<int, int> p1, pair<int, int> p2 ) {
    int aux=this->values[p1.first][p1.second];
    this->values[p1.first][p1.second] = this->values[p2.first][p2.second];
    this->values[p2.first][p2.second] = aux;
}
