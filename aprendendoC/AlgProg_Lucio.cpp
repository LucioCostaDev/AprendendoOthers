/******************************************************************************
 * SISTEMA DE GESTÃO ACADÊMICA
 * Finalidade: Cadastro, listagem, busca e atualização de notas de alunos.
 * Linguagem: C++
 *******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// --- ESTRUTURA DE DADOS ---
// Representa a entidade Aluno com suas características fundamentais
struct Aluno {
    string nome;
    int idade;
    int matricula;
    float notaFinal;
};

// --- PROTÓTIPOS DAS FUNÇÕES ---
// As funções são declaradas aqui para organizar o fluxo do programa
void exibirMenu();
void cadastrarAluno(vector<Aluno> &lista);
void listarAlunos(const vector<Aluno> &lista);
void buscarAluno(const vector<Aluno> &lista);
void atualizarNota(vector<Aluno> &lista);

// --- FUNÇÃO PRINCIPAL ---
int main() {
    // Vetor que armazena as structs de alunos (limite lógico de 100 no switch)
    vector<Aluno> bancoDeDados;
    int opcao;

    // Loop principal do sistema
    do {
        exibirMenu();
        if (!(cin >> opcao)) { // Validação simples para entradas que não são números
            cout << "Entrada invalida! Use apenas numeros." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (opcao) {
            case 1:
                // Requisito: Limite de 100 alunos
                if (bancoDeDados.size() < 100) {
                    cadastrarAluno(bancoDeDados);
                } else {
                    cout << "\nERRO: Capacidade maxima do sistema (100 alunos) atingida!" << endl;
                }
                break;
            case 2:
                listarAlunos(bancoDeDados);
                break;
            case 3:
                buscarAluno(bancoDeDados);
                break;
            case 4:
                atualizarNota(bancoDeDados);
                break;
            case 0:
                cout << "\nEncerrando o sistema acadêmico. Até logo!" << endl;
                break;
            default:
                cout << "\nOpção invalida! Tente novamente." << endl;
        }
    } while (opcao != 0);

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// Exibe as opções disponíveis no console
void exibirMenu() {
    cout << "\n========================================" << endl;
    cout << "       SISTEMA DE CADASTRO DE ALUNOS      " << endl;
    cout << "========================================" << endl;
    cout << "1. Cadastrar Novo Aluno" << endl;
    cout << "2. Listar Todos os Alunos" << endl;
    cout << "3. Buscar Aluno por Matricula" << endl;
    cout << "4. Atualizar Nota Final" << endl;
    cout << "0. Sair" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Escolha uma opcao: ";
}

// Coleta os dados e os armazena no vetor de structs
void cadastrarAluno(vector<Aluno> &lista) {
    Aluno novo;
    
    cout << "\n--- CADASTRO DE ALUNO ---" << endl;
    cout << "Nome Completo: ";
    cin.ignore(); // Limpa o buffer para permitir leitura de nomes com espaços
    getline(cin, novo.nome);
    
    cout << "Idade: ";
    cin >> novo.idade;
    
    cout << "Numero de Matricula: ";
    cin >> novo.matricula;
    
    cout << "Nota Final: ";
    cin >> novo.notaFinal;

    lista.push_back(novo);
    cout << "\n>>> Aluno " << novo.nome << " cadastrado com sucesso!" << endl;
}

// Percorre o vetor e exibe os dados formatados
void listarAlunos(const vector<Aluno> &lista) {
    if (lista.empty()) {
        cout << "\n[!] O sistema não possui alunos cadastrados." << endl;
        return;
    }

    cout << "\n------------------------------------------------------------" << endl;
    cout << left 
        << setw(25) << "NOME" 
        << setw(10) << "IDADE" 
        << setw(15) << "MATRICULA" 
        << "NOTA" << endl;
    cout << "------------------------------------------------------------" << endl;
    
    for (const auto &aluno : lista) {
        cout << left 
            << setw(25) << aluno.nome 
             << setw(10) << aluno.idade 
             << setw(15) << aluno.matricula 
             << fixed << setprecision(2) << aluno.notaFinal << endl;
    }
    cout << "------------------------------------------------------------" << endl;
}

// Realiza uma busca linear no vetor com base na matrícula
void buscarAluno(const vector<Aluno> &lista) {
    if (lista.empty()) {
        cout << "\n[!] Não há dados para pesquisar." << endl;
        return;
    }

    int mat;
    cout << "\nDigite a matrícula desejada: ";
    cin >> mat;

    for (const auto &aluno : lista) {
        if (aluno.matricula == mat) {
            cout << "\nRegistro Encontrado:" << endl;
            cout << "-> Nome: " << aluno.nome << endl;
            cout << "-> Idade: " << aluno.idade << " anos" << endl;
            cout << "-> Nota Atual: " << aluno.notaFinal << endl;
            return;
        }
    }
    cout << "\n[!] Aluno com a matrícula " << mat << " não localizado." << endl;
}

// Localiza o aluno e permite a alteração de um campo específico (nota)
void atualizarNota(vector<Aluno> &lista) {
    if (lista.empty()) {
        cout << "\n[!] Não há alunos cadastrados para atualizar." << endl;
        return;
    }

    int mat;
    cout << "\nDigite a matrícula do aluno: ";
    cin >> mat;

    for (auto &aluno : lista) {
        if (aluno.matricula == mat) {
            cout << "Aluno: " << aluno.nome << " | Nota Atual: " << aluno.notaFinal << endl;
            cout << "Digite a nova nota: ";
            cin >> aluno.notaFinal;
            cout << "\n>>> Nota atualizada com sucesso!" << endl;
            return;
        }
    }
    cout << "\n[!] Matrícula " << mat << " não encontrada." << endl;
}