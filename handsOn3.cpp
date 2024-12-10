/*
Nombre del programador: Tania Ximena Meza Sanchez
Fecha: 27/10/24
Nombre del programa: Hands-on 3

Descripcion:

A partir del Modelo Matem�tico de An�lisis Predictivo,
Simple Linear Regression (SLR), construido en clase:
 1. Implementar el modelo, orientado a objetos, a trav�s
de los lenguajes Java � C.
 2. Dado el DataSet del Caso Benetton calcular los
valores �ptimos para los par�metros del Modelo
Predictivo (Coeficientes de Regresi�n).
 3. S�lo utilizar�n las columnas Sales y Advertising.

 Caso Benetton:
 https://www.displayr.com/what-is-linear-regression/

Requisitos:
 Entradas de la Aplicaci�n:
 1 Un conjunto de observaciones  o DataSet: (x1, y1), (x2,y2),...,(xn,yn)
 2 El DataSet estar� hardcoded (declarado a trav�s de un constructor).
 3 No se capturan valores por predecir; se inyectan a trav�s de la terminal
(Command Prompt) al ejecutar la clase Main.
 Salidas de la Aplicaci�n:
 1 Imprimir la Ecuaci�n de Regresi�n (como string/no imagen):Y = 0 + 1x1
reemplazando los valores �ptimos, calculados, para los par�metros Beta.
 2 Inyectar valores, por predecir, a trav�s del int�rprete de comandos.

*/

#include <iostream>

using namespace std;

class DataSet{
    private:
        double* x;
        double* y;
        int n;
        double beta0;
        double beta1;
        void calculateEquation();

    public:
        DataSet( double xDat[], double yDat[],  int);
        void printEquation() const;
        double predict(double xValue) const;
};

// Constructor para inicializar atributos
DataSet::DataSet(double xDat[], double yDat[], int size)
    : x(xDat), y(yDat), n(size), beta0(0.0), beta1(0.0) {
    calculateEquation();
}

// Calcula la ecuacion
void DataSet::calculateEquation() {
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    double xMean = sumX / n;
    double yMean = sumY / n;

    beta1 = (sumXY - n * xMean * yMean) / (sumX2 - n * xMean * xMean);
    beta0 = yMean - beta1 * xMean;
}

// Imprime la ecuaci�n de regresi�n como cadena de texto
void DataSet::printEquation() const{
    cout << "Ecuacion de regresion: Y =" << beta0 << " + " << beta1 << " * X" << endl;
}

// Predice un valor de Y dado un valor de X ingresado
double DataSet::predict(double xValue) const {
    return beta0 + beta1 * xValue;
}

int main(){
    double advertising[] = {23, 26, 30, 34, 43, 48, 52, 57, 58};
    double sales[] = {651, 762, 856, 1063, 1190, 1298, 1421, 1440, 1518};
    int size = sizeof(advertising) / sizeof(advertising[0]);
    DataSet predictivo(advertising, sales, size);
    cout << "============ Hands-on 3 ============" << endl;

    predictivo.printEquation();

     // Permitir predicciones basadas en un valor ingresado por el usuario
    double newX;
    cout << "Ingresa un valor de Advertising para predecir Sales: ";
    cin >> newX;
    cout << "Prediccion para Advertising = " << newX << ": Sales = "
         << predictivo.predict(newX) << endl;
    return 0;
}
