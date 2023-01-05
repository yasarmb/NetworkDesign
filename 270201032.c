/* Yaşar Mehmet Bağdatlı
 * 270201032
 *
 *
*/



#include <stdio.h>      
#include <sys/types.h>
#include <sys/socket.h>   
#include <netdb.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<time.h>

int printRandoms(int lower, int upper,int count){
    int i;
    for ( i = 0; i < count; i++)
    {
        int num = (rand() % (upper - lower  +1 )) + lower;
        return num;
    }
    
}

//const char APRESSMESSAGE[] = "APRESS - For Professionals, By Professionals!\n";



int main(int argc, char *argv[]) {

	int lower = 0; //for random number lower range
	int upper = 9; // for random number upper range
	int count = 1; // count
	

	char  APRESSMESSAGE[10][100] = {
    	"Aç bırakma hırsız edersin, çok söyleme arsız edersin.\n",
    	"Bak bana bir gözle, bakayım sana iki gözle.\n",
    	"Cami ne kadar büyük olsa imam gene bildiğini okur.\n",
    	"Çobanın gönlü olursa tekeden yağ çıkarır.\n",
    	"Dağ başına harman yapma, savurursun yel için, sel önüne değirmen yapma, öğütürsün.\n",
    	"El yumruğu yemeyen kendi yumruğunu değirmen taşı sanır.\n",
    	"Fala inanma, falsız kalma.\n",
    	"Gönül bir sırça saraydır, kırılırsa yapılmaz.\n",
    	"Harmanda dirgen yiyen sıpa, yılına kadar acısını unutmaz.\n",
    	"Işığını akşamdan önce yakan,sabah çırasına yağ bulamaz.\n"
	};

	srand(time(0));	
	int randomnumber = printRandoms(lower,upper,count);
	
    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    struct sockaddr_in simpleServer;

    if (2 != argc) {

        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);

    }

    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) {

        fprintf(stderr, "Could not create a socket!\n");
        exit(1);

    }
    else {
	    fprintf(stderr, "Socket created!\n");
    }

    /* retrieve the port number for listening */
    simplePort = atoi(argv[1]);

    /* setup the address structure */
    /* use INADDR_ANY to bind to all local addresses  */
    bzero(&simpleServer, sizeof(simpleServer)); 
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
    simpleServer.sin_port = htons(simplePort);

    /*  bind to the address and port with our socket  */
    returnStatus = bind(simpleSocket,(struct sockaddr *)&simpleServer,sizeof(simpleServer));

    if (returnStatus == 0) {
	    fprintf(stderr, "Bind completed!\n");
    }
    else {
        fprintf(stderr, "Could not bind to address!\n");
	close(simpleSocket);
	exit(1);
    }

    /* lets listen on the socket for connections      */
    returnStatus = listen(simpleSocket, 5);

    if (returnStatus == -1) {
        fprintf(stderr, "Cannot listen on socket!\n");
	close(simpleSocket);
        exit(1);
    }

    while (1)

    {

        struct sockaddr_in clientName = { 0 };
	int simpleChildSocket = 0;
	int clientNameLength = sizeof(clientName);

	/* wait here */

        simpleChildSocket = accept(simpleSocket,(struct sockaddr *)&clientName, &clientNameLength);

	if (simpleChildSocket == -1) {

            fprintf(stderr, "Cannot accept connections!\n");
	    close(simpleSocket);
	    exit(1);

	}

        /* handle the new connection request  */
	/* write out our message to the client */
	write(simpleChildSocket, APRESSMESSAGE[randomnumber], strlen(APRESSMESSAGE[randomnumber]));
        close(simpleChildSocket);

    }

    close(simpleSocket);
    return 0;

}
