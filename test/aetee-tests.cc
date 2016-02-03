#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <aetee/aetee.h>
#include <aetee/mathsugar.h>
#include <string>
#include <experimental/tuple>
#include <functional>

TEST(Aetee, TypeConstant)
{
    auto int_ct = aetee::type_c<int>;
    auto string_ct = aetee::type_c<std::string>;
    auto isPOD = [](auto t) { return std::is_pod<typename decltype(t)::type>::value; };
    bool int_is_pod = isPOD(int_ct);
    bool string_is_pod = isPOD(string_ct);
    EXPECT_TRUE(int_is_pod);
    EXPECT_FALSE(string_is_pod);
}

TEST(Aetee, Append)
{
    using aetee::operator<<;
    auto expected = std::make_tuple(1, 2, 3);
    auto actual = aetee::append(std::make_tuple(1, 2), 3);
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Prepend)
{
    auto expected = std::make_tuple(1, 2, 3);
    auto actual = aetee::prepend(std::make_tuple(2, 3), 1);
    EXPECT_EQ(expected, actual);
}

TEST(Aetee, Fold)
{
    auto expected = 10;
    auto actual = aetee::fold(std::make_tuple(1, 2, 3, 4), 0, std::plus<>{});
    EXPECT_EQ(expected, actual);
}
/*
TEST(Aetee, Zip)
{
    auto expected = std::make_tuple(std::make_tuple(1, 2), std::make_tuple(3, 4), std::make_tuple(5, 6));
    auto actual = aetee::zip(std::make_tuple(1, 3, 5), std::make_tuple(2, 4, 6));
    ASSERT_EQ(aetee::length(expected), aetee::length(actual));
    //EXPECT_EQ(expected, actual);
}
*/
