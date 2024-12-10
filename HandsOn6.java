
public class HandsOn6 {

    public static void ordenarBurbuja(int[] datos) {
        int n = datos.length;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (datos[j] > datos[j + 1]) {
                    int temp = datos[j];
                    datos[j] = datos[j + 1];
                    datos[j + 1] = temp;
                }
            }
        }
    }

    public static void imprimir(int[] datos, int rango, int numClases) {
        int n = datos.length;
        int amplitud = (int) Math.ceil((double) rango / numClases);

        System.out.println("Clase\tLimite de Clase\tf\tXc\tFa\tfr\tfra\tPorcentaje");

        int inicio = datos[0];
        int frecuenciaAcumulada = 0;
        double frecuenciaRelativaAcumulada = 0.0;

        for (int i = 0; i < numClases; i++) {
            int limiteInferior = inicio + i * amplitud;
            int limiteSuperior = limiteInferior + amplitud - 1;

            int frecuencia = 0;
            for (int dato : datos) {
                if (dato >= limiteInferior && dato <= limiteSuperior) {
                    frecuencia++;
                }
            }


            double puntoMedio = (limiteInferior + limiteSuperior) / 2.0;


            frecuenciaAcumulada += frecuencia;


            double frecuenciaRelativa = (double) frecuencia / n;
            frecuenciaRelativaAcumulada += frecuenciaRelativa;

            System.out.printf("  %d\t\t%d - %d\t\t\t%d\t%.2f\t%d\t%.2f\t%.2f\t%.2f%%%n",
                    i + 1, limiteInferior, limiteSuperior, frecuencia, puntoMedio,
                    frecuenciaAcumulada, frecuenciaRelativa, frecuenciaRelativaAcumulada, frecuenciaRelativa * 100);
        }

        System.out.printf("TOTAL\tn = %d\t\t\t\t\t\t1.00\t100%%%n", n);
    }

    public static void main(String[] args) {
        // DataSet
        int[] datos = {105, 106, 105, 107, 109, 111, 110, 110, 107, 107, 104, 99, 103, 99, 103, 101, 100,
                101, 100, 103, 98, 92, 97, 94, 95, 95, 93, 95, 95, 95, 91, 82, 91, 85, 90, 86, 87,
                89, 87, 89};
        int n = datos.length;

        ordenarBurbuja(datos);

        int rango = datos[n - 1] - datos[0];
        System.out.println("Rango: " + rango);
        
        int numClases = (int) ((1 + 3.322) * Math.log10(n));
        System.out.println("Número de clases: " + numClases);
        
        imprimir(datos, rango, numClases);
    }
}
