#include <iostream>
#include <fstream>
#include <sstream>
#include "BST.h"
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

int main(int argc, char *argv[]) {
    VS_MEM_CHECK
    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 1;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
    }

    string inputLine;
    BST<int> *intObject;
    BST<string> *stringObject;

    while (!in.eof()) {
        while (getline(in, inputLine)) {
            istringstream iss(inputLine);
            string commandLine;
            iss >> commandLine;
            out << commandLine;
            if (commandLine == "INT") {
                intObject = new BST<int>();
                out << " true";
            }
            else if (commandLine == "add") {
                int nodeValue;
                iss >> nodeValue;
                out << " " << nodeValue;
                if (intObject->addNode(nodeValue)) {
                    out << " true";
                }
                else {
                    out << " false";
                }
            }
            else if (commandLine == "print") {
                out << ": ";
                out << intObject->toString();
            }
            else if (commandLine == "remove") {
                int nodeValue;
                iss >> nodeValue;
                out << " " << nodeValue;
                if (intObject->removeNode(nodeValue)) {
                    out << " true";
                }
                else {
                    out << " false";
                }
            }
            else if (commandLine == "clear") {
                if (intObject->clearTree()) {
                    out << " true";
                }
                else {
                    out << " false";
                }
            }
            else if (commandLine == "size") {
                out << " " << intObject->sizeTree();
            }
            else if (commandLine == "find") {
                int nodeValue;
                iss >> nodeValue;
                out << " " << nodeValue;
                if (intObject->findNode(nodeValue)) {
                    out << " found";
                }
                else {
                    out << " not found";
                }
            }
            else if (commandLine == "STRING") {
                stringObject = new BST<string>();
                out << " true";
                out << endl;
                break;
            }
            out << endl;
        }
        intObject->clearTree();
        while (getline(in, inputLine)) {
            istringstream iss(inputLine);
            string commandLine;
            iss >> commandLine;
            out << commandLine;
            if (commandLine == "add") {
                string nodeValue;
                iss >> nodeValue;
                out << " " << nodeValue;
                if (stringObject->addNode(nodeValue)) {
                    out << " true";
                }
                else {
                    out << " false";
                }
            } else if (commandLine == "print") {
                out << ": ";
                out << stringObject->toString();
            }
            else if (commandLine == "remove") {
                string nodeValue;
                iss >> nodeValue;
                out << " " << nodeValue;
                if (stringObject->removeNode(nodeValue)) {
                    out << " true";
                }
                else {
                    out << " false";
                }
            }
            else if (commandLine == "clear") {
                if (stringObject->clearTree()) {
                    out << " true";
                }
                else {
                    out << " false";
                }
            }
            else if (commandLine == "size") {
                out << " " << stringObject->sizeTree();
            }
            else if (commandLine == "find") {
                string nodeValue;
                iss >> nodeValue;
                out << " " << nodeValue;
                if (stringObject->findNode(nodeValue)) {
                    out << " found";
                }
                else {
                    out << " not found";
                }
            }
            out << endl;
        }
        stringObject->clearTree();
        delete intObject;
        delete stringObject;
    }
    return 0;
}
