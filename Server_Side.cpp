#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> // Required for inet_pton
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <bitset>
#include <cctype>
#include <unordered_map>
#include <fstream>
#include <string>

#pragma comment(lib, "ws2_32.lib")
int flog = 0;
int get_number_1_and_2=0;
int number_1=0;
int number_2=0;
char buffer[1000] = { '\0' };
int cal = 0;
char ch;
char hexvalue[100];
int flog_1 = 0;
int flog_2 = 0;
/*******************************************************************/
/*                 Binary              */
int convertBinarytoDec(long long n)
{
    int dec = 0, i = 0, rem;
    while (n != 0)
    {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    return dec;
}
int convertBinarytoOctal(long long binaryNumber)
{
    int octalNumber = 0, decimalNumber = 0, i = 0;

    while (binaryNumber != 0)
    {
        decimalNumber += (binaryNumber % 10) * pow(2, i);
        ++i;
        binaryNumber /= 10;
    }

    i = 1;

    while (decimalNumber != 0)
    {
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }

    return octalNumber;
}
std::string convertBinaryToHex(const std::string& binaryInput)
{
    // Convert binary string to integer
    unsigned int decimalValue = 0;
    for (char digit : binaryInput) {
        decimalValue <<= 1;
        decimalValue += digit - '0';
    }

    // Convert integer to hexadecimal string
    std::stringstream ss;
    ss << std::hex << decimalValue;
    std::string hexadecimalOutput = ss.str();

    // Ensure the output is in uppercase
    for (char& c : hexadecimalOutput) {
        c = toupper(c);
    }

    // Prepend '0x' to the hexadecimal representation
    hexadecimalOutput = "0x" + hexadecimalOutput;

    return hexadecimalOutput;
}
bool StringBinary(std::string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] != '1' && str[i] != '0')
            return false;
    }
    return true;
}
/*********************************************************************/
/*                 Decimal              */
bool isDecimalNumber(const std::string & input)
{
    if (input.empty())
    {
        return false;
    }

    bool hasDecimalPoint = false;
    for (char c : input)
    {
        if (!isdigit(c))
        {
            if (c == '.' && !hasDecimalPoint)
            {
                hasDecimalPoint = true;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}
std::string decimalToBinary(int decimal) 
{
    if (decimal == 0)
        return "0";

    std::string binary = "";
    while (decimal > 0)
    {
        binary = std::to_string(decimal % 2) + binary;
        decimal /= 2;
    }
    return binary;
}
std::string decimalToOctal(int decimal) 
{
    if (decimal == 0) 
    {
        return "0";
    }

    char octalDigits[100]; // Assume the maximum number of octal digits is 100
    int numOctalDigits = 0;

    while (decimal > 0)
    {
        octalDigits[numOctalDigits] = '0' + decimal % 8;
        decimal /= 8;
        numOctalDigits++;
    }

    std::string octalNumber;
    for (int i = numOctalDigits - 1; i >= 0; i--)
    {
        octalNumber += octalDigits[i];
    }

    return octalNumber;
}
std::string decimalToHexadecimal(int decimal) {
    if (decimal == 0) {
        return "0";
    }

    char hexadecimalDigits[100]; // Assume the maximum number of hexadecimal digits is 100
    int numHexadecimalDigits = 0;
    const char hexChars[] = "0123456789ABCDEF";

    while (decimal > 0) {
        hexadecimalDigits[numHexadecimalDigits] = hexChars[decimal % 16];
        decimal /= 16;
        numHexadecimalDigits++;
    }

    std::string hexadecimalNumber;
    for (int i = numHexadecimalDigits - 1; i >= 0; i--) 
    {
        hexadecimalNumber += hexadecimalDigits[i];
    }

    return hexadecimalNumber;
}
/*********************************************************************/
/*                 Hex              */
// Function to remove a specific substring from the string
std::string removeSubstring(std::string& originalString, std::string& targetSubstring)
{
    std::string modifiedString = originalString;
    size_t foundPos = modifiedString.find(targetSubstring);
    while (foundPos != std::string::npos)
    {
        modifiedString.erase(foundPos, targetSubstring.length());
        foundPos = modifiedString.find(targetSubstring);
    }
    return modifiedString;
}
std::string toUpperCase(std::string& str)
{
    std::string upperStr = str;
    for (char& c : upperStr) 
    {
        c = std::toupper(c);
    }
    return upperStr;
}
bool isHexadecimalNumber(const std::string& input)
{
    if (input.empty())
    {
        return false;
    }

    for (char c : input)
    {
        if (!isxdigit(c))
        {
            return false;
        }
    }

    return true;
}
std::string hexToBinary( std::string& hex)
{
    hex = toUpperCase(hex);
    std::string binary = "";
    const std::string hexChars = "0123456789ABCDEF";

    for (char c : hex) 
    {
        
        c = toupper(c); // Convert the character to uppercase (in case it's lowercase)
        size_t pos = hexChars.find(c);
        if (c == ' ')
        {
            break;
        }
        /*if (pos == std::string::npos)
        {
            return "Invalid Hexadecimal Number";
        }*/
        binary += std::bitset<4>(pos).to_string();
    }

    // Trim leading zeros
    size_t nonZeroPos = binary.find_first_not_of('0');
    return (nonZeroPos != std::string::npos) ? binary.substr(nonZeroPos) : "0";
}
int hexToDecimal(std::string& hex)
{
    std::string hexString = hex; // Replace this with your hex string
    int decimalValue = std::stoi(hexString, nullptr, 16);
    return decimalValue;
}
std::string hexToOctal(std::string& hex)
{
    std::string hexString = hex; // Replace this with your hexadecimal string
    // Convert hexadecimal string to an integer
    int decimalValue = std::stoi(hexString, nullptr, 16);
    // Convert the integer to an octal string
    std::ostringstream oss;
    oss << std::oct << decimalValue;
    std::string octalString = oss.str();
    std::cout << "Hexadecimal: " << hexString << std::endl;
    std::cout << "Octal: " << octalString << std::endl;
    return octalString;
}
/*********************************************************************/
/*                 Octal              */
bool isOctalNumber(const std::string& str)
{
    if (str.empty())
        return false;

    // Check if the string starts with '0'
    /*if (str[0] != '0')
        return false;*/

    // Check if the remaining characters are valid octal digits
    for (size_t i = 1; i < str.length(); ++i)
    {
        if (!std::isdigit(str[i]) || str[i] > '7')
            return false;
    }

    return true;
}
// Function to convert a single octal digit to its binary representation
std::string octalDigitToBinary(char octalDigit)
{
    static const std::unordered_map<char, std::string> octalToBinary = {
        {'0', "000"}, {'1', "001"}, {'2', "010"}, {'3', "011"},
        {'4', "100"}, {'5', "101"}, {'6', "110"}, {'7', "111"}
    };

    return octalToBinary.at(octalDigit);
}
std::string octalToBinary(const std::string& octal)
{
    std::string binary;
    // Convert each octal digit to its binary representation
    for (char octalDigit : octal)
    {
        binary += octalDigitToBinary(octalDigit);
    }
    // Remove leading zeroes
    size_t pos = binary.find_first_not_of('0');
    return (pos != std::string::npos) ? binary.substr(pos) : "0";
}
// Function to convert an octal number to binary
int octaltoDecimal(std::string& octal)
{
    std::string octalString = octal; // Replace this with your octal string
    int decimalValue = std::stoi(octalString, nullptr, 8);

    std::cout << "Octal: " << octalString << std::endl;
    std::cout << "Decimal: " << decimalValue << std::endl;
    return decimalValue;
}
int octaltodec(std::string& octalString)
{
    int decimalValue = 0;
    for (char octalDigit : octalString) 
    {
        if (octalDigit < '0' || octalDigit > '7')
        {
            // Invalid octal digit, return 0 or handle the error accordingly.
            return 0;
        }
        decimalValue = decimalValue * 8 + (octalDigit - '0');
    }
    return decimalValue;
  
}
std::string octaltoHex(std::string octalString)
{
    // Convert octal to decimal
    int decimalValue = octaltodec(octalString);

    // Convert decimal to hexadecimal string
    std::stringstream ss;
    ss << std::hex << decimalValue;
    std::string hexString = ss.str();

    std::cout << "Octal: " << octalString << std::endl;
    std::cout << "Hexadecimal: " << hexString << std::endl;
    return hexString;
}


/**********************************************************************/
void readData()
{
    std::ifstream inputFile("add_two_number.txt", std::ios::in); // Open the file for reading
    //  int i = check;
    if (inputFile.is_open())
    {
        std::string line;
        while (std::getline(inputFile, line))
        {
            std::cout << line << std::endl;
            line = line  + '\n';
            const char* charArray = line.c_str();
            strcat_s(buffer, charArray);
        }

        inputFile.close(); // Close the file
    }
    else
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
}







void Calculator(char ch)
{
    flog_1 = 0;
    flog_2 = 0;
    int sum;
    if (ch == '+')
    {
        memset(buffer, '\0', sizeof(buffer));
        sum = number_1 + number_2;
        std::string strValue = std::to_string(sum);
        const char* charArray = strValue.c_str();
        strcpy_s(buffer, charArray);
        cal = 1;
    }
    else if (ch == '-')
    {
        memset(buffer, '\0', sizeof(buffer));
        sum = number_1 - number_2;
        std::string strValue = std::to_string(sum);
        const char* charArray = strValue.c_str();
        strcpy_s(buffer, charArray);
        cal = 1;
    }
    else if (ch == '*')
    {
        memset(buffer, '\0', sizeof(buffer));
        sum = number_1 * number_2;
        std::string strValue = std::to_string(sum);
        const char* charArray = strValue.c_str();
        strcpy_s(buffer, charArray);
        cal = 1;
    }
    else if (ch == '/')
    {
        memset(buffer, '\0', sizeof(buffer));
        sum = number_1 / number_2;
        std::string strValue = std::to_string(sum);
        const char* charArray = strValue.c_str();
        strcpy_s(buffer, charArray);
        cal = 1;
    }
    else if (ch == '0')
    {
        if (true == StringBinary(std::to_string(number_1)))
        {
            int ret = convertBinarytoDec(number_1);

            std::string Number = std::to_string(number_1);
            const char* Array = Number.c_str();
            std::string strNumber = std::to_string(ret);
            const char* charArray = strNumber.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " in binary number = ");
            strcat_s(buffer, charArray);
            strcat_s(buffer, " in Decimal Number");
            cal = 1;
        }
        else
        {
            std::string Number = std::to_string(number_1);
            const char* Array = Number.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " This number cannot be a thing a decimal number");
        }

    }
    else if (ch == '1')
    {
        if (true == StringBinary(std::to_string(number_1)))
        {
            int ret = convertBinarytoOctal(number_1);
            std::string Number = std::to_string(number_1);
            const char* Array = Number.c_str();
            std::string strNumber = std::to_string(ret);
            const char* charArray = strNumber.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " in binary number = ");
            strcat_s(buffer, charArray);
            strcat_s(buffer, " in Octal Number");
            cal = 1;
        }
        else
        {
            std::string Number = std::to_string(number_1);
            const char* Array = Number.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " This number cannot be a thing a Octal number");
        }
    }
    else if (ch == '2')
    {
        // binaryToHex
        if (true == StringBinary(std::to_string(number_1)))
        {
           // int ret = 
            std::string Number = std::to_string(number_1);
            const char* Array = Number.c_str();
            std::string strNumber = convertBinaryToHex(Number);
            const char* charArray = strNumber.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " in binary number = ");
            strcat_s(buffer, charArray);
            strcat_s(buffer, " in hexadecimal Number");
            cal = 1;
        }
        else
        {
            std::string Number = std::to_string(number_1);
            const char* Array = Number.c_str();
            strcpy_s(buffer,Array);
            strcat_s(buffer, " This number cannot be a thing a Hexadecimal number");
        }
    }
    else if (ch == '3')
    {
        if (true == isDecimalNumber(std::to_string(number_1)))
        {
            std::string Arr = std::to_string(number_1);
            std::string dec = decimalToBinary(number_1);
            const char* charArray = dec.c_str();
            const char* Array = Arr.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " in Decimal number = ");
            strcat_s(buffer, charArray);
            strcat_s(buffer, " in binary Number");
            cal = 1;
        }
        else
        {
            std::string Number = std::to_string(number_1);
            const char* Array = Number.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " This number cannot be a thing a Binary number");
        }

    }
    else if (ch == '4')
    {
        if (true == isDecimalNumber(std::to_string(number_1)))
        {
            std::string Arr = std::to_string(number_1);
            std::string dec = decimalToOctal(number_1);
            const char* charArray = dec.c_str();
            const char* Array = Arr.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " in Decimal number = ");
            strcat_s(buffer, charArray);
            strcat_s(buffer, " in Octal Number");
            cal = 1;
        }
        else
        {
            std::string Number = std::to_string(number_1);
            const char* Array = Number.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " This number cannot be a thing a Octal number");
        }
    }
    else if (ch == '5')
    {
        if (true == isDecimalNumber(std::to_string(number_1)))
        {
            std::string Arr = std::to_string(number_1);
            std::string dec = decimalToHexadecimal(number_1);
            const char* charArray = dec.c_str();
            const char* Array = Arr.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " in Decimal number = ");
            strcat_s(buffer, charArray);
            strcat_s(buffer, " in Octal Number");
            cal = 1;
        }
        else
        {
            std::string Number = std::to_string(number_1);
            const char* Array = Number.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " This number cannot be a thing a Hexadecimal number");
        } 
    }
    else if (ch == '6')
    {
        std::string originalString = hexvalue;
        std::string substringsToRemove[] = {
        "hexadecimal to binary",
        "hexadecimaltobinary",
        "hexadecimalbinary",
        "hb"
        };
        for (std::string& substring : substringsToRemove)
        {
            originalString = removeSubstring(originalString, substring);
        }
        std::cout << "Modified string: " << originalString << std::endl;
        std::string number_1 = originalString;
       // if (true == isHexadecimalNumber(number_1))
        {
            std::cout << "Number : " << number_1 << std::endl;
            std::string dec = hexToBinary(number_1);
            const char* charArray = dec.c_str();
            const char* Array = number_1.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " in Hexadecimal number = ");
            strcat_s(buffer, charArray);
            strcat_s(buffer, " in Binary Number");
            cal = 1;
        }
    }
    else if (ch == '7')
    {
        std::string originalString = hexvalue;
        std::string substringsToRemove[] = {
        "hexadecimal to binary",
        "hexadecimaltobinary",
        "hexadecimalbinary",
        "hb"
        };
        for (std::string& substring : substringsToRemove)
        {
            originalString = removeSubstring(originalString, substring);
        }
        std::cout << "Modified string: " << originalString << std::endl;
        std::string number_1 = originalString;
        // if (true == isHexadecimalNumber(number_1))
        {
            std::cout << "Number : " << number_1 << std::endl;
            int dec = hexToDecimal(originalString);
            std::string stringValue = std::to_string(dec);
            const char* charArray = stringValue.c_str();
            const char* Array = number_1.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " in Hexadecimal number = ");
            strcat_s(buffer, charArray);
            strcat_s(buffer, " in Decimal Number");
            cal = 1;
        }
    }// hexToOctal
    else if (ch == '8')
    {
        std::string originalString = hexvalue;
        std::string substringsToRemove[] = {
        "hexadecimal to binary",
        "hexadecimaltobinary",
        "hexadecimalbinary",
        "hb"
        };
        for (std::string& substring : substringsToRemove)
        {
            originalString = removeSubstring(originalString, substring);
        }
        std::cout << "Modified string: " << originalString << std::endl;
        std::string number_1 = originalString;
        // if (true == isHexadecimalNumber(number_1))
        {
            std::cout << "Number : " << number_1 << std::endl;
            std::string dec = hexToOctal(originalString);
            const char* charArray = dec.c_str();
            const char* Array = number_1.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " in Hexadecimal number = ");
            strcat_s(buffer, charArray);
            strcat_s(buffer, " in Ocatal Number");
            cal = 1;
        } // 
    }// true == isOctalNumber(number_1)
    else if (ch == '9')
    {
        if (true == isOctalNumber(std::to_string(number_1)))
        {
            std::string Arr = std::to_string(number_1);
            std::string dec = octalToBinary(Arr);
            const char* charArray = dec.c_str();
            const char* Array = Arr.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " in Octal number = ");
            strcat_s(buffer, charArray);
            strcat_s(buffer, " in Binary Number");
            cal = 1;
        }
        else
        {
            std::string Number = std::to_string(number_1);
            const char* Array = Number.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " This number cannot be a thing a Hexadecimal number");
        }
    }//
    else if (ch == 'A')
    {
        if (true == isOctalNumber(std::to_string(number_1)))
        {
            std::string Arr = std::to_string(number_1);
            int dec = octaltoDecimal(Arr);
            std::string stringValue = std::to_string(dec);
            const char* charArray = stringValue.c_str();
            const char* Array = Arr.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " in Octal number = ");
            strcat_s(buffer, charArray);
            strcat_s(buffer, " in Deciaml Number");
            cal = 1;
        }
        else
        {
            std::string Number = std::to_string(number_1);
            const char* Array = Number.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " This number cannot be a thing a Hexadecimal number");
        }
    }//
    else if (ch == 'B')
    {
        if (true == isOctalNumber(std::to_string(number_1)))
        {
            std::string Arr = std::to_string(number_1);
            std::string dec = octaltoHex(Arr);
            const char* charArray = dec.c_str();
            const char* Array = Arr.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " in Octal number = ");
            strcat_s(buffer, charArray);
            strcat_s(buffer, " in Deciaml Number");
            cal = 1;
        }
        else
        {
            std::string Number = std::to_string(number_1);
            const char* Array = Number.c_str();
            strcpy_s(buffer, Array);
            strcat_s(buffer, " This number cannot be a thing a Hexadecimal number");
        }
    }
        
}

void Uppercase_to_Lowercase(char* str)
{
    int i;
    for (i = 0; i <= strlen(str); i++)
    {
      
        if (str[i] >= 65 && str[i] <= 90)
        {
            str[i] = str[i] + 32;
        }

        strcpy_s(buffer, str);
    }
}



void Symbol(char* sys)
{
   
    std::string str(sys);
    std::size_t len = str.length();//.
    if (flog_1 == 1 || flog_2 == 1)
    {
        if (str.find("add") != std::string::npos || str.find("+") != std::string::npos || str.find("sum") != std::string::npos || str.find("addition") != std::string::npos)
        {
            ch = '+';
            Calculator(ch);
        }
        else if (str.find("sub") != std::string::npos || str.find("-") != std::string::npos || str.find("minus") != std::string::npos || str.find("Subtraction") != std::string::npos)
        {
            ch = '-';
            Calculator(ch);
        }
        else if (str.find("mul") != std::string::npos || str.find("*") != std::string::npos || str.find("multiplication") != std::string::npos)// || str.find("Subtraction") != std::string::npos)
        {
            ch = '*';
            Calculator(ch);
        }
        else if (str.find("div") != std::string::npos || str.find("/") != std::string::npos || str.find("division") != std::string::npos)// || str.find("Subtraction") != std::string::npos)
        {
            ch = '/';
            Calculator(ch);
        }
        else if (str.find("bd") != std::string::npos || str.find("binary to decimal") != std::string::npos || str.find("binarydecimal") != std::string::npos || str.find("binary decimal") != std::string::npos)
        {
            ch = '0';
            Calculator(ch);
            //BinarytoOctal
        }
        else if (str.find("bo") != std::string::npos || str.find("binary to octal") != std::string::npos || str.find("binaryoctal") != std::string::npos || str.find("binary octal") != std::string::npos)
        {
            ch = '1';
            Calculator(ch);
            //
        }
        else if (str.find("bh") != std::string::npos || str.find("binary to hexadecimal") != std::string::npos || str.find("binaryhexadecimal") != std::string::npos || str.find("binary hexadecimal") != std::string::npos)
        {
            ch = '2';
            Calculator(ch);
            //
        }
        else if (str.find("db") != std::string::npos || str.find("decimal to binary") != std::string::npos || str.find("decimaltobinary") != std::string::npos || str.find("decimalbinary") != std::string::npos)
        {
            ch = '3';
            Calculator(ch);
        }
        else if (str.find("do") != std::string::npos || str.find("decimal to octal") != std::string::npos || str.find("decimaltooctal") != std::string::npos || str.find("decimaloctal") != std::string::npos)
        {
            ch = '4';
            Calculator(ch);
        }
        else if (str.find("dh") != std::string::npos || str.find("decimal to hexadecimal") != std::string::npos || str.find("decimaltohexadecimal") != std::string::npos || str.find("decimalhexadecimal") != std::string::npos)
        {
            ch = '5';
            Calculator(ch);
        }
        else if (str.find("hb") != std::string::npos || str.find("hexadecimal to binary") != std::string::npos || str.find("hexadecimaltobinary") != std::string::npos || str.find("hexadecimalbinary") != std::string::npos)
        {
            ch = '6';
            Calculator(ch);
        }
        else if (str.find("hd") != std::string::npos || str.find("hexadecimal to decimal") != std::string::npos || str.find("hexadecimaltodecimal") != std::string::npos || str.find("hexadecimaldecimal") != std::string::npos)
        {
            ch = '7';
            Calculator(ch);
        }
        else if (str.find("ho") != std::string::npos || str.find("hexadecimal to octal") != std::string::npos || str.find("hexadecimaltooctal") != std::string::npos || str.find("hexadecimaloctal") != std::string::npos)
        {
            ch = '8';
            Calculator(ch);
        }//octalToBinary
        else if (str.find("ob") != std::string::npos || str.find("octal to binary") != std::string::npos || str.find("octaltobinary") != std::string::npos || str.find("octalbinary") != std::string::npos)
        {
            ch = '9';
            Calculator(ch);
        }
        else if (str.find("od") != std::string::npos || str.find("octal to decimal") != std::string::npos || str.find("octaltodecimal") != std::string::npos || str.find("octaldecimal") != std::string::npos)
        {
            ch = 'A';
            Calculator(ch);
        }
        else if (str.find("oh") != std::string::npos || str.find("octal to hexadecimal") != std::string::npos || str.find("octaltohexadecimal") != std::string::npos || str.find("octalhexadecimal") != std::string::npos)
        {
            ch = 'B';
            Calculator(ch);
        }
    }
    else
    {
        ch = 'N';
    }


}

void Get_Nimnber_of_String(char* strr)
{
    std::string str(strr);
    // Regular expression pattern to match an integer
    std::regex pattern("\\b([0-9]+)\\b");
    // Iterator to iterate over all matches
    std::sregex_iterator iterator(str.begin(), str.end(), pattern);
    std::sregex_iterator endIterator;
    if (iterator != endIterator) 
    {
        // Iterate over all matched integers
        for (; iterator != endIterator; ++iterator) 
        {
            std::smatch match = *iterator;
            int intValue = std::stoi(match[1]);

            if (get_number_1_and_2 == 0)
            {
                number_1 = intValue;
                get_number_1_and_2 = 1;
                flog_1 = 1;
            }
            else
            {
                number_2 = intValue;
                get_number_1_and_2 = 0;
                flog = 2;
            }
            
        }
    }
    else
    
    {
        
    }
}

void Message_List(char* buff)
{
    if (ch == 'N')
    {
        if (strcmp(buff, "hello") == 0)
        {
            memset(buffer, '\0', sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), "Hi");
        }
        else if (strcmp(buff, "hi") == 0)
        {
            memset(buffer, '\0', sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), "Hello");
        }
        else if (strcmp(buff, "thank you") == 0)
        {
            memset(buffer, '\0', sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), "welcome");
        }
        else if (strcmp(buff, "good") == 0)
        {
            memset(buffer, '\0', sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), "Thank you");
        }
        else if (strcmp(buff, "i love you") == 0)
        {
            memset(buffer, '\0', sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), "I am a machine I can help you. That's why don't send such question to me, nor do I have feelings");
        }
        else if (strcmp(buff, "ok") == 0)
        {
            memset(buffer, '\0', sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), "Hmmm");
        }
        else if (strcmp(buff, "smart") == 0 || strcmp(buff, "you are very smart") == 0)
        {
            memset(buffer, '\0', sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), "I Know I am very Smart");
        }
        else if (strcmp(buff, "sorry") == 0 || strcmp(buff, "i am soory") == 0)
        {
            memset(buffer, '\0', sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), "No Problem!");
        }//
        else if (strcmp(buff, "history") == 0 || strcmp(buff, "info") == 0)
        {
            char ch;
            memset(buffer, '\0', sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), "ok");
            ShellExecute(HWND_DESKTOP, L"open", L"D:\\C++ Program\\Socket Programming\\ReadInfochat\\x64\\Debug\\ReadInfochat.exe", NULL, NULL, SW_SHOW);
        }
        else if (strcmp(buff, "add two number") == 0 || strcmp(buff, "add two num") == 0)
        {
            memset(buffer, '\0', sizeof(buffer));
            //strcpy_s(buffer, sizeof(buffer), "No Problem!");
            readData();
        }
        else
        {
            memset(buffer, '\0', sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), "We can't take this message sorry!!!!!");
        }
    }
    else
    {
        cal = 0;
       
    }
}


int Server_Program()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // Bind the socket to an IP address and port
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    if (inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr)) != 1)
    {
        std::cerr << "Failed to convert server IP address." << std::endl;
        // closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    serverAddress.sin_port = htons(8080); // Use the server's port number

    if (bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Start listening for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Failed to listen on socket." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server started. Listening on port 8080..." << std::endl;


    // Accept incoming connections and handle them
    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cerr << "Failed to accept client connection." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    char ch[1000];
    std::cout << "Client connected." << std::endl;
    while (1)
    {

        // Receive and send data
        
        memset(buffer, '\0', sizeof(buffer));
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        Uppercase_to_Lowercase(buffer);
        strcpy_s(hexvalue, buffer);
        if (bytesRead == SOCKET_ERROR)
        {
            std::cerr << "Failed to receive data from client." << std::endl;
            exit(0);
        }
        else if (bytesRead == 0)
        {
            std::cout << "Client disconnected." << std::endl;
        }
        else
        {
            Get_Nimnber_of_String(buffer);
            Symbol(buffer);
            Message_List(buffer);
           // Calculator(ch);
            std::cout << "Received data from client: " << buffer << std::endl;
            {
                
                strcpy_s(ch, buffer);
                int bytesRe = send(clientSocket, ch, sizeof(buffer), 0);
                if (bytesRe == SOCKET_ERROR)
                {
                    std::cerr << "Failed to receive data from server." << std::endl;
                }
                else if (bytesRe == 0)
                {
                    std::cout << "Server disconnected." << std::endl;
                }
                else
                {
                    std::cout << "Received data from the server: " << ch << std::endl;
                    memset(buffer, '\0', sizeof(buffer));
                    get_number_1_and_2 = 0;
                }
            }
            

        }
    }

    // Cleanup
    closesocket(serverSocket);

    WSACleanup();

    return 0;
}











int main()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    Server_Program();
    
}
