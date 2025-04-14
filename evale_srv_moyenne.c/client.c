//Axel
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVEUR_IP "127.0.0.1"
#define PORT 1618
#define BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE] = "Bonjour Serveur !";

    // Création du socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Configuration du serveur cible
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVEUR_IP);
    serverAddr.sin_port = htons(PORT);

    // Connexion au serveur
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Erreur lors de la connexion");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }
    
    // Envoi et réception des données
    send(clientSocket, buffer, strlen(buffer), 0);
    recv(clientSocket, buffer, BUFFER_SIZE, 0);

    printf("Réponse du serveur : %s\n", buffer);

    // Fermeture du socket
    close(clientSocket);

    return 0;
}