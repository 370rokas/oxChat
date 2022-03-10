#include <httplib.hpp>
#include <oxCrypt.hpp>

#include <string>
int AppendIntegers(int _1, int _2) {
    std::stringstream converter;
    int Num;

    converter << abs(_1) << abs(_2);
    converter >> Num;

    return Num;
}

int main() {
    httplib::Client cli("127.0.0.1:8080");

    int pkey_g = 0;
    int pkey_p = AppendIntegers(oxCrypt::GeneratePseudoRandomNumber(), oxCrypt::GeneratePseudoRandomNumber());
    int pkey_private = oxCrypt::GeneratePseudoRandomNumber();
    int pkey_public = 0;

    auto res = cli.Get(("/number-exchange?key=" + std::to_string(pkey_p)).c_str());

    if (res) {
        pkey_g = stoi(res->body);
        pkey_public = oxCrypt::CreateDiffieHellmanPublicKey(pkey_private, pkey_g, pkey_p);
        std::cout<< "public: " << pkey_public << std::endl;

        auto res2 = cli.Get(("/key-exchange?key=" + std::to_string(pkey_public)).c_str());

        if (res2) {
            int other_public = stoi(res2->body);
            std::cout << other_public << std::endl;
            std::cout << "SuperKey: " << oxCrypt::CreateDiffieHellmanSuperKey(pkey_private, other_public, pkey_p) << std::endl;
        }
        //pkey_skey = oxCrypt::CreateDiffieHellmanSuperKey(pkey_private, pkey_public);
    } else {
        std::cout << "error: " << httplib::to_string(res.error()) << std::endl;
    }
}