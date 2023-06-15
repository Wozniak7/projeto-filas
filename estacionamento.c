#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

#define CAPACIDADE 12

typedef struct {
    char placa_carro[20];
    int mover;
} Carro;

typedef struct {
    Carro carros[CAPACIDADE];
    fila esperando_partida;
    int contador;
} Estacionamento;

void initEstacionamento(Estacionamento *Estacionamento) {
    Estacionamento->contador = 0;
    inicia_fila(&(Estacionamento->esperando_partida));
}

void CarroEstacionado(Estacionamento *Estacionamento, const char *PlacaCarro) {
    if (Estacionamento->contador < CAPACIDADE) {
        Carro carro;
        strcpy(carro.placa_carro, PlacaCarro);
        carro.mover = 1;
        Estacionamento->carros[Estacionamento->contador] = carro;
        Estacionamento->contador++;
        printf("Carro %s estacionado.\n", PlacaCarro);
    } else {
        enfileira(verifica_tamanho(&(Estacionamento->esperando_partida)), &(Estacionamento->esperando_partida));
        printf("Nao ha vagas disponiveis para o Carro %s. Aguardando vaga.\n", PlacaCarro);
    }
}

int acharCarro(Estacionamento *Estacionamento, const char *PlacaCarro) {
    for (int i = 0; i < Estacionamento->contador; i++) {
        if (strcmp(Estacionamento->carros[i].placa_carro, PlacaCarro) == 0) {
            return i;
        }
    }
    return -1;
}

void removeCarro(Estacionamento *Estacionamento, const char *PlacaCarro) {
    int CarroIndex = acharCarro(Estacionamento, PlacaCarro);

    if (CarroIndex != -1) {
        for (int i = CarroIndex + 1; i < Estacionamento->contador; i++) {
            Estacionamento->carros[i - 1] = Estacionamento->carros[i];
            Estacionamento->carros[i - 1].mover++;
        }

        Carro carro = Estacionamento->carros[CarroIndex];
        printf("Carro %s saiu apos %d deslocamentos.\n", carro.placa_carro, carro.mover);

        Estacionamento->contador--;

        if (!esta_vazia(&(Estacionamento->esperando_partida))) {
            int esperandoMover = desenfileira(&(Estacionamento->esperando_partida));
            Carro carroEsperando;
            strcpy(carroEsperando.placa_carro, "");
            carroEsperando.mover = esperandoMover;
            CarroEstacionado(Estacionamento, carroEsperando.placa_carro);
        }
    } else {
        printf("Carro %s nao encontrado no estacionamento.\n", PlacaCarro);
    }
}

int main() {
    Estacionamento Estacionamento;
    initEstacionamento(&Estacionamento);

    char entrada[2];
    char PlacaCarro[20];

    while (1) {
        printf("Informe a entrada (C - Chegada, P - Partida, F - Finalizar): ");
        scanf("%s", entrada);

        if (entrada[0] == 'F') {
            break;
        }

        printf("Informe a placa do Carro: ");
        scanf("%s", PlacaCarro);

        if (entrada[0] == 'C') {
            CarroEstacionado(&Estacionamento, PlacaCarro);
        } else if (entrada[0] == 'P') {
            removeCarro(&Estacionamento, PlacaCarro);
        }
    }

    return 0;
}
