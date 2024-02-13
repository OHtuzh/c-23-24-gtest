#include "lib/algorithm.hpp"

#include <gtest/gtest.h>

#include <vector>
#include <string>

struct IsEven {
    bool operator()(int i) const {
        return i % 2 == 0;
    }
};

struct ConcatOnlySmallStringsOperator {
    std::string operator()(const std::string& init, const std::string& cur) {
        if (cur.length() > 10) {
            return init;
        }
        return init + cur;
    }
};

TEST(FIND, FOUND) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    ASSERT_EQ(ohtuzh::find(v.begin(), v.end(), 3), v.begin() + 2);
}

TEST(FIND, NOT_FOUND) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    ASSERT_EQ(ohtuzh::find(v.begin(), v.end(), 6), v.end());
}

TEST(FIND_IF, FOUND) {
    std::vector<int> v = {1, 2, 3};
    ASSERT_EQ(ohtuzh::find_if(v.begin(), v.end(), IsEven{}), v.begin() + 1);
}

TEST(FIND_IF, NOT_FOUND) {
    std::vector<int> v = {1, 3, 5};
    ASSERT_EQ(ohtuzh::find_if(v.begin(), v.end(), IsEven{}), v.end());
}

TEST(ACCUMULATE, EMPTY) {
    std::vector<int> v;
    const int kInitValue = 25;
    ASSERT_EQ(ohtuzh::accumulate(v.begin(), v.end(), kInitValue), kInitValue);
}

TEST(ACCUMULATE, SUM_NUMBERS) {
    std::vector<int> v = {1, 2, 3};
    const int kInitValue = 0;
    ASSERT_EQ(ohtuzh::accumulate(v.begin(), v.end(), kInitValue), kInitValue + 1 + 2 + 3);
}

TEST(ACCUMULATE, CONCAT_ONLY_SMALL_STRINGS) {
    std::vector<std::string> v = {
        "small1",
        "hugehugehugehugehuge",
        "hugehugehugehugehuge",
        "small2",
        "small3",
        "hugehugehugehugehuge",
        "hugehugehugehugehuge"
    };
    const std::string kInitString = "init";
    ASSERT_EQ(ohtuzh::accumulate(v.begin(), v.end(), kInitString, ConcatOnlySmallStringsOperator{}), kInitString + "small1small2small3");
}
