#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP
#include <vector>

class Processor
{
private:
    int memory[1024];
    int AC;
    int MQ;
    int MBR;
    int PC;
    int IR;
    int MAR;
    static const size_t MEMORY_LENGTH = 1024;
    static const size_t OPCODE_LENGTH = 6;
    static const size_t ADDRESS_LENGTH = 10;
    static const size_t INSTRUCTION_LENGTH = 16;
    /* 
        Método que seta um valor em um endereço da parte da memória para as instruções 
    */
    void setAddressInMemoryInstrution(int address, int value);
    /*
        Metódo que pega / busca uma instrução da memória de instruções
    */
    void fetchInstruction();
    /*
        Metódo que tenta pegar / buscar uma instrução da memória de instruções
    */
    bool tryFetchInstruction();
    /* 
        Metódo para extrair k bits da posição p
        e retorna o valor extraído como inteiro
    */
    int extractKBitsOfPositionP(int number, int k, int p);
    /* 
        Metódo para reconhecer uma instrução com base no opcode
    */
    void decodeInstruction(int opcode, int addressOrDontCare);
    /*
        Método para tentar reconhecer uma instrução com base no opcode
    */
    bool tryDecodeInstruction(int instruction);
    /* 
        Metódo que pega o endereço / dont care da instrução (inteiro)
    */
    int getAddressOrDontCare(int instruction);
    /* 
        Metódo que pega o opcode da instrução (inteiro)
    */
    int getOpcode(int instruction);
    /*
        Metódo que transforma um opcode e um endereço / dont care em um inteiro de 16 bits.
        (que os 6 primeiros bits são o opcode e os outros 10 são o endereço, para esse caso)
    */
    int encodeInstruction(int opcode, int addressOrDontCare);
    /*
        Metódo que executa as instruções na memória de instruções
    */
public:
    struct Instruction
    {
        int opcode;
        int addressOrDontCare;
    };
    Processor();
    /* 
        Método que seta um valor em um endereço da parte da memória para os dados 
    */
    void setAddressInMemoryData(int address, int value);
    /*
        Método que retorna um valor em um endereço da memória de dados  
    */
    int getAddressInMemoryData(int address);
    /* 
        Método que seta um valor em um endereço da parte da memória para as instruções 
    */
    void executeInstructions();
    /*
        Metódo que cria um programa armazenando na memória de instruções 
    */
    void createProgram(std::vector<int> memoryAdresses, std::vector<Instruction> instructions);
};
#endif
