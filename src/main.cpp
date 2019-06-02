#include <iostream>
#include <vector>
#include <cstddef>
#include "processor.hpp"

int main()
{
    std::cout << "teste";
    Processor P;
    int data[6] = {37, 80, 23, 16, 63, 11};
    for (int i = 0; i < 6; ++i)
    {
        P.setAddressInMemoryData(600 + i, data[i]);
    }
    std::vector<Processor::Instruction> instructions{
        {9, 602},
        {11, 601},
        {10, 0},
        {5, 600},
        {33, 607},
        {9, 604},
        {11, 605},
        {10, 0},
        {33, 608},
        {1, 603},
        {6, 608},
        {33, 609},
        {1, 607},
        {12, 609},
        {33, 607},
        {10, 0},
        {33, 606}}; // Programa
    std::vector<int> memoryAdresses;
    for (std::size_t i = 0; i < instructions.size(); ++i)
    {
        memoryAdresses.push_back(300 + i);
    }

    P.createProgram(memoryAdresses, instructions);
    P.executeInstructions();

    for (int i = 0; i < 7; ++i)
    {
        std::cout
            << "Valor na posição(" << 600 + i << ") na memoria de dados = "
            << P.getAddressInMemoryData(600 + i)
            << std::endl;
    }
}
