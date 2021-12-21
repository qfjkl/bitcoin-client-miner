#include "Miner.h"
#include <iostream>
#include <cmath>
#include <string>


using namespace std;


int main()
{

    /*long nVersion(551550976);

    long n(255);
    char hex_string[20];


    sprintf_s(hex_string, "%X", nVersion);

    cout << hex_string << endl;

    cout << nVersion << endl;*/

    Miner startMiner;
    uint64_t T = startMiner.evaluate();
    cout << "Time " << T << endl;

    //startMiner.connectToServer("192.168.8.101", 7070);

    system("PAUSE");
    return 0;
}


