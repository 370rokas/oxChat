#include "include/oxCrypt.hpp"

#include <random>
#include <chrono>
#include <vector>

std::vector<int> PreparedPseudoRandomSequence;

long long oxCrypt::CreateDiffieHellmanPublicKey(int skey, int pkey1, int pkey2) {
    return (long long) pow(pkey1, skey) % pkey2;
}

long long oxCrypt::CreateDiffieHellmanSuperKey(int skey, int public_key, int pkey2) {
    return (long long) pow(skey, public_key) % pkey2;
}

std::vector<int> oxCrypt::GeneratePseudoRandomSequence(int amount) {
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count() );

    std::mt19937 gen(seed);
    std::vector<int> generated_sequence;

    for(unsigned long i = 0; i < amount; ++i) {
        std::mt19937::result_type n;
        while((n = gen()) > std::mt19937::max() - (std::mt19937::max() - 5 )%6) {}
        generated_sequence.push_back(n);
    }

    return generated_sequence;
}

int oxCrypt::GeneratePseudoRandomNumber() {
    if (PreparedPseudoRandomSequence.size() == 0) {
        // Generate new pseudorandom number sequence
        PreparedPseudoRandomSequence = oxCrypt::GeneratePseudoRandomSequence(100);
    }

    int Num = PreparedPseudoRandomSequence.back();
    PreparedPseudoRandomSequence.pop_back();
    return Num;
}

int oxCrypt::GeneratePseudoRandomDigit() {
    if (PreparedPseudoRandomSequence.size() == 0) {
        // Generate new pseudorandom number sequence
        PreparedPseudoRandomSequence = oxCrypt::GeneratePseudoRandomSequence(100);
    }

    int Num = PreparedPseudoRandomSequence.back();
    PreparedPseudoRandomSequence.pop_back();
    return Num % 6 + 1;
}