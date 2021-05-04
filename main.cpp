#include <iostream>
#include "listatipologiasbens.h"
#include "listaespacos.h"
#include "listapessoasresponsaveis.h"
#include "listabens.h"
#include "listatipologiasbens.cpp"
#include "listaespacos.cpp"
#include "listapessoasresponsaveis.cpp"

using namespace std;

int main()
{
    ListaTipologiasBens tipologia;
    tipologia.ler_ficheiro_inicial();
    ListaEspacos espaco;
    espaco.ler_ficheiro_inicial();
    ListaPessoasResponsaveis responsaveis;
    responsaveis.ler_ficheiro_inicial();
    ListaBens bens;
    bens.ler_ficheiro_inicial();
    int i, x, codigo_espaco = INT_MIN;
    while(true){
        cout << "Escolha uma operacao:\n";
        cout << "1- Edita tipos de bens\n";
        cout << "2- Edita lista de espacos\n";
        cout << "3- Edita lista de pessoas\n";
        cout << "4- Seleciona espaco\n";
        cout << "5- Gerir Inventario\n";
        cout << "6- Listar inventario\n";
        cout << "7- Alienar espaco\n";
        cout << "8- Mudar bens do espaco selecionado\n";
        cout << "9- Outras consultas ao inventario\n";
        cout << "10- Determinacao de espacos criticos\n";
        cout << "99- Sair\n";
        cout << "A sua opcao: ";
        cin >> i;
        if(i == 1)
        {
            cout << "\nEscolha uma operacao:\n";
            cout << "1- Inserir tipologia\n";
            cout << "2- Eliminar tipologia\n";
            cout << "3- Listar tipologias\n";
            cin >> x;
            if(x == 1)
                tipologia.insere_tipologia();
            else if(x == 2)
            {
                tipologia.listar_tipologia();
                tipologia.elimina_tipologia();
            }
            else if(x == 3)
                tipologia.listar_tipologia();
            else
            {
                cout << "Escolha invalida\n";
                break;
            }
        }
        else if(i == 2)
        {
            cout << "\nEscolha uma operacao:\n";
            cout << "1- Inserir espaco\n";
            cout << "2- Eliminar espaco\n";
            cout << "3- Listar espacos\n";
            cin >> x;
            if(x == 1)
                espaco.insere_espaco();
            else if(x == 2)
            {
                espaco.listar_espaco();
                espaco.elimina_espaco();
            }
            else if(x == 3)
                espaco.listar_espaco();
            else
            {
                cout << "Escolha invalida\n";
                break;
            }
        }
        else if(i == 3)
        {
            cout << "\nEscolha uma operacao:\n";
            cout << "1- Inserir pessoa responsavel\n";
            cout << "2- Eliminar pessoa responsavel\n";
            cout << "3- Listar pessoas responsaveis\n";
            cin >> x;
            if(x == 1)
                responsaveis.insere_responsaveis(espaco);
            else if(x == 2)
            {
                responsaveis.listar_responsaveis();
                responsaveis.elimina_responsaveis(espaco);
            }
            else if(x == 3)
                responsaveis.listar_responsaveis();
            else
            {
                cout << "Escolha invalida\n";
                break;
            }
        }
        else if(i == 4)
        {
            codigo_espaco = espaco.seleciona_espaco();
        }
        else if(i == 5)
        {
            if(codigo_espaco == INT_MIN)
            {
                cout << "Nao existe nenhum espaco selecionado\n";
            }
            else{
                cout<<"Lista de bens associados ao espaco selecionado:\n";

                bens.listaBensPorEspaco(codigo_espaco);

                cout << "\nEscolha uma operacao:\n";
                cout << "1- Inserir bem no espaco selecionado\n";
                cout << "2- Abater bem do espaco selecionado\n";
                cin>>x;
                if(x == 1)
                    bens.insereBemNoEspaco(codigo_espaco, espaco, responsaveis, tipologia);
                else if(x == 2)
                    bens.abateBemDoEspaco(codigo_espaco);
                else
                {
                    cout << "Escolha invalida\n";
                    break;
                }
            }
        }
        else if(i == 6)
        {
            bens.mostraPorOrdem();
        }

        else if(i == 7)
        {
            espaco.listar_espaco();
            bens.alienarEspaco();
        }

        else if(i == 8)
        {
            bens.mudar_espaco(codigo_espaco, espaco, responsaveis);
        }

        else if(i == 9)
        {
            int j;
            cout << "\nEscolha uma operacao:\n";
            cout << "1- Listar o inventario de uma tipologia especifica\n";
            cout << "2- Listar o inventario de um espaco\n";
            cout << "3- Listar o inventario dos bens a responsabilidade de uma pessoa\n";
            cin >> j;
            if(j == 1)
            {
                bens.lista_inventario_tipologia(tipologia);
            }
            else if(j == 2)
            {
                bens.lista_inventario_espaco(espaco);
            }
            else if(j == 3)
            {
                bens.lista_inventario_pessoa(responsaveis);
            }
            else
            {
                cout << "\nEscolha invalida\n\n";
                break;
            }
        }

        else if(i == 10)
        {
            bens.espacos_criticos(espaco);
        }

        else if(i == 99)
        {
            char c;
            cout << "Tem a certeza que quer sair? (s/n)\n";
            cin >> c;
            if ( c == 's' || c == 'S')
            {
                cout << "O programa vai terminar\n";
                break;
            }
            continue;
        }
        else
        {
            cout << "Escolha invalida\n";
            continue;
        }
        cout << endl;
    }
    return 0;
}
