#include <iostream>
#include <vector>
#include "Table.h"

int main() {
    std::cout << "ITAndroids - Treinamento de IA: Otimização" << std::endl;
    std::cout << std::endl;

    std::cout << "Gerando tabela" << std::endl;
    vector<int> row1;
    row1.push_back(3);
    row1.push_back(1);
    row1.push_back(2);

    vector<int> row2;
    row2.push_back(4);
    row2.push_back(5);
    row2.push_back(8);

    vector<int> row3;
    row3.push_back(6);
    row3.push_back(0);
    row3.push_back(7);

    vector<vector<int>> values;
    values.push_back(row1);
    values.push_back(row2);
    values.push_back(row3);


    Table *table = new Table(values);

    int ho = table->getHValue();
    int h1 = ho;
    do{
        ho=h1;
        table->betterTable();
        table->printTable();
        std::cout << std::endl;
        h1=table->getHValue();
    }while (h1!=ho);


    table->printTable();
    std::cout << "h = " << table->getHValue() << std::endl;

    return 0;
}