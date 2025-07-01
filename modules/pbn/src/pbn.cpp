#include "pbn.h"

#include "mika.h"
#include "parser.h"
namespace nobridge::pbn {

    TagML processFile(std::string const& path) {
        Reader reader(path);
        Parser parser(reader);
        TagML tagslist = parser.run();
        reader.close();
        return tagslist;
    }

}  // namespace nobridge::pbn
