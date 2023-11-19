#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;


// * GLOBAL VAIRBALES
map<string, int> bases; // bases and their equivalent values
string result; // for storing result
ostringstream convert; // for converting int to string


// * FUNCTION PROTOTYPES
string askBase(string n1);
int toDecimal(long unsigned int variable, int n);
int toOctal(long unsigned int variable, int n);
string toHex(long unsigned int variable);
string toBinary(long unsigned int variable);
void printResult(long unsigned int variable, string result);
int hex2Int(string hexadecimal);
void fromDecimal();
void fromBinary();
void fromOctal();
void fromHex();
void callFunction();


// ! ==================== MAIN ==================== //

int main() {
    // Initialize bases
    bases["binary"] = 2;
    bases["octal"] = 8;
    bases["hex"] = 16;
    bases["decimal"] = 10;

    // Call conversion functions
    cout << "\nWelcome to the number system converter!\n\nWill not work numbers with decimal points.\n\n";
    callFunction();
    return 0;
}


// ! ==================== MAIN FUNCTIONS ==================== //


void fromDecimal() {
    // Ask for variable
    long unsigned int variable;
    cout << "Enter decimal: " << endl;
    cin >> variable;

    // Ask for base and get base value
    string base = askBase("decimal");
    int n = bases[base];

    if (n == 2) {
        cout << "Result: " << variable << " -> " << toBinary(variable) << endl;
        return ;
    }

    // Print result
    cout << "Result: " << variable << " -> " << setbase(n) << variable << endl;
}


void fromBinary() {
    // Ask for variable
    long unsigned int variable;
    int nVariable = 2;
    cout << "Enter binary: " << endl;
    cin >> variable;

    // Ask for base and get base value
    string base = askBase("binary");
    int n = bases[base];

    // Determine base conversion
    switch (n) {
        case 8:
            convert << toOctal(toDecimal(variable, nVariable), n);
            result = convert.str();
            break;
        case 10:
            convert << toDecimal(variable, nVariable);
            result = convert.str();
            break;
        case 16:
            result = toHex(toDecimal(variable, nVariable));
            break;          
    }

    // Print result
    cout << "Result: " << variable << " -> " << result << endl;
}


void fromOctal() {
    // Ask for variable
    long unsigned int variable;
    int nVariable = 8;
    cout << "Enter octal: " << endl;
    cin >> variable;

    // Ask for base and get base value
    string base = askBase("octal");
    int n = bases[base];

    // Determine base conversion
    switch (n) {
        case 2:
            result = toBinary(toDecimal(variable, nVariable));
            break;
        case 10:
            convert << toDecimal(variable, nVariable);
            result = convert.str();
            break;
        case 16:
            result = toHex(toDecimal(variable, nVariable));
            break;
    }

    // Print result
    cout << "Result: " << variable << " -> " << result << endl;
}


void fromHex() {
    // Ask for variable
    string variable;
    int nVariable = 16;
    stringstream ss; // converting medium
    cout << "Enter hex: " << endl;
    cin >> variable;

    // Initialize variables to recieve converted values
    int decimal;
    int octal;

    // Ask for base and get base value
    string base = askBase("hex");
    int n = bases[base];


    // Convert hex to decimal
    ss << hex << variable;   
    ss >> decimal;

    // Determine base conversion
    switch (n) {
        case 2:
            result = toBinary(decimal);
            break;
        case 8:
            convert << oct << decimal;
            result = convert.str();
            break;
        case 10:
            result = to_string(decimal);

            break;
    }

    // Print result
    cout << "Result: " << variable << " -> " << result << endl;
}


// ==================== HELPER FUNCTIONS ==================== //


// Call for functions
void callFunction() {
    // Initialize list of functions
    string functions = "1. From binary\n2. From octal\n3. From decimal\n4. From hex\n5. Exit\n";
    int option;

    // Ask for function
    cout << functions << endl << "Enter function to call (number only): " << endl;
    cin >> option;

    // Call function
    switch (option) {
        case 1:
            fromBinary();
            break;
        case 2:
            fromOctal();
            break;
        case 3:
            fromDecimal();
            break;
        case 4:
            fromHex();
            break;
        default:
            break;
    }
}


// Asks for base to convert to
string askBase(string n1) {
    // Initialize a copy of all bases
    map<string, int> basesCopy = bases;

    // Initialize variable for base to convert to
    int option;
    string n2;

    // Check original base and remove it from the copy
    if (basesCopy.find(n1) != basesCopy.end()) {
        basesCopy.erase(n1);
    }
     
    // Print options for bases to convert to
    cout << "Options for bases to convert to:" << endl;
    int count = 1;
    for (map<string, int>::iterator it = basesCopy.begin(); it != basesCopy.end(); ++it) {
        const pair<string, int> &base = *it;
        cout << count << ". " << base.first << endl;
        count++;
    }

    // Ask user for base to convert to and provide options
    while (true) {
        cout << "Enter base to convert to (enter number only): " << endl;
        cin >> option;

        if (floor(option) == option) 
            break;
    }

    // Get equivalent base name
    map<string, int>::iterator it = basesCopy.begin();
    advance(it, option - 1);
    n2 = it->first;

    // Return base to convert to
    return n2;
}


// Convert input to decimal
int toDecimal(long unsigned int variable, int n) {
    // Initialize variables
    int decimal = 0;
    int i = 0;

    // Do algorithm
    while (variable != 0) {
        decimal += variable % 10 * pow(n, i);
        ++i;
        variable /= 10;
    }

    // Return decimal
    return decimal;
}


// Convert input to octal
int toOctal(long unsigned int variable, int n) {
    // Initialize variables
    int octal = 0;
    int i = 1;

    // Do algorithm
    while (variable != 0) {
        octal += (variable % n) * i;
        variable /= n;
        i *= 10;
    }

    // Return octal
    return octal;
}


// Convert input to hex
string toHex(long unsigned int variable) {
    // Initialize variables
    string hex = "";
    int i = 0;

    // Do algorithm
    while (variable != 0) {
        int remainder = variable % 16;

        if (remainder < 10)
            hex = to_string(remainder) + hex;
        
        else
            hex = char(remainder + 55) + hex;

        variable /= 16;
    }

    // Return hex
    return hex;
}


// Coverting to bit
string toBinary(long unsigned int variable) {
    // Initialize variables
    int bit[32];
    int i = 0;
    string binary = "";

    // Do algorithm
    while (variable > 0) {
        bit[i] = variable % 2;
        variable = variable / 2;
        i++;
    }

    // Reverse the array and store bits as a string (binary)
    for (int j = i - 1; j >= 0; j--)
        binary += to_string(bit[j]);

    cout << "Result: " << binary << endl;
    // Return bit
    return binary;
}