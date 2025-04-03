//server multi-threaded
#include "common.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>	
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#define BUFSZ 1024

//vetor para cada tipo de sensor
int temperature_sensors[12];
int humidity_sensors[12];
int air_quality_sensors[12];

struct client_data{
    int csock;
    struct sockaddr_storage storage;
};


void usage(int argc, char **argv){
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

// ==============================================
// ============= FUNÇÕES AUXILIARES =============
// ==============================================

void show_mensage(struct sensor_message msg){

    printf("log:\n");
    printf("%s sensor in (%d,%d)\n", msg.type, msg.coords[0], msg.coords[1]);
    printf("measurement: %.4f\n", msg.measurement);
    printf("\n");
}

int store_sensor(char *type, int csock){
    int i;
    if (strcmp(type, "temperature") == 0){
        for (i = 0; i < 12; i++){
            if (temperature_sensors[i] == -1){
                temperature_sensors[i] = csock;
                return i;
            }
        }
    } else if (strcmp(type, "humidity") == 0){
        for (i = 0; i < 12; i++){
            if (humidity_sensors[i] == -1){
                humidity_sensors[i] = csock;
                return i;
            }
        }
    } else if (strcmp(type, "air_quality") == 0){
        for (i = 0; i < 12; i++){
            if (air_quality_sensors[i] == -1){
                air_quality_sensors[i] = csock;
                return i;
            }
        }
    }
    return -1;
}

//função que recebe uma mensagem e manda para todas do mesmo tipo
void send_to_all(struct sensor_message msg){
    int i;
    if (strcmp(msg.type, "temperature") == 0){
        for (i = 0; i < 12; i++){
            if (temperature_sensors[i] != -1){
                size_t count = send(temperature_sensors[i], &msg, sizeof(msg), 0);
                if (count != sizeof(msg)){
                    logexit("send");
                }
            }
        }
    } else if (strcmp(msg.type, "humidity") == 0){
        for (i = 0; i < 12; i++){
            if (humidity_sensors[i] != -1){
                size_t count = send(humidity_sensors[i], &msg, sizeof(msg), 0);
                if (count != sizeof(msg)){
                    logexit("send");
                }
            }
        }
    } else if (strcmp(msg.type, "air_quality") == 0){
        for (i = 0; i < 12; i++){
            if (air_quality_sensors[i] != -1){
                size_t count = send(air_quality_sensors[i], &msg, sizeof(msg), 0);
                if (count != sizeof(msg)){
                    logexit("send");
                }
            }
        }
    }
}

//servidor, exibe log padrão com medida negativa (-1.0000) e enviar para os sensores do mesmo tipo
//recebe as coordenadas
void notify_desconexion(char *type, int coords[2]){
    struct sensor_message msg;
    memset(&msg, 0, sizeof(msg));
    strcpy(msg.type, type);
    msg.measurement = -1.0000;
    msg.coords[0] = coords[0];
    msg.coords[1] = coords[1];
    send_to_all(msg);
}

void * client_thread(void *data){

    //parser
    struct client_data *cdata = (struct client_data *)data;
    struct sockaddr *caddr = (struct sockaddr *) (&cdata->storage);

    char caddrstr[BUFSZ];
    addrtostr(caddr, caddrstr, BUFSZ);

    int registered = -1;
    char type[12];
    int coords [2];


    //ler a msg do cliente
    while(1){
        struct sensor_message msg;
        memset(&msg, 0, sizeof(msg));
        size_t recv_count = recv(cdata->csock, &msg, sizeof(msg), 0);
        if (recv_count != sizeof(msg)) {
            notify_desconexion(type, coords);
            //remover sensor do vetor do seu tipo setando como -1
            if (strcmp(type, "temperature") == 0){
                temperature_sensors[registered] = -1;
            } else if (strcmp(type, "humidity") == 0){
                humidity_sensors[registered] = -1;
            } else if (strcmp(type, "air_quality") == 0){
                air_quality_sensors[registered] = -1;
            }
            close(cdata->csock);
            free(cdata);
            pthread_exit(EXIT_SUCCESS);
        }

        //adiciona o sensor no vetor se já não estiver
        if (registered == -1) {
            int idx = store_sensor(msg.type, cdata->csock);
            if (idx == -1) {
                close(cdata->csock);
                free(cdata);
                pthread_exit(EXIT_SUCCESS);
            }
            registered = idx;
            strcpy(type, msg.type);
            coords[0] = msg.coords[0];
            coords[1] = msg.coords[1];
        }

        show_mensage(msg);

        //resposta do cliente
        send_to_all(msg);
    }

    close(cdata->csock);
    free(cdata);

    pthread_exit(EXIT_SUCCESS);
}

// ==============================================
// ==================== MAIN ====================
// ==============================================

int main (int argc, char **argv){
    if (argc < 3){
        usage(argc, argv);
    }
    
    struct sockaddr_storage storage;
    if(0 != server_sockaddr_init(argv[1], argv[2], &storage)){
        usage(argc, argv);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1){
        logexit("socket");	
    }

    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))){
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *) (&storage);

    //bind
    if (0 != bind(s, addr, sizeof(storage))){
        logexit("bind");
    }

    //listen
    if (0 != listen(s, 10)){
        logexit("listen");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);

    //inicia os vetores como -1
    for (int i = 0; i < 12; i++){
        temperature_sensors[i] = -1;
        humidity_sensors[i] = -1;
        air_quality_sensors[i] = -1;
    }

    //accept
    while(1){
        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *) (&cstorage);
        socklen_t caddrlen = sizeof(cstorage);
        
        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1){
            logexit("accept");
        }

        //data
        struct client_data *cdata = malloc(sizeof(*cdata));
        if (!cdata){
            logexit("malloc");
        }
        cdata->csock = csock;
        memcpy(&(cdata->storage), &cstorage, sizeof(cstorage));        

        //criação de thread separado (como se fosse paralelo)
        pthread_t tid;
        pthread_create(&tid, NULL, client_thread, cdata);
            
    }

    exit(EXIT_SUCCESS);
}