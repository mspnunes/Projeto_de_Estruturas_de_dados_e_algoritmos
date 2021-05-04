#include "listabens.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

//==============================================================
//Construtor por defeito
ListaBens:: ListaBens(){
    cabeca = NULL;
}

//==============================================================
//Destrutor
ListaBens::~ListaBens(){
    CNoListaBens *atual, *proximo;

    atual=cabeca;
    while(atual!=NULL){
        proximo=atual->proximo;
        delete atual;
        atual=proximo;
    }
}

//==============================================================
//Metodo para inserir um bem
void ListaBens:: insereBemNoEspaco(int espaco,ListaEspacos &espacos, ListaPessoasResponsaveis &pessoa, ListaTipologiasBens &tipologia)
{
    char x;
    bool flag;
    CNoListaBens *novo=new CNoListaBens;
    CNoListaBens *atual;

    //pedido do codigo
    do{
        do{
            cout << "Insira o codigo do seu bem (10 digitos):\n";
            cin >> novo->codigo;
        }while(novo->codigo < 0 || novo->codigo > 9999999999);
        CNoListaBens *aux=cabeca;

        bool q = false;
        if(cabeca==NULL)
            break;
        else{
            while(aux!=NULL){
                if(aux->codigo == novo->codigo)
                    q = true;
                aux=aux->proximo;
            }
        }
        if (q == true)
            cout << "O codigo do bem que inseriu ja existe\n";
        else break;
    }while(true);

    //pedido da tipologia
    cout << "\nLista de tipologias de bens:\n";
    tipologia.listar_tipologia();
    do{
        do{
            cout << "Insira o codigo da tipologia do seu bem (3 digitos):\n";
            cin >> novo->tipologia;
        }while(novo->tipologia < 0 || novo->tipologia > 999);
        flag = tipologia.procuraItem(novo->tipologia);
        if (flag == true)
            break;
        cout << "A tipologia nao existe\n";
        while(true){
            cout << "Quer inserir uma nova tipologia com este codigo?(s/n)\n";
            cin >> x;
            if(x == 's' || x == 'S')
            {
                tipologia.cria_tipologia(novo->tipologia);
                break;
            }
            else if(x == 'n' || x == 'N')
            {
                novo->tipologia = INT_MIN;
                break;
            }
            else cout << "Opcao invalida\n";
        }
    }while(novo->tipologia == INT_MIN);

    //marcar a tipologia como inventariada
    tipologia.marca_como_inventariado(novo->tipologia);

    //pedido da decricao
    cout << "Insira a descricao do bem (no maximo 255 caracteres):\n";
    cin.ignore();
    cin.getline(novo->descricao, sizeof(novo->descricao));

    //pedido da data de incorporacao
    do{
        cout << "Insira a data de incorporacao(DDMMAAAA):\n";
        cin >> novo->data_incorporacao;
    }while(novo->data_incorporacao < 0 || novo->data_incorporacao > 99999999);

    novo->codigo_espaco=espaco;

    //marcar o espaco como inventariado
    espacos.marca_como_inventariado(novo->codigo_espaco);

    //pedido do valor do bem
    do{
        cout << "Insira o valor do bem:\n";
        cin >> novo->valor_bem;
    }while(novo->valor_bem < 0);

    //pedido do numero mecanografico
    cout << "\nLista de pessoas responsaveis:\n";
    pessoa.listar_responsaveis();
    do{
        do{
            cout << "Insira o numero mecanografico da pessoa responsavel (5 digitos):\n";
            cin >> novo->numero_mecanografico;
        }while(novo->numero_mecanografico < 0 || novo->numero_mecanografico > 99999);
        flag = pessoa.procuraItem(novo->numero_mecanografico);
        if (flag == true)
            break;
        cout << "Esta pessoa responsavel nao existe\n";
        while(true){
            cout << "Quer inserir uma nova pesssoa responsavel com este codigo?(s/n)\n";
            cin >> x;
            if(x == 's' || x == 'S')
            {
                pessoa.cria_responsavel(novo->numero_mecanografico, espaco, espacos);
                break;
            }
            else if(x == 'n' || x == 'N')
            {
                novo->numero_mecanografico = INT_MIN;
                break;
            }
            else cout << "Opcao invalida\n";
        }
    }while(novo->numero_mecanografico == INT_MIN);

    //marcar a pessoa como inventariada
    pessoa.marca_como_inventariado(novo->numero_mecanografico);

    novo->abatido = false;
    novo->data_abate = INT_MIN;

    novo->proximo=NULL;

    if(cabeca==NULL){
        cabeca=novo;
    }else{
        atual=cabeca;
        while(atual->proximo!=NULL)
            atual=atual->proximo;
        atual->proximo=novo;
    }
    ofstream escreve("bens.txt");
    if(!escreve)
    {
        //cout << "O ficheiro de escrita nao abriu\n";
        return;
    }
    escreve << novo->descricao << endl;
    escreve << novo->codigo << endl;
    escreve << novo->tipologia << endl;
    escreve << novo->data_incorporacao << endl;
    escreve << novo->codigo_espaco << endl;
    escreve << novo->valor_bem << endl;
    escreve << novo->numero_mecanografico << endl;
    escreve << novo->data_abate << endl;
    if(novo->abatido == false)
        escreve << "0\n";
    else escreve << "1\n";
    escreve.close();
}

//==============================================================
//Metodo para listar bens por espaco
void ListaBens::listaBensPorEspaco(int espaco)
{
    CNoListaBens * atual=cabeca;
    int i=1;

    while (atual!=NULL) {
        if(atual->codigo_espaco==espaco)
        {
            cout<<"\n==Bem "<< i <<"==\n";

            cout << "Codigo: ";
            cout << atual->codigo << endl;
            cout << "Tipologia: ";
            cout << atual->tipologia << endl;
            cout << "Descricao do bem: ";
            cout << atual->descricao << endl;
            cout << "Data de incorporacao (DDMMAAAA): ";
            cout << atual->data_incorporacao << endl;
            cout << "Codigo do espaco: ";
            cout << atual->codigo_espaco << endl;
            cout << "Valor do bem: ";
            cout << atual->valor_bem << endl;
            cout << "Valor mecanografico do responsavel: ";
            cout << atual->numero_mecanografico << endl;

            if(atual->abatido==true)
            {
                cout << "Data de abate (DDMMAAAA): ";
                cout << atual->data_abate << endl;
            }
            i++;
        }
        atual=atual->proximo;
    }
    if (i == 1)
        cout << "Nao existem bens inventariados no espaco selecionado\n";
}

//==============================================================
//Metodo para abater os bens de um espaco
void ListaBens::abateBemDoEspaco(int espaco)
{
    CNoListaBens *atual = cabeca;
    if(cabeca == NULL)
    {
        cout << "Nao existe nenhum bem no inventario\n";
        return;
    }

    cout << "\nLista de bens inventariados no espaco selecionado:\n";
    listaBensPorEspaco(espaco);

    int c;
    do{
        cout << "\nInsira o codigo do bem que quer abater (10 digitos):\n";
        cin >> c;
    }while (c < 0 || c > 9999999999);

    bool flag = false;
    while (atual != NULL)
    {
        if (atual->codigo == c && atual->codigo_espaco == espaco)
        {
            do{
                cout << "Insira a data em que o bem foi abatido (DDMMAAAA):\n";
                cin >> atual->data_abate;
            }while(atual->data_abate < 0 || atual->data_abate > 99999999);
            atual->abatido=true;
            cout << "O bem foi abatido\n";
            flag = true;
        }
        atual = atual->proximo;
    }
    if (flag == false)
        cout << "O bem que quer abater nao existe.\n";
    escreve_ficheiro();
}


//==============================================================
//Metodo auxiliar para trocar os dados de dois nos
void ListaBens:: trocaNos(CNoListaBens *x, CNoListaBens *y){

    //aux = x;
    CNoListaBens *aux = new CNoListaBens;
    aux->codigo = x->codigo;
    aux->tipologia = x->tipologia;
    strcpy(aux->descricao, x->descricao);
    aux->data_incorporacao = x->data_incorporacao;
    aux->codigo_espaco = x->codigo_espaco;
    aux->valor_bem = x->valor_bem;
    aux->numero_mecanografico = x->numero_mecanografico;
    aux->abatido = x->abatido;
    aux->data_abate = x->data_abate;
    //x = y;
    x->codigo = y->codigo;
    x->tipologia = y->tipologia;
    strcpy(x->descricao, y->descricao);
    x->data_incorporacao = y->data_incorporacao;
    x->codigo_espaco = y->codigo_espaco;
    x->valor_bem = y->valor_bem;
    x->numero_mecanografico = y->numero_mecanografico;
    x->abatido = y->abatido;
    x->data_abate = y->data_abate;
    //y = aux;
    y->codigo = aux->codigo;
    y->tipologia = aux->tipologia;
    strcpy(y->descricao, aux->descricao);
    y->data_incorporacao = aux->data_incorporacao;
    y->codigo_espaco = aux->codigo_espaco;
    y->valor_bem = aux->valor_bem;
    y->numero_mecanografico = aux->numero_mecanografico;
    y->abatido = aux->abatido;
    y->data_abate = aux->data_abate;

}

//==============================================================
//Metodo para ordenar um lista de bens por espaco
void ListaBens:: ordenacaoBolha(){
    bool houveTroca;
    CNoListaBens *atual = cabeca;
    int contador = 0;
    if(cabeca==NULL)
    {
        cout << "Nao existem bens guardados\n" << endl;
        return;
    }
    while (atual != NULL)
    {
        contador++;
        atual = atual->proximo;
    }
    CNoListaBens *anterior;
    for (int i=0; i<contador-1; i++)
    {
        houveTroca = false;
        anterior = cabeca;
        atual = anterior->proximo;
        for (int j = 1; j<contador-i; j++)
        {
            if((atual->codigo_espaco) < (anterior->codigo_espaco))
            {
                trocaNos(atual, anterior);
                houveTroca = true;
            }
            anterior = atual;
            atual = atual->proximo;
        }
    if (!houveTroca) break;
    }
}

//==============================================================
//Metodo para listar uma lista de bens ordenada por espacos
void ListaBens::mostraPorOrdem()
{
    CNoListaBens * atual=cabeca;
    int i = 1;

    if(cabeca==NULL)
    {
        cout << "Nao existem bens guardados na lista\n" << endl;
        return;
    }
    ordenacaoBolha();

    while (atual!=NULL) {
        cout<<"\n==Bem "<< i <<"==\n";

        cout << "Codigo: ";
        cout << atual->codigo << endl;
        cout << "Tipologia: ";
        cout << atual->tipologia << endl;
        cout << "Descricao do bem: ";
        cout << atual->descricao << endl;
        cout << "Data de incorporacao (DDMMAAAA): ";
        cout << atual->data_incorporacao << endl;
        cout << "Codigo do espaco: ";
        cout << atual->codigo_espaco << endl;
        cout << "Valor do bem: ";
        cout << atual->valor_bem << endl;
        cout << "Valor mecanografico do responsavel: ";
        cout << atual->numero_mecanografico << endl;

        if(atual->abatido==true)
        {
            cout << "Data de abate (DDMMAAAA): ";
            cout << atual->data_abate << endl;
        }
        i++;
        atual=atual->proximo;
    }
    escreve_ficheiro();
}

//==============================================================
//Metodo para alienar espaco
void ListaBens:: alienarEspaco(){
    CNoListaBens *atual = cabeca;
    if (atual == NULL)
    {
        //cout << "Nao ha bens no inventario\n";
        return;
    }
    int codigo;
    cout << "Insira o codigo do espaco que pretende alienar (4 digitos):\n ";
    cin >> codigo;
    char x;
    do{
        cout << "Tem a certeza que quer alienar este espaco? (s/n)\n";
        cin >> x;
        if (x == 'n' || x == 'N')
            return;
        else if (x == 's' || x == 'S')
            break;
        cout << "Opcao invalida\n";
    }while (true);

    while (atual != NULL)
    {
        if (atual->codigo_espaco == codigo)
        {
            if (atual->abatido == false)
            {
                atual->abatido = true;
                cout << "Insira a data de abate do bem " << atual->codigo
                     << " cuja descricao e: " << atual->descricao << " (DDMMAAAA)\n";
                cin >> atual->data_abate;
            }
        }
        atual = atual->proximo;
    }
    cout << "O espaco foi alienado\n";
    escreve_ficheiro();
}

//==============================================================
//Metodo para mudar o espaço de um bem
void ListaBens::mudar_espaco(int x, ListaEspacos &espaco, ListaPessoasResponsaveis &pessoa){
    int c, novo;
    char r;
    CNoListaBens *atual;
    do{
        listaBensPorEspaco(x);
        bool encontrado = false;
        do{
            cout << "Insira o codigo do seu bem (10 digitos):\n";
            cin >> c;
        }while(c < 0 || c > 9999999999);
        atual = cabeca;
        while(atual != NULL)
        {
            if (atual->codigo == c && atual->codigo_espaco == x)
            {
                encontrado = true;
                cout << "\nLista de espacos:\n";
                espaco.listar_espaco();
                bool flag;
                char res;
                do{   //pedido do novo espaço e verificaçao se o espaco existe
                    do{
                        cout << "Insira o codigo do espaco para o qual pretende mudar o bem (4 digitos):\n";
                        cin >> novo;
                    }while(novo < 0 || novo > 9999);
                    flag = espaco.procuraItem(novo);
                    if (flag == true)
                        break;
                    cout << "O espaco nao existe\n";
                    while(true){
                        cout << "Quer inserir um novo espaco com este codigo?(s/n)\n";
                        cin >> res;
                        if(res == 's' || res == 'S')
                        {
                            espaco.cria_espaco(novo);
                            break;
                        }
                        else if(res == 'n' || res == 'N')
                        {
                            novo = INT_MIN;
                            break;
                        }
                        else cout << "Opcao invalida\n";
                    }
                }while(novo == INT_MIN);
                atual->codigo_espaco = novo;
                espaco.marca_como_inventariado(atual->codigo_espaco);
                do{         //mudanca de responsavel
                    cout << "Quer mudar tambem o responsavel por este bem?(s/n)\n";
                    char a;
                    cin >> a;
                    if (a == 's' || a == 'S')
                    {
                        int pes = atual->numero_mecanografico;
                        cout << "\nLista de pessoas responsaveis:\n";
                        pessoa.listar_responsaveis();
                        do{
                            do{
                                cout << "Insira o numero mecanografico da nova pessoa responsavel (5 digitos):\n";
                                cin >> atual->numero_mecanografico;
                            }while(atual->numero_mecanografico < 0 || atual->numero_mecanografico > 99999);
                            flag = pessoa.procuraItem(atual->numero_mecanografico);
                            if (flag == true)
                                break;
                            cout << "Esta pessoa responsavel nao existe\n";
                            while(true){
                                cout << "Quer inserir uma nova pesssoa responsavel com este codigo?(s/n)\n";
                                cin >> x;
                                if(x == 's' || x == 'S')
                                {
                                    pessoa.cria_responsavel(atual->numero_mecanografico, x, espaco);
                                    break;
                                }
                                else if(x == 'n' || x == 'N')
                                {
                                    atual->numero_mecanografico = INT_MIN;
                                    break;
                                }
                                else cout << "Opcao invalida\n";
                            }
                        }while(atual->numero_mecanografico == INT_MIN);
                        pessoa.marca_como_inventariado(atual->numero_mecanografico);
                        if(procura_pessoa(pes) == false)
                            pessoa.tira_de_inventariado(pes);
                        break;
                    }
                    else if (a == 'n' || a == 'N')
                    {
                        break;
                    }
                    else cout << "Opcao invalida\n";
                }while (true);
                break;
            }
            atual = atual->proximo;
        }
        if (encontrado == false)
            cout << "O codigo que inseriu nao existe associado ao espaco com o codigo: " << x << endl;
        do{
            cout << "Deseja mudar de espaco mais algum bem? (s/n)\n";
            cin >> r;
            if(r == 's' || r == 'S')
                break;
            else if(r == 'n' || r == 'N')
            {
                if(procura_espaco(x) == false)
                    espaco.tira_de_inventariado(x);
                if(pessoa.procura_espaco(x) == false)
                    espaco.tira_de_associado(x);
                escreve_ficheiro();
                return;
            }
            else cout << "Opcao invalida\n";
        }while (true);
    }while(true);
}

//==============================================================
//Metodo para ver se um espaco existe no inventario
bool ListaBens:: procura_espaco(int x){
    CNoListaBens *atual = cabeca;
    if(cabeca == NULL)
        return false;
    while(atual != NULL)
    {
        if(atual->codigo_espaco == x)
            return true;
        atual = atual->proximo;
    }
    return false;
}

//==============================================================
//Metodo para ver se uma pessoa existe no inventario
bool ListaBens:: procura_pessoa(int x){
    CNoListaBens *atual = cabeca;
    if(cabeca == NULL)
        return false;
    while(atual != NULL)
    {
        if(atual->numero_mecanografico == x)
            return true;
        atual = atual->proximo;
    }
    return false;
}

//==============================================================
//Metodo para listar o inventario de uma tipologia
void ListaBens:: lista_inventario_tipologia(ListaTipologiasBens &t){
    int tipologia;
    double ativos = 0, abatidos = 0;
    cout << "\nLista de tipologias:\n";
    t.listar_tipologia();
    do{
        cout << "Insira o codigo da tipologia da qual quer listar o inventario (3 digitos):\n";
        cin >> tipologia;
    }while(tipologia < 0 || tipologia > 999);
    int contador = 0;

    CNoListaBens *atual = cabeca;
    if(cabeca == NULL)
    {
        cout << "Nao existem bens guardados no inventario\n";
        return;
    }

    cout << "Lista de tipologias com o codigo: " << tipologia << " no inventario:\n";
    while(atual != NULL){
        if(tipologia == atual->tipologia)
        {
            contador++;
            cout<<"\n==Bem "<< contador <<"==\n";

            cout << "Codigo: ";
            cout << atual->codigo << endl;
            cout << "Descricao do bem: ";
            cout << atual->descricao << endl;
            cout << "Data de incorporacao (DDMMAAAA): ";
            cout << atual->data_incorporacao << endl;
            cout << "Codigo do espaco: ";
            cout << atual->codigo_espaco << endl;
            cout << "Valor do bem: ";
            cout << atual->valor_bem << endl;
            cout << "Valor mecanografico do responsavel: ";
            cout << atual->numero_mecanografico << endl;

            if(atual->abatido==true)
            {
                cout << "Data de abate (DDMMAAAA): ";
                cout << atual->data_abate << endl;
                abatidos = abatidos + atual->valor_bem;
            }
            else ativos = ativos + atual->valor_bem;
        }
        atual = atual->proximo;
    }
    if (contador == 0)
    {
        cout << "Nao existem bens inventariados da tipologia que inseriu\n";
        return;
    }
    else
    {
        cout << "Total dos bens desta tipologia: " << ativos + abatidos << endl;
        cout << "Subtotal dos bens ativos: " << ativos << endl;
        cout << "Subtotal dos bens abatidos: " << abatidos << endl;
    }
}

//==============================================================
//Metodo para listar o inventario de um espaco
void ListaBens:: lista_inventario_espaco(ListaEspacos &e){
    int espaco;
    double ativos = 0, abatidos = 0;
    cout << "\nLista de espacos:\n";
    e.listar_espaco();
    do{
        cout << "Insira o codigo do espaco do qual quer listar o inventario (4 digitos):\n";
        cin >> espaco;
    }while(espaco < 0 || espaco > 9999);
    int contador = 0;

    CNoListaBens *atual = cabeca;
    if(cabeca == NULL)
    {
        cout << "Nao existem bens guardados no inventario\n";
        return;
    }

    cout << "Lista de espacos com o codigo: " << espaco << " no inventario:\n";
    while(atual != NULL){
        if(espaco == atual->codigo_espaco)
        {
            contador++;
            cout<<"\n==Bem "<< contador <<"==\n";

            cout << "Codigo: ";
            cout << atual->codigo << endl;
            cout << "Tipologia: ";
            cout << atual->tipologia << endl;
            cout << "Descricao do bem: ";
            cout << atual->descricao << endl;
            cout << "Data de incorporacao (DDMMAAAA): ";
            cout << atual->data_incorporacao << endl;
            cout << "Valor do bem: ";
            cout << atual->valor_bem << endl;
            cout << "Valor mecanografico do responsavel: ";
            cout << atual->numero_mecanografico << endl;

            if(atual->abatido==true)
            {
                cout << "Data de abate (DDMMAAAA): ";
                cout << atual->data_abate << endl;
                abatidos = abatidos + atual->valor_bem;
            }
            else ativos = ativos + atual->valor_bem;
        }
        atual = atual->proximo;
    }
    if (contador == 0)
    {
        cout << "Nao existem bens inventariados do espaco que inseriu\n";
        return;
    }
    else
    {
        cout << "Total dos bens deste espaco: " << ativos + abatidos << endl;
        cout << "Subtotal dos bens ativos: " << ativos << endl;
        cout << "Subtotal dos bens abatidos: " << abatidos << endl;
    }
}

//==============================================================
//Metodo para listar o inventario de uma pessoa
void ListaBens:: lista_inventario_pessoa(ListaPessoasResponsaveis &p){
    int pessoa;
    double ativos = 0, abatidos = 0;
    cout << "\nLista de espacos:\n";
    p.listar_responsaveis();
    do{
        cout << "Insira o numero mecanografico da pessoa do qual quer listar o inventario (5 digitos):\n";
        cin >> pessoa;
    }while(pessoa < 0 || pessoa > 99999);
    int contador = 0;

    CNoListaBens *atual = cabeca;
    if(cabeca == NULL)
    {
        cout << "Nao existem bens guardados no inventario\n";
        return;
    }

    cout << "Lista de pessoas com o codigo: " << pessoa << " no inventario:\n";
    while(atual != NULL){
        if(pessoa == atual->numero_mecanografico)
        {
            contador++;
            cout<<"\n==Bem "<< contador <<"==\n";

            cout << "Codigo: ";
            cout << atual->codigo << endl;
            cout << "Tipologia: ";
            cout << atual->tipologia << endl;
            cout << "Descricao do bem: ";
            cout << atual->descricao << endl;
            cout << "Data de incorporacao (DDMMAAAA): ";
            cout << atual->data_incorporacao << endl;
            cout << "Codigo do espaco: ";
            cout << atual->codigo_espaco << endl;
            cout << "Valor do bem: ";
            cout << atual->valor_bem << endl;

            if(atual->abatido==true)
            {
                cout << "Data de abate (DDMMAAAA): ";
                cout << atual->data_abate << endl;
                abatidos = abatidos + atual->valor_bem;
            }
            else ativos = ativos + atual->valor_bem;
        }
        atual = atual->proximo;
    }
    if (contador == 0)
    {
        cout << "Nao existem bens inventariados da pessoa que inseriu\n";
        return;
    }
    else
    {
        cout << "Total dos bens desta pessoa: " << ativos + abatidos << endl;
        cout << "Subtotal dos bens ativos: " << ativos << endl;
        cout << "Subtotal dos bens abatidos: " << abatidos << endl;
    }
}

//==============================================================
//Metodo para identificar os espacos criticos
void ListaBens::espacos_criticos(ListaEspacos &e){
    if(cabeca == NULL)
    {
        cout << "\nNao existem bens inventariados\n";
        return;
    }
    int dim = e.numero_espacos();
    int * codigos_espaco = (int*) malloc(dim);
    double * valor_espaco = (double*) malloc (dim);
    e.preenche_tabela_espacos(codigos_espaco, valor_espaco, dim);
    CNoListaBens *atual;
    for (int i=0; i<dim; i++)
    {
        atual = cabeca;
        while(atual != NULL)
        {
            if(atual->codigo_espaco == codigos_espaco[i] && atual->abatido == false)
                valor_espaco[i] = valor_espaco[i] + atual->valor_bem;
            atual = atual->proximo;
        }
    }
    bool houveTroca;
    for (int i = 0; i < dim-1; i++) {
        houveTroca = false;
        for (int j = 1; j<dim-i; j++)
        {
            if(valor_espaco[j] > valor_espaco[j-1]) {
                double aux = valor_espaco[j-1];
                valor_espaco[j-1] = valor_espaco[j];
                valor_espaco[j] = aux;
                int aux_c = codigos_espaco[j-1];
                codigos_espaco[j-1] = codigos_espaco[j];
                codigos_espaco[j] = aux_c;
                houveTroca = true;
            }
        }
        if (!houveTroca) break;
    }

    cout << "\nLista de espacos criticos:\n";
    for (int x=0; x<dim; x++)
    {
        cout << "codigo do espaco: " << codigos_espaco[x] << "  ->  valor dos bens ativos: " << valor_espaco[x] << endl;
    }
}

//==============================================================
//Metodo para ler o ficheiro dos bens no inicio do programa
void ListaBens:: ler_ficheiro_inicial(){
    CNoListaBens *atual;
    ifstream ler("bens.txt", ios::in);
    if(!ler.is_open())
    {
        //cout << "O ficheiro nao abriu\n";
        return;
    }

    ler.seekg(0, ios::end);
    int length = ler.tellg();
    if(length == 0)
    {
        //cout << "ESTA VAZIO!!\n";
        return;
    }
    ler.seekg(0, ios::beg);
    string d;
    int x;

    while(!ler.eof()){
        CNoListaBens *novo = new CNoListaBens;
        novo->proximo=NULL;
        getline(ler,d);
        strcpy(novo->descricao,d.c_str());
        ler>>novo->codigo;
        ler >> novo->tipologia;
        ler >> novo->data_incorporacao;
        ler >> novo->codigo_espaco;
        ler >> novo->valor_bem;
        ler >> novo->numero_mecanografico;
        ler >> novo->data_abate;
        ler >> x;
        if (x == 0)
            novo->abatido = false;
        else novo->abatido = true;
        ler.ignore();
        if(cabeca==NULL)
        {
            cabeca=novo;
        }
        else{
            atual=cabeca;
            while(atual->proximo!=NULL)
            {
                atual=atual->proximo;
            }
            atual->proximo=novo;
        }
        ler.peek();
    }
    ler.close();
}

//==============================================================
//Metodo para escrever todo o ficheiro
void ListaBens:: escreve_ficheiro(){
    CNoListaBens *atual = cabeca;
    if(cabeca == NULL)
        return;
    ofstream escreve("bens.txt");
    if(!escreve)
    {
        //cout << "O ficheiro de escrita nao abriu\n";
        return;
    }
    while (atual != NULL) {
        escreve << atual->descricao << endl;
        escreve << atual->codigo << endl;
        escreve << atual->tipologia << endl;
        escreve << atual->data_incorporacao << endl;
        escreve << atual->codigo_espaco << endl;
        escreve << atual->valor_bem << endl;
        escreve << atual->numero_mecanografico << endl;
        escreve << atual->data_abate << endl;
        if(atual->abatido == false)
            escreve << "0\n";
        else escreve << "1\n";
        atual = atual->proximo;
    }
    escreve.close();
}

