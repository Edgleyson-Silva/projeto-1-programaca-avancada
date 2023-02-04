#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

//Classe ambiente
class Ambiente{
private:
    int dimensao_x; // dimensao X do ambiente
    int dimensao_y; // dimensao Y do ambiente
    char** grade; // matriz de caracteres que representa o ambiente
    int posicao_estacao_x; // posicao X da estacao
    int posicao_estacao_y; // posicao Y da estacao

public:
    // construtor que inicializa as dimensões, posição da estação e a matriz "grade"
    Ambiente(int dim_x, int dim_y, int pos_x, int pos_y) : dimensao_x(dim_x), dimensao_y(dim_y), posicao_estacao_x(pos_x), posicao_estacao_y(pos_y){
        grade = new char*[dim_x]; // alocacao de memoria na matriz grade
        for (int i = 0; i < dim_x; i++){
            grade[i] = new char[dim_y];
            for (int j = 0; j < dim_y; j++){
                grade[i][j] = '0'; // preenche o ambiente com zeros
            }
        }
        grade[pos_x][pos_y] = 'E'; // preenche a posicao da estacao
    }

    // obstaculo em uma posicao especifica
    void AdicionarObstaculo(int x, int y){
        if (grade[x][y] == 'E'){ // verifica se o obstaculo esta sendo inserido na posicao da estacao
            cout << "Nao eh possivel adicionar um obstaculo no local" << endl;
        }
        else{
            grade[x][y] = '1'; // adiciona o obstaculo na posicao
        }

    }

    // obstaculo retangular
    void AdicionarRetangulo(int x1, int y1, int x2, int y2){
      for(int i = x1; i <= x2; i++){ // looping para preencher o retangulo
        for(int j = y1; j <= y2; j++){
          if (grade[i][j] == 'E'){ // verifica se o obstaculo esta sendo inserido na posicao da estacao
            cout << "Nao eh possivel adicionar um obstaculo retangular no local" << endl;
          }
          else{
            grade[i][j] = '1'; // adiciona o obstaculo na posicao
          }
        }
      }
    }

    // imprimir ambiente
    void ImprimirAmbiente(){
        cout << "Ambiente: " << endl;
        for (int i = 0; i < dimensao_x; i++){
            for (int j = 0; j < dimensao_y; j++){
                cout << grade[i][j] << " ";
            }
            cout << endl;
        }
    }
};

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
  string line;
  // variaveis lidas no arquivo
  int dim_x, dim_y, pos_x, pos_y, x, y, x1, y1, x2, y2;
  int qtd_obs, qtd_obs_ret;
  ifstream myfile("example.txt"); // abre o arquivo example.txt

  if (myfile.is_open()){ // verifica se o arquivo foi aberto
    cout << "Arquivo aberto" << endl;

    while (getline(myfile, line)){ // looping para ler cada linha do arquivo
      stringstream(line) >> dim_x >> dim_y >> pos_x >> pos_y; // le a primeira linha e extrai os valores para as variaveis
      Ambiente ambienteTeste(dim_x, dim_y, pos_x, pos_y); // ambiente criado com as informacoes lidas
      getline(myfile, line); // le a proxima linha
      stringstream(line) >> qtd_obs; // atribui a linha a quantidade de obstaculos individuais

      for (int i = 0; i < qtd_obs; i++) { // looping que adiciona obstaculos ao ambiente
        getline(myfile, line);
        stringstream(line) >> x >> y; // atribui a posicao do obstaculo
        ambienteTeste.AdicionarObstaculo(x, y); // adiciona obstaculo
      }

      getline(myfile, line); // le a proxima linha referente a quantidade de obstaculos retangulares
      stringstream(line) >> qtd_obs_ret; // atribui a quantidade de obstaculos retangulares

      for (int i = 0; i < qtd_obs_ret; i++) { // looping que adiciona obstaculos retangulares
        getline(myfile, line); // le a linha das coordenadas dos retangulos
        stringstream(line) >> x1 >> y1 >> x2 >> y2; // atribui as coordenadas do retangulo
        ambienteTeste.AdicionarRetangulo(x1, y1, x2, y2); // adiciona retangulo ao ambiente
      }
      ambienteTeste.ImprimirAmbiente(); // imprime o ambiente 
    }

    myfile.close(); // fecha o arquivo

  } else { //caso o arquivo nao abra
      cout << "Nao foi possivel abrir o arquivo" << endl;
  }

return 0;
}