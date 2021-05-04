#ifndef LISTAPESSOASRESPONSAVEIS_H
#define LISTAPESSOASRESPONSAVEIS_H

#include "listaespacos.h"
//==============================================================
//Lista de pessoas responsaveis
class CNoListaPessoasResponsaveis{
public:
    int numero_mecanografico;
    char nome[200];
    char cargo[200];
    int codigo_do_local;
    int telefone;
    bool inventariado;
    CNoListaPessoasResponsaveis *proximo;
};

class ListaPessoasResponsaveis{
private:
    CNoListaPessoasResponsaveis *cabeca;
public:
    ListaPessoasResponsaveis();
    ~ListaPessoasResponsaveis();
    void insere_responsaveis(ListaEspacos &espaco);
    void elimina_responsaveis(ListaEspacos &espaco);
    void listar_responsaveis();
    bool procuraItem(int x);
    void cria_responsavel(int num_mecanografico, int espaco, ListaEspacos &lista);
    void marca_como_inventariado(int x);
    void tira_de_inventariado(int x);
    bool procura_espaco(int x);
    void ler_ficheiro_inicial();
    void escreve_ficheiro();
};

#endif // LISTAPESSOASRESPONSAVEIS_H
