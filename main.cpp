#include <iostream>

using namespace std;

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

int main() {

    int opcion1 = 0;
    int opcion1_1 = 0;
    string dni = 0;

    // MENU 1
    do {
        cout << "***** MENU PRINCIPAL *****" << endl;
        cout << "1. IDENTIFICACIÓN" << endl;
        cout << "2. SALIR" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion1;

        switch (opcion1) {
            case 1: {
                do {
                    cout << "***** DATOS PERSONALES *****" << endl;
                    cout << "Ingresa tu DNI: ";
                    cin >> dni;
                } while (dni.length() != 8);
            }
            case 2: {
                cout << "El sistema ha finalizado" << endl;
                return 0;
            }
            default: {}
        }
    } while (opcion1 < 1 || opcion1 > 2);

    return 0;
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}