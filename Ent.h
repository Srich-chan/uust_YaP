//
// Created by ы on 23.09.2025.
//

#ifndef TESTO_H
#define TESTO_H

#include <iostream>
#include <vector>

using std::vector, std::string;

namespace test {
    
    class Ent {
        string _name;
        vector<string> groups;
    public:
        explicit Ent (const string &name) {
            groups.reserve(8);
            _name = name;
        }

        void group_add(string &group) {
            groups.emplace_back(group);
        }
    };

    class Existing : protected Ent {
        //Vector 3d
        double pos[3];
        // _name = 1;
    public:
        Existing () : pos {{0.0, 0.0, 0.0}} {}
    };

    class Moveable : protected Existing{};

    class Physic : protected Moveable {};

    class Character : protected Physic {};

} // testt

#endif //TESTO_H
