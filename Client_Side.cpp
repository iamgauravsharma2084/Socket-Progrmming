#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> // Required for inet_pton
#include <fstream>
#include <string>
#pragma comment(lib, "ws2_32.lib")
int check = 0;
COORD coord = { 0,0 };
void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Savedata(std::string fi,std::string se)
{
    std::ofstream outputFile("data.txt",std::ios::app); 

    if (outputFile.is_open())
    { 
        outputFile << fi << "         " << se << std::endl;
        outputFile << "-------------------------------" << std::endl;
        check++;
        outputFile.close(); // Close the file
        std::cout << "Data has been written to the file." << std::endl;
    }
    else
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
}



int Cilent_Porgram()
{
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // Connect to the server
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) != 1) {
        std::cerr << "Failed to convert server IP address." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    serverAddress.sin_port = htons(8080); // Use the server's port number

    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
   
   // readData();
     system("cls");
    std::cout << "Connected to the server." << std::endl;
    char message[5000];// = "Hello, server!";
    char buffer[5000];
    while (1)
    {
       // system("cls");
        //readData();
       // gotoxy(80, 5);
        std::cout << "Enter the message: ";
        //gotoxy(40, 6);
        std::cin.getline(message, 1000);
        if (message == "cls" || message=="clean")
        {
            system("cls");
        }
        //strcat_s(message, "\n"); // Append a delimiter to mark the end of the message

        if (send(clientSocket, message, strlen(message), 0) == SOCKET_ERROR)
        {
            std::cerr << "Failed to send data to the server." << std::endl;
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Sent data to the server: " << message << std::endl;

        memset(buffer, '\0', sizeof(buffer));
        int totalBytesRead = 0;
        int expectedMessageLength = 0;
        //while (true)
        {
            int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead == SOCKET_ERROR)
            {
                std::cerr << "Failed to receive data from the server." << std::endl;
                break;
            }
            else if (bytesRead == 0)
            {
                std::cout << "Server disconnected." << std::endl;
                break;
            }
            else
            {

                std::cout << "Received data from the server: " << buffer << std::endl;
                Savedata(message,buffer);
            }
        }
    }

    // Close the socket
    closesocket(clientSocket);

    // Cleanup
    WSACleanup();
}



int main()
{
     ShellExecute(HWND_DESKTOP,L"open",L"D:\\C++ Program\\Socket Programming\\Server_Side\\x64\\Debug\\Server_Side.exe",NULL,NULL,SW_SHOW);
     Sleep(1000);
     system("mode con: cols=200 lines=40");
     Cilent_Porgram();
    return 0;
}
