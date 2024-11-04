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

typedef struct {

char nome[51];
char cpf[12];
char telefone[15];
char email[50];
char endereco[100]; 

}Cliente;

int menuOpcoes();
int menuClientes();
int menuEstoque();
void encerraPrograma();
Cliente* cadastroClientes(Cliente* clientes, int* numCliente);
void fileCliente(Cliente* cliente);
Produto* cadastroProdutos(Produto* produto, int* numProduto);
void fileEstoque(Produto* produto);
Cliente* excluirCliente(Cliente* clientes, int* numCliente);



void switchCliente(int opcao, Cliente** clientes, int* numCliente){

    switch(opcao){

        case 1:
            *clientes = cadastroClientes(*clientes, numCliente);

            break;

        case 2:
                        
            break;

        case 3:
            *clientes = excluirCliente(*clientes, numCliente);          
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

void switchEstoque(int opcao, Produto** produto, int* numProduto){

    switch(opcao){

        case 1:
            *produto = cadastroProdutos(*produto, numProduto);
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

void buscaProduto();
void excluiProduto();
int insereEstoque();
void vizualizaEstoque();

int main(){

    int opcaoCE, opcao, num1 = 0, num2=0;
    Cliente *clientes = NULL;
    Produto *produto = NULL;

    do{
        opcaoCE = menuOpcoes();

        switch(opcaoCE){

            case 1:
     
                do{
                    opcao = menuClientes();
                    switchCliente(opcao, &clientes, &num1);
                 
                }while(opcao<1 || opcao>5);   
                break;    

            case 2:

                do{
                    
                    opcao = menuEstoque();
                    switchEstoque(opcao, &produto, &num2);
                 
                }while(opcao<1 || opcao>6);
                break;  

            case 3:

                encerraPrograma();
                break;

            default:
                printf("Opcao invalida! Tente novamente\n");
        }

    }while(opcaoCE < 1 || opcaoCE > 2);
    free(clientes);
    free(produto);

    return 0;
}

int menuOpcoes(){

    int opcao;
    printf("1 - Clientes\n");
    printf("2 - Estoque\n");
    printf("3 - Sair\n");
    printf("Insira a opcao que deseja acessar: ");
    scanf("%d", &opcao);
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
    return opcao;
}

void encerraPrograma(){
    printf("Programa encerrado!");
    exit(SAIR);
}

Cliente* cadastroClientes(Cliente* clientes, int* numCliente){
    (*numCliente)++;
    clientes = (Cliente*)realloc(clientes, (*numCliente) * sizeof(Cliente));
    if(clientes == NULL){
        printf("Erro alocacao\n");
        exit(1);
    }
    Cliente* novoCliente = &clientes[*numCliente-1];

    printf("Digite o nome do cliente: ");
    scanf(" %50[^\n]", novoCliente->nome);
    printf("Digite o CPF: ");
    scanf(" %11s", novoCliente->cpf);
    printf("Digite o telefone: ");
    scanf(" %14s", novoCliente->telefone);
    printf("Digite o endereço: ");
    scanf(" %99[^\n]", novoCliente->endereco);
    printf("Digite o email: ");
    scanf(" %49s", novoCliente->email);

    fileCliente(novoCliente);

    return clientes;
}

void fileCliente(Cliente* cliente){
    FILE *arquivoCliente;
    arquivoCliente = fopen("Clientes.txt", "a+");

    if(arquivoCliente != NULL){

        fprintf(arquivoCliente, "Nome: %sCPF: %sTelefone: %sEndereco: %sEmail: %s\n", cliente->nome,cliente->cpf,cliente->telefone,cliente->endereco,cliente->email);
        fclose(arquivoCliente);

    }else{

        printf("Erro ao abrir arquivo!");
        exit(SAIR);
    }

}

Produto* cadastroProdutos(Produto* produto, int* numProduto){
    (*numProduto)++;
    produto = (Produto*)realloc(produto, (*numProduto) * sizeof(Produto));
    if(produto == NULL){
        printf("Erro alocacao\n");
        exit(1);
    }
    Produto* novoProduto = &produto[*numProduto-1];

    printf("Digite o codigo do produto: ");
    scanf("%d", &novoProduto->codigo);
    printf("Digite o nome do produto: ");
    scanf("%51[^\n]",novoProduto->nome);
    printf("Digite o valor de custo do produto: ");
    scanf("%f", &novoProduto->valorDeCusto);
    printf("Digite o valor de venda do produto:");
    scanf("%f", &novoProduto->valorDeVenda);
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novoProduto->quantidade);

    fileEstoque(novoProduto);

    return produto;
}

void fileEstoque(Produto* produto){
    FILE *arquivoProduto;
    arquivoProduto = fopen("Estoque.txt", "a+");

    if(arquivoProduto != NULL){

        fprintf(arquivoProduto, "Codigo: %dNome: %sCusto: %.2fVenda: %.2fQuantidade: %d\n", produto->codigo,produto->nome,produto->valorDeCusto,produto->valorDeVenda,produto->quantidade);
        fclose(arquivoProduto);

    }else{

        printf("Erro ao abrir arquivo!");
        exit(SAIR);
    }

}

Cliente* excluirCliente(Cliente* clientes, int* numCliente) {
    char cpfExcluir[12];
    printf("Digite o CPF do cliente que deseja excluir do cadastro: ");
    scanf("%s", cpfExcluir);

    int i;
    for (i = 0; i < *numCliente; i++) {
        if (strcmp(clientes[i].cpf, cpfExcluir) == 0) {
            for (int j = i; j < *numCliente - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            (*numCliente)--; 
            clientes = realloc(clientes, (*numCliente) * sizeof(Cliente));
            if (clientes == NULL && *numCliente > 0) {
                printf("Erro ao alocar memoria\n");
                exit(1);
            }
            printf("Cliente com CPF %s excluido com sucesso!\n", cpfExcluir);
            return clientes;
        }
    }
    printf("Cliente com CPF %s nao encontrado.\n", cpfExcluir);
    return clientes;
}

void excluirClienteFile(){


    
}