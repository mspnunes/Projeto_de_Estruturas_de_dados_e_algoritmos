#ifndef LISTAESPACOS_H
#define LISTAESPACOS_H

//==============================================================
//Lista de espacos
class CNoListaEspacos{
public:
    int codigo_espaco;
    char edificio[51];
    int andar;
    char designacao[51];
    double area;
    bool inventariado;
    bool associado;
    CNoListaEspacos *proximo;
};
class ListaEspacos{
private:
    CNoListaEspacos *cabeca;
public:
    ListaEspacos();
    ~ListaEspacos();
    void insere_espaco();
    void cria_espaco(int espaco);
    void elimina_espaco();
    bool listar_espaco();
    int seleciona_espaco();
    bool procuraItem(int x);
    void marca_como_inventariado(int x);
    void tira_de_inventariado(int x);
    void marca_como_associado(int x);
    void tira_de_associado(int x);
    int numero_espacos();
    void preenche_tabela_espacos(int espacos[], double valor[], int dim);
    void ler_ficheiro_inicial();
    void escreve_ficheiro();
};

#endif // LISTAESPACOS_H
