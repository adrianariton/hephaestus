#include "Greek.h"

Greek::Greek(std::string __name_or_index){
    get_greek_unicode(__name_or_index, unicode_value, lettername);
}

std::ostream& operator<<(std::ostream& os, Greek& nr){
    os<<(nr.unicode_value);
    return os;
}