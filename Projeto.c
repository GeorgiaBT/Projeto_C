#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SAIR 0

typedef struct{

   int codigo;
   char nome[51];
   int quantidade;
   float valorDeVenda, valorDeCusto;

}Produto;

typedef struct{

    char rua[50];
    char bairro[20];
    char cidade[20];
    char estado[20];
    int cep;
    int numero;

}Endereco;

typedef struct {

char nome[51];
char cpf[12];
char telefone[15];
char email[50];
Endereco enderecoCliente; 

}Cliente;

int menuOpcoes();
int menuClientes();
int menuEstoque();
void encerraPrograma();

void cadastroCliente(){
}

void listaCliente(){
}

void excluiCliente(){
}

void switchCliente(int opcao){

    switch(opcao){

        case 1:

            break;

        case 2:
                        
            break;

        case 3:
                        
            break;

        case 4:

            break;

        case 5:
            encerraPrograma();
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");

        }
}

void switchEstoque(int opcao){

    switch(opcao){

        case 1:

            break;

        case 2:

            break;

        case 3:

            break;

        case 4:

            break;

        case 5:
            
            break;
       
        case 6:
            encerraPrograma();
            break;

        default:
            printf("Opcao invalida! Tente novamente\n");
    }

}

void cadastraProduto();
void buscaProduto();
void excluiProduto();
int insereEstoque();
void vizualizaEstoque();

int main(){

    int opcaoCE, opcao;

    do{
        opcaoCE = menuOpcoes();

        switch(opcaoCE){

            case 1:
     
                do{
                    opcao = menuClientes();
                    switchCliente(opcao);
                 
                }while(opcao<1 || opcao>5);   
                break;    

            case 2:

                do{
                    
                    opcao = menuEstoque();
                    switchEstoque(opcao);
                 
                }while(opcao<1 || opcao>6);
                break;  

            case 3:

                encerraPrograma();
                break;

            default:
                printf("Opcao invalida! Tente novamente\n");
        }

    }while(opcaoCE < 1 || opcaoCE > 2);

    return 0;
}

int menuOpcoes(){

    int opcao;
    printf("1 - Clientes");
    printf("2 - Estoque");
    printf("3 - Sair");
    printf("Insira a opcao que deseja acessar");
    scanf(opcao);
    return opcao;

}

int menuClientes(){

    int opcao;
    printf("1 - Cadastrar cliente\n");
    printf("2 - Listar cliente\n");
    printf("3 - Excluir cliente\n");
    printf("4 - Realizar um pedido\n");
    printf("5 - Sair\n");
    printf("Insira a opcao desejada: ");
    scanf("%d", & opcao);

    return opcao;
};

int menuEstoque(){

    int opcao;
    printf("1 - Cadastrar produto\n");
    printf("2 - Pesquisar produto\n");
    printf("3 - Excluir produto\n");
    printf("4 - Inserir no estoque\n");
    printf("5 - Vizualizar estoque\n");
    printf("6 - Sair\n");
    scanf("%d", &opcao);

}

void encerraPrograma(){
    printf("Programa encerrado!");
    exit(SAIR);
}