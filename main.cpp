#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

const int MAX_CANDIDATOS = 3;
const string HASH_GENESIS = "GENESIS";

struct Candidato {
    string nombre;
    int votos;
};

struct Bloque {
    int indice;
    string hashAnterior;
    string hashActual;
    int opcionCandidato;
};

Candidato candidatos[MAX_CANDIDATOS] = {
    {"Roberto Sanchez", 0},
    {"Keiko Fujimori", 0},
    {"Rafael Lopez Aliaga", 0}
};

vector<Bloque> blockchain;

void inicializarBlockchain();
void mostrarMenuPrincipal();
void mostrarCandidatos();
void registrarVoto();
void mostrarMenuConteoVotos();
void mostrarBlockchain();
void verificarBlockchain();
string generarHash(int indice, string hashAnterior, int candidato);

int main() {
    setlocale(LC_ALL, "");
    inicializarBlockchain();

    cout << " ********** SISTEMA DE VOTACIÓN ELECTRÓNICA **********\n\n";
    int opcion;
    do {
        mostrarMenuPrincipal();
        cout << "Ingrese la opción: ";
        cin >> opcion;
        switch (opcion) {
            case 1: {
                registrarVoto();
                break;
            }
            case 2: {
                mostrarMenuConteoVotos();
                break;
            }
            case 3: {
                mostrarBlockchain();
                break;
            }
            case 4: {
                verificarBlockchain();
                break;
            }
            case 5: {
                cout << "\nGracias por utilizar el sistema.\n";
                break;
            }
            default: {
                cout << "\nOpción incorrecta, vuelva a intentar por favor.\n";
            }
        }
    } while (opcion != 5);
    return 0;
}

void inicializarBlockchain() {
    Bloque genesis;

    genesis.indice = 0;
    genesis.hashAnterior = HASH_GENESIS;
    genesis.opcionCandidato = 0;
    genesis.hashActual = generarHash(genesis.indice,genesis.hashAnterior, genesis.opcionCandidato);

    blockchain.push_back(genesis);
}

void mostrarMenuPrincipal() {
    cout << "----- MENÚ PRINCIPAL -----\n";
    cout<<"1. Registrar voto\n";
    cout<<"2. Conteo de votos\n";
    cout<<"3. Mostrar blockchain\n";
    cout<<"4. Verificar blockchain\n";
    cout<<"5. Salir\n";
}

void registrarVoto() {
        Bloque nuevoBloque;
        nuevoBloque.indice = blockchain.size();
        nuevoBloque.hashAnterior = blockchain.back().hashActual;

        mostrarCandidatos();
        int opcionCandidato;

        do {
            cout << "\nIngrese la opción: ";
            cin >> opcionCandidato;
        } while (opcionCandidato < 1 || opcionCandidato > MAX_CANDIDATOS);

        cout << "\nVoto registrado para " << candidatos[opcionCandidato - 1].nombre << endl;

        nuevoBloque.opcionCandidato = opcionCandidato;
        candidatos[opcionCandidato - 1].votos++;
        nuevoBloque.hashActual = generarHash(nuevoBloque.indice,nuevoBloque.hashAnterior, nuevoBloque.opcionCandidato);

        blockchain.push_back(nuevoBloque);

        cout << "\n====================\n";
        cout << "Bloque " << nuevoBloque.indice << " creado.\n";
        cout << "Hash: " << nuevoBloque.hashActual;
        cout << "\n====================\n";
}

void mostrarMenuConteoVotos() {
    int opcion;

    do {
        cout << "----- MENÚ CONTEO DE VOTOS -----\n";
        cout << "1. Votos por candidato\n";
        cout << "2. Total de votos emitidos\n";
        cout << "3. Volver\n";
        cout << "Ingrese la opción:: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                cout << "\n----- VOTOS POR CANDIDATO -----\n";
                for (int i = 0; i < MAX_CANDIDATOS; i++){
                    cout << i + 1 << ". " << candidatos[i].nombre << " : " << candidatos[i].votos << " votos\n";
                }
                break;
            }
            case 2: {
                int total = 0;
                for (int i = 0; i < MAX_CANDIDATOS; i++) {
                    total = total + candidatos[i].votos;
                }
                cout << "\nTotal de votos emitidos: " << total << endl;
                break;
            }
            case 3: {
                cout << "\nVolviendo al menú principal ...\n";
                break;
            }
            default: {
                cout << "\nOpción incorrecta, vuelva a intentar por favor.\n";
            }
        }
    } while (opcion != 3);
}

string generarHash(int indice, string hashAnterior, int opcionCandidato) {
    string datos = to_string(indice) + hashAnterior + to_string(opcionCandidato);
    hash<string> hash;
    size_t valorHash = hash(datos);
    return to_string(valorHash);
}

void mostrarCandidatos() {
    cout << "\n----- LISTA DE CANDIDATOS -----\n";
    for (int i = 0; i < MAX_CANDIDATOS; i++) {
        cout << i + 1 <<". " << candidatos[i].nombre << endl;
    }
}

void mostrarBlockchain() {
    cout << "\n----- BLOCKCHAIN DEL SISTEMA DE VOTACIÓN ELECTRÓNICA -----\n";

    if (blockchain.size() == 1) {
        cout << "\nSolo existe el bloque Génesis.\n";
    } else {
        for (int i = 0; i < blockchain.size(); i++) {
            cout << "\n====================\n";
            cout << "Bloque #" << blockchain[i].indice;
            cout << "\n----- Hashes -----";
            cout << "\nHash anterior: " << blockchain[i].hashAnterior;
            cout << "\nHash actual: " << blockchain[i].hashActual;

            cout << "\n----- Datos -----";
            cout << "\nCandidato: " << candidatos[blockchain[i].opcionCandidato - 1].nombre;
            cout << "\n====================\n";
        }
    }
}

void verificarBlockchain() {
    cout << "\n----- VERIFICACION BLOCKCHAIN -----\n";

    bool cadenaValida = true;

    if (blockchain[0].hashAnterior != HASH_GENESIS) {
        cout << "Error en el bloque Génesis.\n" << endl;
        cadenaValida = false;
    }

    for (int i = 1; i < blockchain.size(); i++) {
        string hashCalculado = generarHash(blockchain[i].indice, blockchain[i].hashAnterior, blockchain[i].opcionCandidato);

        if (hashCalculado != blockchain[i].hashActual) {
            cout << "\nBloque #" << i << " ha sido alterado.\n";
            cout << "Hash almacenado: " << blockchain[i].hashActual << endl;
            cout << "Hash calculado: " << hashCalculado << endl;
            cadenaValida = false;
        }

        if (blockchain[i].hashAnterior != blockchain[i - 1].hashActual) {
            cout << "\nBloque #" << i << " con enlace incorrecto.\n";
            cout << "Hash esperado: " << blockchain[i - 1].hashActual << endl;
            cout << "Hash almacenado: " << blockchain[i].hashAnterior << endl;
            cadenaValida = false;
        }
    }

    if (cadenaValida) {
        cout << "\nBlockchain correcta, no se detectaron alteraciones.\n";
    } else {
        cout << "\nBlockchain incorrecta, existe al menos un bloque modificado.\n";
    }
}