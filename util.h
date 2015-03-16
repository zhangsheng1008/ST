//---------------------------------------------------------------------------

#ifndef utilH
#define utilH
#include <vcl.h>
#include <Forms.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <StdCtrls.hpp>
#include <iostream.h>
//---------------------------------------------------------------------------


const char* HEX_REGEX = "([0-9a-fA-F]{2}?)";

const String REG_LEFT_SYMBOL = "{";
const String REG_RIGHT_SYMBOL = "}";
String _fastcall paraProcess(String src, String para[]);
TStringList* _fastcall regexMap(String src, String regex);
void _fastcall initContent(TForm *form, String prefix, String content);
unsigned char* convertHexCommand(String cmd, unsigned int *len);
String convertHexResult(unsigned char* buf, int len);
#endif
