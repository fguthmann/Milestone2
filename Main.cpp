#include "Main.h"


using namespace std ;

int main(int argc, char *argv[]) {
    try {
        boot::Main().main(stoi(argv[1]));
    } catch (char const* e) {
        cout << e << endl;
    }
    return 0;
}