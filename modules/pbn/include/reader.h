#ifndef PBNLIB_READER_H
#define PBNLIB_READER_H

#include <fstream>
#include <string>

namespace nobridge::pbn {

    class Reader {
       public:
        explicit Reader(std::string filename);
        std::string nextLine();
        std::string line();
        std::string lastLine();
        void close();
        bool eof() { return m_eof; }
        bool ok() { return m_ok; }

       private:
        std::ifstream m_file;
        std::string m_filename;
        std::string m_line;
        std::string m_last_line;
        bool m_eof;
        bool m_ok;
    };

}  // namespace nobridge::pbn

#endif
