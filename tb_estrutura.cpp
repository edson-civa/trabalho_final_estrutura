#include <iostream>
#include <queue>
#include <sstream>
#include <string>
using namespace std;


// falta calcular os tempos, e colocar os cout pra eles 
// e falta calcular o pico de pacientes, no fim ja tem o cout certinho

// salva todos os dados de um atendimento
struct atendimento
{
    string senha;
    char prioridade;
    int hh;
    int mm;
};

// cada prioridade tem sua fila 
queue<atendimento> fila_vermelha;
queue<atendimento> fila_amarelo;
queue<atendimento> fila_verde;
queue<atendimento> fila_branco;

int main(){
    string line;

    int qtd_vermelha = 0;
    int qtd_amarelo = 0;
    int qtd_verde = 0;
    int qtd_branco = 0;
    int total = 0;
    int total_atendidos = 0;
    int pico = 0;

    int atendidos_vermelha = 0;
    int atendidos_amarelo = 0;
    int atendidos_verde = 0;
    int atendidos_branco = 0;

    while (getline(cin, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        char cmd;
        ss >> cmd;

        atendimento n;


        if (cmd == 'C') { // salva o paciente na fila da sua prioridade
            ss >> n.senha >> n.prioridade >> n.hh >> n.mm;
            if (n.prioridade == 'V'){
                fila_vermelha.push(n);
                qtd_vermelha++;

            }else if(n.prioridade == 'A'){
                fila_amarelo.push(n);
                qtd_amarelo++;

            }else if(n.prioridade == 'D'){
                fila_verde.push(n);
                qtd_verde++;

            }else if(n.prioridade == 'B'){
                fila_branco.push(n);
                qtd_branco++;

            }else{
                cout << "Erro ao cadastrar paciente, prioridade invalida! \n";
            }        
        }else if(cmd == 'A'){ //atendimento do paciente, verifica se tem alguem na na fila de prioridade mais alta, se nao tiver tenta a proxima 
            string hh, mm;
            ss >> hh >> mm;

            if (!fila_vermelha.empty()){
                fila_vermelha.pop();
                qtd_vermelha--;
                atendidos_vermelha++;

            }else if(!fila_amarelo.empty()){
                fila_amarelo.pop();
                qtd_amarelo--;
                atendidos_amarelo++;

            }else if(!fila_verde.empty()){
                fila_verde.pop();
                qtd_verde--;
                atendidos_verde++;

            }else if(!fila_branco.empty()){
                fila_branco.pop();
                qtd_branco--;
                atendidos_branco++;

            }else{
                cout << hh << " " << mm << " Sem pacientes aguardando atendimento\n"; 
                continue;
            }
            total_atendidos++;

        }else if(cmd == 'D'){ // mostra a situacao atual
            total = qtd_vermelha+qtd_branco+qtd_verde+qtd_amarelo;
            cout << "V:" << qtd_vermelha << " "
            << "A:" << qtd_amarelo << " "
            << "D:" <<  qtd_verde << " "
            << "B:" <<  qtd_branco << " | "
            << "Atendidos:" << total_atendidos << endl;  
        }else if(cmd == 'Q'){// mostra o final 
            total = qtd_vermelha+qtd_branco+qtd_verde+qtd_amarelo;
            cout << "--- RELATÓRIO FINAL ---\n"
                << "Total atendidos: " << total_atendidos << endl
                << "Por prioridade: V=" << atendidos_vermelha << " A=" << atendidos_amarelo << " D=" << atendidos_verde << " B=" << atendidos_branco << endl
                << "Pico de lotação" << pico << endl
                << "Espera Maxima:" << endl;
        }

    }
    

    return 0;
}