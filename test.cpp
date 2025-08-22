// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
// Author: Austin Donaubauer
// Date: 7/26/2025 

class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
 //TEST_F(CollectionTest, AlwaysFail)
 //{
 //    FAIL();
 //}

 // TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    EXPECT_TRUE(!collection->empty());

    // if not empty, what must the size be?
    EXPECT_EQ(collection->size(), 1) << "Collection Added 1 value";
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{

    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(5);

    // is the collection still empty after adding 5 values
    EXPECT_TRUE(!collection->empty());

    // Size of collection is 5
    EXPECT_EQ(collection->size(), 5) << "Collection Added 5 values";

}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeIsGreaterThanOrEqual) {

    // Max Size for size 0
    // Assert that current size of the collection is 0
    ASSERT_EQ(collection->size(), 0);
    // Assert that max size is greater than the size of the collection
    ASSERT_GE(collection->max_size(), collection->size()) << "Collection MaxSize greater than Collection size";


    // Max size for size 1
    add_entries(1);

    // Assert that current size of the collection is 1
    ASSERT_EQ(collection->size(), 1);
    // Assert that max size is greater than the size of the collection
    ASSERT_GE(collection->max_size(), collection->size()) << "Collection MaxSize greater than Collection size";

    // Max size for size 5
    add_entries(4);

    // Assert that current size of the collection is 5
    ASSERT_EQ(collection->size(), 5);
    // Assert that max size is greater than the size of the collection
    ASSERT_GE(collection->max_size(), collection->size()) << "Collection MaxSize greater than Collection size";

    // Max size for size 10
    add_entries(5);

    // Assert that current size of the collection is 10
    ASSERT_EQ(collection->size(), 10);
    // Assert that max size is greater than the size of the collection
    ASSERT_GE(collection->max_size(), collection->size()) << "Collection MaxSize greater than Collection size";

}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityIsGreaterThanOrEqual) {

    // Capacity for size 0
    // Assert that current size of the collection is 0
    ASSERT_EQ(collection->size(), 0);
    // Assert that capacity is greater than the size of the collection
    ASSERT_GE(collection->capacity(), collection->size()) << "Collection Capacity greater than Collection size";

    // Capacity for size 1
    add_entries(1);

    // Assert that current size of the collection is 1
    ASSERT_EQ(collection->size(), 1);
    // Assert that capacity is greater than the size of the collection
    ASSERT_GE(collection->capacity(), collection->size()) << "Collection Capacity greater than Collection size";

    // Capacity for size 5
    add_entries(4);

    // Assert that current size of the collection is 5
    ASSERT_EQ(collection->size(), 5);
    // Assert that capacity is greater than the size of the collection
    ASSERT_GE(collection->capacity(), collection->size()) << "Collection Capacity greater than Collection size";

    // Capacity for size 10
    add_entries(5);

    // Assert that current size of the collection is 10
    ASSERT_EQ(collection->size(), 10);
    // Assert that capacity is greater than the size of the collection
    ASSERT_GE(collection->capacity(), collection->size()) << "Collection Capacity greater than Collection size";

}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizingCollectionIncreases) {

    // Add entries
    add_entries(3);

    // Get current size of the collection to compare after resize
    size_t previousSize = collection->size();

    // Resize collection
    collection->resize(5);

    // Assert that collection was resized to a greater size that the previous size
    ASSERT_TRUE(collection->size() > previousSize) << "Collection Resized to increase collection size";

}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizingCollectionDescreases) {

    // Add entries
    add_entries(3);

    // Get current size of the collection to compare after resize
    size_t previousSize = collection->size();

    //resize collection
    collection->resize(2);

    // Assert that collection was resized to a less size that the previous size
    ASSERT_TRUE(collection->size() < previousSize) << "Collection Resized to decrease collection size";

}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizingCollectionToZero) {

    // Add entries
    add_entries(3);

    // Get current size of the collection to compare after resize
    size_t previousSize = collection->size();

    // Resize collection
    collection->resize(0);

    // Assert that resize adjusted collection to size 0
    ASSERT_TRUE(collection->size() == 0) << "Collection Resized to 0";

}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearCollection) {

    // Add entries to collection
    add_entries(5);

    // Assert that collection size is now 5 after add entries
    ASSERT_EQ(collection->size(), 5);

    // Clear collection of entries
    collection->clear();

    // Assert that after clear, the size of the collection is now 0
    ASSERT_EQ(collection->size(), 0) << "Collection Cleared";

}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseCollection) {

    // Add entries to collection
    add_entries(5);

    // Assert that there are now values in the vector after add entries
    ASSERT_EQ(collection->size(), 5);

    // Erase collection begin and end
    collection->erase(collection->begin(), collection->end());

    // Asserts that after erase, the size of the vector is now 0 because erase erased the collection entries
    ASSERT_EQ(collection->size(), 0);



}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveCollection) {

    // Add Entries to collection
    add_entries(5);

    // Get current values of collection for size and capacity to compare
    // to values after reserve
    size_t previousSize = collection->size();
    size_t previousCapacity = collection->capacity();

    // Reserve
    collection->reserve(10);

    // Asserts that the size of the collectin is still the same after reserve
    ASSERT_TRUE(collection->size() == previousSize);

    // Asserts that capacity has increased and is now greater than the previous capacity
    ASSERT_TRUE(collection->capacity() > previousCapacity);

}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeException) {

    add_entries(5);

    // Test that std::out_of_range exception is thrown
    EXPECT_THROW(collection->at(6), std::out_of_range);

}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
TEST_F(CollectionTest, SwapCollectionEntry) {

    add_entries(5);

    // Create local vector to test swap
    std::vector<int> anotherCollectionToSwap(10, 10);

    // Assert that the collection swap has not occurred yet
    ASSERT_EQ(collection->size(), 5);

    // Swap the collection for the other collection
    collection->swap(anotherCollectionToSwap);

    // Assert that the collection swap occurred
    ASSERT_EQ(collection->size(), 10);

    // Assert that the collection swap occurred
    ASSERT_EQ(anotherCollectionToSwap.size(), 5);

}

TEST_F(CollectionTest, OutOfRangeExceptionOnEmptyCollection) {

    // Expect out of range exception to be thrown if collection is 
    // attempted to be accessed at any index
    // Testing edge case of accessing an index of an empty collection (vector)
    EXPECT_THROW(collection->at(0), std::out_of_range);

}