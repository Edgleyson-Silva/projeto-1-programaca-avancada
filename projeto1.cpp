#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Ambiente{
private:
    int dimensao_x;
    int dimensao_y;
    char** grade;
    int posicao_estacao_x;
    int posicao_estacao_y;

public:
    Ambiente(int dim_x, int dim_y, int pos_x, int pos_y) : dimensao_x(dim_x), dimensao_y(dim_y), posicao_estacao_x(pos_x), posicao_estacao_y(pos_y){
        grade = new char*[dim_x];
        for (int i = 0; i < dim_x; i++){
            grade[i] = new char[dim_y];
            for (int j = 0; j < dim_y; j++){
                grade[i][j] = '0';
            }
        }
        grade[pos_x][pos_y] = 'E';
    }

    void AdicionarObstaculo(){
        int x, y;
        cout << "Informe a posicao x do obstaculo: ";
        cin >> x;
        cout << "Informe a posicao y do obstaculo: ";
        cin >> y;
        if (grade[x][y] == 'E'){
            cout << "Nao eh possivel adicionar um obstaculo no local";
        }
        else{
            grade[x][y] = '1';
        }

    }

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

int main(){
    Ambiente ambienteTeste(10,6,2,3);
    ambienteTeste.ImprimirAmbiente();
    return 0;
}