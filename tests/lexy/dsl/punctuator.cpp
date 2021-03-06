// Copyright (C) 2020 Jonathan Müller <jonathanmueller.dev@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include <lexy/dsl/punctuator.hpp>

#include <doctest/doctest.h>

TEST_CASE("dsl punctuators")
{
    CHECK(std::is_same_v<const decltype(LEXY_LIT(".")), decltype(lexy::dsl::period)>);
    CHECK(std::is_same_v<const decltype(LEXY_LIT(",")), decltype(lexy::dsl::comma)>);
    CHECK(std::is_same_v<const decltype(LEXY_LIT(":")), decltype(lexy::dsl::colon)>);
    CHECK(std::is_same_v<const decltype(LEXY_LIT(";")), decltype(lexy::dsl::semicolon)>);

    CHECK(std::is_same_v<const decltype(LEXY_LIT("-")), decltype(lexy::dsl::hyphen)>);
    CHECK(std::is_same_v<const decltype(LEXY_LIT("/")), decltype(lexy::dsl::slash)>);
    CHECK(std::is_same_v<const decltype(LEXY_LIT("\\")), decltype(lexy::dsl::backslash)>);
    CHECK(std::is_same_v<const decltype(LEXY_LIT("'")), decltype(lexy::dsl::apostrophe)>);

    CHECK(std::is_same_v<const decltype(LEXY_LIT("#")), decltype(lexy::dsl::hash_sign)>);
    CHECK(std::is_same_v<const decltype(LEXY_LIT("$")), decltype(lexy::dsl::dollar_sign)>);
    CHECK(std::is_same_v<const decltype(LEXY_LIT("@")), decltype(lexy::dsl::at_sign)>);
}

