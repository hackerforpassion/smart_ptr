/*
 * Copyright (c) 2014 Glen Joseph Fernandes
 * glenfe at live dot com
 *
 * Distributed under the Boost Software License,
 * Version 1.0. (See accompanying file LICENSE_1_0.txt
 * or copy at http://boost.org/LICENSE_1_0.txt)
 */
#include <boost/config.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/smart_ptr/make_unique_array.hpp>

class type {
public:
    static unsigned int instances;

    explicit type() {
        instances++;
    }

    ~type() {
        instances--;
    }

private:
    type(const type&);
    type& operator=(const type&);
};

unsigned int type::instances = 0;

int main() {
#if !defined(BOOST_NO_CXX11_SMART_PTR)
    {
        std::unique_ptr<int[]> a1 = boost::make_unique<int[]>(3);
        BOOST_TEST(a1.get() != 0);
        BOOST_TEST(a1[0] == 0);
        BOOST_TEST(a1[1] == 0);
        BOOST_TEST(a1[2] == 0);
    }

    {
        std::unique_ptr<int[][2]> a1 = boost::make_unique<int[][2]>(2);
        BOOST_TEST(a1.get() != 0);
        BOOST_TEST(a1[0][0] == 0);
        BOOST_TEST(a1[0][1] == 0);
        BOOST_TEST(a1[1][0] == 0);
        BOOST_TEST(a1[1][1] == 0);
    }

    {
        std::unique_ptr<const int[]> a1 = boost::make_unique<const int[]>(3);
        BOOST_TEST(a1.get() != 0);
        BOOST_TEST(a1[0] == 0);
        BOOST_TEST(a1[1] == 0);
        BOOST_TEST(a1[2] == 0);
    }

    {
        std::unique_ptr<const int[][2]> a1 = boost::make_unique<const int[][2]>(2);
        BOOST_TEST(a1.get() != 0);
        BOOST_TEST(a1[0][0] == 0);
        BOOST_TEST(a1[0][1] == 0);
        BOOST_TEST(a1[1][0] == 0);
        BOOST_TEST(a1[1][1] == 0);
    }

    BOOST_TEST(type::instances == 0);
    {
        std::unique_ptr<type[]> a1 = boost::make_unique<type[]>(3);
        BOOST_TEST(a1.get() != 0);
        BOOST_TEST(type::instances == 3);
        a1.reset();
        BOOST_TEST(type::instances == 0);
    }

    BOOST_TEST(type::instances == 0);
    {
        std::unique_ptr<type[][2]> a1 = boost::make_unique<type[][2]>(2);
        BOOST_TEST(a1.get() != 0);
        BOOST_TEST(type::instances == 4);
        a1.reset();
        BOOST_TEST(type::instances == 0);
    }

    BOOST_TEST(type::instances == 0);
    {
        std::unique_ptr<const type[]> a1 = boost::make_unique<const type[]>(3);
        BOOST_TEST(a1.get() != 0);
        BOOST_TEST(type::instances == 3);
        a1.reset();
        BOOST_TEST(type::instances == 0);
    }

    BOOST_TEST(type::instances == 0);
    {
        std::unique_ptr<const type[][2]> a1 = boost::make_unique<const type[][2]>(2);
        BOOST_TEST(a1.get() != 0);
        BOOST_TEST(type::instances == 4);
        a1.reset();
        BOOST_TEST(type::instances == 0);
    }
#endif

    return boost::report_errors();
}
