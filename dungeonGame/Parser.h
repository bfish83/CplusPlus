#ifndef _parser_included_
#define _parser_included_

#include "XMLSerializable.h"
#include <map>
#include <functional>
#include <string>
#include <vector>

using namespace std;

void parseElement(map<string, function<XMLSerializable * ()>> & mConstructors, istream & input, string sPrefix, XMLSerializable * pObject, vector<XMLSerializable*> & vWorld);
void parseXML(map<string, function<XMLSerializable * ()>> & mConstructors, string sFilename, vector<XMLSerializable*> & vWorld);

#endif
