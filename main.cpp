#include <iostream>
#include <string>

using namespace std;

const int MAX_CANDIDATOS = 3;
const int MAX_BLOQUES = 20;
const string HASH_GENESIS = "GENESIS";

int contadorVotos[MAX_CANDIDATOS] = {0};
string candidatos[MAX_CANDIDATOS] = {"Roberto Sanchez", "Keiko Fujimori", "Rafael Lopez Aliaga"};

int indiceBloque[MAX_BLOQUES] = {0};
string hashAnterior[MAX_BLOQUES] = {""};
string hashActual[MAX_BLOQUES] = {""};
string dniBloque[MAX_BLOQUES] = {""};
int candidatoBloque[MAX_BLOQUES] = {0};

int bloqueActual=0;
int totalBloques=1;

void inicializarBlockchain();
void mostrarMenuPrincipal();
void mostrarCandidatos();
void registrarVoto();
void mostrarMenuConteoVotos();
void mostrarBlockchain();
void verificarBlockchain();
string generarHash(int indice, string hashAnterior, string dni, int candidato);

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
    indiceBloque[0] = 0;
    hashAnterior[0] = HASH_GENESIS;
    hashActual[0] = generarHash(0,HASH_GENESIS,"",0);
    bloqueActual = 0;
    totalBloques = 1;
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
    if (totalBloques >= MAX_BLOQUES) {
        cout << "\nSe alcanzó el número máximo de bloques.\n";
        return;
    }

    bloqueActual = totalBloques;
    totalBloques++;

    indiceBloque[bloqueActual] = bloqueActual;
    hashAnterior[bloqueActual] = hashActual[bloqueActual - 1];

    string dni;
    int opcionCandidato;

    do {
        cout << "\nIngrese su DNI: ";
        cin >> dni;

        if (dni.length() != 8) {
            cout << "\nDNI incorrecto, vuelva a intentar por favor.\n";
        }
    } while (dni.length() != 8);

    mostrarCandidatos();

    do {
        cout << "\nIngrese la opción: ";
        cin >> opcionCandidato;

    } while (opcionCandidato < 1 || opcionCandidato > MAX_CANDIDATOS);

    cout << "\nVoto registrado para " << candidatos[opcionCandidato - 1] << endl;

    dniBloque[bloqueActual] = dni;
    candidatoBloque[bloqueActual] = opcionCandidato;

    contadorVotos[opcionCandidato - 1]++;

    hashActual[bloqueActual] = generarHash(indiceBloque[bloqueActual], hashAnterior[bloqueActual], dni, opcionCandidato);

    cout << "\n====================\n";
    cout << "Bloque " << bloqueActual << " creado.\n";
    cout << "Hash: " << hashActual[bloqueActual];
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
                    cout << i + 1 << ". " << candidatos[i] << " : " << contadorVotos[i] << " votos\n";
                }
                break;
            }

            case 2: {
                int total = 0;
                for (int i = 0; i < MAX_CANDIDATOS; i++) {
                    total += contadorVotos[i];
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

string generarHash(int indice, string hashAnterior, string dni, int candidato) {
    int suma = indice;

    for (char caracter : hashAnterior) {
        suma += caracter;
    }

    if (dni != "") {
        for (char caracter : dni) {
            suma += caracter;
        }
    }
    suma += candidato * 31;
    return "HASH" + to_string(suma);
}

void mostrarCandidatos(){
    cout << "\n----- LISTA DE CANDIDATOS -----\n";
    for (int i = 0; i < MAX_CANDIDATOS; i++) {
        cout << i + 1 <<". " << candidatos[i] << endl;
    }
}

void mostrarBlockchain() {
    cout << "\n----- BLOCKCHAIN DEL SISTEMA DE VOTACIÓN ELECTRÓNICA -----\n";

    if (totalBloques == 1) {
        cout << "\nSolo existe el bloque Génesis.\n";
        return;
    }

    for (int i = 1; i < totalBloques; i++) {
        cout << "\n====================\n";
        cout << "Bloque #" << indiceBloque[i] << endl;
        cout << "\n----- Hashes -----" << endl;
        cout << "Hash anterior: " << hashAnterior[i] << endl;
        cout << "Hash actual: " << hashActual[i] << endl;

        cout << "\n----- Datos -----" << endl;
        cout << "Candidato: " << candidatos[candidatoBloque[i] - 1];
        cout << "\n====================\n";
    }
}

void verificarBlockchain() {
    cout << "\n----- VERIFICACION BLOCKCHAIN -----\n";

    bool cadenaValida = true;

    if (hashAnterior[0] != HASH_GENESIS) {
        cout << "Error en el bloque Génesis.\n" << endl;
        cadenaValida = false;
    }

    for (int i = 1; i < totalBloques; i++) {
        string hashCalculado = generarHash(indiceBloque[i],hashAnterior[i],dniBloque[i], candidatoBloque[i]);

        if (hashCalculado != hashActual[i]) {
            cout << "\nBloque #" << i << " ha sido alterado.\n";
            cout << "Hash almacenado: " << hashActual[i] << endl;
            cout << "Hash calculado: " << hashCalculado << endl;
            cadenaValida = false;
        }

        if (hashAnterior[i] != hashActual[i - 1]) {
            cout << "\nBloque #" << i << " con enlace incorrecto.\n";
            cout << "Hash esperado: " << hashActual[i - 1] << endl;
            cout << "Hash almacenado: " << hashAnterior[i] << endl;
            cadenaValida = false;
        }
    }

    if (cadenaValida) {
        cout << "\nBlockchain correcta, no se detectaron alteraciones.\n";
    } else {
        cout << "\nBlockchain incorrecta, existe al menos un bloque modificado.\n";
    }
}