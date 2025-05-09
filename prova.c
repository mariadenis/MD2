#include <stdio.h>
#include <stdlib.h>


typedef struct {
    long base;       
    long modulo;    
    long potencia;   
    long resultado;  
} CongruenciaModular;


typedef struct {
    long numero_h;
    long numero_g;
    long numero_n;
    long x1;
    long quociente;
    long resto;
} DadosIntermediarios;


int verificaPrimalidade(long numero) {
    if (numero <= 1) return 0;
    if (numero == 2 || numero == 3) return 1;
    if (numero % 2 == 0) return 0;
    
    long i;
    for (i = 3; i*i <= numero; i += 2) {
        if (numero % i == 0) return 0;
    }
    return 1;
}


long calculaMDC(long primeiro, long segundo) {
    long temp;
    
   
    if (primeiro < segundo) {
        temp = primeiro;
        primeiro = segundo;
        segundo = temp;
    }
    
    while (segundo != 0) {
        temp = primeiro - segundo * (primeiro / segundo);
        primeiro = segundo;
        segundo = temp;
    }
    
    return primeiro;
}


long buscaInversoModular(long elemento, long modulo) {
    long inverso;
    for (inverso = 1; inverso < modulo; inverso++) {
        if ((elemento * inverso) % modulo == 1)
            return inverso;
    }
    return -1; 
}


long calculaTotiente(long num) {
    printf("    Calculando o totiente de %ld usando o metodo de contagem direta:\n", num);
    
    long i, contador = 0;
    
    for (i = 1; i < num; i++) {
        if (calculaMDC(i, num) == 1) {
            contador++;
            printf("    - %ld eh coprimo com %ld\n", i, num);
        }
    }
    
    printf("    Total de numeros coprimos: %ld\n", contador);
    return contador;
}


long exponenciacaoModular(long base, long exp, long mod) {
    if (exp == 0) return 1;
    
    long metade = exponenciacaoModular(base, exp/2, mod);
    long resultado = (metade * metade) % mod;
    
    if (exp % 2 == 1)
        resultado = (resultado * base) % mod;
        
    return resultado;
}


void calculadorModular() {
    CongruenciaModular mod;
    DadosIntermediarios dados;
    
    printf("*** SISTEMA DE CALCULO MODULAR ***\n\n");
    
  
    printf("Informe os valores de H, G e n separados por espaco: ");
    scanf("%ld %ld %ld", &dados.numero_h, &dados.numero_g, &dados.numero_n);
    
    printf("Informe o valor do expoente x: ");
    scanf("%ld", &mod.potencia);
    
    printf("Informe o valor do módulo n1: ");
    scanf("%ld", &mod.modulo);
    
    printf("\n=== INICIO DA RESOLUCAO ===\n\n");
    
   
    printf("PASSO 1: Analisando a primalidade de G e n\n");
    int g_primo = verificaPrimalidade(dados.numero_g);
    int n_primo = verificaPrimalidade(dados.numero_n);
    
    printf("    • G = %ld eh %sprimo\n", dados.numero_g, g_primo ? "" : "não ");
    printf("    • n = %ld eh %sprimo\n", dados.numero_n, n_primo ? "" : "não ");
    
    
    long mdc_gn = calculaMDC(dados.numero_g, dados.numero_n);
    printf("    • MDC(G, n) = %ld\n", mdc_gn);
    
    if (mdc_gn != 1) {
        printf("\nATENCAO: Como MDC(%ld, %ld) = %ld != 1, nao podemos prosseguir!\n", 
               dados.numero_g, dados.numero_n, mdc_gn);
        return;
    }
    
    
    printf("\nPASSO 2: Determinando o inverso modular de G em Z_n\n");
    long g_inv = buscaInversoModular(dados.numero_g, dados.numero_n);
    
    if (g_inv == -1) {
        printf("    • G nao possui inverso modular em Z_%ld\n", dados.numero_n);
        return;
    }
    
    printf("    • O inverso de %ld mod %ld eh %ld\n", dados.numero_g, dados.numero_n, g_inv);
    printf("    • Verificacao: (%ld × %ld) mod %ld = %ld\n", 
           dados.numero_g, g_inv, dados.numero_n, (dados.numero_g * g_inv) % dados.numero_n);
    
   
    printf("\nPASSO 3: Encontrando o valor da base a\n");
    mod.base = (dados.numero_h * g_inv) % dados.numero_n;
    printf("    • a = (H × G⁻¹) mod n = (%ld × %ld) mod %ld = %ld\n", 
           dados.numero_h, g_inv, dados.numero_n, mod.base);
    
    
    printf("\nPASSO 4: Verificando se a e n1 sao coprimos\n");
    long mdc_an1 = calculaMDC(mod.base, mod.modulo);
    printf("    • MDC(%ld, %ld) = %ld\n", mod.base, mod.modulo, mdc_an1);
    printf("    • a e n1 %s coprimos\n", (mdc_an1 == 1) ? "sao" : "nao sao");
    
    
    printf("\nPASSO 5: Verificando se n1 é primo\n");
    int n1_primo = verificaPrimalidade(mod.modulo);
    printf("    • n1 = %ld eh %sprimo\n", mod.modulo, n1_primo ? "" : "nao ");
    
    
    printf("\n");
    if (n1_primo) {
        printf("PASSO 6: Como n1 eh primo, usamos o Pequeno Teorema de Fermat\n");
        dados.x1 = mod.modulo - 1;
        printf("    • x1 = n1 - 1 = %ld - 1 = %ld\n", mod.modulo, dados.x1);
    } else {
        printf("PASSO 7: Como n1 nao eh primo, usamos o Teorema de Euler\n");
        dados.x1 = calculaTotiente(mod.modulo);
        printf("    • x1 = φ(n1) = φ(%ld) = %ld\n", mod.modulo, dados.x1);
    }
    
    
    printf("\nPASSO 8: Decomposicao do expoente pelo teorema da divisao\n");
    dados.quociente = mod.potencia / dados.x1;
    dados.resto = mod.potencia % dados.x1;
    printf("    • Divisao: %ld ÷ %ld = %ld com resto %ld\n", 
           mod.potencia, dados.x1, dados.quociente, dados.resto);
    printf("    • x = x1·q + r = %ld·%ld + %ld = %ld\n", 
           dados.x1, dados.quociente, dados.resto, 
           dados.x1 * dados.quociente + dados.resto);
    
    
    printf("\nPASSO 9: Reescrevendo a expressao\n");
    printf("    • a^x mod n1 = ((a^x1)^q · a^r) mod n1\n");
    
    
    printf("\nPASSO 10: Calculando valores intermediarios\n");
    
  
    long a_elevado_x1 = exponenciacaoModular(mod.base, dados.x1, mod.modulo);
    printf("    • a^x1 mod n1 = %ld^%ld mod %ld = %ld\n", 
           mod.base, dados.x1, mod.modulo, a_elevado_x1);
    
  
    long ax1_elevado_q = exponenciacaoModular(a_elevado_x1, dados.quociente, mod.modulo);
    printf("    • (a^x1)^q mod n1 = %ld^%ld mod %ld = %ld\n", 
           a_elevado_x1, dados.quociente, mod.modulo, ax1_elevado_q);
    
   
    long a_elevado_r = exponenciacaoModular(mod.base, dados.resto, mod.modulo);
    printf("    • a^r mod n1 = %ld^%ld mod %ld = %ld\n", 
           mod.base, dados.resto, mod.modulo, a_elevado_r);
    
   
    printf("\nPASSO 11: Calculando o resultado final\n");
    mod.resultado = (ax1_elevado_q * a_elevado_r) % mod.modulo;
    printf("    • ((a^x1)^q · a^r) mod n1 = (%ld · %ld) mod %ld = %ld\n", 
           ax1_elevado_q, a_elevado_r, mod.modulo, mod.resultado);
    
    printf("\n*** RESULTADO FINAL ***\n");
    printf("%ld^%ld mod %ld = %ld\n", 
           mod.base, mod.potencia, mod.modulo, mod.resultado);
}

int main() {
    calculadorModular();
    return 0;
}