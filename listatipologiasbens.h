#ifndef LISTATIPOLOGIASBENS_H
#define LISTATIPOLOGIASBENS_H

#include <iostream>
using namespace std;

//==============================================================
//Lista de tipologias de bens
class CNoListaTipologiasBens{
public:
    int codigo;
    char designacao_curta[21];
    char descricao[256];
    bool inventariado;
    CNoListaTipologiasBens *proximo;
};

class ListaTipologiasBens
{
private:
    CNoListaTipologiasBens *cabeca;
public:
    ListaTipologiasBens();
    ~ListaTipologiasBens();
    void insere_tipologia();
    void elimina_tipologia();
    void listar_tipologia();
    bool procuraItem(int x);
    void cria_tipologia(int codigo);
    void marca_como_inventariado(int x);
    void ler_ficheiro_inicial();
    void escreve_ficheiro();
};

#endif // LISTATIPOLOGIASBENS_H
