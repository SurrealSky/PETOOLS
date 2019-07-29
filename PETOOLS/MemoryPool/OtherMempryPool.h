#pragma once
class COptex
{
public:
	COptex()		{ InitializeCriticalSection(&cs); }
	~COptex()		{ DeleteCriticalSection(&cs);	  }
public:
	void Enter()	{ EnterCriticalSection(&cs); }
	void Leave()	{ LeaveCriticalSection(&cs); }
private:
	CRITICAL_SECTION cs;
};

class CObjectLock
{
public:
	CObjectLock(COptex& lock) : m_lock(lock) { m_lock.Enter();}
	~CObjectLock() { m_lock.Leave(); }
private:
	COptex& m_lock;
};

class CMemPool
{
private:
	DWORD m_dwDefPoolSize;
	DWORD m_dwDefBlockSize;
	DWORD m_dwDefIncrease;
	COptex m_Lock;
	std::map<LPSTR, DWORD> m_mapUsed;
	std::map<LPSTR, DWORD> m_mapFree;

	std::map<LPSTR, DWORD> m_mapBigUsed;
	std::map<LPSTR, DWORD> m_mapBigFree;
public:
	CMemPool():m_dwDefPoolSize(100), m_dwDefBlockSize(0x10000), m_dwDefIncrease(10) {	}
	virtual ~CMemPool()		{ FreeAll(); }
	virtual void  Release() { delete this; }

	virtual DWORD GetDefPoolSize()  { return m_dwDefPoolSize; }
	virtual DWORD GetDefBlockSize() { return m_dwDefBlockSize;}
	virtual DWORD GetDefIncrease()  { return m_dwDefIncrease; }

	virtual void  SetDefault(DWORD dwdefPoolSize, DWORD dwdefBlockSize, DWORD dwdefIncrease) 
	{
		m_dwDefPoolSize = dwdefPoolSize;
		m_dwDefBlockSize = dwdefBlockSize;
		m_dwDefIncrease  = dwdefIncrease;
		AddBlock(dwdefPoolSize, dwdefBlockSize);
	}

	void AddBlock(DWORD dwSize, DWORD dwBlockSize)
	{
		//CObjectLock lock(m_Lock);
		for (DWORD idx=0; idx<dwSize; idx++)
		{
			char* p = NULL;
			try
			{
				p = new char[dwBlockSize];
			}
			catch (...) { p = NULL; }
			if (p != NULL)
			{
				m_mapFree.insert(std::make_pair(p, dwBlockSize));
			}
			else
			{
				//throw std::bad_alloc("memory alloc fail.");
				OutputDebugString(TEXT("netlayer.alloc memory fail."));
			}
		}
	}

	virtual void* Alloc(DWORD dwSize)
	{
		CObjectLock lock(m_Lock);


		if (dwSize <= m_dwDefBlockSize) //|| dwSize == 0 
		{
			if (m_mapFree.size() == 0)
			{
				AddBlock(m_dwDefIncrease, m_dwDefBlockSize);
			}
			if (m_mapFree.size() == 0)
				return NULL;
			std::map<LPSTR, DWORD>::iterator it = m_mapFree.begin();
			std::pair<LPSTR, DWORD> p = *it;
			m_mapFree.erase(it);
			m_mapUsed.insert(p);
			return p.first;
		}
		else
		{
			std::map<LPSTR, DWORD>::iterator it = m_mapBigFree.begin();
			for (; it != m_mapBigFree.end(); it++)
			{
				if (it->second >= dwSize)
				{
					std::pair<LPSTR, DWORD> p = *it;
					m_mapBigUsed.insert(*it);
					m_mapBigFree.erase(it);
					return p.first;
				}
			}

			DWORD dwBlockSize = ((dwSize/m_dwDefBlockSize)+1) * m_dwDefBlockSize;
			char* p = new char[dwBlockSize];
			m_mapBigUsed.insert(std::make_pair(p, dwBlockSize));

			return p;
		}
	}

	virtual void Free(void* pBlock)
	{
		CObjectLock lock(m_Lock);


		std::map<LPSTR, DWORD>::iterator it = m_mapUsed.find((LPSTR)pBlock);
		if (it != m_mapUsed.end())
		{
			std::pair<LPSTR, DWORD> p = *it;
			m_mapUsed.erase(it);
			m_mapFree.insert(p);
			return ;
		}
		it = m_mapBigUsed.find((LPSTR)pBlock);
		if (it != m_mapBigUsed.end())
		{
			std::pair<LPSTR, DWORD> p = *it;
			m_mapBigUsed.erase(it);
			m_mapBigFree.insert(p);
		}
	}

	virtual void FreeAll()
	{
		CObjectLock lock(m_Lock);
		try 
		{
			std::map<LPSTR, DWORD>::iterator it = m_mapFree.begin();
			for (; it != m_mapFree.end(); it++)
			{
				delete [](it->first);
			}
			m_mapFree.clear();
			for (it=m_mapUsed.begin(); it != m_mapUsed.end(); it++)
			{
				delete [](it->first);
			}
			m_mapUsed.clear();

			for (it=m_mapBigFree.begin(); it != m_mapBigFree.end(); it++)
			{
				delete [](it->first);
			}
			m_mapBigFree.clear();

			for (it=m_mapBigUsed.begin(); it != m_mapBigUsed.end(); it++)
			{
				delete [](it->first);
			}
			m_mapBigUsed.clear();
		}
		catch (...) { }
	}

	virtual DWORD GetBufSize(void* pBlock)
	{
		CObjectLock lock(m_Lock);
		std::map<LPSTR, DWORD>::iterator it = m_mapFree.find((LPSTR)pBlock);
		if (it != m_mapFree.end())
			return it->second;

		it = m_mapUsed.find((LPSTR)pBlock);
		if (it != m_mapUsed.end())
			return it->second;

		it = m_mapBigFree.find((LPSTR)pBlock);
		if (it != m_mapBigFree.end())
			return it->second;

		it = m_mapBigUsed.find((LPSTR)pBlock);
		if (it != m_mapBigUsed.end())
			return it->second;

		return 0;
	}

	virtual BOOL  IsAllocFrom(void* pBlock)
	{
		CObjectLock lock(m_Lock);
		if (m_mapFree.find((LPSTR)pBlock) != m_mapFree.end())
			return TRUE;

		if (m_mapUsed.find((LPSTR)pBlock) != m_mapUsed.end())
			return TRUE;

		if (m_mapBigFree.find((LPSTR)pBlock) != m_mapBigFree.end())
			return TRUE;

		if (m_mapBigUsed.find((LPSTR)pBlock) != m_mapBigUsed.end())
			return TRUE;
		return FALSE;
	}
};