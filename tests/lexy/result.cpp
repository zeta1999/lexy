// Copyright (C) 2020 Jonathan Müller <jonathanmueller.dev@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include <lexy/result.hpp>

#include <doctest/doctest.h>
#include <string>

TEST_CASE("result")
{
    SUBCASE("trivial")
    {
        constexpr lexy::result<int, int> def;
        CHECK(!def);
        CHECK(!def.has_value());
        CHECK(def.has_error());
        CHECK(def.error() == 0);

        constexpr lexy::result<int, int> val(lexy::result_value, 42);
        CHECK(val);
        CHECK(val.has_value());
        CHECK(!val.has_error());
        CHECK(val.value() == 42);

        constexpr lexy::result<int, int> err(lexy::result_error, 42);
        CHECK(!err);
        CHECK(!err.has_value());
        CHECK(err.has_error());
        CHECK(err.error() == 42);

        constexpr lexy::result<short, int> conv_err(err);
        CHECK(!conv_err);
        CHECK(!conv_err.has_value());
        CHECK(conv_err.has_error());
        CHECK(conv_err.error() == 42);
    }
    SUBCASE("non-trivial")
    {
        auto check_value = [](const auto& res, const char* value) {
            CHECK(res);
            CHECK(res.has_value());
            CHECK(!res.has_error());
            CHECK(res.value() == value);
        };
        auto check_error = [](const auto& res, const char* error) {
            CHECK(!res);
            CHECK(!res.has_value());
            CHECK(res.has_error());
            CHECK(res.error() == error);
        };

        lexy::result<std::string, std::string> def;
        check_error(def, "");

        lexy::result<std::string, std::string> val(lexy::result_value,
                                                   "a somewhat long string against SSO");
        check_value(val, "a somewhat long string against SSO");

        lexy::result<std::string, std::string> err(lexy::result_error,
                                                   "a somewhat long string against SSO");
        check_error(err, "a somewhat long string against SSO");

        lexy::result<int, std::string> conv_err(err);
        check_error(conv_err, "a somewhat long string against SSO");

        SUBCASE("move ctor - value")
        {
            const auto moved = LEXY_MOV(val);
            check_value(moved, "a somewhat long string against SSO");
            check_value(val, "");
        }
        SUBCASE("move ctor - error")
        {
            const auto moved = LEXY_MOV(err);
            check_error(moved, "a somewhat long string against SSO");
            check_error(err, "");
        }
        SUBCASE("move assign - value = value")
        {
            lexy::result<std::string, std::string> val2(lexy::result_value,
                                                        "another somewhat long string, again SSO");
            check_value(val2, "another somewhat long string, again SSO");

            val2 = LEXY_MOV(val);
            check_value(val2, "a somewhat long string against SSO");
            check_value(val, "");
        }
        SUBCASE("move assign - value = error")
        {
            lexy::result<std::string, std::string> val2(lexy::result_value,
                                                        "another somewhat long string, again SSO");
            check_value(val2, "another somewhat long string, again SSO");

            val2 = LEXY_MOV(err);
            check_error(val2, "a somewhat long string against SSO");
            check_error(err, "");
        }
        SUBCASE("move assign - error = value")
        {
            lexy::result<std::string, std::string> err2(lexy::result_error,
                                                        "another somewhat long string, again SSO");
            check_error(err2, "another somewhat long string, again SSO");

            err2 = LEXY_MOV(val);
            check_value(err2, "a somewhat long string against SSO");
            check_value(val, "");
        }
        SUBCASE("move assign - error = error")
        {
            lexy::result<std::string, std::string> err2(lexy::result_error,
                                                        "another somewhat long string, again SSO");
            check_error(err2, "another somewhat long string, again SSO");

            err2 = LEXY_MOV(err);
            check_error(err2, "a somewhat long string against SSO");
            check_error(err, "");
        }
    }
}

TEST_CASE("result<int, void>")
{
    CHECK(lexy::result<int, void>::has_void_error());

    constexpr lexy::result<int, void> def;
    CHECK(!def);
    CHECK(!def.has_value());
    CHECK(def.has_error());

    constexpr lexy::result<int, void> val(lexy::result_value, 42);
    CHECK(val);
    CHECK(val.has_value());
    CHECK(!val.has_error());
    CHECK(val.value() == 42);

    constexpr lexy::result<int, void> err(lexy::result_error);
    CHECK(!err);
    CHECK(!err.has_value());
    CHECK(err.has_error());
}

TEST_CASE("result<void, int>")
{
    CHECK(lexy::result<void, int>::has_void_value());

    constexpr lexy::result<void, int> def;
    CHECK(!def);
    CHECK(!def.has_value());
    CHECK(def.has_error());
    CHECK(def.error() == 0);

    constexpr lexy::result<void, int> val(lexy::result_value);
    CHECK(val);
    CHECK(val.has_value());
    CHECK(!val.has_error());

    constexpr lexy::result<void, int> err(lexy::result_error, 42);
    CHECK(!err);
    CHECK(!err.has_value());
    CHECK(err.has_error());
    CHECK(err.error() == 42);
}

