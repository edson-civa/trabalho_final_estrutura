#include <iostream>
#include <queue>
#include <sstream>
#include <string>
using namespace std;

// salva todos os dados de um atendimento
struct atendimento {
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

    int max_espera = 0;
    
    cout << "-- Sistema de cadastro de pacientes --"<< endl;
    cout << "Digite C para cadastro de paciente"<< endl; 
    cout << "digite A para Realizar um Atendimento" << endl;
    cout << "Digite D para ver o numero total de pacientes e todos os atendimentos"<< endl;
    cout << "Digite Q para sair do sistema"<< endl;

    while (getline(cin, line)) {

        if (line.empty()) continue;

        stringstream ss(line);
        char cmd;
        ss >> cmd;

        atendimento n;

        if (cmd == 'C') { 
            ss >> n.senha >> n.prioridade >> n.hh >> n.mm;

            if (n.prioridade == 'V'){
                fila_vermelha.push(n);
                qtd_vermelha++;

            } else if(n.prioridade == 'A'){
                fila_amarelo.push(n);
                qtd_amarelo++;

            } else if(n.prioridade == 'D'){
                fila_verde.push(n);
                qtd_verde++;

            } else if(n.prioridade == 'B'){
                fila_branco.push(n);
                qtd_branco++;

            } else {
                cout << "Erro ao cadastrar paciente, prioridade invalida! \n";
            }

            // atualiza pico corretamente
            int atual = fila_vermelha.size() + fila_amarelo.size() + fila_verde.size() + fila_branco.size();
            if (atual > pico) pico = atual;

        } else if (cmd == 'A') {

            string hh_s, mm_s;
            ss >> hh_s >> mm_s;
            int h_at = stoi(hh_s);
            int m_at = stoi(mm_s);

            bool temPaciente = false;
            atendimento atual;

            if (!fila_vermelha.empty()) {
                atual = fila_vermelha.front();
                fila_vermelha.pop();
                atendidos_vermelha++;
                temPaciente = true;

            } else if (!fila_amarelo.empty()) {
                atual = fila_amarelo.front();
                fila_amarelo.pop();
                atendidos_amarelo++;
                temPaciente = true;

            } else if (!fila_verde.empty()) {
                atual = fila_verde.front();
                fila_verde.pop();
                atendidos_verde++;
                temPaciente = true;

            } else if (!fila_branco.empty()) {
                atual = fila_branco.front();
                fila_branco.pop();
                atendidos_branco++;
                temPaciente = true;
            }

            if (!temPaciente) {
                cout << hh_s << " " << mm_s << " Sem pacientes aguardando atendimento\n"; 
                continue;
            }

            total_atendidos++;

            // Cálculo da espera
            int chegada_min = atual.hh * 60 + atual.mm;
            int atendimento_min = h_at * 60 + m_at;
            int espera = atendimento_min - chegada_min;

            if (espera > max_espera)
                max_espera = espera;

        } else if (cmd == 'D') {
            total = qtd_vermelha + qtd_amarelo + qtd_verde + qtd_branco;
            cout << "V:" << qtd_vermelha << " "
                 << "A:" << qtd_amarelo << " "
                 << "D:" << qtd_verde << " "
                 << "B:" << qtd_branco << " "
                 << "Atendidos:" << total_atendidos << endl;

        } else if (cmd == 'Q') {
            total = qtd_vermelha + qtd_amarelo + qtd_verde + qtd_branco;
            cout << "--- RELATÓRIO FINAL ---\n"
                 << "Total atendidos: " << total_atendidos << endl
                 << "Por prioridade: V=" << atendidos_vermelha 
                 << " A=" << atendidos_amarelo 
                 << " D=" << atendidos_verde 
                 << " B=" << atendidos_branco << endl
                 << "Pico de lotação: " << pico << endl
                 << "Espera Maxima: " << max_espera << " min" << endl;
            break;
        }       
    }
    return 0;
}
