#ifndef XMLSERIALIZABLE_H_INCLUDED
#define XMLSERIALIZABLE_H_INCLUDED

#include <string>
#include <iostream>

using namespace std;

class XMLSerializable {
public:
	XMLSerializable() {}
	~XMLSerializable() {}

	virtual void dumpObject();
	virtual void dumpObjectData();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
};

#endif
 