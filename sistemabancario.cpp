#include <iostream>
#include <string>

using namespace std;

struct Conta {
    int numero_conta = 0;
    int tipo_conta = 0;

    string nome_cliente = "";
    string cpf_cliente = "";
    string tipoConta = "";
    string statusConta = "";

    double saldo = 0;

    bool status_conta = false;
};

Conta contas[5];

int quantidadeContas = 0;
int opcao = 0;


// ======================================================
// STATUS DA CONTA
// ======================================================

bool lerStatusConta(Conta& conta) {

    string entrada;

    while (true) {

        cout << "Digite o status da conta:\n";
        cout << "(1) Ativa\n";
        cout << "(0) Inativa\n";

        cin >> entrada;

        if (entrada == "0" || entrada == "1") {

            conta.status_conta = (entrada == "1");

            if (conta.status_conta) {
                conta.statusConta = "Ativa";
            } else {
                conta.statusConta = "Inativa";
            }

            return true;
        }

        cout << "\nStatus invalido. Digite 0 ou 1.\n";
    }
}


// ======================================================
// NUMERO DA CONTA
// ======================================================

void lerNumeroConta(Conta& conta) {

    do {

        cout << "\nDigite o numero da conta: ";
        cin >> conta.numero_conta;

        if (conta.numero_conta <= 0) {

            cout << "\nNumero da conta invalido."
                 << " Tente novamente.\n";
        }

    } while (conta.numero_conta <= 0);
}


// ======================================================
// NOME DO CLIENTE
// ======================================================

void lerNomeCliente(Conta& conta) {

    cout << "Digite o nome do cliente: ";

    getline(cin >> ws, conta.nome_cliente);
}

// ======================================================
// VALIDAR CPF
// ======================================================

bool validarCPF(string cpf) {

    // Verifica se tem 11 digitos
    if (cpf.length() != 11) {
        return false;
    }

    // Verifica se todos os caracteres sao numeros
    for (char c : cpf) {
        if (c < '0' || c > '9') {
            return false;
        }
    }

    // Rejeita CPFs com todos os numeros iguais
    bool todosIguais = true;

    for (int i = 1; i < 11; i++) {
        if (cpf[i] != cpf[0]) {
            todosIguais = false;
            break;
        }
    }

    if (todosIguais) {
        return false;
    }


    // Calculo do primeiro digito verificador
    int soma = 0;
    int peso = 10;

    for (int i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * peso;
        peso--;
    }

    int resto = soma % 11;

    int digito1;

    if (resto < 2) {
        digito1 = 0;
    } else {
        digito1 = 11 - resto;
    }

    if (digito1 != cpf[9] - '0') {
        return false;
    }


    // Calculo do segundo digito verificador
    soma = 0;
    peso = 11;

    for (int i = 0; i < 10; i++) {
        soma += (cpf[i] - '0') * peso;
        peso--;
    }

    resto = soma % 11;

    int digito2;

    if (resto < 2) {
        digito2 = 0;
    } else {
        digito2 = 11 - resto;
    }

    if (digito2 != cpf[10] - '0') {
        return false;
    }

    return true;
}


// ======================================================
// CPF
// ======================================================

void lerCPF(Conta& conta) {

    do {

        cout << "Digite o CPF do cliente (apenas numeros): ";
        cin >> conta.cpf_cliente;

        if (!validarCPF(conta.cpf_cliente)) {
            cout << "\nCPF invalido, por favor, tente novamente.\n";
        }

    } while (!validarCPF(conta.cpf_cliente));
}


// ======================================================
// TIPO DA CONTA
// ======================================================

void lerTipoConta(Conta& conta) {

    do {

        cout << "Digite o tipo de conta:\n";
        cout << "(1) Poupanca\n";
        cout << "(2) Corrente\n";

        cin >> conta.tipo_conta;

        if (conta.tipo_conta != 1 && conta.tipo_conta != 2) {

            cout << "\nTipo de conta invalido."
                 << " Tente novamente.\n";
        }

    } while (
        conta.tipo_conta != 1 &&
        conta.tipo_conta != 2
    );

    if (conta.tipo_conta == 1) {
        conta.tipoConta = "Poupanca";
    } else {
        conta.tipoConta = "Corrente";
    }
}


// ======================================================
// SALDO
// ======================================================

void lerSaldo(Conta& conta) {

    do {

        cout << "Digite o saldo: R$";
        cin >> conta.saldo;

        if (conta.saldo < 0) {

            cout << "\nSaldo invalido."
                 << " Tente novamente.\n";
        }

    } while (conta.saldo < 0);
}


// ======================================================
// MOSTRAR DADOS DA CONTA
// ======================================================

void ConsultarConta(const Conta& conta) {

    cout << "\n====================================\n";

    cout << "Numero da conta: "
         << conta.numero_conta << endl;

    cout << "Nome do cliente: "
         << conta.nome_cliente << endl;

    cout << "CPF do cliente: "
         << conta.cpf_cliente << endl;

    cout << "Tipo de conta: "
         << conta.tipoConta << endl;

    cout << "Saldo: R$"
         << conta.saldo << endl;

    cout << "Status da conta: "
         << conta.statusConta << endl;

    cout << "====================================\n";
}


// ======================================================
// PROCURAR CONTA
// ======================================================

int buscarConta(int numero) {

    for (int i = 0; i < quantidadeContas; i++) {

        if (contas[i].numero_conta == numero) {

            return i;
        }
    }

    return -1;
}


// ======================================================
// CADASTRAR CONTA
// ======================================================

void cadastrarConta() {

    if (quantidadeContas >= 5) {

        cout << "\nLimite de 5 contas atingido.\n";

        return;
    }

    Conta& conta = contas[quantidadeContas];

    string confirmacao;
    int dado_alterar;

    lerNumeroConta(conta);
    lerNomeCliente(conta);
    lerCPF(conta);
    lerTipoConta(conta);
    lerSaldo(conta);
    lerStatusConta(conta);

    ConsultarConta(conta);

    cout << "\nOs dados estao corretos?"
         << " (s - Sim, n - Nao): ";

    cin >> confirmacao;


    while (confirmacao == "n") {

        cout << "\nQual dado deseja alterar?\n";

        cout << "(1) Numero da conta\n";
        cout << "(2) Nome\n";
        cout << "(3) CPF\n";
        cout << "(4) Tipo de conta\n";
        cout << "(5) Saldo\n";
        cout << "(6) Status da conta\n";

        cout << "\nDigite o respectivo numero: ";

        cin >> dado_alterar;


        switch (dado_alterar) {

            case 1:

                lerNumeroConta(conta);

                break;


            case 2:

                lerNomeCliente(conta);

                break;


            case 3:

                lerCPF(conta);

                break;


            case 4:

                lerTipoConta(conta);

                break;


            case 5:

                lerSaldo(conta);

                break;


            case 6:

                lerStatusConta(conta);

                break;


            default:

                cout << "\nOpcao invalida.\n";

                break;
        }


        ConsultarConta(conta);


        cout << "\nOs dados estao corretos agora?"
             << " (s - Sim, n - Nao): ";

        cin >> confirmacao;
    }


    quantidadeContas++;

    cout << "\nConta cadastrada com sucesso!\n";
}


// ======================================================
// CONSULTAR UMA CONTA
// ======================================================

void consultarContaCadastrada() {

    int numero;

    cout << "\nDigite o numero da conta: ";
    cin >> numero;

    int indice = buscarConta(numero);


    if (indice == -1) {

        cout << "\nConta nao encontrada.\n";

        return;
    }


    ConsultarConta(contas[indice]);
}


// ======================================================
// VERIFICAR SALDO
// ======================================================

void verificarSaldo() {

    int numero;

    cout << "\nDigite o numero da conta: ";
    cin >> numero;

    int indice = buscarConta(numero);


    if (indice == -1) {

        cout << "\nConta nao encontrada.\n";

        return;
    }


    if (contas[indice].status_conta) {

        cout << "\nSaldo: R$"
             << contas[indice].saldo
             << endl;

    } else {

        cout << "\nConta inativa.\n";
    }
}


// ======================================================
// ALTERAR TIPO DA CONTA
// ======================================================

void AlterarTipoConta() {

    int numero;

    cout << "\nDigite o numero da conta: ";
    cin >> numero;

    int indice = buscarConta(numero);


    if (indice == -1) {

        cout << "\nConta nao encontrada.\n";

        return;
    }


    if (contas[indice].status_conta) {

        cout << "\nTipo atual: "
             << contas[indice].tipoConta
             << endl;

        lerTipoConta(contas[indice]);

        cout << "\nTipo de conta alterado para: "
             << contas[indice].tipoConta
             << endl;

    } else {

        cout << "\nConta inativa."
             << " Ative a conta primeiro.\n";
    }
}


// ======================================================
// ATIVAR / DESATIVAR CONTA
// ======================================================

void alterarStatusConta() {

    int numero;

    cout << "\nDigite o numero da conta: ";
    cin >> numero;

    int indice = buscarConta(numero);


    if (indice == -1) {

        cout << "\nConta nao encontrada.\n";

        return;
    }


    contas[indice].status_conta =
        !contas[indice].status_conta;


    if (contas[indice].status_conta) {

        contas[indice].statusConta = "Ativa";

    } else {

        contas[indice].statusConta = "Inativa";
    }


    cout << "\nConta "
         << contas[indice].statusConta
         << " com sucesso.\n";
}


// ======================================================
// MAIN
// ======================================================

int main() {

    do {

        cout << "\n\n";
        cout << "===============================================\n";
        cout << "              BANCO SOLUMK                     \n";
        cout << "===============================================\n";

        cout << "1. Cadastrar conta\n";
        cout << "2. Consultar conta\n";
        cout << "3. Verificar saldo\n";
        cout << "4. Alterar tipo de conta\n";
        cout << "5. Ativar/desativar conta\n";
        cout << "6. Sair\n";

        cout << "===============================================\n";

        cout << "Selecione uma opcao: ";

        cin >> opcao;


        switch (opcao) {

            case 1:

                cadastrarConta();

                break;


            case 2:

                consultarContaCadastrada();

                break;


            case 3:

                verificarSaldo();

                break;


            case 4:

                AlterarTipoConta();

                break;


            case 5:

                alterarStatusConta();

                break;


            case 6:

                cout << "\nEncerrando o sistema...\n"
                     << "\nSistema encerrado!\n";

                break;


            default:

                cout << "\nOpcao invalida.\n";

                break;
        }


    } while (opcao != 6);


    return 0;
}