# Parte 2 da prova de Matemática Discreta 2 

## Verificação Modular com Fermat e Euler

Este programa em C implementa uma verificação de segurança baseada em conceitos de teoria dos números, como primalidade, coprimalidade, Pequeno Teorema de Fermat, Teorema de Euler e exponenciação modular eficiente.

## Funcionalidades

- Verifica se os números inseridos são primos.
- Testa se dois números são coprimos (MDC = 1).
- Calcula inverso modular usando o Algoritmo de Euclides Estendido.
- Aplica o Pequeno Teorema de Fermat ou o Teorema de Euler, conforme o caso.
- Executa exponenciação modular de forma eficiente.
- Decompõe um expoente `x` em `x = x1·q + r` e calcula:
- resultado = (a^q)^x1 · a^r mod n

- 
## Como executar

1. Compile o código:
 ```bash
 gcc main.c -o verificador
./verificador
