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