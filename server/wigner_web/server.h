#ifndef SERVER_H
#define SERVER_H

#include <string>

namespace wigner_web{
    class Server{
    public:
        std::string process(const std::string& request);
    };
}

#endif
