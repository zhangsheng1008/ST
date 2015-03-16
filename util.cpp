//---------------------------------------------------------------------------


#pragma hdrstop

#include "util.h"
#include "boost/regex.hpp"
#include <Forms.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <StdCtrls.hpp>
#include <sstream>
#include <iostream>
//---------------------------------------------------------------------------

#pragma package(smart_init)
using namespace std;

String _fastcall paraProcess(String src, String para[]){
	boost::regex reg("(\\{\\d\\.\\d\\})|(\\{\\d\\})");
	int i = 1;
	boost::smatch m;
	String strRep;
	String result = src;
	std::string s = src.t_str();
	std::string::const_iterator it = s.begin();
	std::string::const_iterator end = s.end();
	String reg_last;
	while(boost::regex_search(it, end, m, reg)){
	  int k,j;
	  String paraDes;
	  if (m[1].matched) {
		 paraDes = (m[0].str()).c_str();
		 j = StrToInt(paraDes[2]) - 1;
		 k = StrToInt(paraDes[4]);
		 result = StringReplace(result, paraDes, para[j][k], TReplaceFlags(rfReplaceAll));
	  } else {
		 paraDes = (m[2].str()).c_str();
		 j = StrToInt(paraDes[2]) - 1;
		 strRep = para[j];
		 result = StringReplace(result, paraDes, para[j], TReplaceFlags(rfReplaceAll));
	  }
	  it = m[0].second;
	  i++;
	}

	return result;


}

TStringList* _fastcall regexMap(String src, String regex){
	boost::regex reg(regex.t_str());
	boost::smatch m;
	TStringList *res = new TStringList();
	std::string s = src.t_str();
	std::string::const_iterator it = s.begin();
	std::string::const_iterator end = s.end();
	if(boost::regex_search(it, end, m, reg)){
		for (unsigned int i = 0; i < m.size(); i++) {
			if (m[i+1].matched)
				res->Append(m[i+1].str().c_str());

		}
	}
	return res;

}

void _fastcall initContent(TForm *form, String prefix, String content){
	String name;
	int idx;
	TStringList *s = new TStringList();
	s->Delimiter = ',';
	s->DelimitedText = content;
	for (int i= 0; i < form->ComponentCount - 1; i++) {
		if(GetPropInfo(form->Components[i], "Name")){
			name = GetStrProp(form->Components[i], "Name");
			if(name.SubString(0, prefix.Length()) == prefix){
            	idx = StrToInt(name[name.Length() - 1]);
				if(GetPropInfo(form->Components[i], "Text"))
					SetStrProp(form->Components[i], "Text", (*s)[idx-1]);
				if(GetPropInfo(form->Components[i], "Caption"))
					SetStrProp(form->Components[i], "Caption", (*s)[idx-1]);
		}
	 }
   }

}

int convertStrToHex(string str){
	std::stringstream ss;
	unsigned int x;
	ss << std::hex <<str;
	ss >> x;
	return x;
}


unsigned char* convertHexCommand(String cmd, unsigned int* len){
	boost::regex reg(HEX_REGEX);
	boost::smatch m;
	std::string s = cmd.t_str();
	std::string::const_iterator it = s.begin();
	std::string::const_iterator end = s.end();
	*len = 0;
	while(boost::regex_search(it, end, m, reg)){
	  it = m[0].second;
	  *len = *len + 1 ;
	}
	it = s.begin();
	int vLen = *len;
	unsigned char *c = new unsigned char[vLen];
	int i = 0;
	while(boost::regex_search(it, end, m, reg)){
	  if (m[1].matched)
		 c[i] = (convertStrToHex(m[1].str()));
	  it = m[0].second;
	  i++;
	}
	return c;
}

String convertHexResult(unsigned char* buf, int len){
	String res;
	for (int i = 0; i < len; i++) {
	   res = res + IntToHex(buf[i], 2);
	}
	return res;
}
