#include "common.h"
#include <pthread.h>
#include <math.h>
#include <time.h>

#define BUFSZ 1024
#define MAX_SENSORS 12

int SOCKET = -1;
struct sensor_message* SENSOR = NULL;
struct sensor_message NEIGHBORS[MAX_SENSORS];
struct sensor_message* NEAR[3];
int SLEEP_TIME;

void usage (int argc, char **argv){
    printf("usage: %s <server IP> <server port>", argv[0]);
    printf("example: %s 127.0.0.1 51511", argv[0]);
}

// ==============================================
// ============= TRATAMENTO DE ERRO =============
// ==============================================

void show_mensage(struct sensor_message msg, char *status){
    printf("log:\n");
    printf("%s sensor in (%d,%d)\n", msg.type, msg.coords[0], msg.coords[1]);
    printf("measurement: %.4f\n", msg.measurement);
    printf("action: %s", status);
    //se status for diferente de correction  of
    if (strcmp(status, "correction  of") != 0){
        printf("\n\n");
    }
}

void error_message (char *error){
    printf("%s", error);
    printf("Usage: ./client <server_ip> <port> -type <temperature|humidity|air_quality> -coords <x> <y>\n");
    exit(EXIT_FAILURE);
}

void tratamento_erro(int argc, char **argv){

    char *error = NULL;
    if (argc < 8){
        error = "Error: Invalid number of arguments\n";
    }
    else if (strcmp(argv[3], "-type") != 0) {
        error = "Error: Expected '-type' argument\n";
    }
    else if (strcmp(argv[4], "temperature") != 0 && strcmp(argv[4], "humidity") != 0 && strcmp(argv[4], "air_quality") != 0) {
        error = "Error: Invalid sensor type\n";
    }
    else if (strcmp(argv[5], "-coords") != 0) {
        error = "Error: Expected '-coords' argument\n";
    }
    else{
        int x = atoi(argv[6]);
        int y = atoi(argv[7]);
        if (x < 0 || x > 9 || y < 0 || y > 9) {
            error ="Error: Coordinates must be in the range 0-9\n";
        }
    }
    if (error != NULL){
        error_message(error);
    }
}

// ==============================================
// ============= FUNÇÕES AUXILIARES =============
// ==============================================

int get_sleep_time() {
    if (strcmp(SENSOR->type, "temperature") == 0) {
        return 5;
    } else if (strcmp(SENSOR->type, "humidity") == 0) {
        return 7;
    } else if (strcmp(SENSOR->type, "air_quality") == 0) {
        return 10;
    }
    return 0;
}

float gera_medicao_inicial() {
    if (strcmp(SENSOR->type, "temperature") == 0) {
        return 20.0 + (rand() % 2000) / 100.0; // 20.0 - 40.0
    } else if (strcmp(SENSOR->type, "humidity") == 0) {
        return 10.0 + (rand() % 8000) / 100.0; // 10.0 - 90.0
    } else if (strcmp(SENSOR->type, "air_quality") == 0) {
        return 15.0 + (rand() % 1500) / 100.0; // 15.0 - 30.0
    }
    return 0.0;
}

float euclidean_distance(int coords1[2], int coords2[2]) {
    return sqrt(pow(coords1[0] - coords2[0], 2) + pow(coords1[1] - coords2[1], 2));
}

float update_measurement(struct sensor_message external_sensor) {
    float d = euclidean_distance(SENSOR->coords, external_sensor.coords);
    float old_measurement = SENSOR->measurement;
    float new_measurement = SENSOR->measurement +  0.1 * (1 / (d + 1)) * (external_sensor.measurement - SENSOR->measurement);

    if (new_measurement < 0) { new_measurement = 0;} 
    else if (new_measurement > 100) {new_measurement = 100;}

    SENSOR->measurement = new_measurement;

    return new_measurement - old_measurement;
}

struct sensor_message *find_nearest_neighbor() {
    float menor = 1000.0;
    struct sensor_message *menor_vizinho = NULL;
    for (int i = 0; i < MAX_SENSORS; i++) {
        if (NEIGHBORS[i].coords[0] != -1 && NEAR[0] != &NEIGHBORS[i] && NEAR[1] != &NEIGHBORS[i] && NEAR[2] != &NEIGHBORS[i]) {
            float d = euclidean_distance(SENSOR->coords, NEIGHBORS[i].coords);
            if (d < menor) {
                menor = d;
                menor_vizinho = &NEIGHBORS[i];
            }
        }
    }
    return menor_vizinho;
}

int add_sensor(struct sensor_message *external_sensor){
    if (external_sensor == NULL) {
        return 0;
    }

    float d = euclidean_distance(SENSOR->coords, external_sensor->coords);
    float greater = -1000.0;
    int index = -1;
    
    //encontra a maior distancia de near
    for (int i = 0; i < 3; i++) {
        if (NEAR[i] != NULL) {
            float d2 = euclidean_distance(SENSOR->coords, NEAR[i]->coords);
            if (d2 > greater) {
                greater = d2;
                index = i;
            }
        }
        else {
            NEAR[i] = external_sensor;
            return 1;
        }
    }

    if (d < greater) {
        NEAR[index] = external_sensor;
        return 1;
    }

    return 0;

}

void remove_sensor(struct sensor_message external_sensor){
    for (int i = 0; i < MAX_SENSORS; i++) {
        if (NEIGHBORS[i].coords[0] == external_sensor.coords[0] && NEIGHBORS[i].coords[1] == external_sensor.coords[1]) {
            for (int j = 0; j < 3; j++) {
                if (NEAR[j] != NULL && NEAR[j]->coords[0] == external_sensor.coords[0] && NEAR[j]->coords[1] == external_sensor.coords[1]) {
                    NEAR[j] = NULL;
                }
            }
            NEIGHBORS[i].coords[0] = -1;
            NEIGHBORS[i].coords[1] = -1;
        }
    }
    add_sensor(find_nearest_neighbor());
}

int save_sensor(struct sensor_message external_sensor) {
    int index = -1;
    for (int i = 0; i < MAX_SENSORS; i++) {
        if (index == -1 && NEIGHBORS[i].coords[0] == -1) {
            index = i;
        }
        if (NEIGHBORS[i].coords[0] == external_sensor.coords[0] && NEIGHBORS[i].coords[1] == external_sensor.coords[1]) {
            return 0;
        }
    }

    if (index != -1) {
        NEIGHBORS[index] = external_sensor;
        return add_sensor(&NEIGHBORS[index]);
    } else {
        printf("Error: neighbors list is full\n");
        return 0;
    }

}

int is_neighbor(struct sensor_message external_sensor) {
    for (int i = 0; i < 3; i++) {
        if (NEAR[i] != NULL && NEAR[i]->coords[0] == external_sensor.coords[0] && NEAR[i]->coords[1] == external_sensor.coords[1]) {
            return 1;
        }
    }
    return 0;
}

int is_me(struct sensor_message external_sensor){
    return (SENSOR->coords[0] == external_sensor.coords[0] && SENSOR->coords[1] == external_sensor.coords[1]);
}

void *sensor_thread (){

    while(1){
        sleep(SLEEP_TIME);
        size_t count = send(SOCKET, SENSOR, sizeof(struct sensor_message), 0);
        if (count != sizeof(struct sensor_message)){
            printf("Error: send\n");
            logexit("send");
        }
    }
    pthread_exit(NULL);
}

void *process_server_message(void *arg) {
    struct sensor_message *server_msg = (struct sensor_message *)arg;
    float value;

    if (*server_msg->type != *SENSOR->type) {
        free(server_msg);
        pthread_exit(NULL);
    }

    if (is_me(*server_msg)) {
        show_mensage(*server_msg, "same location");
    } else if (server_msg->measurement == -1.0000) {
        remove_sensor(*server_msg);
        show_mensage(*server_msg, "removed");
    } else if (is_neighbor(*server_msg)) {
        value = update_measurement(*server_msg);
        show_mensage(*server_msg, "correction  of");
        printf(" %.4f\n\n", value);
    } else {
        int saved = save_sensor(*server_msg);
        if (saved != 0) {
            value = update_measurement(*server_msg);
            show_mensage(*server_msg, "correction  of");
            printf(" %.4f\n\n", value);
        } else {
            show_mensage(*server_msg, "not  neighbor");
        }
    }

    free(server_msg);
    pthread_exit(NULL);
}


// ==============================================
// ==================== MAIN ====================
// ==============================================


int main(int argc, char **argv){
    
    tratamento_erro(argc, argv);

    //inicializa SENSOR
    SENSOR = (struct sensor_message *)malloc(sizeof(struct sensor_message));
    if (SENSOR == NULL){
        logexit("malloc");
    }
    memset(SENSOR, 0, sizeof(struct sensor_message));

    //inicialização do sensor
    srand(time(NULL));

    strncpy(SENSOR->type, argv[4], sizeof(SENSOR->type) - 1);
    SENSOR->coords[0] = atoi(argv[6]);
    SENSOR->coords[1] = atoi(argv[7]);
    SENSOR->measurement = gera_medicao_inicial(SENSOR->type);

    SLEEP_TIME = get_sleep_time();

    //inicialização dos sensores vizinhos
    for (int i = 0; i < MAX_SENSORS; i++){
        NEIGHBORS[i].coords[0] = -1;
        NEIGHBORS[i].coords[1] = -1;
    }

    for (int i = 0; i < 3; i++){
        NEAR[i] = NULL;
    }

    //conexão com o servidor
    struct sockaddr_storage storage;
    if(0 != addrparse(argv[1], argv[2], &storage)){
        usage(argc, argv);
    }

    SOCKET = socket(storage.ss_family, SOCK_STREAM, 0);
    if (SOCKET == -1){
        logexit("socket");
    }

    struct sockaddr *addr = (struct sockaddr *) (&storage);
    if (0 != connect(SOCKET, addr, sizeof(storage))){
        logexit("connect");
    }

    // Criação da thread para enviar medições
    pthread_t tid;
    if (pthread_create(&tid, NULL, sensor_thread, NULL) != 0) {
        close(SOCKET);
        return EXIT_FAILURE;
    }

    // Loop principal para receber dados do servidor
    while (1) {
        struct sensor_message *server_msg = malloc(sizeof(struct sensor_message));
        if (server_msg == NULL) {
            break;
        }
        memset(server_msg, 0, sizeof(struct sensor_message));

        // Recebe a resposta do servidor
        size_t recv_count = recv(SOCKET, server_msg, sizeof(struct sensor_message), 0);
        if (recv_count <= 0) {
            free(server_msg);
            break;
        }

        // Criação da thread para processar a mensagem
        pthread_t tid;
        if (pthread_create(&tid, NULL, process_server_message, server_msg) != 0) {
            free(server_msg);
        }

        pthread_detach(tid);
    }

//  Finaliza a thread e o socket
    pthread_cancel(tid);
    pthread_join(tid, NULL);
    close(SOCKET);

    return EXIT_SUCCESS;
}