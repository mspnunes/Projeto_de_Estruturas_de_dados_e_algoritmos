#ifndef LISTABENS_H
#define LISTABENS_H

#include "listaespacos.h"
#include "listapessoasresponsaveis.h"
#include "listatipologiasbens.h"

//==============================================================
//Lista de bens
class CNoListaBens{
public:
    int codigo;
    int tipologia;
    char descricao[256];
    int data_incorporacao;
    int codigo_espaco;
    double valor_bem;
    int numero_mecanografico;
    bool abatido;
    int data_abate;
    CNoListaBens *proximo;
};

class ListaBens{
private:
    CNoListaBens *cabeca;
    void trocaNos(CNoListaBens *x, CNoListaBens *y);
public:
    ListaBens();
    ~ListaBens();
    void listaBensPorEspaco(int espaco);
    void insereBemNoEspaco(int espaco, ListaEspacos &espacos, ListaPessoasResponsaveis &pessoa, ListaTipologiasBens &tipologia);
    void abateBemDoEspaco(int espaco);
    void mostraPorOrdem();
    void ordenacaoBolha();
    void alienarEspaco();
    void mudar_espaco(int x, ListaEspacos &espaco, ListaPessoasResponsaveis &pessoa);
    bool procura_espaco(int x);
    bool procura_pessoa(int x);
    void lista_inventario_tipologia(ListaTipologiasBens &t);
    void lista_inventario_espaco(ListaEspacos &e);
    void lista_inventario_pessoa(ListaPessoasResponsaveis &p);
    void espacos_criticos(ListaEspacos &e);
    void ler_ficheiro_inicial();
    void escreve_ficheiro();

};

#endif // LISTABENS_H
