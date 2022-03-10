#ifndef OXCHAT_OXCRYPT_HPP
#define OXCHAT_OXCRYPT_HPP

#include <vector>

namespace oxCrypt {
    int GeneratePseudoRandomNumber();
    int GeneratePseudoRandomDigit();
    std::vector<int> GeneratePseudoRandomSequence(int amount);
    long long CreateDiffieHellmanPublicKey(int skey, int pkey1, int pkey2);
    long long CreateDiffieHellmanSuperKey(int skey, int public_key, int pkey2);
}

#endif //OXCHAT_OXCRYPT_HPP
