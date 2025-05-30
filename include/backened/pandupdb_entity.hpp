#ifndef PANUPDB_ENTITY_HPP
#define PANUPDB_ENTITY_HPP

#include <iostream>
#include <cstdint>

namespace Magic_Number {

    constexpr uint32_t make_magic(const char tag[4]) {
        return (static_cast<uint32_t>(tag[0]) << 24) |
               (static_cast<uint32_t>(tag[1]) << 16) |
               (static_cast<uint32_t>(tag[2]) << 8)  |
               (static_cast<uint32_t>(tag[3]));
    }

    constexpr uint32_t DATA    = make_magic("DBDF");
    constexpr uint32_t INDEX   = make_magic("DBIF");
    constexpr uint32_t CATALOG = make_magic("DBCT");

}

#endif