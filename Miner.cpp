
#include <vector>
#include "Bitcoin/Sha256.hpp"
#include "Bitcoin/Sha256Hash.hpp"
#include "Bitcoin/Uint256.hpp"
#include "Miner.h"
#include <intrin.h>
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>
#include <typeinfo>
#include <cmath>




using namespace std;


void Miner::setVal(long nVersion, string hashPrevBlock,
    string hashMerkleRoot, long nTime,
    long nBits, long nNonce) {

    nVersion = nVersion;
    hashPrevBlock = hashPrevBlock;
    hashMerkleRoot = hashMerkleRoot;
    nTime = nTime;
    nBits = nBits;
    nNonce = nNonce;



}


long Miner::hexadecimalToDecimal(string hexVal)
{
    int len = hexVal.size();

    // Initializing base value to 1, i.e 16^0

    int base = 1;
    long dec_val = 0;

    // Extracting characters as digits from last
    // character
    for (int i = len - 1; i >= 0; i--) {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value

        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;

            // incrementing base by power
            base = base * 16;
        }

        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (toupper(hexVal[i]) >= toupper('A') && toupper(hexVal[i]) <= toupper('F')) {
            dec_val += (toupper(hexVal[i]) - 55) * base;

            // incrementing base by power
            base = base * 16;
        }
    }
    return dec_val;
}


long Miner::getSubStr(string header, int x, int y){

    string subStr;
    //int lS = x;

    if(x > y){

        for(int t=x; t>=y; t--){
            subStr += header[t];
        }

    } else{

        for(int t1=x; t1<= y; t1++){
            subStr += header[t1];
        }
    }
    //cout << subStr << endl;
    return hexadecimalToDecimal(subStr);
}



string Miner::serialize(long n){
    // convert first in to base 16

    char hex_string[9];
    sprintf_s(hex_string, "%X", n);


   string h = string(hex_string);
   reverseStr(h);
   return h;
}

/*string Miner::replaceString(string repl, string String, int items[2]){
    cpt = 0;
    for(int i=items[0]; i<=items[1]; i++){
        String[i] = repl[cpt];
        cpt += 1;
    }


} */

string Miner::upperCase(string String){
    int i(0);

    while(i < String.length()){

        if(islower(String[i])){

            String[i] = toupper(String[i]);
        }
        i ++;
    }
    return String;

}


uint64_t Miner::evaluate() {

    time_t current_time = time(NULL);

    string evaluateHeader = "0000ff3fd90c0dfca35c8738aa92e1c5bdf706ba14eaafbb379206000000000000000000ad66d8cda0330c3af011ba6b7bc705789767c55a72a818685b3e06a0b8b9a2b054e82260b9210d17099976a6";
    //evaluateHeader = upperCase(evaluateHeader);


    vector<unsigned char> vectorByte = ToHexIntoVectorByte(evaluateHeader);
    nNonce = getSubStr(evaluateHeader, 160, 152);
    //Sha256Hash doubleSha256;
    for(int c=0; c<1e6; c++){

        Sha256Hash doubleSha256 = Sha256::getDoubleHash(vectorByte.data(), vectorByte.size());
        string Hash = hexStr(doubleSha256.value, sizeof(doubleSha256.value));
        //reverseStr(Hash);
     /*   nBits = getSubStr(evaluateHeader, 152, 144);
        //int items = [144, 152];
        //reverseStr(nBits);
        */
        //cout << vectorByte.data() << endl;
        //evaluateHeader.replace(152, 160, serialize(nNonce));
        //cout <<i << " Header : " << Hash << " Nonce " << nNonce << endl;
        //cout << i << vectorByte.data() << endl;
        nNonce = nNonce + 1;
    }

// b9210d17
    time_t past_time = time(NULL);

    return past_time - current_time;

}

double Miner::getTarget() {

    return 0.0;
}

bool Miner::searchOfGoodNonce() {


    return true;
}


void Miner::connectToServer(string host, int port){

    WSADATA wsaData;
    int err;
    err = WSAStartup(MAKEWORD(2, 2), &wsaData);

    //cout << err;
    SOCKET sock;
    SOCKADDR_IN sin;



    sock = socket(AF_INET, SOCK_STREAM, 0);

    sin.sin_addr.s_addr = inet_addr(host.c_str());
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    connect(sock, (SOCKADDR*)&sin, sizeof(sin));

    closesocket(sock);
    WSACleanup();

    uint64_t timeEval = evaluate();
    cout << endl << "Time : " << timeEval << " Seconds" << endl;
}


 vector<unsigned char> Miner::ToHexIntoVectorByte(string &hexData)
{

    vector<unsigned char>* bytes = new vector<unsigned char>();
    for (unsigned i = 0; i < hexData.length(); i += 2)
    {
        string byteSubString = hexData.substr(i, 2);
        unsigned char byte = (unsigned char)strtol(byteSubString.c_str(), NULL, 16);
        bytes->push_back(byte);

    }
    return *bytes;
}

string Miner::hexStr(BYTE* data, int len) {
    stringstream ss;
    ss << std::hex;

    for (int i(0); i < len; ++i)
        ss << std::setw(2) << std::setfill('0') << (int)data[i];

    return ss.str();
}


// Function to reverse a string
void Miner::reverseStr(string& str)
{
    int n = str.length();

    // Swap character starting from two
    // corners
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);

}
