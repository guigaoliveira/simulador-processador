#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <cstddef>
#include "processor.hpp"

Processor::Processor()
{
    AC = 0;
    MQ = 0;
    MBR = 0;
    PC = 0;
    IR = 0;
    MAR = 0;
    std::fill(memory, memory + MEMORY_LENGTH, 0);
}

void Processor::setAddressInMemoryData(const int address, const int value)
{
    if (address >= 512 && address <= 1023)
    {
        memory[address] = value;
    }
    else
    {
        std::cout << "Erro: endereco deve ser entre 512 e 1023 para a memoria de dados";
    }
}

int Processor::getAddressInMemoryData(const int address)
{
    if (address >= 512 && address <= 1023)
    {
        return memory[address];
    }
    else
    {
        std::cout << "Erro: endereco deve ser entre 512 e 1023 para a memoria de dados";
        return -1;
    }
}

void Processor::setAddressInMemoryInstrution(const int address, const int value)
{
    if (address >= 0 && address <= 511)
    {
        memory[address] = value;
    }
    else
    {
        std::cout << "Erro: endereco deve ser entre 0 e 511 para a memoria de instrucoes";
    }
}

void Processor::fetchInstruction()
{
    MAR = PC;
    MBR = memory[MAR];
    IR = MBR;
    PC++;
}

bool Processor::tryFetchInstruction()
{
    if (!(PC >= 0 && PC <= 511))
        return false;
    fetchInstruction();
    return true;
}

int Processor::extractKBitsOfPositionP(const int number, const int k, const int p)
{
    return (((1 << k) - 1) & (number >> (p - 1)));
}

void Processor::decodeInstruction(const int opcode, const int addressOrDontCare)
{
    std::cout << "------" << std::endl;
    switch (opcode)
    {
    case 10: // 001010 LOAD MQ
        AC = MQ;
        std::cout << "LOAD MQ"
                  << "\n";
        std::cout << "AC=" << AC << ", "
                  << "MQ=" << MQ << "\n";
        break;
    case 9: // 001001 LOAD MQ, X
        MQ = memory[addressOrDontCare];
        std::cout << "LOAD MQ, " << addressOrDontCare << "\n";
        std::cout << "MQ=" << MQ << "\n";
        break;
    case 33: //value 100001 STOR X
        memory[addressOrDontCare] = AC;
        std::cout << "STOR " << addressOrDontCare << "\n";
        std::cout << "MEMORIA[" << addressOrDontCare << "]=" << AC << "\n";
        break;
    case 1: // 000001 LOAD X
        AC = memory[addressOrDontCare];
        std::cout << "LOAD " << addressOrDontCare << "\n";
        std::cout << "AC=" << AC << "\n";
        break;
    case 5: // 000101 ADD X
        AC += memory[addressOrDontCare];
        std::cout << "ADD " << addressOrDontCare << "\n";
        std::cout << "AC=" << AC << "\n";
        break;
    case 6: // 000110 SUB X
        AC -= memory[addressOrDontCare];
        std::cout << "SUB " << addressOrDontCare << "\n";
        std::cout << "AC=" << AC << "\n";
        break;
    case 11:
    { // 001011 MUL X
        int result = MQ * memory[addressOrDontCare];
        AC = 0;
        MQ = result;
        std::cout << "MUL " << addressOrDontCare << "\n";
        std::cout << "AC=" << AC << ", "
                  << "MQ= " << MQ << "\n";
        break;
    }
    case 12: // 001100 DIV X
        MQ = AC / memory[addressOrDontCare];
        AC = AC % memory[addressOrDontCare];
        std::cout << "DIV " << addressOrDontCare << "\n";
        std::cout << "AC=" << AC << ", "
                  << "MQ= " << MQ << "\n";
        break;
    }
    std::cout << "------" << std::endl;
}

bool Processor::tryDecodeInstruction(const int instruction)
{
    int addressOrDontCare = getAddressOrDontCare(instruction);
    if (addressOrDontCare != 0 && !(addressOrDontCare >= 512 && addressOrDontCare <= 1023))
    {
        return false;
    }
    int opcode = getOpcode(instruction);
    if (opcode)
    {
        decodeInstruction(opcode, addressOrDontCare);
    }
    return true;
}

int Processor::getAddressOrDontCare(const int instruction)
{
    return extractKBitsOfPositionP(instruction, 10, 7);
}

int Processor::getOpcode(const int instruction)
{
    return extractKBitsOfPositionP(instruction, OPCODE_LENGTH, 1);
}

int Processor::encodeInstruction(const int opcode, const int addressOrDontCare)
{
    std::bitset<16> instrutionInBinary;
    if (
        (opcode > pow(2, OPCODE_LENGTH) - 1) ||
        (addressOrDontCare > pow(2, ADDRESS_LENGTH) - 1) ||
        (OPCODE_LENGTH + ADDRESS_LENGTH > INSTRUCTION_LENGTH))
    {
        std::cout << "Nao e possivel representar opcode ou endereco";
        return -1;
    }
    for (std::size_t i = 0; i < OPCODE_LENGTH; ++i)
    {
        instrutionInBinary[i] = (opcode >> i) & 1;
    } // adiciona os bits do opcode
    std::size_t totalBitsOfAddress = addressOrDontCare && static_cast<int>(log2(addressOrDontCare)) + 1;
    for (std::size_t i = 0; i < totalBitsOfAddress; ++i)
    {
        instrutionInBinary[OPCODE_LENGTH + i] = (addressOrDontCare >> i) & 1;
    } // adiciona os bits do endereço
    std::cout << totalBitsOfAddress << '\n';
    return static_cast<int>(instrutionInBinary.to_ulong());
}

void Processor::executeInstructions()
{
    std::cout << "Inicio da executacao as instrucoes na memoria..." << std::endl;
    std::cout << "Instrucoes: " << std::endl;
    while (tryFetchInstruction())
    {
        tryDecodeInstruction(IR);
    }
    std::cout << "Fim da executacao as instrucoes na memoria de instrucoes..." << std::endl;
}

void Processor::createProgram(std::vector<int> memoryAdresses, std::vector<Instruction> instructions)
{
    std::size_t instructionsSize = instructions.size();
    if (memoryAdresses.size() != instructionsSize)
    {
        return;
    }
    for (std::size_t i = 0; i < instructionsSize; i++)
    {
        int instruction = encodeInstruction(instructions[i].opcode, instructions[i].addressOrDontCare);
        setAddressInMemoryInstrution(memoryAdresses[i], instruction);
    }
    std::cout << "Novo programa carregado..." << std::endl;
}
