//Servidor cliente con libreria nativa independiente de la api de windows "winsock2.h" version mejorada de "winsock.h", esta ultima incluida en el encabezado principal de la api de windows "windows.h". Contiene las funciones principales de la programacion con sockets que se encuentran en gran mayoria de los sistemas operativos, "winsock2.h" es portable a la mayoria de verisones de windows y maneja una gran variedad de protocoloes.
/*
Caracteristicas:
- Usa protocolo "http" para la solicitud de archivos
- Comunicacion estandar TCP/IP
*/

//╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦
//╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩

#include<stdio.h>
#include<stdlib.h>
#include"winsock2.h"

//╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦
//╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩

#define CONNECT_IP      "23.79.196.238"
#define CONNECT_PORT    80
#define FILE_P          "C:\\Users\\FRANCO\\Desktop\\download.html"
#define BUFFSIZE        200000

#define HTML_REQUEST    "GET /index.html HTTP/1.1\n"\
                        "Host: www.mit.edu\n"\
                        "Accept: text/html\n"\
                        "Accept-Language: es\n"\
                        "Connection: close\n\n"

//╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦
//╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩

void clean_buff(char*,int);     //Reestablece el buffer en cada llamada
void fill_buff(char*,char*);    //Rellena el buffer con una cadena como argumento

//╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦
//╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩

int main(){
    WSADATA data;
    SOCKET sock;
    struct sockaddr_in address;
    char buff[BUFFSIZE];
    FILE *f=fopen(FILE_P,"w");
    int i=0;

    if(WSAStartup(WINSOCK_VERSION,&data)){
        printf("\nWINSOCK no se inicializo correctamente\n");
        goto exit;
    }else{
        if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET){
            printf("\nNo se pudo crear el socket\n");
            goto exit;
        }else{
            address.sin_family=AF_INET;
            address.sin_port=htons(CONNECT_PORT);
            address.sin_addr.S_un.S_addr=inet_addr(CONNECT_IP);

            if(connect(sock,(struct sockaddr*)(&address),sizeof(address))){
                printf("\nFallo en la conexion a: %s en el puerto: %d\n",CONNECT_IP,(int)CONNECT_PORT);
                goto exit;
            }else{
                clean_buff(buff,sizeof(buff));
                fill_buff(buff,HTML_REQUEST);

                if(send(sock,buff,sizeof(HTML_REQUEST),0)==SOCKET_ERROR){
                    printf("\nError al enviar la solicitud\n");
                    goto exit;
                }else{
                    clean_buff(buff,sizeof(buff));

                    if(shutdown(sock,SD_SEND)==SOCKET_ERROR){                       //Apaga el enviado de datos al socket
                        printf("\nError al finalizar la solicitud\n");
                        goto exit;
                    }else{
                        do{
                            if((i=recv(sock,buff,sizeof(buff),0))==SOCKET_ERROR){   //Recibe y controla la cantidad de datos por el servidor
                                printf("\nError al recibir la respuesta\n");
                                goto exit;
                            }
                            printf("\nBytes recibidos: %d\n",i);
                        }while(i>0);

                        printf("\n%s\n",buff);                                      //Imprime la respuesta del servidor para manejar errorres

                        for(i=0;buff[i]!='\n'||buff[i+1]!='\n';i++);                //Avanza en el buffer hasta encontrar dos saltos de linea(cuerpo de splicitud)
                        i+=2;                                                       //Avanza al cuerpo de la solicitud

                        while(buff[i]){
                            fputc(buff[i],f);                                       //Guarda caracter a caracter los datos del buffer en el archivo
                            i++;
                        }

                        fclose(f);
                        closesocket(sock);
                        WSACleanup();
                    }
                }
            }
        }
    }



    exit:
    system("pause");
    return 0;
}

//╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦╦
//╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩╩

void clean_buff(char *buff_ptr, int buff_size){
    while(buff_size%10){                                        //Inicializa uno a uno el buffer desde el final y lo hace multiplo de 10 si es mayor a 10
        *(buff_ptr+(buff_size-1))=0;
        buff_size--;
    }

    for(buff_size;buff_size>0;buff_ptr+=10,buff_size-=10){      //Inicializa de 10 en 10 el buffer desde el principio
        *buff_ptr=0;
        *(buff_ptr+1)=0;
        *(buff_ptr+2)=0;
        *(buff_ptr+3)=0;
        *(buff_ptr+4)=0;
        *(buff_ptr+5)=0;
        *(buff_ptr+6)=0;
        *(buff_ptr+7)=0;
        *(buff_ptr+8)=0;
        *(buff_ptr+9)=0;
    }

    return;
}

void fill_buff(char *buff, char *fill){
    while(*fill){                                               //Mientras la cadena sea un caracter diferente de '\0'
        *buff=*fill;
        buff++;
        fill++;
    }

    return;
}
