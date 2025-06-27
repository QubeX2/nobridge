#include "pbn.h"

#include "mika.h"
#include "parser.h"
namespace nobridge::pbn {

    GameL processFile(std::string const& path) {
        Reader reader(path);
        Parser parser(reader);
        GameL games = parser.run();
        reader.close();
        return games;
    }

}  // namespace nobridge::pbn
