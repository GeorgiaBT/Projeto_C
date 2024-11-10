#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*
O que fazer:
criar a funcao editar cliente (so vai permitir editar telefone, email e endereco ja q ngm muda de nome nem cpf)

Rever o codigo:
    -EM todos os lugares que for possivel, vamos alocar memoria
    -Onde estiver usando vetor sem ponteiro vamos fazer de ponteiro
*/


#define SAIR 0
#define LIMPAR "cls"

typedef struct
{

    int codigo;
    char nome[51];
    int quantidade;
    float valorDeVenda, valorDeCusto;

} Produto;

typedef struct
{

    char nome[51];
    char cpf[12];
    char telefone[15];
    char email[50];
    char endereco[100];

} Cliente;

//funções base
int menuOpcoes(); //melhorei layout
void switchMenuInicial(int opcaoCE, Produto **produto, Cliente **clientes,int *numProdutos,int *numClientes);
int menuClientes();//melhorei layout
int menuEstoque();//melhorei layout
void encerraPrograma(); //verificada
void lerArquivoClientes(Cliente **clientes, int *numCliente); //atualizei
void lerArquivoProdutos(Produto **produtos, int *numProdutos); //atualizei

//funções clientes
void switchCliente(int opcao, Cliente **clientes, int *numCliente,Produto **produto, int *numProduto);
int menuCadastros();//melhorei layout
int menuListar(); //melhorei layout
void switchCadastros(int opcao, Cliente **clientes, int *numCLiente);
void switchListar(int opcao, Cliente **clientes, int *numCLiente);
Cliente *cadastroClientes(Cliente *clientes, int *numCliente);
void fileCliente(Cliente *cliente);
Cliente *excluirCliente(Cliente *clientes, int *numCliente);
void excluirClienteFile(char *cpfExcluir );
void listaTodosClientes(Cliente *clientes, int numClientes);
void buscaCLiente(Cliente *clientes, int numClientes);
void realizarPedido(Cliente *clientes, int numClientes, Produto *produtos, int numProdutos);
void atualizarEstoqueFile(Produto *produtos, int numProdutos);
void salvarPedidoNoArquivo(Cliente cliente, Produto *produtosComprados, int *quantidades, int numProdutos, float totalPedido, int codigoComprado);
int menuAlterarCliente(); //melhorei layout
void editarCliente(Cliente *clientes, int numClientes);
void switchAlteracaoCliente(int alteracao, Cliente *clientes, int i, int numClientes);
void alteraTelefone(Cliente *clientes, int i, int numClientes);
void alteraEmail(Cliente *clientes, int i, int numClientes);
void alteraEndereco(Cliente *clientes, int i, int numClientes);
void atualizarClienteFile(Cliente *clientes, int numClientes);


//funções produtos
void switchEstoque(int opcao, Produto **produto, int *numProduto);
Produto *cadastroProdutos(Produto *produto, int *numProduto);
void fileEstoque(Produto *produto);
void listarProdutos(Produto *produto, int numProduto);
Produto *excluiProduto(Produto *produto, int *numProduto);
void excluirProdutoFile(int codigoExcluir);
void buscarProduto(Produto *produto, int numProduto);
int menuAlterarEstoque(); //melhorei layout
void switchAlteracao(int alteracao, Produto *produto, int numProduto,int i);
void inserirEstoque(Produto *produto, int numProduto);
void alteraValorVenda(Produto *produto, int numProdutos, int i);
void alteraQTD(Produto *produto, int numProdutos, int i);
void alteraValorCusto(Produto *produto, int numProdutos, int i);
int menuCadastroEstoque();  //melhorei layout
int menuVizuEstoque(); //melhorei layout
void switchCadastroEstoque(int opcao, Produto **produto, int *numProduto);
void switchVizuEstoque(int opcao, Produto **produto, int *numProduto);

int main()
{
    int opcaoCE, numProdutos = 0, numClientes=0;
    Cliente *clientes = NULL;
    Produto *produto = NULL;
    
    lerArquivoClientes(&clientes, &numClientes);
    lerArquivoProdutos(&produto, &numProdutos);

    do
    {
        opcaoCE = menuOpcoes();
        switchMenuInicial(opcaoCE,&produto,&clientes,&numProdutos,&numClientes);

    } while (opcaoCE != 3);
    free(clientes);
    free(produto);

    return 0;
}

void switchMenuInicial(int opcaoCE, Produto **produto, Cliente **clientes,int *numProdutos,int *numClientes){

    int opcao;
    switch (opcaoCE)
        {

        case 1:

            do
            {
                opcao = menuClientes();
                switchCliente(opcao, clientes, numClientes, produto, numProdutos);

            } while (opcao < 1 || opcao > 4);
            break;

        case 2:

            do
            {

                opcao = menuEstoque();
                switchEstoque(opcao, produto, numProdutos);

            } while (opcao < 1 || opcao > 3);
            break;

        case 3:
            encerraPrograma();
            break;

        default:
            printf("Opcao invalida! Tente novamente\n");
        }

}

void switchCliente(int opcao, Cliente **clientes, int *numCliente,Produto **produto, int *numProduto)
{
    int opcaoMenu;
    switch (opcao)
    {

    case 1:

        do
        {
            opcaoMenu = menuCadastros();
            switchCadastros(opcaoMenu, clientes, numCliente);

        } while (opcaoMenu < 1 || opcaoMenu > 4);

        break;

    case 2:

        do{

            opcaoMenu = menuListar();
            switchListar(opcaoMenu, clientes, numCliente);

        }while(opcaoMenu<1 || opcaoMenu>3);
        
        break;

    case 3:
        realizarPedido(*clientes, *numCliente, *produto,  *numProduto);
        break;

    case 4:
        return;
        break;

    default:
        printf("Opcao invalida! Tente novamente.\n");
    }
}

void switchEstoque(int opcao, Produto **produto, int *numProduto)
{
    int opcoes;
    switch (opcao)
    {

        case 1:
            do{

                opcoes = menuCadastroEstoque();
                switchCadastroEstoque(opcoes, produto, numProduto);

            }while(opcoes<1 || opcoes>4);
            break;

        case 2:
            do{

                opcoes = menuVizuEstoque();
                switchVizuEstoque(opcoes, produto, numProduto);

            }while(opcoes<1 || opcoes>3);
            break;

        case 3:
            return;
            break;

        default:
            printf("Opcao invalida! Tente novamente\n");
    }
}

void lerArquivoProdutos(Produto **produtos, int *numProdutos){
    FILE *arquivoProduto = fopen("Estoque.txt", "r");
    if (arquivoProduto == NULL) {
        printf("Erro ao abrir o arquivo de produtos!\n");
        return;
    }

    Produto produtoTemp;
    while (fscanf(arquivoProduto, "Codigo: %d, Nome do produto: %50[^,], Valor de custo: %f, Valor de Venda: %f, Quantidade: %d\n",&produtoTemp.codigo, produtoTemp.nome, &produtoTemp.valorDeCusto,&produtoTemp.valorDeVenda, &produtoTemp.quantidade) == 5)
    {
        (*numProdutos)++;
        *produtos = realloc(*produtos, (*numProdutos) * sizeof(Produto));
        if (*produtos == NULL) {
            printf("Erro ao alocar memória\n");
            exit(1);
        }
        (*produtos)[*numProdutos - 1] = produtoTemp;
    }

    fclose(arquivoProduto);

}

void lerArquivoClientes(Cliente **clientes, int *numCliente){
    FILE *arquivoCliente = fopen("Clientes.txt", "r");
    if (arquivoCliente == NULL) {
        printf("Erro ao abrir o arquivo de clientes!\n");
        return;
    }

    Cliente clienteTemp;
    while (fscanf(arquivoCliente, "Nome: %50[^,], CPF: %11[^,], Telefone: %14[^,], Endereco: %99[^,], Email: %49[^\n]\n",clienteTemp.nome, clienteTemp.cpf, clienteTemp.telefone,clienteTemp.endereco, clienteTemp.email) == 5)
    {
        (*numCliente)++;
        *clientes = realloc(*clientes, (*numCliente) * sizeof(Cliente));
        if (*clientes == NULL) {
            printf("Erro ao alocar memória\n");
            exit(1);
        }
        (*clientes)[*numCliente - 1] = clienteTemp;
    }

    fclose(arquivoCliente);
    
}

int menuOpcoes()
{
    int opcao;
    printf("=====================================\n");
    printf("                MENU                 \n");
    printf("=====================================\n");
    printf("1 - Clientes\n");
    printf("2 - Estoque\n");
    printf("3 - Sair\n");
    printf("=====================================\n");
    printf("Insira a opcao que deseja acessar: ");
    scanf("%d", &opcao);

    return opcao;
}

int menuClientes()
{
    int opcao;
    system(LIMPAR); 
    printf("=====================================\n");
    printf("           Menu de Cliente           \n");
    printf("=====================================\n");
    printf("1 - Cadastros\n");
    printf("2 - Listar clientes\n");
    printf("3 - Realizar um pedido\n");
    printf("4 - Voltar\n");
    printf("=====================================\n");
    printf("Insira a opcao desejada: ");
    scanf("%d", &opcao);
    return opcao;
}

int menuCadastros(){

    int opcao;
    system(LIMPAR); 
    printf("=====================================\n");
    printf("          Menu de Cadastros          \n");
    printf("=====================================\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Editar cliente\n");
    printf("3 - Excluir cliente\n");
    printf("4 - Voltar\n");
    printf("=====================================\n");
    printf("Insira a opcao desejada: ");
    scanf("%d", &opcao);

    return opcao;

}

void switchCadastros(int opcao, Cliente **clientes, int *numCLiente){

    switch(opcao){

        case 1:
            *clientes = cadastroClientes(*clientes, numCLiente);
            break;

        case 2:
            editarCliente(*clientes,*numCLiente);
            break;

        case 3:
            *clientes = excluirCliente(*clientes, numCLiente);
            break;

        case 4:
            return;
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");

    }
    
}

int menuEstoque()
{

    int opcao;
    system(LIMPAR); 
    printf("=====================================\n");
    printf("           Menu de Estoque           \n");
    printf("=====================================\n");
    printf("1 - Cadastros\n");
    printf("2 - Visualizar estoque\n");
    printf("3 - Voltar\n");
    printf("=====================================\n");
    printf("Insira a opcao desejada: ");
    scanf("%d", &opcao);

    return opcao;
}

void switchVizuEstoque(int opcao, Produto **produto, int *numProduto){

    switch(opcao){

        case 1:
            listarProdutos(*produto, *numProduto);
            break;

        case 2:
            buscarProduto(*produto, *numProduto);
            break;

        case 3:
            return;
            break;

        default:
            printf("Opcao invalida! Tente novamente\n");
        }

}

void switchCadastroEstoque(int opcao, Produto **produto, int *numProduto){

    switch(opcao){

        case 1:
            *produto = cadastroProdutos(*produto, numProduto);
            break;

        case 2:
            *produto = excluiProduto(*produto, numProduto);
            break;

        case 3:
            inserirEstoque(*produto, *numProduto);
            break;

        case 4:
            return;
            break;

        default:
            printf("Opcao invalida! Tente novamente\n");
    }
    
}

int menuVizuEstoque(){
    
    int opcao;
    system(LIMPAR);
    printf("=====================================\n");
    printf("           Menu de Estoque           \n");
    printf("=====================================\n");
    printf("1 - Listar Produtos\n");
    printf("2 - Pesquisar por produto\n");
    printf("3 - Voltar\n");
    printf("=====================================\n");
    printf("Insira a opcao desejada: ");
    scanf("%d", &opcao);
    return opcao;
}

int menuCadastroEstoque(){

    int opcao;
    system(LIMPAR);
    printf("=====================================\n");
    printf("         Cadastro de Estoque         \n");
    printf("=====================================\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Excluir produto\n");
    printf("3 - Editar no estoque\n");
    printf("4 - Voltar\n");
    printf("=====================================\n");
    printf("Insira a opcao desejada: ");
    scanf("%d", &opcao);
    return opcao;

}

void encerraPrograma()
{
    system(LIMPAR);
    printf("\nPrograma encerrado!\n");
    exit(SAIR);
}

Cliente *cadastroClientes(Cliente *clientes, int *numCliente)
{
    system(LIMPAR);
    int i;
    printf("===================================== Cadatrar Cliente =======================================\n");
    
    char cpfTemp[12];

    
    printf("Digite o nome do cliente: ");
    scanf(" %50[^\n]", clientes[*numCliente].nome);
    printf("Digite o CPF: ");
    scanf(" %11s", cpfTemp);
    
    for(i =0; i<*numCliente; i++){

        if(strcmp(clientes[i].cpf, cpfTemp) ==0){

            printf("CPF já cadastrado!\n");
            return clientes;
        }

    }

    (*numCliente)++;
    clientes = (Cliente *)realloc(clientes, (*numCliente) * sizeof(Cliente));
    if (clientes == NULL)
    {
        printf("Erro alocacao\n");
        exit(1);
    }
    Cliente *novoCliente = &clientes[*numCliente - 1];
    strcpy(novoCliente->cpf, cpfTemp);
    printf("Digite o telefone: ");
    scanf(" %14s", novoCliente->telefone);
    printf("Digite o endereço: ");
    scanf(" %99[^\n]", novoCliente->endereco);
    printf("Digite o email: ");
    scanf(" %49s", novoCliente->email);

    fileCliente(novoCliente);

    printf("Cliente cadastrado com sucesso!\n");

    return clientes;
}

void fileCliente(Cliente *cliente)
{
    FILE *arquivoCliente;
    arquivoCliente = fopen("Clientes.txt", "a+");

    if (arquivoCliente != NULL)
    {

        fprintf(arquivoCliente, "Nome: %s, CPF: %s, Telefone: %s, Endereco: %s, Email: %s\n", cliente->nome, cliente->cpf, cliente->telefone, cliente->endereco, cliente->email);
        fclose(arquivoCliente);
    }
    else
    {

        printf("Erro ao abrir arquivo!");
        exit(SAIR);
    }
}

int menuListar(){

    int opcao;
    system(LIMPAR);
    printf("=====================================\n");
    printf("           Listar Clientes           \n");
    printf("=====================================\n");
    printf("1 - Exibir todos clientes\n");
    printf("2 - Buscar cliente por CPF\n");
    printf("3 - Voltar\n");
    printf("=====================================\n");
    printf("Insira a opcao desejada: ");
    scanf("%d", &opcao);

    return opcao;

}

void switchListar(int opcao, Cliente **clientes, int *numCLiente){

    switch(opcao){

        case 1:
            listaTodosClientes(*clientes, *numCLiente);
            break;

        case 2:
            buscaCLiente(*clientes, *numCLiente);
            break;

        case 3:
            return;
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");

    }

}

Produto *cadastroProdutos(Produto *produto, int *numProduto)
{
    system(LIMPAR);
    printf("===================================== Cadastrar Produto =======================================\n");
    
    int codigoTemp;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigoTemp);

    for(int i =0; i<*numProduto;i++){

        if(codigoTemp == produto[i].codigo){

            printf("Código já cadastrado!\n");
            return produto;

        }

    }

    (*numProduto)++;
    produto = (Produto *)realloc(produto, (*numProduto) * sizeof(Produto));
    if (produto == NULL)
    {
        printf("Erro alocacao\n");
        exit(1);
    }
    Produto *novoProduto = &produto[*numProduto - 1];
    novoProduto->codigo = codigoTemp;
    
    getchar();
    printf("Digite o nome do produto: ");
    scanf("%51[^\n]", novoProduto->nome);
    printf("Digite o valor de custo do produto: ");
    scanf("%f", &novoProduto->valorDeCusto);
    printf("Digite o valor de venda do produto:");
    scanf("%f", &novoProduto->valorDeVenda);
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novoProduto->quantidade);

    fileEstoque(novoProduto);
    
    return produto;
}

void fileEstoque(Produto *produto)
{
    FILE *arquivoProduto;
    arquivoProduto = fopen("Estoque.txt", "a+");

    if (arquivoProduto != NULL)
    {
        fprintf(arquivoProduto, "Codigo: %d, Nome do produto: %s, Valor de custo: %.2f, Valor de Venda: %.2f, Quantidade: %d\n", produto->codigo, produto->nome, produto->valorDeCusto,produto->valorDeVenda, produto->quantidade);
        fclose(arquivoProduto);

    }
    else
    {
        printf("Erro ao abrir arquivo!");
        exit(SAIR);
    }
}

Cliente *excluirCliente(Cliente *clientes, int *numCliente)
{
    system(LIMPAR);
    printf("========================================== Excluir Cliente ===========================================\n\n");
    if (*numCliente == 0)
    {
        printf("Nao ha clientes cadastrados.\n");
        return clientes;
    }

    char cpfExcluir[12];
    bool clienteEncontrado = false;
    int i, j;
    char confirmar;

    printf("Digite o CPF do cliente a ser excluido: ");
    scanf("%s", cpfExcluir);
    system(LIMPAR);

    for (i = 0; i < *numCliente; i++)
    {
        if (strcmp(clientes[i].cpf, cpfExcluir) == 0)
        {
            clienteEncontrado = true;

            printf("\nCliente encontrado:\n");
            printf("Nome: %s\nCPF: %s\nTelefone: %s\n", clientes[i].nome, clientes[i].cpf, clientes[i].telefone);
            printf("Email: %s\nEndereco: %s\n", clientes[i].email, clientes[i].endereco);

            printf("Confirma que deseja excluir este cliente? (S/N): ");
            scanf(" %c", &confirmar);

            if (confirmar == 's' || confirmar == 'S')
            {
                for (j = i; j < *numCliente - 1; j++)
                {
                    clientes[j] = clientes[j + 1];
                    
                }
                (*numCliente)--;

                clientes = realloc(clientes, (*numCliente) * sizeof(Cliente));
                if (clientes == NULL && *numCliente > 0)
                {
                    printf("Erro ao realocar memoria.\n");
                    exit(1);
                }

                excluirClienteFile(cpfExcluir);
                printf("Cliente excluido com sucesso.\n");
            }
            else
            {
                printf("Exclusao cancelada.\n");
            }
            break;
        }
    }

    if (!clienteEncontrado)
    {
        printf("Cliente com CPF %s nao encontrado.\n", cpfExcluir);
    }

    return clientes;
}

void excluirClienteFile(char *cpfExcluir) {

    FILE *arquivoOriginal = fopen("Clientes.txt", "r");
    FILE *arquivoTemp = fopen("Clientes_temp.txt", "w");

    if (arquivoOriginal == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
    
    char linha[300];  // Buffer para armazenar cada linha
    bool clienteEncontrado = false;

    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL) {
        // Verifica se a linha atual contém o CPF do cliente a ser excluído
        if (strstr(linha, cpfExcluir) != NULL) {
            clienteEncontrado = true;
            // Ignora esta linha, pois é o cliente que queremos excluir
        } else {
            fputs(linha, arquivoTemp);  // Copia a linha para o arquivo temporário
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);

    // Remove o arquivo original e renomeia o temporário
    remove("Clientes.txt");
    rename("Clientes_temp.txt", "Clientes.txt");

    if (clienteEncontrado) {
        printf("Cliente com CPF %s excluído do arquivo com sucesso.\n", cpfExcluir);
    } else {
        printf("Cliente com CPF %s não encontrado no arquivo.\n", cpfExcluir);
    }
}

void listarProdutos(Produto *produto, int numProduto)
{
    system(LIMPAR);
    printf("===================================== Produtos do Estoque =======================================\n");
    if (numProduto == 0)
    {
        printf("Nao ha produtos cadastrados no estoque.\n");
        return;
    }

    for (int i = 0; i < numProduto; i++)
    {
        printf("Produto %d:\n", i + 1);
        printf("Codigo: %d\n", produto[i].codigo);
        printf("Nome: %s\n", produto[i].nome);
        printf("Quantidade: %d\n", produto[i].quantidade);
        printf("Valor de Custo: %.2f\n", produto[i].valorDeCusto);
        printf("Valor de Venda: %.2f\n", produto[i].valorDeVenda);
        printf("-------------------------\n");
    }
}

void listaTodosClientes(Cliente *clientes, int numClientes)
{
    system(LIMPAR);
    printf("===================================== Lista do Clientes Cadastrados =======================================\n");

    int i;
    if (numClientes == 0)
    {
        printf("Nao ha clientes cadastrados.\n");
        return;
    }

    for (i = 0; i < numClientes; i++)
    {
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s\n", clientes[i].nome);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Endereco: %s\n", clientes[i].endereco);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("Email: %s\n", clientes[i].email);
        printf("-------------------------\n");
    }
}

Produto *excluiProduto(Produto *produto, int *numProduto)
{
    system(LIMPAR);
    printf("========================================== Excluir Produto ===========================================\n\n");
    if (*numProduto == 0)
    {
        printf("Nao ha produtos cadastrados.\n");
        return produto;
    }

    int codigoExcluir, i, j;
    bool produtoEncontrado = false;
    char confirmar;

    printf("Digite o codigo do produto a ser excluido: ");
    scanf("%d", &codigoExcluir);
    system(LIMPAR);

    for (i = 0; i < *numProduto; i++)
    {
        if (produto[i].codigo == codigoExcluir)
        {
            produtoEncontrado = true;

            printf("\nProduto encontrado:\n");
            printf("Codigo: %d\nNome: %s\nQuantidade: %d\n", produto[i].codigo, produto[i].nome, produto[i].quantidade);
            printf("Valor de Custo: %.2f\nValor de Venda: %.2f\n", produto[i].valorDeCusto, produto[i].valorDeVenda);

            printf("Confirma que deseja excluir este produto? (S/N): ");
            scanf(" %c", &confirmar);

            if (confirmar == 's' || confirmar == 'S')
            {
                for (j = i; j < *numProduto - 1; j++)
                {
                    produto[j] = produto[j + 1];
                }
                (*numProduto)--;

                produto = realloc(produto, (*numProduto) * sizeof(Produto));
                if (produto == NULL && *numProduto > 0)
                {
                    printf("Erro ao realocar memoria.\n");
                    exit(1);
                }
                excluirProdutoFile(codigoExcluir);
                printf("Produto excluido com sucesso.\n");
            }
            else
            {
                printf("Exclusao cancelada.\n");
            }
            break;
        }
    }
    if (!produtoEncontrado)
    {
        printf("Produto com codigo %d nao encontrado.\n", codigoExcluir);
    }

    return produto;
}

void excluirProdutoFile(int codigoExcluir)
{
    FILE *arquivoOriginal = fopen("Estoque.txt", "r");
    FILE *arquivoTemp = fopen("Estoque_temp.txt", "w");

    if (arquivoOriginal == NULL || arquivoTemp == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    char linha[300]; 
    bool produtoEncontrado = false;

    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL)
    {
        Produto produtoTemp;

        if (sscanf(linha, "Codigo: %d, Nome do produto: %49[^,], Valor de custo: %f, Valor de Venda: %f, Quantidade: %d\n", 
                   &produtoTemp.codigo, produtoTemp.nome, &produtoTemp.valorDeCusto, &produtoTemp.valorDeVenda, &produtoTemp.quantidade) == 5)
        {
            if (produtoTemp.codigo == codigoExcluir)
            {
                produtoEncontrado = true;
            }
            else
            {
                fputs(linha, arquivoTemp); 
            }
        }
        else
        {
         
            fputs(linha, arquivoTemp);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);

  
    remove("Estoque.txt");
    rename("Estoque_temp.txt", "Estoque.txt");

    if (produtoEncontrado)
    {
        printf("Produto com código %d excluído do arquivo com sucesso.\n", codigoExcluir);
    }
    else
    {
        printf("Produto com código %d não encontrado no arquivo.\n", codigoExcluir);
    }
}

void buscarProduto(Produto *produto, int numProduto)
{
    int codBusca, i;
    bool prodEncontrado = false;

    printf("Digite o codigo do produto a ser buscado: ");
    scanf("%d", &codBusca);

    for (i = 0; i < numProduto; i++)
    {
        if (produto[i].codigo == codBusca)
        {
            prodEncontrado = true;

            printf("\n---Produto encontrado---\n");
            printf("Codigo: %d\n", produto[i].codigo);
            printf("Nome: %s\n", produto[i].nome);
            printf("Quantidade: %d\n", produto[i].quantidade);
            printf("Valor de Custo: %.2f\n", produto[i].valorDeCusto);
            printf("Valor de Venda: %.2f\n", produto[i].valorDeVenda);
            printf("-------------------------\n");

            break;
        }
    }
    if (!prodEncontrado)
    {
        printf("Produto com codigo %d nao encontrado.\n", codBusca);
    }
}

void buscaCLiente(Cliente *clientes, int numClientes){

    int i;
    bool clienteEncontrado = false;
    char cpfBusca[11];

    printf("Digite o CPF do cliente a ser buscado: ");
    scanf("%11s", cpfBusca);

    for (i = 0; i < numClientes; i++)
    {
        if (strcmp(clientes[i].cpf, cpfBusca) == 0)
        {
            clienteEncontrado = true;

            printf("\n---Cliente encontrado---\n");
            printf("Nome: %s\n", clientes[i].nome);
            printf("CPF: %s\n", clientes[i].cpf);
            printf("Telefone: %s\n", clientes[i].telefone);
            printf("Endereco: %s\n", clientes[i].endereco);
            printf("Email: %s\n", clientes[i].email);
            printf("-------------------------\n");

            break;
        }
    }
    if (!clienteEncontrado)
    {
        printf("Cliente com CPF %s nao encontrado.\n", cpfBusca);
    }

}

void inserirEstoque(Produto *produto, int numProduto)


{
    system(LIMPAR);
    int codProduto,i;
    bool prodEncontrado = false;

    printf("========================================== Alterar ===========================================\n");
    printf("Digite o codigo do produto pra alterar ao estoque: ");
    scanf("%d", &codProduto);
    system(LIMPAR);

    for (i = 0; i < numProduto; i++)
    {
        if (produto[i].codigo == codProduto)
        {
            prodEncontrado = true;
            printf("\nProduto encontrado:\n");
            printf("Codigo: %d\n", produto[i].codigo);
            printf("Nome: %s\n", produto[i].nome);
            printf("Quantidade atual em estoque: %d\n", produto[i].quantidade);
            printf("Valor de Custo: %.2f\n", produto[i].valorDeCusto);
            printf("Valor de Venda: %.2f\n", produto[i].valorDeVenda);

            int alteracao;

            do
            {
                alteracao = menuAlterarEstoque();
                switchAlteracao(alteracao,produto,numProduto,i);

            } while (alteracao != 4);

            break;
        }
    }

    if (!prodEncontrado)
    {
        printf("Produto com codigo %d nao encontrado no estoque.\n", codProduto);
        return;
    }
}

int menuAlterarEstoque(){

    int escolherAltercao;
    printf("==========================================\n");
    printf("                Alterar                   \n");
    printf("==========================================\n");
    printf("1 - Inserir Quantidade no Estoque\n");
    printf("2 - Alterar Valor de Custo\n");
    printf("3 - Alterar Valor de Venda\n");
    printf("4 - Voltar\n");
    printf("==========================================\n");
    printf("Digite a opção que deseja alterar: ");
    scanf("%d", &escolherAltercao);
    return escolherAltercao;
}

void switchAlteracao(int alteracao, Produto *produto, int numProduto, int i){

    switch (alteracao)
    {
        case 1:
            alteraQTD(produto, numProduto,i);
            break;

        case 2:
            alteraValorCusto(produto,numProduto,i); 
            break;
        case 3:
            alteraValorVenda(produto,numProduto,i);  
            break;
        case 4:
            return;
            break;
        default:
            printf("Opcao invalida! Tente novamente\n");
            break;
        }

}

void alteraValorVenda(Produto *produto, int numProdutos,int i){

    float vVendaAlterar;

    printf("Digite o valor a ser alterado: ");
    scanf("%f", &vVendaAlterar);
    if (vVendaAlterar > 0)
    {
        produto[i].valorDeVenda = vVendaAlterar;
        printf("Novo valor de venda do produto '%s' (Codigo: %d): %.2f\n", produto[i].nome, produto[i].codigo, produto[i].valorDeVenda);
        atualizarEstoqueFile(produto, numProdutos);
    }
    else
    {
        printf("Valor invalido! O valor deve ser maior que zero.\n");
    }
}
void alteraValorCusto(Produto *produto, int numProdutos,int i){
    
    float vCustoAlterar; 
    printf("Digite o valor a ser alterado: ");
    scanf("%f", &vCustoAlterar);
    if (vCustoAlterar > 0)
    {
        produto[i].valorDeCusto = vCustoAlterar;
        printf("Novo valor de custo do produto '%s' (Codigo: %d): %.2f\n", produto[i].nome, produto[i].codigo, produto[i].valorDeCusto);
        atualizarEstoqueFile(produto,numProdutos);
    }
    else
    {
        printf("Valor invalido! O valor deve ser maior que zero.\n");
    }
}

void alteraQTD(Produto *produto, int numProdutos, int i){

    int qtdAdicionar;
    printf("Digite a quantidade a ser adicionada: ");
    scanf("%d", &qtdAdicionar);
    if (qtdAdicionar > 0)
        {
            produto[i].quantidade += qtdAdicionar;
            printf("Nova quantidade em estoque do produto '%s' (Codigo: %d): %d\n", produto[i].nome, produto[i].codigo, produto[i].quantidade);
            atualizarEstoqueFile(produto,numProdutos);
        }
        else
        {
            printf("Quantidade invalida! A quantidade a ser adicionada deve ser maior que zero.\n");
        }
}

void realizarPedido(Cliente *clientes, int numClientes, Produto *produtos, int numProdutos)
{
    char cpf[12];
    int codigoProduto, quantidadeNova, i, j;
    bool clienteEncontrado = false, produtoEncontrado = false;
    float valorGasto;

    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf);

    for (i = 0; i < numClientes; i++)
    {
        if (strcmp(clientes[i].cpf, cpf) == 0)
        {
            printf("Cliente encontrado: %s\n", clientes[i].nome);
            clienteEncontrado = true;
            break;
        }
    }

    if (!clienteEncontrado)
    {
        printf("Cliente não encontrado!\n");
        return;
    }

    printf("Digite o código do produto: ");
    scanf("%d", &codigoProduto);

    for (j = 0; j < numProdutos; j++)
    {   
        if (produtos[j].codigo == codigoProduto)
        {
            if(produtos[j].quantidade ==0){

                printf("Produto sem estoque!\n");
                return;

            }else{
                printf("\n----------------------------------------------------\n");
                printf("\nProduto: %s\nQuantidade em estoque: %d\nValor: %.2f\n", produtos[j].nome, produtos[j].quantidade, produtos[j].valorDeVenda);
                produtoEncontrado = true;
                break;
            }
        }
    }

    if (!produtoEncontrado)
    {
        printf("Produto não encontrado!\n");
        return;
    }

    printf("\n----------------------------------------------------\n");
    printf("Digite a quantidade desejada: ");
    scanf("%d", &quantidadeNova);

    if (produtos[j].quantidade < quantidadeNova)
    {
        printf("Estoque insuficiente!\n");
        return;
    }

    char resposta;
    printf("\n----------------------------------------------------\n");
    printf("Valor do pedido: %.2f\nConfirmar? (S/N)\n", produtos[j].valorDeVenda*quantidadeNova);
    scanf(" %c",&resposta);

    if(resposta == 'S' || resposta == 's'){

        produtos[j].quantidade -= quantidadeNova;
        valorGasto = produtos[j].valorDeVenda * quantidadeNova;

        printf("Pedido realizado com sucesso! Total: R$ %.2f\n", valorGasto);

        atualizarEstoqueFile(produtos, numProdutos);
        salvarPedidoNoArquivo(*clientes, produtos, &quantidadeNova, numProdutos, valorGasto,codigoProduto);
        return;

    }else{

        printf("Pedido cancelado!\n");
        return;

    }

}

void atualizarEstoqueFile(Produto *produtos, int numProdutos)
{
    FILE *arquivoProduto = fopen("Estoque.txt", "w"); // modo "w" para sobrescrever

    if (arquivoProduto != NULL)
    {
        for (int i = 0; i < numProdutos; i++)
        {
            fprintf(arquivoProduto, "Codigo: %d, Nome do produto: %s, Valor de custo: %.2f, Valor de Venda: %.2f, Quantidade: %d\n",
                    produtos[i].codigo, produtos[i].nome, produtos[i].valorDeCusto, produtos[i].valorDeVenda, produtos[i].quantidade);
        }
        fclose(arquivoProduto);
    }
    else
    {
        printf("Erro ao abrir arquivo para atualização do estoque!\n");
        exit(SAIR);
    }
}

void salvarPedidoNoArquivo(Cliente cliente, Produto *produtosComprados, int *quantidades, int numProdutos, float totalPedido, int codigoComprado)
{
    FILE *arquivoPedido = fopen("Pedidos.txt", "a+");
    if (arquivoPedido == NULL)
    {
        printf("Erro ao abrir arquivo de pedidos!\n");
        return;
    }

    fprintf(arquivoPedido, "Cliente: %s, CPF: %s, Total do Pedido: %.2f\n", cliente.nome, cliente.cpf, totalPedido);
    fprintf(arquivoPedido, "Produtos Comprados:\n");

    for (int i = 0; i < numProdutos; i++)
    {
        if(produtosComprados[i].codigo == codigoComprado){

            fprintf(arquivoPedido, "- Produto: %s, Codigo: %d, Quantidade: %d, Preço Unitário: %.2f, Total: %.2f\n",
                produtosComprados[i].nome,
                produtosComprados[i].codigo,
                quantidades[i],
                produtosComprados[i].valorDeVenda,
                produtosComprados[i].valorDeVenda * quantidades[i]);

        }

    }

    fprintf(arquivoPedido, "---------------------------------------\n");
    fclose(arquivoPedido);

    printf("Pedido salvo com sucesso no arquivo!\n");
}

void editarCliente(Cliente *clientes, int numClientes)
{
    system(LIMPAR);
    char cpf[12];
    bool clienteEncontrado = false;

    printf("========================================== Editar Cliente ===========================================\n");
    printf("Digite o CPF do cliente para editar (somente números): ");
    scanf("%s", cpf);
    system(LIMPAR);

    for (int i = 0; i < numClientes; i++)
    {
        if (strcmp(clientes[i].cpf, cpf) == 0)
        {
            clienteEncontrado = true;
            printf("\nCliente encontrado:\n");
            printf("Nome: %s\n", clientes[i].nome);
            printf("CPF: %s\n", clientes[i].cpf);
            printf("Telefone atual: %s\n", clientes[i].telefone);
            printf("Email atual: %s\n", clientes[i].email);
            printf("Endereço atual: %s\n", clientes[i].endereco);

            int alteracao;
            do
            {
                alteracao = menuAlterarCliente();
                switchAlteracaoCliente(alteracao, clientes, i, numClientes);

            } while (alteracao != 4);
            break;
        }
    }

    if (!clienteEncontrado)
    {
        printf("Cliente com CPF %s não encontrado.\n", cpf);
    }
}

int menuAlterarCliente()
{
    int escolherAlteracao;
   printf("==========================================\n");
    printf("           Alterar Cliente                \n");
    printf("==========================================\n");
    printf("1 - Alterar Telefone\n");
    printf("2 - Alterar Email\n");
    printf("3 - Alterar Endereço\n");
    printf("4 - Voltar\n");
    printf("==========================================\n");
    printf("Digite a opção que deseja alterar: ");
    scanf("%d", &escolherAlteracao);
    return escolherAlteracao;
}

void switchAlteracaoCliente(int alteracao, Cliente *clientes, int i, int numClientes)
{
    switch (alteracao)
    {
    case 1:
        alteraTelefone(clientes, i, numClientes);
        break;
    case 2:
        alteraEmail(clientes, i, numClientes);
        break;
    case 3:
        alteraEndereco(clientes, i, numClientes);
        break;
    case 4:
        return;
        break;
    default:
        printf("Opção inválida! Tente novamente.\n");
        break;
    }
}

void alteraTelefone(Cliente *clientes, int i, int numClientes)
{
    char novoTelefone[15];
    printf("Digite o novo telefone: ");
    scanf("%s", novoTelefone);
    strcpy(clientes[i].telefone, novoTelefone);
    printf("Telefone atualizado para %s.\n", clientes[i].telefone);
    atualizarClienteFile(clientes, numClientes);
}

void alteraEmail(Cliente *clientes, int i, int numClientes)
{
    char novoEmail[50];
    printf("Digite o novo email: ");
    scanf("%s", novoEmail);
    strcpy(clientes[i].email, novoEmail);
    printf("Email atualizado para %s.\n", clientes[i].email);
    atualizarClienteFile(clientes, numClientes);
}

void alteraEndereco(Cliente *clientes, int i, int numClientes)
{
    char novoEndereco[100];
    printf("Digite o novo endereço: ");
    scanf(" %[^\n]s", novoEndereco);
    strcpy(clientes[i].endereco, novoEndereco);
    printf("Endereço atualizado para %s.\n", clientes[i].endereco);
    atualizarClienteFile(clientes, numClientes);
}

void atualizarClienteFile(Cliente *clientes, int numClientes)
{
    FILE *arquivoCliente = fopen("Clientes.txt", "w"); 
    if (arquivoCliente != NULL)
    {
        for (int i = 0; i < numClientes; i++)
        {
            fprintf(arquivoCliente, "Nome: %s, CPF: %s, Telefone: %s, Endereco: %s, Email: %s\n",
                    clientes[i].nome, clientes[i].cpf, clientes[i].telefone, clientes[i].endereco, clientes[i].email);
        }
        fclose(arquivoCliente);
    }
    else
    {
        printf("Erro ao abrir arquivo para atualização dos clientes!\n");
        exit(SAIR);
    }
}
