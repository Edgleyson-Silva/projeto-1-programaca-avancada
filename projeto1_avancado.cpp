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
    int posicao_estacao_x; // posicao X da estacao
    int posicao_estacao_y; // posicao Y da estacao

public:
    int public_dimensao_x(){
      return dimensao_x;
    }
    int public_dimensao_y(){
      return dimensao_y;
    }
    char** grade; // matriz de caracteres que representa o ambiente
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

class Robo{
  private:
    string robo_nome;
    int robo_x, robo_y;
    int robo_bateria;
    Ambiente &ambiente; // adicionar uma referencia a objeto da classe Ambiente

  public:
    Ambiente& publicAmbiente() {
      return ambiente;
    }
    int publicBateria(){
      return robo_bateria;
    }
    int publicX(){
      return robo_x;
    }
    int publicY(){
      return robo_y;
    }

    Robo(string nome_robo, int x_robo, int y_robo, int bateria_robo, Ambiente &amb) : robo_nome(nome_robo), robo_x(x_robo), robo_y(y_robo), robo_bateria(bateria_robo), ambiente(amb){
      ambiente.grade[x_robo][y_robo] = 'R';
    }
};

class Bateria{
  private:
    int nivel;
  
  public:
    Bateria(int nivel_valor) : nivel(nivel_valor) {}

    int publicDecarrega(){
      return nivel--;
    }

    int publicCarrega(){
      return nivel++;
    }

    int publicMostraNivel(){
      return nivel;
    }
};

class Modelo1 : public Robo{
    private:
      bool para_choque;
    public:
      Bateria bateria_robo = publicBateria();
      int robo_x = publicX();
      int robo_y = publicY();
      Modelo1(string nome_robo, int x_robo, int y_robo, int bateria_robo, Ambiente &amb) : Robo(nome_robo, x_robo, y_robo, bateria_robo, amb){};
      Ambiente ambiente = publicAmbiente();
      int dimensao_x = ambiente.public_dimensao_x();
      int dimensao_y = ambiente.public_dimensao_y();
      void Limpar(){
        cout << "--------------------------------------------------------------------------------------" << endl;
        // Enquanto a bateria não acaba
        while(bateria_robo.publicMostraNivel() > 0){
          // Gera números aleatórios para escolher a direção do movimento
          
          int valorRand = rand();
          int direcao = valorRand % 4;
          int x = robo_x;
          int y = robo_y;
          int direcao_oposta;

          // Verifica a direção escolhida e se o movimento é possível
          //direção 0 -> cima
          if(direcao == 0 && robo_x > 0 && ambiente.grade[robo_x - 1][robo_y] != '1' && direcao_oposta != 0){
            direcao_oposta = 1;
            while(robo_x - 1 > -1 && robo_x - 1 >= 0 && ambiente.grade[robo_x - 1][robo_y] != '1' && bateria_robo.publicMostraNivel() > 0){
              x = robo_x - 1;
              if(x != robo_x || y != robo_y){
                ambiente.grade[robo_x][robo_y] = '0';
                robo_x = x;
                robo_y = y;
                ambiente.grade[robo_x][robo_y] = 'R';
                bateria_robo.publicDecarrega();
              }
              else{
                break;
              }
              ambiente.ImprimirAmbiente();
              cout << "--------------------------------------------------------------------------------------" << endl;
              cout << bateria_robo.publicMostraNivel() << endl;
            }
          }
          //direção 1 -> baixo
          else if(direcao == 1 && robo_x < dimensao_x - 1 && ambiente.grade[robo_x + 1][robo_y] != '1' && direcao_oposta != 1){
            direcao_oposta = 0;
            while(robo_x + 1 < dimensao_x && robo_x <= dimensao_x - 1 && ambiente.grade[robo_x + 1][robo_y] != '1' && bateria_robo.publicMostraNivel() > 0){
              x = robo_x + 1;
              if(x != robo_x || y != robo_y){
                ambiente.grade[robo_x][robo_y] = '0';
                robo_x = x;
                robo_y = y;
                ambiente.grade[robo_x][robo_y] = 'R';
                bateria_robo.publicDecarrega();
              }
              else{
                break;
              }
              ambiente.ImprimirAmbiente();
              cout << "--------------------------------------------------------------------------------------" << endl;
              cout << bateria_robo.publicMostraNivel() << endl;
            }
          }
          //direção 2 -> esquerda
          else if(direcao == 2 && robo_y > 0 && ambiente.grade[robo_x][robo_y - 1] != '1' && direcao_oposta != 2){
            direcao_oposta = 3;
            while(robo_y - 1 > -1 && robo_y >= 0 && ambiente.grade[robo_x][robo_y - 1] != '1' && bateria_robo.publicMostraNivel() > 0){
              y = robo_y - 1;
              if(x != robo_x || y != robo_y){
                ambiente.grade[robo_x][robo_y] = '0';
                robo_x = x;
                robo_y = y;
                ambiente.grade[robo_x][robo_y] = 'R';
                bateria_robo.publicDecarrega();
              }
              else{
                break;
              }
              ambiente.ImprimirAmbiente();
              cout << "--------------------------------------------------------------------------------------" << endl;
              cout << bateria_robo.publicMostraNivel() << endl;
            }
          }
          //direção 3 -> direita
          else if(direcao == 3 && robo_y < dimensao_y - 1 && ambiente.grade[robo_x][robo_y + 1] != '1' && direcao_oposta != 3){
            direcao_oposta = 2;
            while(robo_y + 1 < dimensao_y && robo_y <= dimensao_y - 1 && ambiente.grade[robo_x][robo_y + 1] != '1' && bateria_robo.publicMostraNivel() > 0){
              y = robo_y + 1;
              if(x != robo_x || y != robo_y){
                ambiente.grade[robo_x][robo_y] = '0';
                robo_x = x;
                robo_y = y;
                ambiente.grade[robo_x][robo_y] = 'R';
                bateria_robo.publicDecarrega();
              }
              else{
                break;
              }
              ambiente.ImprimirAmbiente();
              cout << "--------------------------------------------------------------------------------------" << endl;
              cout << bateria_robo.publicMostraNivel() << endl;
            } 
          }

          // Se o movimento é possível, atualiza a posição do robô
        ambiente.ImprimirAmbiente();
        cout << "--------------------------------------------------------------------------------------" << endl;
      }
    }
  };



int main() {
  srand(time(NULL)); //para gerar diferentes numeros na função rand()

  string line;
  // variaveis lidas no arquivo
  int dim_x, dim_y, pos_x, pos_y, x, y, x1, y1, x2, y2;
  int qtd_obs, qtd_obs_ret;
  string nomeRobo;
  int xRobo, yRobo, bateriaRobo;

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

      getline(myfile, line); // le a linha do nome do robo
      stringstream(line) >> nomeRobo; 

      getline(myfile, line); // le a linha da posicao do robo
      stringstream(line) >> xRobo >> yRobo; 

      getline(myfile, line); // le a linha da porcentagem da bateria
      stringstream(line) >> bateriaRobo;

      Robo roboTeste(nomeRobo, xRobo, yRobo, bateriaRobo, ambienteTeste);

      ambienteTeste.ImprimirAmbiente(); // imprime o ambiente 

      Modelo1 modelo1Teste(nomeRobo, xRobo, yRobo, bateriaRobo, ambienteTeste);

      modelo1Teste.Limpar();

      //ambienteTeste.ImprimirAmbiente(); // imprime o ambiente 

    }

    myfile.close(); // fecha o arquivo

  } else { //caso o arquivo nao abra
      cout << "Nao foi possivel abrir o arquivo" << endl;
  }

return 0;
}
