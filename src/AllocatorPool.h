#pragma once
#include <memory>
#include <iostream>

namespace Core
{
	template <typename T>
	union AllocatorPoolChunk
	{
		T Chunk;
		AllocatorPoolChunk<T>* Next;

		AllocatorPoolChunk() {}; // erstellen der Virtual funtion table damit auch objekte mit Constructor und Destructor supported werden.
		~AllocatorPoolChunk() {};
	};

	template <typename T>
	class AllocatorPool
	{
	public:

		// TODO: Rule of 5!!!!

		explicit AllocatorPool(size_t pSize = 256) : mSize(pSize)  // explicit um casten zu verhindern. mSize wird sofort mit dem wert von pSize befüllt
		{
			mChunkArray = new AllocatorPoolChunk<T>[mSize]; // erstellt das Array der Chunks
			mChunkHead = mChunkArray;

			for (size_t i = 0; i < mSize -1; ++i)
				mChunkArray[i].Next = std::addressof(mChunkArray[i + 1]);

			mChunkArray[mSize - 1].Next = nullptr;

		}
		
		~AllocatorPool()
		{
			if (mCounter != 0)
			{
				std::cout << "Nicht alle / Zu viele Elemente wurden freigegeben. Counter: " << mCounter << std::endl;
				__debugbreak();
			}

			mChunkHead = nullptr;
			delete[] mChunkArray;
			mChunkArray = nullptr;
		}



		// TODO : Objekte mit Constructor erlauben plx
		T* Alloc()
		{
			if (mChunkHead == nullptr)
			{
				std::cerr << "Nööö, kein platz mehr :(";
				__debugbreak();
				return nullptr;
			}


			AllocatorPoolChunk<T>* mHeadOld = mChunkHead;
			mChunkHead = mChunkHead->Next;

			T* mReturnChunk = new (std::addressof(mHeadOld->Chunk)) T;
			++mCounter;
			return mReturnChunk;
		}

		void DeAlloc(T* pChunkToDeallocate)
		{
			pChunkToDeallocate->~T();
			AllocatorPoolChunk<T>* mTempChunk = reinterpret_cast<AllocatorPoolChunk<T>*>(pChunkToDeallocate);
			mTempChunk->Next = mChunkHead;
			mChunkHead = mTempChunk;
			--mCounter;
		}



	private:
		size_t mSize; // anzahl aller chunks
		AllocatorPoolChunk<T>* mChunkArray; //zeiger auf das Array aller chunks
		AllocatorPoolChunk<T>* mChunkHead; // Zeiger für aktuelles leeres chunk
		int16_t mCounter;
	};


}

