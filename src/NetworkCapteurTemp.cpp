#include "NetworkCapteurTemp.hpp"


NetworkCapteurTemp::NetworkCapteurTemp(uint16_t port):udpPort{port}{

    this->udpServerThread = std::jthread(&NetworkCapteurTemp::_serverThread,this);

}


void    NetworkCapteurTemp::_serverThread(){

int sockfd;
sockaddr_in servaddr, cliaddr;
char buffer[MAXLINE];

std::clog << "UDP server starting (port : " << static_cast<int>(this->getudpPort()) << ")\n"; 

// Creating socket file descriptor
if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) throw NetworkException("Error while creating socket.");

// Filling server information
servaddr.sin_family = AF_INET; // IPv4
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(this->getudpPort());

// Bind the socket with the server address
if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) throw NetworkException("Error while binding the socket.");
socklen_t len = sizeof(cliaddr); //len is value/result;
int n;
while(true){
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
    buffer[n] = '\0';
    std::string stmp{buffer};
    std::cout << "Message received = " << stmp << std::endl;
    try{
        this->setRawTemp(std::stoi(stmp));
        std::clog << "New temperature received. OK\n";
    }
    catch(const std::invalid_argument& e){
        std::cerr << "Received value is not an integer.\n";
    }
    catch(const std::out_of_range& e){
        std::cerr << "Received value is out of range.\n";
    }


    }
}





