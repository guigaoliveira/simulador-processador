# Simulador de um processador
Esse repositório possui os códigos para um trabalho da disciplina DCA0104 – Arquitetura de Computadores da UFRN. 

O problema do trabalho consiste em simular um processador hipotético, inspirado no modelo do IAS de Von Neumann, cujo diagramade blocos é apresentado a seguir. Ele contém uma memória de 1,0 kWord, endereçável a words de 2bytes (16 bits). Esta memória é segmentada em duas regiões. Na primeira, os endereços vão de 0 até 511 e são exclusivos para armazenamento de instruções. Já o segundo segmento tem endereços quevão de 512 até 1023, exclusivo para armazenamento de dados. O tamanho da palavra (word) manipulada por esse processador é de 16 bits (2 bytes). Esse processador é desenvolvido com um conjunto de registradores especiais, todos de 16 bits:

- AC (acumulador);
- MQ (quociente multiplicador);
- MBR (registrador de buffer de memória);
- PC (contador de programa);
- IR (registrador de instrução); e
- MAR (registrador de endereço da memória).

Não há registradores de uso geral. Todos os dados devem ser armazenados em alguma posição da memória, no segmento para dados. 

As instruções têm também 16 bits de tamanho, onde 6 bits são para o código da operação (opcode) eos 10 bits restantes ou são para endereçamento da memória (em algumas instruções) ou valor don't care. A tabela a seguir apresenta parte do conjunto de instruções que tem interesse direto neste problema:

| Opcode | Representação em Ling. de Montagem | Descrição |
|---|---|---|
| 001010 | LOAD MQ | Transfere o conteúdo do MQ para AC. |
| 001001 | LOAD MQ X | Transfere o conteúdo da memória no endereço X para MQ |
| 100001 | STOR X | Transfere o conteúdo de AC para o local X da memória |
| 000001 | LOAD X | Transfere o conteúdo do local X da memória para AC |
| 000101 | ADD X | Soma o conteúdo da memória no endereço X com AC. O resultado é gravado em AC. |
| 000110 | SUB X | Subtrai o conteúdo da memória que está no endereço X do valor de AC. O resultado é gravadoem AC (AC ← AC – Mem[X]) |
| 001011 | MUL X | Multiplica o conteúdo da memória no endereço X por MQ. Os bits mais significativos são armazenados em AC e os bits menos significativos ficam em MQ |
| 001100 | DIV X | Divide AC pelo conteúdo da memória no endereçoX. O quociente é colocado em MQ e o resto em AC. |
