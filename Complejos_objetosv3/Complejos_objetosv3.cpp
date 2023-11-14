#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// clase numeros complejos
class Numero {
private:
    int Real; // Parte real de un numero complejo
    int Complejo; // Parte compleja o imaginaria de un número complejo

public:
    Numero(int, int); // Constructor de la clase
    void suma(Numero);
    void resta(Numero);
    void multiplicacion(Numero);
    void division(Numero);
};

// del constructor de la clase Numero
Numero::Numero(int real, int complejo) : Real(real), Complejo(complejo) {} // constructor

// Función para simplificar la impresión de números complejos
void simplificarParteCompleja(int resultadoReal, int resultadoComplejo) {
    cout << endl << "El resultado es: " << resultadoReal; // Imprime la parte real
    if (resultadoComplejo < 0) {
        cout << resultadoComplejo << 'i' << endl; // Si la parte compleja es negativa, no imprime el signo de +
    }
    else if (resultadoComplejo == 1) {
        cout << '+' << 'i' << endl; // Si la parte compleja es 1, imprime solo 'i' en lugar de '1i'
    }
    else if (resultadoComplejo != 0) {
        cout << '+' << resultadoComplejo << 'i' << endl; // Imprime el + XNumeroi si la parte compleja no es cero
    }
}

void Numero::suma(Numero numero2) {
    int resultadoReal = Real + numero2.Real;
    int resultadoComplejo = Complejo + numero2.Complejo;
    simplificarParteCompleja(resultadoReal, resultadoComplejo);
}

void Numero::resta(Numero numero2) {
    int resultadoReal = Real - numero2.Real;
    int resultadoComplejo = Complejo - numero2.Complejo;
    simplificarParteCompleja(resultadoReal, resultadoComplejo);
}

void Numero::multiplicacion(Numero numero2) {
    int resultadoReal = Real * numero2.Real - Complejo * numero2.Complejo;
    int resultadoComplejo = Real * numero2.Complejo + Complejo * numero2.Real;
    simplificarParteCompleja(resultadoReal, resultadoComplejo);
}

void Numero::division(Numero numero2) {
    int conjugadoReal = numero2.Real;
    int conjugadoComplejo = -numero2.Complejo;

    int resultadoReal = Real * conjugadoReal - Complejo * conjugadoComplejo;
    int resultadoComplejo = Real * conjugadoComplejo + Complejo * conjugadoReal;
    simplificarParteCompleja(resultadoReal, resultadoComplejo);

    cout << " / ";

    int resultadoReal2 = numero2.Real * conjugadoReal - numero2.Complejo * conjugadoComplejo;
    int resultadoComplejo2 = numero2.Real * conjugadoComplejo + numero2.Complejo * conjugadoReal;
    simplificarParteCompleja(resultadoReal2, resultadoComplejo2);
}

// Función para contar un carácter en una cadena
size_t countOccurrences(char c, string& str) {
    size_t count = 0;

    for (char i : str)
        if (i == c) count++;

    return count;
}

// Función de validación de la entrada (placeholder, reemplazar con validación real según sea necesario)
bool validarInput(string expresion) {
    return true;
}

// Función para decodificar la entrada y obtener los números reales e imaginarios
void Decodificador(string expresion, int numeros[], int realIndex, int complexIndex) {

    char operators[] = { '+', '-', '*', '/' };

    size_t totalOperators = 0;
    for (char c : operators) {
        totalOperators += countOccurrences(c, expresion);
    }

    if (totalOperators == 2) {
        size_t posicionOperador = expresion.find_first_of("+-");
        istringstream streamPrimerNumero(expresion.substr(0, posicionOperador - 1));
        streamPrimerNumero >> numeros[realIndex];

        size_t segundaPosicionOperador = expresion.find_first_of("+-", posicionOperador + 1);

        cout << endl << posicionOperador << endl;
        cout << endl << segundaPosicionOperador << endl;


        if (segundaPosicionOperador != string::npos) {
            istringstream streamSegundoNumero(expresion.substr(segundaPosicionOperador));
            streamSegundoNumero >> numeros[complexIndex];
        }
        else {
            istringstream streamSegundoNumero(expresion.substr(posicionOperador + 1));
            streamSegundoNumero >> numeros[complexIndex];
        }
    }
    else {
        size_t posicionOperador = expresion.find_first_of("+-");
        istringstream streamPrimerNumero(expresion.substr(0, posicionOperador));
        streamPrimerNumero >> numeros[realIndex];

        size_t segundaPosicionOperador = expresion.find_first_of("+-", posicionOperador + 1);

        if (segundaPosicionOperador != string::npos) {
            istringstream streamSegundoNumero(expresion.substr(segundaPosicionOperador));
            streamSegundoNumero >> numeros[complexIndex];
        }
        else {
            istringstream streamSegundoNumero(expresion.substr(posicionOperador + 1));
            streamSegundoNumero >> numeros[complexIndex];
        }

        if (posicionOperador != string::npos && expresion[posicionOperador] == '-') {
            numeros[complexIndex] = -numeros[complexIndex];
        }
    }
}

int main() {
    cout << "NUMEROS COMPLEJOS CON OBJETOS" << endl << endl;
    cout << "Seleccione una operacion" << endl;
    cout << "1. Suma" << endl << "2. Resta" << endl << "3. Multiplicacion" << endl << "4. Division" << endl;

    int tipoOperacion, numeros1[2], numeros2[2];
    string expresion1, expresion2;
    cin >> tipoOperacion;

    switch (tipoOperacion) {
    case 1:
        cout << endl << "Suma" << endl;
        cout << endl << "Ingrese la primera expresion (por ejemplo: 8+2i o 8-2i): ";
        cin >> expresion1;
        if (validarInput(expresion1)) {
            Decodificador(expresion1, numeros1, 0, 1);

            cout << numeros1[0] << numeros1[1];

            cout << endl << "Ingrese la segunda expresion (por ejemplo: 8+2i o 8-2i): ";
            cin >> expresion2;
            if (validarInput(expresion2)) {
                Decodificador(expresion2, numeros2, 0, 1);
                Numero numero1(numeros1[0], numeros1[1]);
                Numero numero2(numeros2[0], numeros2[1]);

                numero1.suma(numero2);
            }
        }
        break;

    case 2:
        cout << endl << "Resta" << endl;
        cout << "Ingrese la primera expresion (por ejemplo: 8+2i o 8-2i): ";
        cin >> expresion1;
        if (validarInput(expresion1)) {
            Decodificador(expresion1, numeros1, 0, 1);

            cout << endl << "Ingrese la segunda expresion (por ejemplo: 8+2i o 8-2i): ";
            cin >> expresion2;
            if (validarInput(expresion2)) {
                Decodificador(expresion2, numeros2, 0, 1);
                Numero numero1(numeros1[0], numeros1[1]);
                Numero numero2(numeros2[0], numeros2[1]);
                numero1.resta(numero2);
            }
        }
        break;

    case 3:
        cout << endl << "Multiplicacion" << endl;
        cout << "Ingrese la primera expresion (por ejemplo: 8+2i o 8-2i): ";
        cin >> expresion1;
        if (validarInput(expresion1)) {
            Decodificador(expresion1, numeros1, 0, 1);

            cout << endl << "Ingrese la segunda expresion (por ejemplo: 8+2i o 8-2i): ";
            cin >> expresion2;
            if (validarInput(expresion2)) {
                Decodificador(expresion2, numeros2, 0, 1);
                Numero numero1(numeros1[0], numeros1[1]);
                Numero numero2(numeros2[0], numeros2[1]);

                numero1.multiplicacion(numero2);
            }
        }
        break;

    case 4:
        cout << endl << "Division" << endl;
        cout << "Ingrese la primera expresion (por ejemplo: 8+2i o 8-2i): ";
        cin >> expresion1;
        if (validarInput(expresion1)) {
            Decodificador(expresion1, numeros1, 0, 1);

            cout << endl << "Ingrese la segunda expresion (por ejemplo: 8+2i o 8-2i): ";
            cin >> expresion2;
            if (validarInput(expresion2)) {
                Decodificador(expresion2, numeros2, 0, 1);
                Numero numero1(numeros1[0], numeros1[1]);
                Numero numero2(numeros2[0], numeros2[1]);

                numero1.division(numero2);
            }
        }
        break;

    default:
        cout << "Seleccione una operacion valida" << endl;
        break;
    }

    return 0;
}