#include "ireadable.hpp"

ostream& operator << (ostream& out, IReadable& readable){
    readable.print(out);
    return out;
}