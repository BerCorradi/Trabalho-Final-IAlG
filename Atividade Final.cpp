/* João Gabriel Carvalho Criscolo, Plinio Alves Cardoso, Bernardo */

#include <iostream>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <fstream>

using namespace std;

struct musico {
    long long CPF;
    string nome;
    int idade;
    string instrumento;
    string banda;
    bool removido = false;
};

void ordenar(musico *lista, int tam) {
    for (int i = 0; i < tam; i++) {
        for (int j = i + 1; j < tam; j++) {
            if (lista[i].CPF > lista[j].CPF) {
                musico temp = lista[j];
                lista[j] = lista[i];
                lista[i] = temp;
            }
        }
    }
}

int buscabinaria(musico *lista, int cpfprocurado, int inicio, int fim) {
    int meio = (inicio + fim) / 2;

    if (fim >= inicio) {
        if (lista[meio].CPF == cpfprocurado)
            return meio;
        else if (lista[meio].CPF < cpfprocurado)
            return buscabinaria(lista, cpfprocurado, meio + 1, fim);
        else
            return buscabinaria(lista, cpfprocurado, inicio, meio - 1);
    } else {
        return -1;
    }
}

void redimensionar(musico *&lista, int &capacidade) {
    int nova_capacidade = capacidade + 5;
    musico *novo = new musico[nova_capacidade];
    for (int i = 0; i < capacidade; i++) {
        novo[i] = lista[i];
    }
    delete[] lista;
    lista = novo;
    capacidade = nova_capacidade;
}

void inserir(musico *&lista, int &tam, int capacidade) {
    int inserir;
    cout << "Deseja inserir? 1-sim 2-nao: ";
    cin >> inserir;

    while (inserir == 1) {
        if (tam >= capacidade) {
            redimensionar(lista, capacidade);
        }

        cout << "Insira os dados do musico: " << endl;
        cout << "Nome: ";
        cin.ignore();
        getline(cin, lista[tam].nome);
        cout << "Idade: ";
        cin >> lista[tam].idade;
        cout << "CPF: ";
        cin >> lista[tam].CPF;
        cout << "Instrumento: ";
        cin.ignore();
        getline(cin, lista[tam].instrumento);
        cout << "Banda: ";
        getline(cin, lista[tam].banda);
        tam++;

        cout << "Deseja inserir outro? 1-sim 2-nao: ";
        cin >> inserir;
    }
}

void excluir(musico *&lista, int &tam) {
	int cpfexcluir;
	cout << "Digite o CPF do musico que deseja excluir: ";
	cin >> cpfexcluir;
	ordenar(lista, tam);
	int posicao = buscabinaria(lista, cpfexcluir, 0, tam - 1);
	
	if (posicao != -1) {
		lista[posicao].removido = true;
		cout << "Musico marcado para ser excluido com sucesso!" << endl;
		} else {
		cout << "Musico com CPF " << cpfexcluir << " nao encontrado." << endl;
		}
}

void alterar(musico *&lista, int &tam) {
    int cpfalterar;
    cout << "Digite o CPF do musico que deseja alterar: ";
    cin >> cpfalterar;

    ordenar(lista, tam);
    int posicao = buscabinaria(lista, cpfalterar, 0, tam - 1);

    if (posicao != -1) {
        cout << "-------------------------" << endl;
        cout << "Insira os novos dados do musico: " << endl;
        cout << "Nome: ";
        cin.ignore();
        getline(cin, lista[posicao].nome);
        cout << "Idade: ";
        cin >> lista[posicao].idade;
        cout << "CPF: ";
        cin >> lista[posicao].CPF;
        cout << "Instrumento: ";
        cin.ignore();
        getline(cin, lista[posicao].instrumento);
        cout << "Banda: ";
        getline(cin, lista[posicao].banda);
        cout << "Musico alterado com sucesso!" << endl;
        cout << "-------------------------" << endl;
    } else {
        cout << "Musico com CPF " << cpfalterar << " nao encontrado." << endl;
    }
}

void listarMusicos(musico *lista, int tam) {
    if (tam == 0) {
        cout << "Nenhum musico cadastrado." << endl;
        return;
    }

    cout << "------ LISTA DE MUSICOS ------" << endl;
    for (int i = 0; i < tam; i++) {
		if (lista[i].removido == false){
			cout << "Nome: " << lista[i].nome << endl;
			cout << "Idade: " << lista[i].idade << endl;
			cout << "CPF: " << lista[i].CPF << endl;
			cout << "Instrumento: " << lista[i].instrumento << endl;
			cout << "Banda: " << lista[i].banda << endl;
			cout << "-------------------------" << endl;
		}
    }
}

void bandaComMaisMusicos(musico *lista, int tam) {
    if (tam == 0) {
        cout << "Nenhum musico cadastrado." << endl;
        return;
    }

    string* bandas= new string[tam]; 
    int* contagem= new int [tam];
    for(int i = 0; i < tam; i++) {
        contagem[i] = 0;
    }
    int qtdBandas = 0;

    for (int i = 0; i < tam; i++) {
		if (lista[i].removido == false) {
			bool encontrada = false;
			for (int j = 0; j < qtdBandas; j++) {
				if (lista[i].banda == bandas[j]) {
					contagem[j]++;
					encontrada = true;
				}
            }
        
			if (!encontrada) {
				bandas[qtdBandas] = lista[i].banda;
				contagem[qtdBandas]= 1;
				qtdBandas++;
			}
		}
    }

    
    string* bandaTop= new string[tam];
    int contador = 1;
    int max = 0;
    bandaTop[0]= bandas[0];
    for (int i = 1; i < qtdBandas; i++) {
    
        if (contagem[i] > max) {
            max = contagem[i];
            bandaTop[0] = bandas[i];
        }
    }
    for (int i = 1; i < qtdBandas; i++) {
        if (contagem[i] == max && bandas[i] != bandaTop[0]) {
            bandaTop[contador] = bandas[i];
            contador++;
        }
    }
    if(contador== tam){
        cout<< "Empate entre todas as bandas com " << max << " musicos cada." << endl;
    }else if(contador>1){
        cout<< "Empate entre as bandas: ";
        for(int i=0; i<contador; i++){
            cout<< bandaTop[i] << ", ";
        }
        cout<< " com " << max << " musicos cada." << endl;
    }else if( contador == 0) cout << "Banda com mais musicos: " << bandaTop[0] << " (" << max << " musicos)" << endl;

    delete[] bandas;
    delete[] contagem; 
    delete[] bandaTop;
}

int interface() {
    int opcao;
    cout << "----MENU PRINCIPAL----" << endl;
    cout << "1 - Inserir novo musico" << endl;
    cout << "2 - Buscar musico por CPF" << endl;
    cout << "3 - Marcar para excluir musico por CPF" << endl;
    cout << "4 - Alterar dados do musico" << endl;
    cout << "5 - Banda com mais musicos" << endl;
    cout << "6 - Listar todos os musicos" << endl;
    cout << "7 - Informacoes do projeto" << endl;
	cout << "8 - Buscar por um intervalo" << endl;
    cout << "0 - Sair" << endl;
    cout << "Escolha: ";
    cin >> opcao;
    return opcao;
}

int leitura(int &capacidade, int &tam, musico *&lista) {
    ifstream entrada("musicos.csv");
    if (!entrada.is_open()) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return -1;
    }

    while (true) {
        if (tam >= capacidade) {
            redimensionar(lista, capacidade);
        }

        getline(entrada, lista[tam].nome, ';');
        if (entrada.eof() || lista[tam].nome == "") break;

        entrada >> lista[tam].idade;
        entrada.ignore();
        entrada >> lista[tam].CPF;
        entrada.ignore();
        getline(entrada, lista[tam].instrumento, ';');
        getline(entrada, lista[tam].banda, ';');
		entrada >> lista[tam].removido;
		entrada.ignore();
        tam++;
    }

    entrada.close();
    return 0;
}

void registrar(musico *lista, int tam) {
    cout<< "--------------------------" << endl;
    cout << "Digite o nome do arquivo para salvar os dados: ";
    string nome_arquivo;
    cin>> nome_arquivo;
    ofstream saida(nome_arquivo);
    for (int i = 0; i < tam; i++) {
		if (lista[i].removido == false){
			saida << lista[i].nome << ";"
				  << lista[i].idade << ";"
				  << lista[i].CPF << ";"
				  << lista[i].instrumento << ";"
				  << lista[i].banda << ";"
				  << lista[i].removido << ";";
		  }
    }
    saida.close();
    cout << "Dados salvos com sucesso no arquivo " << nome_arquivo << "!" << endl;
    cout<< "--------------------------" << endl;
}
void informacoes_projeto()
{
    cout << "-------------------------" << endl;
    cout << "Projeto de Cadastro de Musicos - Turma 22A" << endl;
    cout << "Desenvolvido por: " << endl;
    cout << "Joao Gabriel Carvalho Criscolo" << endl;
    cout << "Plinio Alves Cardoso" << endl;
    cout << "Bernardo" << endl;
    cout << "Linguagem utilizada: C++" << endl;
    cout << "Funcionalidades: Inserir, Buscar, Excluir, Alterar dados de musicos" << endl;
    cout << "Dados armazenados em arquivo CSV" << endl;
    cout << "-------------------------" << endl;
}
void listarIntervalo(musico *lista, int tam, int inicio, int fim) {
    if (tam == 0) {
        cout << "Nenhum musico cadastrado." << endl;
        return;
    }

    if (inicio < 0) inicio = 0;
    if (fim >= tam) fim = tam - 1;
    if (inicio > fim) {
        cout << "Intervalo invalido." << endl;
        return;
    }

    cout << "------ LISTA DE MUSICOS (" << inicio << " a " << fim << ") ------" << endl;
    for (int i = inicio; i <= fim; i++) {
        if (lista[i].removido == false){
			cout << "Indice " << i << ":" << endl;
			cout << "Nome: " << lista[i].nome << endl;
			cout << "Idade: " << lista[i].idade << endl;
			cout << "CPF: " << lista[i].CPF << endl;
			cout << "Instrumento: " << lista[i].instrumento << endl;
			cout << "Banda: " << lista[i].banda << endl;
			cout << "-------------------------" << endl;
		}
    }
}
int main() {
    int capacidade = 40, tam = 0;
    musico *lista = new musico[capacidade];
    if (leitura(capacidade, tam, lista) == -1)
        return -1;

    int opcao;
    do {
        opcao = interface();
        cout << "-------------------------" << endl << endl;

        switch (opcao) {
            case 1:
                inserir(lista, tam, capacidade);
                break;
			case 2: {
				ordenar(lista, tam);
				cout << "Digite o CPF que deseja procurar: ";
				int procurado;
				cin >> procurado;
				int pos = buscabinaria(lista, procurado, 0, tam - 1);
				
				if (pos != -1) {
					if (lista[pos].removido == false) {
						cout << "Musico encontrado:" << endl;
						cout << "Nome: " << lista[pos].nome << endl;
						cout << "Idade: " << lista[pos].idade << endl;
						cout << "CPF: " << lista[pos].CPF << endl;
						cout << "Instrumento: " << lista[pos].instrumento << endl;
						cout << "Banda: " << lista[pos].banda << endl;
					} else {
						cout << "Musico encontrado, mas esta marcado para exclusao." <<endl;
					}
				} else {
					cout << "Musico nao encontrado." << endl;
				}
				break;
			}
            case 3:
                excluir(lista, tam);
                break;
            case 4:
                alterar(lista, tam);
                break;
            case 5:
                bandaComMaisMusicos(lista, tam);
                break;
            case 6:
                listarMusicos(lista, tam);
                break;
              
			case 7:
				informacoes_projeto(); //chamar a funcao para mostrar as informacoes do projeto
				break;
			
			case 8:
				int inicio, fim;
				cout << "Digite o indice inicial: ";
				cin >> inicio;
				cout << "Digite o indice final: ";
				cin >> fim;
				listarIntervalo(lista, tam, inicio, fim);
				break;
			
            case 0:
                cout << "Saindo do programa..." << endl;
                registrar(lista, tam);
                break;
                
            default:
                cout << "Opcao invalida, tente novamente." << endl;
                return interface(); //alterei para retornar ao menu em caso de opcao invalida
                break;
        }

    } while (opcao != 0);

    delete[] lista;
    return 0;
}