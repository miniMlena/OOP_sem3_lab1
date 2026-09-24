#include <gtest/gtest.h>
#include "array_ops.h"

TEST(ArrayCreateTest, CreateSize5) {
    int* a = array_create(5);
    ASSERT_NE(a, nullptr);
    for (std::size_t i = 0; i < 5; i++) {
        EXPECT_EQ(a[i], 0);
    }
    array_delete(a);
}

TEST(ArrayCreateTest, CreateEmpty) {
    int* a = array_create(0);
    EXPECT_EQ(a, nullptr);
    array_delete(a);
}

TEST(ArrayResizeTest, ResizeLarger) {
    std::size_t s = 3;
    int* a = array_create(s);
    a[0] = 1; a[1] = 2; a[2] = 3;
    
    a = array_resize(a, s, 5);
    
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 3);
    EXPECT_EQ(a[3], 0);
    EXPECT_EQ(a[4], 0);
    array_delete(a);
}

TEST(ArrayResizeTest, ResizeSmaller) {
    std::size_t s = 5;
    int* a = array_create(s);
    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4; a[4] = 5;
    
    a = array_resize(a, s, 3);
    
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 3);
    
    array_delete(a);
}

TEST(ArrayResizeTest, ResizeToZero) {
    std::size_t s = 5;
    int* a = array_create(s);
    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4; a[4] = 5;
    
    a = array_resize(a, s, 0);
    
    EXPECT_EQ(a, nullptr);
}

TEST(ArrayResizeTest, ResizeFromZero) {
    std::size_t s = 0;
    int* a = nullptr;
    
    a = array_resize(a, s, 5);
    
    EXPECT_EQ(a, nullptr);
}

TEST(ArrayInsertTest, InsertInMiddle) {
    std::size_t s = 5;
    int* a = array_create(s);
    a = array_insert(a, s, 3, 10);
    EXPECT_EQ(s, 6);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 3);
    EXPECT_EQ(a[3], 10);
    EXPECT_EQ(a[4], 4);
    EXPECT_EQ(a[5], 5);
    array_delete(a);
}

TEST(ArrayInsertTest, InsertAtBeginning) {
    std::size_t s = 3;
    int* a = array_create(s);
    a[0] = 1; a[1] = 2; a[2] = 3;
    
    a = array_insert(a, s, 0, 99);
    
    EXPECT_EQ(s, 4);
    EXPECT_EQ(a[0], 99);
    EXPECT_EQ(a[1], 1);
    EXPECT_EQ(a[2], 2);
    EXPECT_EQ(a[3], 3);
    array_delete(a);
}

TEST(ArrayInsertTest, InsertAtEnd) {
    std::size_t s = 3;
    int* a = array_create(s);
    a[0] = 1; a[1] = 2; a[2] = 3;
    
    a = array_insert(a, s, 3, 99);
    
    EXPECT_EQ(s, 4);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 3);
    EXPECT_EQ(a[3], 99);
    array_delete(a);
}

TEST(ArrayInsertTest, InsertNullptr) {
    std::size_t s = 0;
    int* a = array_insert(nullptr, s, 0, 10);
    EXPECT_EQ(a, nullptr);
    EXPECT_EQ(s, 0);
}

TEST(ArrayRemoveTest, RemoveFromMiddle) {
    std::size_t s = 5;
    int* a = array_create(s);
    a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4; a[4] = 5;
    
    a = array_remove(a, s, 2);
    
    EXPECT_EQ(s, 4);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 4);
    EXPECT_EQ(a[3], 5);
    array_delete(a);
}

TEST(ArrayRemoveTest, RemoveFirst) {
    std::size_t s = 3;
    int* a = array_create(s);
    a[0] = 1; a[1] = 2; a[2] = 3;
    
    a = array_remove(a, s, 0);
    
    EXPECT_EQ(s, 2);
    EXPECT_EQ(a[0], 2);
    EXPECT_EQ(a[1], 3);
    array_delete(a);
}

TEST(ArrayRemoveTest, RemoveLast) {
    std::size_t s = 3;
    int* a = array_create(s);
    a[0] = 1; a[1] = 2; a[2] = 3;
    
    a = array_remove(a, s, 2);
    
    EXPECT_EQ(s, 2);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    array_delete(a);
}

TEST(ArrayRemoveTest, RemoveFromEmpty) {
    std::size_t s = 0;
    int* a = nullptr;
    
    int* result = array_remove(a, s, 0);
    
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(s, 0);
}

TEST(ArrayRemoveTest, RemoveOnlyElement) {
    std::size_t s = 1;
    int* a = array_create(s);
    a[0] = 8;
    
    a = array_remove(a, s, 0);
    
    EXPECT_EQ(a, nullptr);
    EXPECT_EQ(s, 0);
}

TEST(ArrayPrintTest, PrintNonEmpty) {
    int* a = array_create(5);
    a[0] = 5; a[1] = 4; a[2] = 3; a[3] = 2; a[4] = 1;
    testing::internal::CaptureStdout();
    array_print(a, 5);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
    EXPECT_NE(output.find("4"), std::string::npos);
    EXPECT_NE(output.find("5"), std::string::npos);
    array_delete(a);
}

TEST(ArrayPrintTest, PrintNullptr) {
    testing::internal::CaptureStdout();
    array_print(nullptr, 0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST(ArrayDeleteTest, DeleteAndNullify) {
    int* a = array_create(5);
    ASSERT_NE(a, nullptr);
    array_delete(a);
    EXPECT_EQ(a, nullptr);
}

TEST(ArrayDeleteTest, DeleteNullptr) {
    int* a = nullptr;
    array_delete(a);
    EXPECT_EQ(a, nullptr);
}

TEST(ArrayKthSmallestTest, KthSmallestHappyPath) {
    std::size_t s = 6;
    int* a = array_create(s);
    a[0] = 5; a[1] = 2; a[2] = 9; a[3] = 1; a[4] = 5; a[5] = 6;
    
    EXPECT_EQ(array_kth_smallest(a, s, 1), 1);
    EXPECT_EQ(array_kth_smallest(a, s, 2), 2);
    EXPECT_EQ(array_kth_smallest(a, s, 3), 5);
    EXPECT_EQ(array_kth_smallest(a, s, 4), 5);
    EXPECT_EQ(array_kth_smallest(a, s, 5), 6);
    EXPECT_EQ(array_kth_smallest(a, s, 6), 9);
    
    array_delete(a);
}

TEST(ArrayKthSmallestTest, KthSmallestSingleElement) {
    std::size_t s = 1;
    int* a = array_create(s);
    a[0] = 8;
    
    EXPECT_EQ(array_kth_smallest(a, s, 1), 8);
    
    array_delete(a);
}

TEST(ArrayKthSmallestTest, KthSmallestEmpty) {
    std::size_t s = 0;
    int* a = nullptr;
    
    testing::internal::CaptureStdout();
    array_kth_smallest(a, s, 1);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST(ArrayKthSmallestTest, KthSmallestDoesNotModifyOriginal) {
    std::size_t s = 5;
    int* a = array_create(s);
    a[0] = 3; a[1] = 1; a[2] = 4; a[3] = 1; a[4] = 5;
    array_kth_smallest(a, s, 3);
    
    EXPECT_EQ(a[0], 3);
    EXPECT_EQ(a[1], 1);
    EXPECT_EQ(a[2], 4);
    EXPECT_EQ(a[3], 1);
    EXPECT_EQ(a[4], 5);
    
    array_delete(a);
}