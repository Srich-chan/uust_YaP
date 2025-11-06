#include <cstdio>

typedef struct {
    char name[128];
    unsigned weight;
} diet;

struct ZOO {
    char name[128];
    char nick[128];
    diet _diet[];


};

int main () {
    ZOO Oleg = ZOO {
        "Oleg",
        "Gega",
        {
            {"meat", 1}
        }
    };
    ZOO * he = &Oleg;

    printf(he->_diet->name);
    if (he->_diet->name == "meat") printf("\n%s кушац %s", Oleg.name, Oleg._diet->name);


    else printf("\nidk");
}