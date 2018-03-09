#ifndef CODE_TABLE_H
#define CODE_TABLE_H

#include <vector>
#include "utility"

using namespace std;

class Table {

public:
    Table(vector<vector<int>> values);
    ~Table() = default;

    int getHValue();

    void printTable();

    pair<int, int> getZero();

    void betterTable();

    void changePositions(pair<int, int> p1, pair<int, int> p2);


private:
    vector<vector<int>> values;

};


#endif //CODE_TABLE_H
