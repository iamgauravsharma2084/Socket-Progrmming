#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void readData()
{
    std::ifstream inputFile("D:\\C++ Program\\Socket Programming\\Client_Side\\data.txt", std::ios::in); // Open the file for reading
  //  int i = check;
    if (inputFile.is_open())
    {
        std::string line;
        while (std::getline(inputFile, line))
        {
          //  gotoxy(1, i);
            std::cout << line << std::endl; // Print each line of the file
          //  i--;
        }

        inputFile.close(); // Close the file
    }
    else
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
}
int main()
{
    char ch;
    readData();
    std::cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        exit(0);
    }
}