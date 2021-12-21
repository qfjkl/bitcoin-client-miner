#pragma once
#ifndef MINER_H_INCLUDED
#define MINER_H_INCLUDED

#include "Bitcoin/Sha256.hpp"
#include "Bitcoin/Sha256Hash.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "byte_type.h"
#pragma comment(lib, "ws2_32.lib")

class Miner {

private:
    long nVersion;
    std::string hashPrevBlock;
    std::string hashMerkleRoot;
    long nTime;
    long nBits;
    long nNonce;


public:

    void setVal(long nVersion, std::string hashPrevBlock,
        std::string hashMerkleRoot, long nTime,
        long nBits, long nNonce);

    long hexadecimalToDecimal(std::string hexVal);

    std::string upperCase(std::string String);

    std::string serialize(long n);

   // std::string replaceString(string repl, string String, int items[2]);

    long getSubStr(std::string header, int x, int y);

    uint64_t evaluate();

    double getTarget();

    bool searchOfGoodNonce();

    /*string serializeBlockHeader(long nVersion, string hashPrevBlock,
        string hashMerkleRoot, long nTime,
        long nBits, long nNonce);*/

    void connectToServer(std::string host, int port);

    //std::string hexStr(BYTE* data, int len);

    void getHeaderHash(std::string headerString);

    std::vector<unsigned char> ToHexIntoVectorByte(std::string &hexData);

    void reverseStr(std::string& str);

    std::string hexStr(BYTE* data, int len);
};




#endif // MINER_H_INCLUDED
