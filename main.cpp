#include <iostream>

using namespace std;

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

int main() {

    int opcionMenuPrincipal = 0;
    int opcionMenuSecundario = 0;
    int opcionMenuConteos = 0;
    string dni = "";
    int opcionCandidato = 0;
    string candidatos[3] = { "Roberto Sanchez", "Keiko Fujimori", "Rafael López Aliaga"};
    int contadorVotosCandidato[3] = {0, 0, 0};

    // MENU 1

    do {
        cout << "***** MENU PRINCIPAL *****" << endl;
        cout << "1. REGISTRO DE VOTO" << endl;
        cout << "2. CONTEO DE VOTOS" << endl;
        cout << "3. SALIR " << endl;
        cout << "Ingresa la opción: ";
        cin >> opcionMenuPrincipal;

        switch (opcionMenuPrincipal) {
            case 1: {
                do {
                    cout << "***** MENU SECUNDARIO *****" << endl;
                    cout << "1. IDENTIFICACIÓN" << endl;
                    cout << "2. VOLVER" << endl;
                    cout << "Ingrese una opción: ";
                    cin >> opcionMenuSecundario;

                    switch (opcionMenuSecundario) {
                        case 1: {
                            do {
                                cout << "***** DATOS PERSONALES *****" << endl;
                                cout << "Ingresa tu DNI: ";
                                cin >> dni;
                            } while (dni.length() != 8);

                            do {
                                cout << "***** LISTA DE CANDIDATOS *****" << endl;

                                for (int i = 0; i < 3; i++) {
                                    cout << i+1 << ". " << candidatos[i] << endl;
                                }
                                cout << "Elige la opción de tu candidato: ";
                                cin >> opcionCandidato;
                            } while (opcionCandidato < 1 || opcionCandidato > 3);

                            cout << "Has votado por " << candidatos[opcionCandidato - 1] << "." << endl;
                            contadorVotosCandidato[opcionCandidato - 1] = contadorVotosCandidato[opcionCandidato - 1] + 1;


                        }
                        case 2: {
                            cout << "El sistema ha finalizado" << endl;
                            return 0;
                        }
                        default: {}
                    }
                } while (opcionMenuSecundario < 1 || opcionMenuSecundario > 2);
            }

            case 2: {
                do {
                    cout << "***** MENU SECUNDARIO *****" << endl;
                    cout << "1. CANTIDAD DE VOTOS TOTALES" << endl;
                    cout << "2. CANTIDAD DE VOTOS POR PROVINCIA" << endl;
                    cout << "3. VOLVER " << endl;
                    cout << "Ingresa la opción: ";
                    cin >> opcionMenuConteos;
                } while (opcionMenuConteos < 1 || opcionMenuConteos > 3);

                switch (opcionMenuConteos) {
                    case 1: {
                        cout << "***** VOTOS TOTALES *****" << endl;
                        for (int i = 0; i < 3; i++) {
                            cout << i+1 << ". " << candidatos[i] << " " << contadorVotosCandidato[opcionCandidato - 1] << " votos" << endl;
                        }
                        break;
                    }
                    case 2: {
                        cout << "***** VOTOS POR PROVINCIA *****" << endl;
                    }
                }
            }
        }
    } while (opcionMenuPrincipal < 1 || opcionMenuPrincipal > 3);



    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}