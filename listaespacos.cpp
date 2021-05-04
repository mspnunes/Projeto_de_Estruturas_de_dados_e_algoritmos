#include "listaespacos.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//==============================================================
//Construtor por defeito
ListaEspacos:: ListaEspacos(){
    cabeca = NULL;
}

//==============================================================
//Destrutor
ListaEspacos::~ListaEspacos(){
    CNoListaEspacos *atual, *proximo;

    atual=cabeca;
    while(atual!=NULL){
        proximo=atual->proximo;
        delete atual;
        atual=proximo;
    }
}

//==============================================================
//Metodo para inserir
void ListaEspacos:: insere_espaco(){
    CNoListaEspacos *novo=new CNoListaEspacos;
    CNoListaEspacos *atual;

    do{
        do{
            cout << "Insira o codigo do espaco (4 digitos):\n";
            cin >> novo->codigo_espaco;
        }while(novo->codigo_espaco < 0 || novo->codigo_espaco > 9999);
        bool x = procuraItem(novo->codigo_espaco);
        if (x == true)
            cout << "O codigo do espaco que inseriu ja existe\n";
        else break;
    }while(true);
    cin.ignore();
    cout << "Insira o nome do edificio onde se encontra o espaco (no maximo 50 caracteres):\n";
    cin.getline(novo->edificio, sizeof(novo->edificio));
    cout << "Insira o andar do espaco:\n";
    cin >> novo->andar;
    cin.ignore();
    cout << "Insira a designacao do espaco (no maximo 50 caracteres):\n";
    cin.getline(novo->designacao, sizeof(novo->designacao));
    do{
        cout << "Insira a area do espaco:\n";
        cin >> novo->area;
    }while(novo->area < 0);

    novo->inventariado = false;
    novo->associado = false;
    novo->proximo=NULL;

    if(cabeca==NULL){
        cabeca=novo;
    }else{
        atual=cabeca;
        while(atual->proximo!=NULL)
            atual=atual->proximo;
        atual->proximo=novo;
    }

    ofstream escreve("espacos.txt");
    if(!escreve)
    {
        //cout << "O ficheiro de escrita nao abriu\n";
        return;
    }
    escreve << novo->edificio << endl;
    escreve << novo->designacao << endl;
    escreve << novo->codigo_espaco << endl;
    escreve << novo->andar << endl;
    escreve << novo->area << endl;
    if(novo->inventariado == false)
        escreve << "0\n";
    else escreve << "1\n";
    if(novo->associado == false)
        escreve << "0\n";
    else escreve << "1\n";
    escreve.close();
}

//==============================================================
//Metodo para eliminar
void ListaEspacos:: elimina_espaco(){
    int c;
    bool encontrado = false;
    do{
        cout << "Qual e o codigo do espaco que pretende eliminar (4 digitos)?\n";
        cin >> c;
    }while(c < 0 || c > 9999);

    CNoListaEspacos *atual = cabeca;
    CNoListaEspacos *anterior = NULL;

    if(cabeca == NULL)
    {
        cout << "Nao existe nenhum espaco para eliminar\n\n";
        return;
    }
    while (atual != NULL)
    {
        if (atual->codigo_espaco == c && atual->inventariado == false && atual->associado == false)
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
        if(atual->codigo_espaco == c && atual->inventariado == true)
        {
            cout << "O item nao pode ser eliminado pois esta associado a bens do inventario\n\n";
            encontrado = true;
        }
        else if(atual->codigo_espaco == c && atual->associado == true)
        {
            cout << "O item nao pode ser eliminado pois esta associado a uma pessoa responsavel\n\n";
            encontrado = true;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    if (encontrado == false)
    {
       cout << "A tipologia que quer eliminar nao existe\n";
    }
}

//==============================================================
//Metodo para listar
bool ListaEspacos:: listar_espaco(){
    CNoListaEspacos *atual = cabeca;
    int c = 1;
    bool vazio=false;

    if(cabeca==NULL)
    {
        cout << "Nao existem espacos guardados\n" << endl;
        vazio=true;
    }
    else{
        while(atual!=NULL){
            cout << "Espaco " << c << ":\n";
            cout << "Codigo espaco: " << atual->codigo_espaco << endl;
            cout << "Edificio: " << atual->edificio << endl;
            cout << "Andar: " << atual->andar << endl;
            cout << "Designacao: " << atual->designacao << endl;
            cout << "Area: " << atual->area << endl;
            cout << endl << endl;
            c++;
            atual=atual->proximo;
        }
    }
    return vazio;
}

//==============================================================
//Metodo para selecionar espaço
int ListaEspacos::seleciona_espaco()
{
    int codigo_espaco;
    cout<<"Lista completa de espacos:\n\n";
    listar_espaco();
    do{
        do{
            cout<<"Introduza o codigo do espaco pretendido:(max. 4 digitos)\n";
            cin.ignore();
            cin>>codigo_espaco;
        }while(codigo_espaco<0 || codigo_espaco>9999);

        if(procuraItem(codigo_espaco) == true)
        {
            cout << "O espaco foi selecionado\n";
            return codigo_espaco;
        }
        else{
            char x;
            cout << "O espaco que inseriu nao existe\n";
            while(true){
                cout << "Quer inserir um novo espaco com este codigo?(s/n)\n";
                cin >> x;
                if(x == 's' || x == 'S')
                {
                    cria_espaco(codigo_espaco);
                    return codigo_espaco;
                }
                else if(x == 'n' || x == 'N')
                {
                    codigo_espaco = INT_MIN;
                    break;
                }
                else cout << "Opcao invalida\n";
            }
        }
    }while(codigo_espaco == INT_MIN);
    return codigo_espaco;
}

//==============================================================
//Metodo para procurar espaço
bool ListaEspacos:: procuraItem(int x){
    CNoListaEspacos *atual=cabeca;

    if(cabeca==NULL)
        return false;
    else{
        while(atual!=NULL){
            if(atual->codigo_espaco == x)
                return true;
            atual=atual->proximo;
        }
        return false;
    }
}

//==============================================================
//Metodo para criar espaço a partir de um codigo de espaco
void ListaEspacos:: cria_espaco(int espaco){
    CNoListaEspacos *novo=new CNoListaEspacos;
    CNoListaEspacos *atual;

    novo->codigo_espaco = espaco;
    cin.ignore();
    cout << "Insira o nome do edificio onde se encontra o espaco (no maximo 50 caracteres):\n";
    cin.getline(novo->edificio, sizeof(novo->edificio));
    cout << "Insira o andar do espaco:\n";
    cin >> novo->andar;
    cin.ignore();
    cout << "Insira a designacao do espaco (no maximo 50 caracteres):\n";
    cin.getline(novo->designacao, sizeof(novo->designacao));
    do{
        cout << "Insira a area do espaco:\n";
        cin >> novo->area;
    }while(novo->area < 0);

    novo->inventariado = false;
    novo->associado = false;
    novo->proximo=NULL;

    if(cabeca==NULL){
        cabeca=novo;
    }else{
        atual=cabeca;
        while(atual->proximo!=NULL)
            atual=atual->proximo;
        atual->proximo=novo;
    }

    ofstream escreve("espacos.txt");
    if(!escreve)
    {
        //cout << "O ficheiro de escrita nao abriu\n";
        return;
    }
    escreve << novo->edificio << endl;
    escreve << novo->designacao << endl;
    escreve << novo->codigo_espaco << endl;
    escreve << novo->andar << endl;
    escreve << novo->area << endl;
    if(novo->inventariado == false)
        escreve << "0\n";
    else escreve << "1\n";
    if(novo->associado == false)
        escreve << "0\n";
    else escreve << "1\n";
    escreve.close();
}

//==============================================================
//Metodo para marcar um espaço como inventariado
void ListaEspacos:: marca_como_inventariado(int x){
    CNoListaEspacos *aux = cabeca;
    while (aux != NULL)
    {
        if(aux->codigo_espaco == x)
        {
            aux->inventariado = true;
        }
        aux = aux->proximo;
    }
    escreve_ficheiro();
}

//==============================================================
//Metodo para tirar um espaço de inventariado
void ListaEspacos:: tira_de_inventariado(int x){
    CNoListaEspacos *aux = cabeca;
    while(aux != NULL)
    {
        if(aux->codigo_espaco == x)
            aux->inventariado = false;
        aux = aux->proximo;
    }
    escreve_ficheiro();
}

//==============================================================
//Metodo para marcar um espaço como associado
void ListaEspacos:: marca_como_associado(int x){
    CNoListaEspacos *aux = cabeca;
    while (aux != NULL)
    {
        if(aux->codigo_espaco == x)
        {
            aux->associado = true;
        }
        aux = aux->proximo;
    }
    escreve_ficheiro();
}

//==============================================================
//Metodo para tirar um espaço de associado
void ListaEspacos:: tira_de_associado(int x){
    CNoListaEspacos *aux = cabeca;
    while(aux != NULL)
    {
        if(aux->codigo_espaco == x)
            aux->associado = false;
        aux = aux->proximo;
    }
    escreve_ficheiro();
}

//==============================================================
//Metodo para contar o numero de espacos existentes no inventario
int ListaEspacos:: numero_espacos(){
    CNoListaEspacos *atual = cabeca;
    if (atual == NULL)
        return 0;
    int contador = 0;
    while(atual != NULL)
    {
        if (atual->inventariado == true)
            contador++;
        atual = atual->proximo;
    }
    return contador;
}

//==============================================================
//Metodo para preencher a tabela com o codigo dos espacos inventariados
void ListaEspacos:: preenche_tabela_espacos(int espacos[], double valor[], int dim){
    CNoListaEspacos *atual = cabeca;
    int contador = 0;
    while(atual != NULL && contador < dim)
    {
        if(atual->inventariado == true)
        {
            espacos[contador] = atual->codigo_espaco;
            valor[contador] = 0;
        }
        contador++;
        atual = atual->proximo;
    }
    return;
}

//==============================================================
//Metodo para ler o ficheiro dos espacos no inicio do programa
void ListaEspacos:: ler_ficheiro_inicial(){
    CNoListaEspacos *atual;
    ifstream ler("espacos.txt", ios::in);
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
    string e;
    int x, y;

    while(!ler.eof()){
        CNoListaEspacos *novo = new CNoListaEspacos;
        novo->proximo=NULL;
        getline(ler,d);
        getline(ler,e);
        strcpy(novo->edificio,e.c_str());
        strcpy(novo->designacao,d.c_str());
        ler>>novo->codigo_espaco;
        ler >> novo->andar;
        ler >> novo->area;
        ler >> x;
        if (x == 0)
            novo->inventariado = false;
        else novo->inventariado = true;
        ler >> y;
        if (y == 0)
            novo->associado = false;
        else novo->associado = true;
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
void ListaEspacos:: escreve_ficheiro(){
    CNoListaEspacos *atual = cabeca;
    if(cabeca == NULL)
        return;
    ofstream escreve("espacos.txt");
    if(!escreve)
    {
        //cout << "O ficheiro de escrita nao abriu\n";
        return;
    }
    while (atual != NULL) {
        escreve << atual->edificio << endl;
        escreve << atual->designacao << endl;
        escreve << atual->codigo_espaco << endl;
        escreve << atual->andar << endl;
        escreve << atual->area << endl;
        if(atual->inventariado == false)
            escreve << "0\n";
        else escreve << "1\n";
        if(atual->associado == false)
            escreve << "0\n";
        else escreve << "1\n";
        atual = atual->proximo;
    }
    escreve.close();
}
