#ifndef CODE_TABLE_H
#define CODE_TABLE_H

#include <vector>

using namespace std;

class Table {

public:
    Table(vector<vector<int>> values);
    ~Table() = default;

    int getHValue();

    void printTable();

    int getZero();

private:
    vector<vector<int>> values;

};


#endif //CODE_TABLE_H
