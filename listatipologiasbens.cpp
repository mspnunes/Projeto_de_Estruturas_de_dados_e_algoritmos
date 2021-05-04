#include "listatipologiasbens.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

//==============================================================
//Construtor por defeito
ListaTipologiasBens:: ListaTipologiasBens(){
    cabeca = NULL;
}

//==============================================================
//Destrutor
ListaTipologiasBens::~ListaTipologiasBens(){
    CNoListaTipologiasBens *atual, *proximo;

    atual=cabeca;
    while(atual!=NULL){
        proximo=atual->proximo;
        delete atual;
        atual=proximo;
    }
}

//==============================================================
//Metodo para inserir
void ListaTipologiasBens:: insere_tipologia(){
    CNoListaTipologiasBens *novo=new CNoListaTipologiasBens;
    CNoListaTipologiasBens *atual;

    do{
        do{
            cout << "Insira o codigo da tipologia (3 digitos):\n";
            cin >> novo->codigo;
        }while(novo->codigo < 0 || novo->codigo >999);
        bool x = procuraItem(novo->codigo);
        if(x == true)
            cout << "O codigo da tipologia que inseriu ja existe\n";
        else break;
    }while(true);
    cin.ignore();
    cout << "Insira a tipologia do seu bem (no maximo 20 caracteres):\n";
    cin.getline(novo->designacao_curta, sizeof(novo->designacao_curta));
    cout << "Insira a descricao da tipologia (no maximo 255 caracteres):\n";
    cin.getline(novo->descricao, sizeof(novo->descricao));

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
    cout << endl;

    ofstream escreve("tipologias.txt", ios::app);
    if(!escreve)
    {
        cout << "O ficheiro de escrita nao abriu\n";
        return;
    }
    escreve << novo->descricao << endl;
    escreve << novo->designacao_curta << endl;
    escreve << novo->codigo << endl;
    if(novo->inventariado == false)
        escreve << "0\n";
    else escreve << "1\n";
    escreve.close();
}

//==============================================================
//Metodo para eliminar
void ListaTipologiasBens:: elimina_tipologia(){
    int c;
    bool encontrado = false;
    do{
        cout << "Qual e o codigo da tipologia que pretende eliminar (3 digitos)?\n";
        cin >> c;
    }while (c < 0 || c > 999);

    CNoListaTipologiasBens *atual = cabeca;
    CNoListaTipologiasBens *anterior = NULL;

    if(cabeca == NULL)
    {
        cout << "Nao existe nenhuma tipologia para eliminar\n\n";
        return;
    }
    while (atual != NULL)
    {
        if (atual->codigo == c && atual->inventariado == false)
        {
            if(anterior == NULL)
                cabeca = atual->proximo;
            else
                anterior->proximo = atual->proximo;
            delete atual;
            cout << "O item foi eliminado\n\n";
            escreve_ficheiro();
            encontrado = true;
            return;
        }
        if(atual->codigo == c && atual->inventariado == true)
        {
            cout << "O item nao pode ser eliminado pois esta associado a bens do inventario\n\n";
            encontrado = true;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    if (encontrado == false)
        cout << "A tipologia que quer eliminar nao existe\n";
}

//==============================================================
//Metodo para listar
void ListaTipologiasBens:: listar_tipologia(){
    CNoListaTipologiasBens *atual = cabeca;
    int c = 1;
    cout << endl;

    if(cabeca==NULL)
        cout << "Nao existem tipologias de bens guardadas\n" << endl;
    else{
        while(atual!=NULL){
            cout << "Tipologia " << c << ":\n";
            cout << "Codigo: " << atual->codigo << endl;
            cout << "Designacao curta: " << atual->designacao_curta << endl;
            cout << "Descricao: " << atual->descricao << endl;
            cout << endl;
            c++;
            atual=atual->proximo;
        }
    }
    cout << endl;
}

//==============================================================
//Metodo para procurar tipologia
bool ListaTipologiasBens:: procuraItem(int x){
    CNoListaTipologiasBens *atual=cabeca;

    if(cabeca==NULL)
        return false;
    else{
        while(atual!=NULL){
            if(atual->codigo == x)
                return true;
            atual=atual->proximo;
        }
        return false;
    }
}

//==============================================================
//Metodo para criar tipologia a partir de um codigo da tipologia
void ListaTipologiasBens:: cria_tipologia(int codigo){
    CNoListaTipologiasBens *novo=new CNoListaTipologiasBens;
    CNoListaTipologiasBens *atual;

    novo->codigo = codigo;
    cin.ignore();
    cout << "Insira a tipologia do seu bem (no maximo 20 caracteres):\n";
    cin.getline(novo->designacao_curta, sizeof(novo->designacao_curta));
    cout << "Insira a descricao da tipologia (no maximo 255 caracteres):\n";
    cin.getline(novo->descricao, sizeof(novo->descricao));

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
    //cout << endl;

    ofstream escreve("tipologias.txt", ios::app);
    if(!escreve)
    {
        cout << "O ficheiro de escrita nao abriu\n";
        return;
    }
    escreve << novo->descricao << endl;
    escreve << novo->designacao_curta << endl;
    escreve << novo->codigo << endl;
    if(novo->inventariado == false)
        escreve << "0\n";
    else escreve << "1\n";
    escreve.close();
}

//==============================================================
//Metodo para marcar uma tipologia como inentariada
void ListaTipologiasBens:: marca_como_inventariado(int x){
    CNoListaTipologiasBens *aux = cabeca;
    while (aux != NULL)
    {
        if(aux->codigo == x)
        {
            aux->inventariado = true;
        }
        aux = aux->proximo;
    }
    escreve_ficheiro();
}

//==============================================================
//Metodo para ler o ficheiro das tipologias no inicio do programa
void ListaTipologiasBens:: ler_ficheiro_inicial(){
    CNoListaTipologiasBens *atual;
    ifstream ler("tipologias.txt", ios::in);
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
    string dc;
    string d;
    int x;

    while(!ler.eof()){
        CNoListaTipologiasBens *novo = new CNoListaTipologiasBens;
        novo->proximo=NULL;
        getline(ler,dc);
        getline(ler,d);
        strcpy(novo->descricao,dc.c_str());
        strcpy(novo->designacao_curta,d.c_str());
        ler>>novo->codigo;
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
void ListaTipologiasBens:: escreve_ficheiro(){
    CNoListaTipologiasBens *atual = cabeca;
    if(cabeca == NULL)
        return;
    ofstream escreve("tipologias.txt");
    if(!escreve)
    {
        cout << "O ficheiro de escrita nao abriu\n";
        return;
    }
    while (atual != NULL) {
        escreve << atual->descricao << endl;
        escreve << atual->designacao_curta << endl;
        escreve << atual->codigo << endl;
        if(atual->inventariado == false)
            escreve << "0\n";
        else escreve << "1\n";
        atual = atual->proximo;
    }
    escreve.close();
}

