#include "pch.h"
#include "..\sharedPtr\SharedPtr.h"
#include <crtdbg.h>

class MemoryLeakDetector {
public:
    MemoryLeakDetector() {
        _CrtMemCheckpoint(&memState);
    }

    ~MemoryLeakDetector() {
        _CrtMemState stateNow, stateDiff;
        _CrtMemCheckpoint(&stateNow);
        int diffResult = _CrtMemDifference(&stateDiff, &memState, &stateNow);
        if (diffResult)
            reportFailure(stateDiff.lSizes[1]);
    }
private:
    void reportFailure(unsigned int unfreedBytes) {
        FAIL() << "Memory leak of " << unfreedBytes << " byte(s) detected.";
    }
    _CrtMemState memState;
};

class SharedPtrTests : public ::testing::Test
{
private:
    MemoryLeakDetector detector;
};

TEST_F(SharedPtrTests, GivenSharedPtr_WhenGetIsCalled_ThenItShouldReturnRawPointer)
{
	int* tempPtr = new int(3);
	SharedPtr<int> ptr(tempPtr);
	EXPECT_EQ(ptr.Get(), tempPtr);
}

TEST_F(SharedPtrTests, GivenSharedPtr_WhenSharedPtrIsCopiedIsCalled_ThenUseCountShouldReturnTwo__WhenSecondSharedPtrIsDeleted_ThenUseCountShouldReturnOne)
{
	SharedPtr<int> ptr(new int(3));
    EXPECT_EQ(ptr.UseCount(), 1);
    {
        SharedPtr<int> ptr2(ptr);
        EXPECT_EQ(ptr2.UseCount(), 2);
        EXPECT_EQ(ptr.UseCount(), 2);
    }
    EXPECT_EQ(ptr.UseCount(), 1);
}

TEST_F(SharedPtrTests, GivenPtrWithValue5_WhenResetIsCalled_ThenItShouldChangeValueAndCounter)
{
    SharedPtr<int> ptr(new int(3));
    ptr.Reset(new int(5));
    EXPECT_EQ(*(ptr.Get()), 5);
    EXPECT_EQ(ptr.UseCount(), 1);
}

TEST_F(SharedPtrTests, GivenSharedPtr_WhenMultiplicationOperatorIsCalled_ThenItShouldReturnValue)
{
    SharedPtr<int> ptr(new int(3));
    EXPECT_EQ(*ptr, 3);
}

TEST_F(SharedPtrTests, GivenTwoSharedPtrs_WhenAssignmentsOperatorIsCalled_ThenItShouldHaveEqualValue)
{
    SharedPtr<int> ptr(new int(3));
    SharedPtr<int> ptr2(new int(5));
    ptr = ptr2;
    EXPECT_EQ(ptr.Get(), ptr2.Get());
}