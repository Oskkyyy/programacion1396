#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANO_MAX_COLA 10
#define LIMITE_ORO 4
#define CONTRASENA_ORO "gold"

int i=1;

// Estructura del nodo de la cola principal
struct Nodo {
    int turno;
    char categoria;
    struct Nodo* siguiente;
};

// Estructura de la cola principal
struct Cola {
    struct Nodo* frente;
    struct Nodo* final;
    int tamano;
    int contadorOro;
};

// Estructura del nodo de la fila virtual
struct NodoFila {
    int dato;
    int privilegio;
    struct NodoFila* siguiente;
};

// Función para inicializar la cola principal
struct Cola* inicializarCola() {
    struct Cola* cola = (struct Cola*)malloc(sizeof(struct Cola));
    if (cola == NULL) {
        printf("Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }

    cola->frente = NULL;
    cola->final = NULL;
    cola->tamano = 0;
    cola->contadorOro = 0;

    return cola;
}

// Función para mostrar la cola principal
void mostrarCola(struct Cola* cola) {
    printf("\nTurnos en la cola:\n");
    struct Nodo* actual = cola->frente;
    while (actual != NULL) {
        printf("Turno: %d, Categoría: %c\n", actual->turno, actual->categoria);
        actual = actual->siguiente;
    }
}

// Función para asignar un turno en la cola principal
void asignarTurno(struct Cola* cola, char categoria) {
    if (cola->tamano >= TAMANO_MAX_COLA) {
        printf("La cola ha alcanzado su límite. No se pueden asignar más turnos.\n");
        return;
    }

    if (categoria == 'O') {
        char contrasena[20];
        printf("Ingrese la contraseña para la categoría oro: ");
        scanf("%s", contrasena);

        if (strcmp(contrasena, CONTRASENA_ORO) != 0) {
            printf("Contraseña incorrecta. No se puede agregar a la categoría oro.\n");
            return;
        }
    }

    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nuevoNodo == NULL) {
        printf("Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }

    nuevoNodo->turno = cola->tamano + 1;
    nuevoNodo->categoria = categoria;
    nuevoNodo->siguiente = NULL;

    if (categoria == 'O') {
        struct Nodo* anterior = NULL;
        struct Nodo* actual = cola->frente;

        while (actual != NULL && actual->turno < nuevoNodo->turno) {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (anterior == NULL) {
            nuevoNodo->siguiente = cola->frente;
            cola->frente = nuevoNodo;
        } else {
            anterior->siguiente = nuevoNodo;
            nuevoNodo->siguiente = actual;
        }

        cola->contadorOro++;

        if (cola->final == NULL || nuevoNodo->turno > cola->final->turno) {
            cola->final = nuevoNodo;
        }
    } else {
        if (cola->final == NULL) {
            cola->frente = nuevoNodo;
            cola->final = nuevoNodo;
        } else {
            cola->final->siguiente = nuevoNodo;
            cola->final = nuevoNodo;
        }
    }

    printf("Turno asignado: %d, Categoría: %c\n", nuevoNodo->turno, nuevoNodo->categoria);
    cola->tamano++;
}

// Función para buscar un turno en la cola principal
void buscarTurno(struct Cola* cola, int turno) {
    struct Nodo* actual = cola->frente;
    while (actual != NULL) {
        if (actual->turno == turno) {
            printf("Turno %d encontrado en la cola. Categoría: %c\n", turno, actual->categoria);
            return;
        }
        actual = actual->siguiente;
    }

    printf("Turno %d no encontrado en la cola.\n", turno);
}

// Función para eliminar un turno de la cola principal
void eliminarTurno(struct Cola* cola, struct NodoFila** cabezaFila, int turno) {
    struct Nodo* anterior = NULL;
    struct Nodo* actual = cola->frente;

    while (actual != NULL && actual->turno != turno) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        printf("Turno %d no encontrado en la cola. No se puede eliminar.\n", turno);
        return;
    }

    if (anterior == NULL) {
        // El nodo a eliminar es el primero
        cola->frente = actual->siguiente;
        if (cola->frente == NULL) {
            // Si la cola queda vacía después de la eliminación, actualizamos 'final' también
            cola->final = NULL;
        }
    } else {
        anterior->siguiente = actual->siguiente;
        if (anterior->siguiente == NULL) {
            // Si el nodo a eliminar es el último, actualizamos 'final'
            cola->final = anterior;
        }
    }

    // Eliminar el turno correspondiente de la fila virtual
    eliminarEnFila(cabezaFila, turno);

    free(actual);
    cola->tamano--;

    printf("Turno %d eliminado de la cola.\n", turno);
}

// Función para eliminar un elemento de la fila virtual
void eliminarEnFila(struct NodoFila** cabeza, int turno) {
    struct NodoFila* anterior = NULL;
    struct NodoFila* actual = *cabeza;

    while (actual != NULL && actual->dato != turno) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        // El elemento no está en la fila virtual
        return;
    }

    if (anterior == NULL) {
        // El nodo a eliminar es el primero
        *cabeza = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
}


// Función para obtener la cantidad de elementos en la cola principal
void cantidadElementos(struct Cola* cola) {
    printf("Cantidad de elementos en la fila: %d\n", cola->tamano);
}

// Función para insertar un elemento en la fila virtual
void insertarEnFila(struct NodoFila** cabeza, int dato, int privilegio) {
    struct NodoFila* nuevoNodo = (struct NodoFila*)malloc(sizeof(struct NodoFila));
    if (!nuevoNodo) {
        printf("Error al asignar memoria para el nuevo nodo de la fila virtual.\n");
        exit(EXIT_FAILURE);
    }

    nuevoNodo->dato = dato;
    nuevoNodo->privilegio = privilegio;
    nuevoNodo->siguiente = NULL;

    if (*cabeza == NULL || privilegio > (*cabeza)->privilegio) {
        nuevoNodo->siguiente = *cabeza;
        *cabeza = nuevoNodo;
    } else {
        struct NodoFila* actual = *cabeza;
        while (actual->siguiente != NULL && privilegio <= actual->siguiente->privilegio) {
            actual = actual->siguiente;
        }
        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }
}

// Función para imprimir la fila virtual
void imprimirFila(struct NodoFila* cabeza) {
    printf("\nFila Virtual:\n");
    struct NodoFila* actual = cabeza;
    while (actual != NULL) {
        printf("Turno %d, Dato: %d\n",i++ , actual->dato);
        actual = actual->siguiente;
    }
}

// Función para mostrar el menú de bienvenida
void mostrarMenu() {
    printf("\n=== Bienvenido a la Fila Virtual ===\n");
    printf("1. Mostrar personas en la cola\n");
    printf("2. Agregar persona a la cola\n");
    printf("3. Eliminar turno de la cola\n");
    printf("4. Buscar persona en la cola\n");
    printf("5. Mostrar numero de elementos\n");
    printf("6. Salir\n");
    printf("===================================\n");
}

int main() {
    struct Cola* cola = inicializarCola();
    struct NodoFila* cabezaFila = NULL;

    int opcion;
    int turno;
    char categoria;

    do {
        mostrarMenu();
        printf("Seleccione una opcion (1-6): ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrarCola(cola);
                imprimirFila(cabezaFila);
                break;
            case 2:
                printf("Ingrese la categoria de la persona (E: estandar, O: oro): ");
                scanf(" %c", &categoria);
                asignarTurno(cola, categoria);
                insertarEnFila(&cabezaFila, cola->tamano, (categoria == 'O' ? LIMITE_ORO : 0));
                break;
            case 3:
                printf("Ingrese el turno a eliminar de la cola: ");
                scanf("%d", &turno);
                eliminarTurno(cola, &cabezaFila, turno);
                break;

            case 4:
                printf("Ingrese el turno a buscar en la cola: ");
                scanf("%d", &turno);
                buscarTurno(cola, turno);
                break;
            case 5:
                cantidadElementos(cola);
                break;
            case 6:
                printf("Saliendo del programa. Hasta luego!\n");
                break;
            default:
                printf("Opcion no valida. Intentelo de nuevo.\n");
        }

    } while (opcion != 6);

    struct Nodo* actualCola = cola->frente;
    while (actualCola != NULL) {
        struct Nodo* tempCola = actualCola;
        actualCola = actualCola->siguiente;
        free(tempCola);
    }

    struct NodoFila* actualFila = cabezaFila;
    while (actualFila != NULL) {
        struct NodoFila* tempFila = actualFila;
        actualFila = actualFila->siguiente;
        free(tempFila);
    }

    free(cola);

    return 0;
}
