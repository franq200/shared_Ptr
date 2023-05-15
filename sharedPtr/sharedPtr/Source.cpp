#include "SharedPtr.h"
#include <iostream>

// only for memory leaks debugging
#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <stdlib.h>  
#include <crtdbg.h>   //for malloc and free

struct MyStruct
{
	MyStruct(int n) : number(n) { std::cout << "Struct c-tor " << number << "\n"; }
	~MyStruct() { std::cout << "Struct d-tor " << number << "\n"; }

	int number;
};

int main()
{
	
	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld); //take a snapshot
	/*
	{

		SharedPtr<MyStruct> shared_ptr(new MyStruct(112));
		SharedPtr<MyStruct> newShared(shared_ptr);
		shared_ptr = newShared;
		std::cout <<   (*newShared).number << "    " << (*shared_ptr).number;

		/*
		if(shared_ptr)
		{

		}
		

	}
	*/
	_CrtMemCheckpoint(&sNew); //take a snapshot 
	if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
	{
		OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
		_CrtMemDumpStatistics(&sDiff);
		OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
		_CrtMemDumpAllObjectsSince(&sOld);
		OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
		_CrtDumpMemoryLeaks();
	}
	
	
	SharedPtr<int> ptr(new int(5));
	
	if (ptr)
	{
		std::cout << "zwraca";
	}
	else
	{
		std::cout << "nie zwraca";
	}
	
	
	SharedPtr<int> ptr2(new int(5));
	
	std::cout << *(ptr.Get());
	std::cout << ptr.UseCount();
	ptr = ptr2;
	std::cout << *(ptr.Get());
	std::cout << ptr.UseCount();
	
	
	if (ptr == ptr2)
	{
		std::cout << "takie same";
	}
	else
	{
		std::cout << "inne";
	}
	
	return true;
}