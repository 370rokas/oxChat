#include <httplib.hpp>
#include <oxCrypt.hpp>

int main(void) {
    httplib::Server svr;

    int pkey_g = 0;
    while (pkey_g <= 0 || pkey_g >= 10) {
        pkey_g = abs(oxCrypt::GeneratePseudoRandomDigit());
    }

    int pkey_p = 0;
    int pkey_private = oxCrypt::GeneratePseudoRandomNumber();
    int pkey_public = 0;

    svr.Get("/number-exchange", [&pkey_p, &pkey_g, &pkey_public, &pkey_private](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("key")) {
            for (int i = 0; i < req.get_param_value("key").length(); i++) {
                if (isdigit(req.get_param_value("key")[i]) == false) {
                    res.set_content("invalid key", "text/plain");
                }
            }

            pkey_p = stoi(req.get_param_value("key"));
            pkey_public = oxCrypt::CreateDiffieHellmanPublicKey(pkey_private, pkey_g, pkey_p);

            res.set_content(std::to_string(pkey_g), "text/plain");
        } else {
            res.set_content("no key", "text/plain");
        }
    });

    svr.Get("/key-exchange", [&](const httplib::Request& req, httplib::Response& res) {
        if (req.has_param("key")) {
            for (int i = 0; i < req.get_param_value("key").length(); i++) {
                if (isdigit(req.get_param_value("key")[i]) == false) {
                    res.set_content("invalid key", "text/plain");
                }
            }
            std::cout << "wawa" << req.get_param_value("key") << std::endl;

            int other_public = stoi(req.get_param_value("key"));
            std::cout << "SuperKey: " << oxCrypt::CreateDiffieHellmanSuperKey(pkey_private, other_public, pkey_p) << std::endl;

            res.set_content(std::to_string(pkey_public), "text/plain");
        } else {
            std::cout << "not wawa" << std::endl;
            res.set_content("no key", "text/plain");
        }
    });

    std::cout << "start server" << std::endl;
    svr.listen("0.0.0.0", 8080);
}