#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

#define CAPACITY 12

typedef struct {
    char license_plate[20];
    int moves;
} Car;

typedef struct {
    Car cars[CAPACITY];
    fila waiting_queue;
    int count;
} ParkingLot;

void initParkingLot(ParkingLot *parkingLot) {
    parkingLot->count = 0;
    inicia_fila(&(parkingLot->waiting_queue));
}

void parkCar(ParkingLot *parkingLot, const char *licensePlate) {
    if (parkingLot->count < CAPACITY) {
        Car car;
        strcpy(car.license_plate, licensePlate);
        car.moves = 0;
        parkingLot->cars[parkingLot->count] = car;
        parkingLot->count++;
        printf("Carro %s estacionado.\n", licensePlate);
    } else {
        enfileira(verifica_tamanho(&(parkingLot->waiting_queue)), &(parkingLot->waiting_queue));
        printf("Não há vagas disponíveis para o carro %s. Aguardando vaga.\n", licensePlate);
    }
}

int findCarIndex(ParkingLot *parkingLot, const char *licensePlate) {
    for (int i = 0; i < parkingLot->count; i++) {
        if (strcmp(parkingLot->cars[i].license_plate, licensePlate) == 0) {
            return i;
        }
    }
    return -1;
}

void removeCar(ParkingLot *parkingLot, const char *licensePlate) {
    int carIndex = findCarIndex(parkingLot, licensePlate);

    if (carIndex != -1) {
        Car car = parkingLot->cars[carIndex];
        printf("Carro %s saiu após %d deslocamentos.\n", car.license_plate, car.moves);

        for (int i = carIndex + 1; i < parkingLot->count; i++) {
            parkingLot->cars[i - 1] = parkingLot->cars[i];
            parkingLot->cars[i - 1].moves++;
        }

        parkingLot->count--;

        if (!esta_vazia(&(parkingLot->waiting_queue))) {
            int waitingMoves = desenfileira(&(parkingLot->waiting_queue));
            Car waitingCar;
            strcpy(waitingCar.license_plate, "");
            waitingCar.moves = waitingMoves;
            parkCar(parkingLot, waitingCar.license_plate);
        }
    } else {
        printf("Carro %s não encontrado no estacionamento.\n", licensePlate);
    }
}

int main() {
    ParkingLot parkingLot;
    initParkingLot(&parkingLot);

    char entry[2];
    char licensePlate[20];

    while (1) {
        printf("Informe a entrada (C - Chegada, P - Partida, F - Finalizar): ");
        scanf("%s", entry);

        if (entry[0] == 'F') {
            break;
        }

        printf("Informe a placa do carro: ");
        scanf("%s", licensePlate);

        if (entry[0] == 'C') {
            parkCar(&parkingLot, licensePlate);
        } else if (entry[0] == 'P') {
            removeCar(&parkingLot, licensePlate);
        }
    }

    return 0;
}
