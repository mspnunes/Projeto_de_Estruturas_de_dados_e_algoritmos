#include "listapessoasresponsaveis.h"
#include "listaespacos.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//==============================================================
//Construtor por defeito
ListaPessoasResponsaveis:: ListaPessoasResponsaveis(){
    cabeca = NULL;
}

//==============================================================
//Destrutor
ListaPessoasResponsaveis::~ListaPessoasResponsaveis(){
    CNoListaPessoasResponsaveis *atual, *proximo;

    atual=cabeca;
    while(atual!=NULL){
        proximo=atual->proximo;
        delete atual;
        atual=proximo;
    }
}

//==============================================================
//Metodo para inserir
void ListaPessoasResponsaveis:: insere_responsaveis(ListaEspacos &espaco){
    CNoListaPessoasResponsaveis *novo=new CNoListaPessoasResponsaveis;
    CNoListaPessoasResponsaveis *atual;

    do{
        do{
            cout << "Insira o numero mecanografico do responsavel (5 digitos):\n";
            cin >> novo->numero_mecanografico;
        }while(novo->numero_mecanografico < 0 || novo->numero_mecanografico > 99999);
        bool x = procuraItem(novo->numero_mecanografico);
        if (x == true)
            cout << "O numero mecanografico do responsavel que inseriu ja existe\n";
        else break;
    }while(true);
    cin.ignore();
    cout << "Insira o nome do responsavel:\n";
    cin.getline(novo->nome, sizeof(novo->nome));
    cout << "Insira o cargo do responsavel:\n";
    cin.getline(novo->cargo, sizeof(novo->cargo));

    cout << "\nLista de espacos:\n";
    espaco.listar_espaco();
    bool flag;
    char x;
    do{
        do{
            cout << "Introduza o codigo do espaco onde o responsavel trabalha habitualmente (4 digitos):\n";
            cin >> novo->codigo_do_local;
        }while(novo->codigo_do_local < 0 || novo->codigo_do_local > 9999);
        flag = espaco.procuraItem(novo->codigo_do_local);
        if (flag == true)
        {
            espaco.marca_como_associado(novo->codigo_do_local);
            break;
        }
        cout << "O espaco nao existe\n";
        while(true){
            cout << "Quer inserir um novo espaco com este codigo?(s/n)\n";
            cin >> x;
            if(x == 's' || x == 'S')
            {
                espaco.cria_espaco(novo->codigo_do_local);
                espaco.marca_como_associado(novo->codigo_do_local);
                break;
            }
            else if(x == 'n' || x == 'N')
            {
                novo->codigo_do_local = INT_MIN;
                break;
            }
            else cout << "Opcao invalida\n";
        }
    }while(novo->codigo_do_local == INT_MIN);

    cout << "Introduza o numero de telefone do responsavel:\n";
    cin >> novo->telefone;

    novo->inventariado = false;
    novo->proximo=NULL;

    if(cabeca==NULL){
        cabeca=novo;
    }else{
        atual=cabeca;
        while(atual->proximo!=NULL)
            atual=atual->proximo;
        atual->proximo=novo;
    }
    ofstream escreve("pessoas.txt");
    if(!escreve)
    {
        cout << "O ficheiro de escrita nao abriu\n";
        return;
    }
    escreve << novo->nome << endl;
    escreve << novo->cargo << endl;
    escreve << novo->numero_mecanografico << endl;
    escreve << novo->codigo_do_local << endl;
    escreve << novo->telefone << endl;
    if(novo->inventariado == false)
        escreve << "0\n";
    else escreve << "1\n";
    escreve.close();
}

//==============================================================
//Metodo para eliminar
void ListaPessoasResponsaveis:: elimina_responsaveis(ListaEspacos &espaco){
    int c;
    bool encontrado = false;
    do{
        cout << "Qual e o numero mecanografico do responsavel que pretende eliminar (5 digitos)?\n";
        cin >> c;
    }while(c < 0 || c > 99999);

    CNoListaPessoasResponsaveis *atual = cabeca;
    CNoListaPessoasResponsaveis *anterior = NULL;

    if(cabeca == NULL)
    {
        cout << "Nao existe nenhum espaco para eliminar\n";
        return;
    }
    while (atual != NULL)
    {
        if (atual->numero_mecanografico == c && atual->inventariado == false)
        {
            if(anterior == NULL)
                cabeca = atual->proximo;
            else
                anterior->proximo = atual->proximo;
            bool p = procura_espaco(atual->codigo_do_local);
            if(p == false)
            {
                espaco.tira_de_associado(atual->codigo_do_local);
            }
            delete atual;
            cout << "O item foi eliminado\n\n";
            escreve_ficheiro();
            encontrado = true;
            return;
        }
        if(atual->numero_mecanografico == c && atual->inventariado == true)
        {
            cout << "O item nao pode ser eliminado pois esta associado a bens do inventario\n";
            encontrado = true;
            cerr << "2\n";
        }
        anterior = atual;
        atual = atual->proximo;
        cerr << "3\n";
    }
    if (encontrado == false)
        cout << "A tipologia que quer eliminar nao existe\n";
}

//==============================================================
//Metodo para listar
void ListaPessoasResponsaveis:: listar_responsaveis(){
    CNoListaPessoasResponsaveis *atual = cabeca;
    int c = 1;

    if(cabeca==NULL)
        cout << "Nao existem pessoas responsaveis guardadas\n" << endl;
    else{
        while(atual!=NULL){
            cout << "Espaco " << c << ":\n";
            cout << "Numero mecanografico: " << atual->numero_mecanografico << endl;
            cout << "Nome: " << atual->nome << endl;
            cout << "Cargo: " << atual->cargo << endl;
            cout << "Codigo do local habitual de trabalho: " << atual->codigo_do_local << endl;
            cout << "Telefone: " << atual->telefone << endl;
            cout << endl << endl;
            c++;
            atual=atual->proximo;
        }
    }
}

//==============================================================
//Metodo para procurar pessoas
bool ListaPessoasResponsaveis:: procuraItem(int x){
    CNoListaPessoasResponsaveis *atual=cabeca;

    if(cabeca==NULL)
        return false;
    else{
        while(atual!=NULL){
            if(atual->numero_mecanografico == x)
                return true;
            atual=atual->proximo;
        }
        return false;
    }
}

//==============================================================
//Metodo para criar pessoas a partir do n mecanografico
void ListaPessoasResponsaveis:: cria_responsavel(int num_mecanografico, int espaco, ListaEspacos &lista){
    CNoListaPessoasResponsaveis *novo=new CNoListaPessoasResponsaveis;
    CNoListaPessoasResponsaveis *atual;

    novo->numero_mecanografico = num_mecanografico;
    cin.ignore();
    cout << "Insira o nome do responsavel:\n";
    cin.getline(novo->nome, sizeof(novo->nome));
    cout << "Insira o cargo do responsavel:\n";
    cin.getline(novo->cargo, sizeof(novo->cargo));

    novo->codigo_do_local = espaco;
    lista.marca_como_associado(novo->codigo_do_local);

    cout << "Introduza o numero de telefone do responsavel:\n";
    cin >> novo->telefone;

    novo->inventariado = false;
    novo->proximo=NULL;

    if(cabeca==NULL){
        cabeca=novo;
    }else{
        atual=cabeca;
        while(atual->proximo!=NULL)
            atual=atual->proximo;
        atual->proximo=novo;
    }

    ofstream escreve("pessoas.txt");
    if(!escreve)
    {
        cout << "O ficheiro de escrita nao abriu\n";
        return;
    }
    escreve << novo->nome << endl;
    escreve << novo->cargo << endl;
    escreve << novo->numero_mecanografico << endl;
    escreve << novo->codigo_do_local << endl;
    escreve << novo->telefone << endl;
    if(novo->inventariado == false)
        escreve << "0\n";
    else escreve << "1\n";
    escreve.close();
}

//==============================================================
//Metodo para marcar pessoas como inventariadas
void ListaPessoasResponsaveis:: marca_como_inventariado(int x){
    CNoListaPessoasResponsaveis *aux = cabeca;
    while (aux != NULL)
    {
        if(aux->numero_mecanografico == x)
        {
            aux->inventariado = true;
        }
        aux = aux->proximo;
    }
    escreve_ficheiro();
}

//==============================================================
//Metodo para tirar pessoas de inventariadas
void ListaPessoasResponsaveis:: tira_de_inventariado(int x){
    CNoListaPessoasResponsaveis *aux_p = cabeca;
    while(aux_p != NULL)
    {
        if(aux_p->numero_mecanografico == x)
            aux_p->inventariado = false;
        aux_p = aux_p->proximo;
    }
    escreve_ficheiro();
}

//==============================================================
//Metodo para ver se um espaco existe nas pessoas
bool ListaPessoasResponsaveis:: procura_espaco(int x){
    CNoListaPessoasResponsaveis *atual = cabeca;
    if(cabeca == NULL)
        return false;
    while(atual != NULL)
    {
        if(atual->codigo_do_local == x)
            return true;
        atual = atual->proximo;
    }
    return false;
}

//==============================================================
//Metodo para ler o ficheiro dos responsaveis no inicio do programa
void ListaPessoasResponsaveis:: ler_ficheiro_inicial(){
    CNoListaPessoasResponsaveis *atual;
    ifstream ler("pessoas.txt", ios::in);
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
    string n;
    string c;
    int x;

    while(!ler.eof()){
        CNoListaPessoasResponsaveis *novo = new CNoListaPessoasResponsaveis;
        novo->proximo=NULL;
        getline(ler,n);
        getline(ler,c);
        strcpy(novo->nome,n.c_str());
        strcpy(novo->cargo,c.c_str());
        ler>>novo->numero_mecanografico;
        ler>>novo->codigo_do_local;
        ler>>novo->telefone;
        ler >> x;
        if(x == 0)
            novo->inventariado = false;
        else novo->inventariado = true;
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
void ListaPessoasResponsaveis:: escreve_ficheiro(){
    CNoListaPessoasResponsaveis *atual = cabeca;
    if(cabeca == NULL)
        return;
    ofstream escreve("pessoas.txt");
    if(!escreve)
    {
        cout << "O ficheiro de escrita nao abriu\n";
        return;
    }
    while (atual != NULL) {
        escreve << atual->nome << endl;
        escreve << atual->cargo << endl;
        escreve << atual->numero_mecanografico << endl;
        escreve << atual->codigo_do_local << endl;
        escreve << atual->telefone << endl;
        if(atual->inventariado == false)
            escreve << "0\n";
        else escreve << "1\n";
        atual = atual->proximo;
    }
    escreve.close();
}


