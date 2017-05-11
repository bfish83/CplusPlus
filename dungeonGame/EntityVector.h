#ifndef _EntityVector_included_
#define _EntityVector_included_

#include "Tools.h"
#include "XMLSerializable.h"
#include <vector>
#include <functional>

using namespace std;

template<class T>
class EntityVector
{
public:
	void constructVector(vector<XMLSerializable*> & vVector)
	{
		for (auto pObject : vVector)
		{
			T * pT = dynamic_cast<T*>(pObject);

			if (pT != NULL)
			{
				m_vTs.push_back(pT);
			}
		}
	}

	T * generate(function<bool(T*)> pFunc)
	{
		vector<T*> vTemp;

		for (auto pT : m_vTs)
		{
			if (pFunc(pT))
			{
				vTemp.push_back(pT);
			}
		}

		if (vTemp.size() == 0)
			return NULL;

		return new T(*vTemp[Tools::randomValue(vTemp.size())]);

	}

private:
	vector<T*> m_vTs;
};


#endif



