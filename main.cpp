//car some

#include <iostream>
#include <memory>

class Thing {};


class Engine : public Thing {
private:
    int horse_power;
public:
    Engine (int power) : horse_power {power} {}

    [[nodiscard]] int get_power() const {
        return horse_power;
    }
};

class Car : Thing {
    std::string name;

public:
    Engine eng;

    Car (const char* n, Engine engine) :
    eng{ engine }, name { n }{}
};
///};

int main() {
    auto car = Car("minicuper", 100);

    auto p = &car;

    std::cout << p->eng.get_power();
}
