#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <windows.h>
#include <string>
#include <iostream>

class Exception
{
  private: DWORD code;
  public: DWORD getCode(){return this->code;}

  private: std::string message;
  public: std::string getMessage(){return this->message;}

  public: Exception(DWORD errorCode)
  {
    this->code = errorCode;
    LPVOID lpMsgBuf;
    DWORD bufLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL );
    if (bufLen)
    {
      LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
      std::string result(lpMsgStr, lpMsgStr+bufLen);
      this->message = result;
      LocalFree(lpMsgBuf);
    }
  }

  public: print()
  {
    std::cout << "FTDException " << this->code << ": " << this->message << '\n';
  }
};

#endif
