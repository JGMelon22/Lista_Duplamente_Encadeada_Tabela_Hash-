#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 23
#define MAX 50

typedef struct{

    int id;
    char nome[MAX];
    double valor;
}Devedor;

Devedor tableHash[TAM];

int menu(){
    
    int op;
    

    printf("\n====================================================================================\n");
    printf("\t TABELA PARA AGIOTAS ORGANIZAR SEUS DEVEDORES");
    printf("\n====================================================================================\n");

  
  
    printf("[1] - Inserir devedor.\n");
    printf("[2] - Buscar devedor.\n");
    printf("[3] - Imprimir devedores.\n");
    printf("[0] - Sair.\n");

    scanf("%d", &op);

    return op;
}

//INICIALIZA A TABELA COM -1 NA MEMÓRIA
void init(){
    
    for(int i = 0; i<TAM; i++){
        tableHash[i].id = -1;
    }
}

//função de espalhamento
int gerarCodigoHash(int chave){

    return chave % TAM;
}

/**
 *ler e retornar um devedor 
 */

Devedor getDevedor(){
    Devedor d;
    printf("Digite o id: ");
    scanf("%i", &d.id);
    getchar(); //limpa o buffe
    
    printf("Digite o nome do devedor: ");
    fgets(d.nome, MAX, stdin);

    printf("Digite o valor que precisa ser pago: ");
     scanf("%lf", &d.valor);

    return d;
}

//INSERE UM DEVEDOR NA TABELA
void insert(){
    Devedor d = getDevedor();
    int indice = gerarCodigoHash(d.id);

    //verifica se já existe algum valor nesse indice
    while(tableHash[indice].id != -1){
        indice = gerarCodigoHash(indice + 1);
    }

    tableHash[indice] = d;

}

/** 
 *Busca por devedores 
*/

Devedor* search(int chave){

    int indice = gerarCodigoHash(chave);
    
    while(tableHash[indice].id != -1){
        if(tableHash[indice].id == chave){
            return &tableHash[indice];
        }
        else{
            indice = gerarCodigoHash(chave + 1);
        }
    }

    //CASO ESSE DEVEDOR NÃO ESTEJA NA TABELA
    return NULL;

}

/**
 * imprime a tabela
 */

void imprimir(){
    printf("\n----------------------------------------------------------------------------------------\n");
    for(int i = 0; i<TAM; i++){
        if(tableHash[i].id != -1){
            printf("%2d = %3d \t %s \t %.2lf", i, tableHash[i].id, tableHash[i].nome, tableHash[i].valor);
        }

        else{
            printf("%d = vazio!\n", i);
        }
    }
    printf("\n----------------------------------------------------------------------------------------\n");
}

int main(void){
    int op, chave;
    Devedor *d;

    init();

    do{
        op = menu();

        switch(op){

            case 0:
                printf("[*] Saindo!\n");
                break;

            case 1:
                insert();
                break;
            
            case 2:
                printf("Digite o id a ser buscado: ");
                scanf("%d", &chave);
                d = search(chave);

                if(d){
                    printf("\n\t ID: %d \n\t Nome: %s \n\t  Valor devido: %.2lf\n", d->id, d->nome, d->valor);
                }
                else{
                    printf("\nID não encontrado\n");
                }
                break;

            case 3:
                imprimir();
                break;

            default:
                printf("[*] opção inválida!\n");
                break;
        }

    }while(op != 0);



    return 0;
}
