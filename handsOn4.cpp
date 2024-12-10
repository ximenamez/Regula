/*
Nombre del programador: Tania Ximena Meza Sanchez
Fecha: 27/10/24
Nombre del programa: Hands-on 4

Descripcion:

 A partir del Modelo Matem�tico de An�lisis Predictivo,
Quadratic  Regression (QR), planteado en clase:
 1. Implementar la t�cnica a trav�s de Java/C.
 2. Dado -por ejemplo-  el DataSet en
https://www.six-sigma-material.com/Regression.html
calcular los valores �ptimos para los Par�metros del
Modelo Cuadr�tico.


Requisitos:
  Inputs:
 1 Un conjunto de observaciones o DataSet:(x1, y1), (x2,y2),...,(xn,yn)
 2 El DataSet estar� predefinido a trav�s de un constructor de clase.
 3 No se captura el Data Set.
  Outputs:
Imprimir
a La Curva de Regresi�n (como string/no imagen), sustituyendo los valores de los
par�metros del modelo  y los nombres las variables.
 b Al menos cinco predicciones (hardcoded) en funci�n a valores conocidos y
desconocidos de la variable Batch Size.
1 Calcular e imprimir los valores de:
2 Correlaci�n
3 Coeficiente de Determinaci�n.

*/

#include <iostream>
#include <cmath>

using namespace std;

const int MAX_DATA_POINTS = 8;

class QuadraticRegression {
private:
    double x[MAX_DATA_POINTS];
    double y[MAX_DATA_POINTS];
    double a, b, c; // Coeficientes de la ecuaci�n cuadr�tica
    int n;

    void calculateCoefficients();

public:
    QuadraticRegression(double xData[], double yData[], int size);
    void printEquation() const;
    double predict(double xValue) const;
    double calculateCorrelation() const;
    double calculateR2() const;
};

// Constructor
QuadraticRegression::QuadraticRegression(double xData[], double yData[], int size)
    : a(0.0), b(0.0), c(0.0), n(size) {
    for (int i = 0; i < n; i++) {
        x[i] = xData[i];
        y[i] = yData[i];
    }
    calculateCoefficients();
}

// C�lculo de los coeficientes de regresi�n cuadr�tica
void QuadraticRegression::calculateCoefficients() {
    double sumX = 0, sumY = 0, sumX2 = 0, sumX3 = 0, sumX4 = 0, sumXY = 0, sumX2Y = 0;

    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumX2 += x[i] * x[i];
        sumX3 += x[i] * x[i] * x[i];
        sumX4 += x[i] * x[i] * x[i] * x[i];
        sumXY += x[i] * y[i];
        sumX2Y += x[i] * x[i] * y[i];
    }

    // Resolviendo el sistema de ecuaciones para a, b, c
    double denom = n * sumX2 * sumX4 + 2 * sumX * sumX3 * sumX2 - sumX2 * sumX2 * sumX2 - n * sumX3 * sumX3 - sumX * sumX * sumX4;

    a = (n * sumX2Y * sumX4 + sumY * sumX3 * sumX2 + sumX * sumXY * sumX3 - sumY * sumX2 * sumX2 - n * sumXY * sumX4 - sumX * sumX * sumX2Y) / denom;
    b = (n * sumXY * sumX4 + sumY * sumX * sumX3 + sumX2 * sumX2Y - sumY * sumX2 * sumX - n * sumX2Y * sumX4 - sumX * sumX * sumXY) / denom;
    c = (sumX2 * sumX2Y * n + sumY * sumX * sumX3 + sumX2 * sumXY * sumX - sumY * sumX2 * sumX2 - sumX2Y * sumX2 * n - sumX * sumX * sumX4) / denom;
}

// Imprime la ecuaci�n de regresi�n cuadr�tica
void QuadraticRegression::printEquation() const {
    cout << "Ecuacion de regresion: Y = " << a << " * X^2 + " << b << " * X + " << c << endl;
}

// Predice un valor de Y dado un valor de X
double QuadraticRegression::predict(double xValue) const {
    return a * xValue * xValue + b * xValue + c;
}

// Calcula la correlaci�n
double QuadraticRegression::calculateCorrelation() const {
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0, sumY2 = 0;

    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
        sumY2 += y[i] * y[i];
    }

    double correlation = (n * sumXY - sumX * sumY) / sqrt((n * sumX2 - sumX * sumX) * (n * sumY2 - sumY * sumY));
    return correlation;
}

// Calcula el coeficiente de determinaci�n R�
double QuadraticRegression::calculateR2() const {
    double sumY = 0, sumY2 = 0, meanY = 0;

    for (int i = 0; i < n; i++) {
        sumY += y[i];
        sumY2 += y[i] * y[i];
    }

    meanY = sumY / n;
    double totalVariance = sumY2 - (sumY * sumY) / n;
    double explainedVariance = 0;

    for (int i = 0; i < n; i++) {
        double predictedY = predict(x[i]);
        explainedVariance += (predictedY - meanY) * (predictedY - meanY);
    }

    return explainedVariance / totalVariance;
}

int main() {
    // DataSet
    double batchSize[MAX_DATA_POINTS] = {108, 115, 106, 97, 95, 91, 97, 83};
    double output[MAX_DATA_POINTS] = {95, 96, 95, 97, 93, 94, 95, 93};

    QuadraticRegression qr(batchSize, output, MAX_DATA_POINTS);
    cout << "============ Hands-on 4 ============" << endl;

    qr.printEquation();

    // Realizar predicciones
    cout << "Predicciones:" << endl;
    double predictionValues[] = {1.5, 2.5, 3.5, 4.5, 5}; // Valores para predicci�n
    for (double x : predictionValues) {
        cout << "Para Batch Size = " << x << ", Predicci�n = " << qr.predict(x) << endl;
    }

    // Calcular e imprimir correlaci�n y coeficiente de determinaci�n
    cout << "Correlacion: " << qr.calculateCorrelation() << endl;
    cout << "Coeficiente de Determinacion R�: " << qr.calculateR2() << endl;

    return 0;
}

