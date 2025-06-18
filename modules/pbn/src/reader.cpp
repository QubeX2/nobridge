#include "reader.h"

#include <fstream>
#include <iostream>
#include <string>

namespace nobridge::pbn {

    Reader::Reader(std::string filename) {
        m_filename = filename;
        m_file.open(filename);
        m_eof = false;
        m_ok = static_cast<bool>(m_file.is_open());
    }

    void Reader::close() {
        if (m_file.is_open()) {
            m_file.close();
            m_ok = false;
            m_eof = true;
        }
    }

    std::string Reader::lastLine() { return m_last_line; }

    std::string Reader::line() { return m_line; }

    std::string Reader::nextLine() {
        if (!m_file.is_open()) {
            m_ok = false;
            m_eof = true;
            return "";
        }

        if (!m_file.eof()) {
            std::getline(m_file, m_line);
            m_last_line = m_line;
            return m_line;
        } else {
            m_eof = true;
            return "";
        }
    }

}  // namespace nobridge::pbn
