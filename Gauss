#include <stdio.h>

void imprimirMatriz(int ecuaciones, int incognitas, float *);
void pivotearMatriz(int ecuaciones, int incognitas, float *, float *, float *, int j);

int main() {
    int numEcuaciones = 0, numIncognitas = 0;

    printf("Ingresa el número de ecuaciones: ");
    scanf("%i", &numEcuaciones);
    printf("Ingresa el número de incógnitas: ");
    scanf("%i", &numIncognitas);

    if (numEcuaciones != numIncognitas) {
        printf("Advertencia: El sistema de ecuaciones no se puede resolver. El número de incógnitas debe ser igual al número de ecuaciones.");
        return 1; // Salir del programa con código de error 1.
    }

    numIncognitas++; // Ajustar el número de incógnitas para la matriz aumentada.
    float matriz[numEcuaciones][numIncognitas];

    printf("\nIngresa los valores de la matriz A:\n");
    for (int j = 0; j < numIncognitas; j++) {
        for (int i = 0; i < numEcuaciones; i++) {
            if (numIncognitas - 1 == j) {
                printf("Ingresa los datos del vector de resultados\n");
            }
            printf("Ingresa el valor en (%i,%i): ", i + 1, j + 1);
            scanf("%f", &matriz[i][j]);
        }
    }

    printf("\nMatriz Inicial:\n");
    imprimirMatriz(numEcuaciones, numIncognitas, &matriz[0][0]);
    printf("\n");

    float pivoteAux = 0;
    float vectorPivote[numIncognitas];
    float vectorPivoteAux[numIncognitas];
    float n = 0;

    for (int j = 0; j < numIncognitas - 1; j++) {
        pivotearMatriz(numEcuaciones, numIncognitas, &matriz[0][0], &vectorPivote[0], &vectorPivoteAux[0], j);

        for (int i = 0; i < numEcuaciones; i++) {
            printf("\n(%d,%d)\n", i + 1, j + 1);
            if (i != j && j < numIncognitas - 1) {
                n = matriz[i][j];
            }

            for (int k = 0; k < numIncognitas; k++) {
                matriz[i][k] = (-1 * n * vectorPivote[k]) + matriz[i][k];
            }

            if (i == j) {
                for (int l = 0; l < numIncognitas; l++) {
                    matriz[i][l] = vectorPivoteAux[l];
                    if (matriz[i][l] == -0) {
                        matriz[i][l] = 0;
                    }
                }
            }
            imprimirMatriz(numEcuaciones, numIncognitas, &matriz[0][0]);
        }

        n = 0;
        for (int k = 0; k < numIncognitas; k++) {
            vectorPivote[k] = 0;
        }
    }
}

void imprimirMatriz(int ecuaciones, int incognitas, float *matriz) {
    printf("\n\n");
    int contar = 0;

    for (int i = 0; i < ecuaciones * incognitas; i++) {
        if (contar < incognitas) {
            printf(" %.3f ", matriz[i]);
            contar++;
        } else {
            contar = 0;
            printf("\n");
            printf(" %.3f ", matriz[i]);
            contar++;
        }
    }
}

void pivotearMatriz(int ecuaciones, int incognitas, float *matriz, float *vectorPivote, float *vectorPivoteAux, int j) {
    float pivoteAux = 0;
    float matrizTemporal[ecuaciones][incognitas];
    int sumi = 0;

    for (int i = 0; i < ecuaciones; i++) {
        for (int k = 0; k < incognitas; k++) {
            matrizTemporal[i][k] = matriz[sumi];
            sumi++;
        }
    }

    for (int i = 0; i < ecuaciones; i++) {
        if (i == j) {
            pivoteAux = matrizTemporal[i][j];
            printf("Pivote: %.3f\n", pivoteAux);

            for (int l = 0; l < incognitas; l++) {
                matrizTemporal[i][l] = matrizTemporal[i][l] / pivoteAux;
                vectorPivote[l] = matrizTemporal[i][l];
                vectorPivoteAux[l] = matrizTemporal[i][l];
            }
        }
    }

    sumi = 0;
    for (int i = 0; i < ecuaciones; i++) {
        for (int k = 0; k < incognitas; k++) {
            matriz[sumi] = matrizTemporal[i][k];
            sumi++;
        }
    }
}
