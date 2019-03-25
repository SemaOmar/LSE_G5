#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#include "piTankGoLib.h"
#include "piTankGo_1.h"

#define host "localHost"
#define puerto	5555


int cliente(){
 //int result = 0;
  struct sockaddr_in cliente; //Declaración de la estructura con información para la conexión
  struct hostent *servidor; //Declaración de la estructura con información del host
  servidor = gethostbyname(host); //Asignacion
  if(servidor == NULL)
  { //Comprobación
    printf("Host erróneo\n");
    return 1;
  }
  int conexion;
  char buffer[100];
  conexion = socket(AF_INET, SOCK_STREAM, 0); //Asignación del socket
 
  bzero((char *)&cliente, sizeof((char *)&cliente)); //Rellena toda la estructura de 0's
        //La función bzero() es como memset() pero inicializando a 0 todas la variables
  cliente.sin_family = AF_INET; //asignacion del protocolo
  cliente.sin_port = htons(puerto); //asignacion del puerto
  bcopy((char *)servidor->h_addr, (char *)&cliente.sin_addr.s_addr, sizeof(servidor->h_length));
  //bcopy(); copia los datos del primer elemendo en el segundo con el tamaño máximo 
  //del tercer argumento.


  //cliente.sin_addr = *((struct in_addr *)servidor->h_addr); //<--para empezar prefiero que se usen
  //inet_aton(argv[1],&cliente.sin_addr); //<--alguna de estas dos funciones
  if(connect(conexion,(struct sockaddr *)&cliente, sizeof(cliente)) < 0)
  { //conectando con el host
    printf("Error conectando con el host\n");
    close(conexion);
    return 1;
  }
  printf("Conectado con %s:%d\n",inet_ntoa(cliente.sin_addr),htons(cliente.sin_port));
  //inet_ntoa(); está definida en <arpa/inet.h>


//*******************************************

  send(conexion, '1', 100, 0); //envio

  bzero(buffer, 100);

  recv(conexion, buffer, 100, 0); //recepción
	if strcmp(buffer, "1")
	{
		flags_juego |= FLAG_TARGET_DONE;
		flags_player |= FLAG_START_IMPACTO;
	}

  printf("%s", buffer);

return 0;
}
