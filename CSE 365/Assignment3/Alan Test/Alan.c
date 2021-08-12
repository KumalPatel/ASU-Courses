#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// the following code is taken from https://github.com/superwills/NibbleAndAHalf/blob/master/NibbleAndAHalf/base64.h
/*
  https://github.com/superwills/NibbleAndAHalf
  base64.h -- Fast base64 encoding and decoding.
  version 1.0.0, April 17, 2013 143a
  Copyright (C) 2013 William Sherif
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.
  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:
  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
  William Sherif
  will.sherif@gmail.com
  YWxsIHlvdXIgYmFzZSBhcmUgYmVsb25nIHRvIHVz
*/



const static char* b64="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" ;

// maps A=>0,B=>1..
const static unsigned char unb64[]={
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //10 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //20 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //30 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //40 
  0,   0,   0,  62,   0,   0,   0,  63,  52,  53, //50 
 54,  55,  56,  57,  58,  59,  60,  61,   0,   0, //60 
  0,   0,   0,   0,   0,   0,   1,   2,   3,   4, //70 
  5,   6,   7,   8,   9,  10,  11,  12,  13,  14, //80 
 15,  16,  17,  18,  19,  20,  21,  22,  23,  24, //90 
 25,   0,   0,   0,   0,   0,   0,  26,  27,  28, //100 
 29,  30,  31,  32,  33,  34,  35,  36,  37,  38, //110 
 39,  40,  41,  42,  43,  44,  45,  46,  47,  48, //120 
 49,  50,  51,   0,   0,   0,   0,   0,   0,   0, //130 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //140 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //150 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //160 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //170 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //180 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //190 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //200 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //210 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //220 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //230 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //240 
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, //250 
  0,   0,   0,   0,   0,   0, 
}; // This array has 256 elements

// Converts binary data of length=len to base64 characters.
// Length of the resultant string is stored in flen
// (you must pass pointer flen).
char* base64( const void* binaryData, int len, int *flen )
{
  const unsigned char* bin = (const unsigned char*) binaryData ;
  char* res ;
  
  int rc = 0 ; // result counter
  int byteNo ; // I need this after the loop
  
  int modulusLen = len % 3 ;
  int pad = ((modulusLen&1)<<1) + ((modulusLen&2)>>1) ; // 2 gives 1 and 1 gives 2, but 0 gives 0.
  
  *flen = 4*(len + pad)/3 ;
  res = (char*) malloc( *flen + 1 ) ; // and one for the null
  if( !res )
  {
    puts( "ERROR: base64 could not allocate enough memory." ) ;
    puts( "I must stop because I could not get enough" ) ;
    return 0;
  }
  
  for( byteNo = 0 ; byteNo <= len-3 ; byteNo+=3 )
  {
    unsigned char BYTE0=bin[byteNo];
    unsigned char BYTE1=bin[byteNo+1];
    unsigned char BYTE2=bin[byteNo+2];
    res[rc++]  = b64[ BYTE0 >> 2 ] ;
    res[rc++]  = b64[ ((0x3&BYTE0)<<4) + (BYTE1 >> 4) ] ;
    res[rc++]  = b64[ ((0x0f&BYTE1)<<2) + (BYTE2>>6) ] ;
    res[rc++]  = b64[ 0x3f&BYTE2 ] ;
  }
  
  if( pad==2 )
  {
    res[rc++] = b64[ bin[byteNo] >> 2 ] ;
    res[rc++] = b64[ (0x3&bin[byteNo])<<4 ] ;
    res[rc++] = '=';
    res[rc++] = '=';
  }
  else if( pad==1 )
  {
    res[rc++]  = b64[ bin[byteNo] >> 2 ] ;
    res[rc++]  = b64[ ((0x3&bin[byteNo])<<4)   +   (bin[byteNo+1] >> 4) ] ;
    res[rc++]  = b64[ (0x0f&bin[byteNo+1])<<2 ] ;
    res[rc++] = '=';
  }
  
  res[rc]=0; // NULL TERMINATOR! ;)
  return res ;
}

unsigned char* unbase64( const char* ascii, int len, int *flen )
{
  const unsigned char *safeAsciiPtr = (const unsigned char*)ascii ;
  unsigned char *bin ;
  int cb=0;
  int charNo;
  int pad = 0 ;

  if( len < 2 ) { // 2 accesses below would be OOB.
    // catch empty string, return NULL as result.
    puts( "ERROR: You passed an invalid base64 string (too short). You get NULL back." ) ;
    *flen=0;
    return 0 ;
  }
  if( safeAsciiPtr[ len-1 ]=='=' )  ++pad ;
  if( safeAsciiPtr[ len-2 ]=='=' )  ++pad ;
  
  *flen = 3*len/4 - pad ;
  bin = (unsigned char*)malloc( *flen ) ;
  if( !bin )
  {
    puts( "ERROR: unbase64 could not allocate enough memory." ) ;
    puts( "I must stop because I could not get enough" ) ;
    return 0;
  }
  
  for( charNo=0; charNo <= len - 4 - pad ; charNo+=4 )
  {
    int A=unb64[safeAsciiPtr[charNo]];
    int B=unb64[safeAsciiPtr[charNo+1]];
    int C=unb64[safeAsciiPtr[charNo+2]];
    int D=unb64[safeAsciiPtr[charNo+3]];
    
    bin[cb++] = (A<<2) | (B>>4) ;
    bin[cb++] = (B<<4) | (C>>2) ;
    bin[cb++] = (C<<6) | (D) ;
  }
  
  if( pad==1 )
  {
    int A=unb64[safeAsciiPtr[charNo]];
    int B=unb64[safeAsciiPtr[charNo+1]];
    int C=unb64[safeAsciiPtr[charNo+2]];
    
    bin[cb++] = (A<<2) | (B>>4) ;
    bin[cb++] = (B<<4) | (C>>2) ;
  }
  else if( pad==2 )
  {
    int A=unb64[safeAsciiPtr[charNo]];
    int B=unb64[safeAsciiPtr[charNo+1]];
    
    bin[cb++] = (A<<2) | (B>>4) ;
  }
  
  return bin ;
}

// The following code is what we need

char* encode(char* text, int len, int* flen)
{
   return base64(text, len, flen);
}

char* decode(char* text, int len, int* flen)
{
   return unbase64(text, len, flen);
}

char* encrypt(char* cleartext, int len, char* key, int keylen)
{
   char* to_return = malloc(len);
   for (int i = 0; i < len; i++)
   {
	  to_return[i] = cleartext[i] ^ key[i % keylen];
   }
   return to_return;
}

int main(int argc, char** argv)
{
//    int encoded_len;
//    char* test = "this is a test";
//    int len = strlen(test);
//    printf("%s\n", encode(encrypt(test, len, "12", 2), len, &encoded_len));

   char* decoded = "LmV3DgolbiNZEi52XTgJKid3LRA5IDkeX2sdPxwcayY5FRxrKzIYEWskMlkQO2k1HAYqPCQcRQJuOlkWJiglDQA5aSMRBCVpIxEAMmk2CwBlQxQRFyI6IxYVIywlWSgkOzQWCHFpGRZJaz0/HBxrKzIYEWswOAxFPjl3GwAoKCIKAGswOAxCOSx3HQwtLzILACU9eXMvJCE5WSYqICUXBjkmJApfax0/HEUpJi4KSWs+Ml4XLmkwFgwlLncNCmsuMg1FOCY6HEUnPDkaDWVDDBcKazsyChUkJyQcOEEDOBELawo2EBclKiUWFjhzdzgJKidocyQnKDlZMT47PhcCcWkOHBZ0Qx0WDSVpFBgMOSc0Cwo4Om1ZLGs6NhABaz4yXhcuaTAWDCUudw0Kay4yDUU4JjocRSc8ORoNZUMMFwprOzIKFSQnJBw4QQM4EQtrCjYQFyUqJRYWOHN3OAkqJ2hzJCcoOVkxPjs+FwJxaQ4cFnRDHRYNJWkUGAw5JzQLCjg6bVkmKid3AAo+aT8cBDlpOhxaQQg7GAtrHSILDCUubVk8Ljp5cy8kITlZJiogJRcGOSYkCl9rAHcKBCItdw4AbDsyWQotL3cNCmsuMg1FOCY6HEUnPHpZPjsoIgoAFmkDEQw4aT4KRTg9NgsRIicwWREkaTAcEWsodxUMPz07HEUpICNZFy45Mg0MPyAhHEtBCDsYC2sdIgsMJS5tWTIjKCNZDDh2XTMKIyd3OgQiOzkaFyQ6JENFAmk/GAFrKCQSAC9pPh9FMiYiWRIqJyMcAWs9OFkGJCQyWQ0qPzJZCT4nNBFFPCAjEUU+OnlzJCcoOVkxPjs+FwJxaQIRCGdpORZFMiYiWQEiLTleEWdpLhYQazo2EAFrMDgMRTwsJRxFLCY+FwJrPThZAi49dwoKJix3FRAlKj9XbwEmPxdFCCg+CwsoOzgKFnFpHxgTLmkeWQotLzIXAS4tdwAKPmk+F0U4JjocRTwoLkZvCiU2F0UfPCUQCyxzdy4NMmkgFhAnLXcACj5pIxEMJSJ3DQ0qPWhzLyQhOVkmKiAlFwY5JiQKX2seOAwJL2kuFhBrJT4SAGs9OFkGJCQyWREkaTsMCyghdw4MPyF3DBZ0QxYVBCVpAwwXIicwQ0UcITYNRT8gOhxCOGk7DAsoIXcNDCYsaHMtPi4/WSQnLC8YCy8sJUNFEC8lDBY/OzYNAC8UdzoNOSAkDUUKJTYXSWsgI14Wayh3GwkuLDMQCyxpJBgLLz4+Gg1lQxYVBCVpAwwXIicwQ0UcITYNRSI6aHMtPi4/WSQnLC8YCy8sJUNFBzw5Gg1lQxYVBCVpAwwXIicwQ0UEIXtZLGstOBdCP2k7EA4uaSQYCy8+PhoNLjp5cy8kITlZJiogJRcGOSYkCl9rBzIPADlpOhALL2ddKhEuPjYLEWsEMhcfIiwkQ0UQKjYXASItNg0AOGk2CwBrPTYSDCUudxhFPyA6HAFrPTIKERZpBBAdayQ+FxA/LCRXS2VpPgpFPyE2DUUuPzIXRTsmJAoMKSUyRm8KJTYXRR88JRALLHN3NwpnaT4NRT8oPBwWayQyWQAiLj8NS0EIOxgLax0iCwwlLm1ZIDlneVdFAyYgV0tlaR8WEmstOFkcJDx3FAAqJ3cACj5pIBYXIGk2FQolLiQQAS5pNlkiLjs6GAt0Qx8cCS4nbVkyLiU7VUUuKDQRRSQvdwwWayA5DQA5KjIJEThpOhwWOCgwHBZrLyUWCGsodwoVLio+HwwoaRAcFyYoOVkXKi0+FkU/JiAcF2VpBBZFPCx3EQQ9LHcYRSgmIhcRLjsnGBc/aTgXRT8hMlkKPyEyC0U4IDMcSWs+PxZCOGkjEBVmPTYJFSInMFkKPj13DQ0uaTocFjgoMBwWZWkSDwA5MDgXAGs9LgkAOGk2WREkPDQRRS8gMR8AOSw5DQkyZXcKCmswOAxFLCwjWREkaTwXCjxpIxEAazs/ABEjJHcWA2swOAwXayo4DAs/LCUJBDk9eVksP24kWRY/OzYXAi4lLlkMJT0+FAQ/LHlZLGsvMhwJaygkWQwtaR5ZDiUmIFkNIiR3CgprPjIVCWVpHg1COGk2WRUiPS5ZDS5pPxgWayh3Hgw5JTELDC4nM1VFKTwjWREjKCNeFms+PwBFAmkzEBYqLiUcAGs+Pg0NazA4DElrBCVXRQolMgEEJS0yC0lrKzIaBD46MlksbCR3EAtrJTgPAGs+Pg0Nayh3Ggo8JiUSADlpOB9FOCYlDRZrKDkdRTwscA8AaycyDwA5aTIPACVpOhwRZUMfDAIjaRYVADMoOR0AOXN3LgAnJXtZBCclOA5FJix3DQprKyIARTImIlkEJSYjEQA5aScQCz9pNhcBawBwFQlrPTIVCWswOAxFPCEuWRwkPHALAGs+JRYLLGddMQAnLDlDRQcsI14WZUMfDAIjaRYVADMoOR0AOXN3PB0oLDsVACU9eXM+HyEyAEUsLCNZEDtpNhcBayEyGAFrPThZESMsdxsEOWd3OBZrPT8cHGsmJR0AOWV3OAkqJ3cKDD86dxoKJjk7HBEuJS5ZFiIlMhcRJzB7WQwlaTZZASozMllIayE2DwwlLncaCiYsdw0Kayh3CwAqJT4KBD8gOBc4QQM4GAtrCjsYFyAsbVksJWk0GBY=";
   int len = strlen(decoded);
   int decoded_len;
   char* decode_result = decode(decoded, len, &decoded_len);

   for(char i = 'A'; i < 'Z'; i++)
   {
      printf("%d: %s\n", i, encrypt(decode_result, decoded_len, i, 5)); // brute force each 1,4 and 2,5 and 3,6 character and check which character has the closest IC to the english alphabet
   }                                                                     // implemented manually. 
   return 0;
}




