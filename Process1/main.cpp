#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <conio.h>



#define BufferSize 256
#define BUFSIZE 20
using namespace std;
    LPCSTR pathfile = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE3\\l4.txt";

string ShowDirectory(LPCSTR path,LPCSTR file, char(&buf)[BufferSize])
{
    WIN32_FIND_DATA wind;
    SetCurrentDirectory(path);
    OFSTRUCT buffer;
    //LPCSTR file = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE3\\l4.txt";
    //LPCSTR file = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE3\\l4.txt";
    HFILE hfile = OpenFile(pathfile, &buffer, OF_READ);


    //char buf[BufferSize] = {0};
    char *buf1 = new char[256];
    //string buf1;
    DWORD dwWritten = 0;
    HANDLE search1 = FindFirstFile(TEXT("*.*"),&wind);

    if(search1 != INVALID_HANDLE_VALUE)
    {
        do
        {
            GetCurrentDirectory(sizeof(buf),buf);
            if(wind.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    if (strcmp(wind.cFileName,"..")!=0 && strcmp(wind.cFileName,".")!=0)
                        {
                            //cout<<"Your Result: "<<endl;
                            //cout<<wind.cFileName<<endl;
                            if(strcmp(file,wind.cFileName) == 0)
                                cout<<"Your Directory Name: "<<wind.cFileName<<endl;
                            else
                                cout<<"Wrong DIRECTORY"<<endl;
                        }
                }
            else
            {
                if(strcmp(file,wind.cFileName) == 0)
                    {
                        cout<<"Your FILE Name: "<<wind.cFileName<<endl;
                        //sprintf(buf1,wind.cFileName);
                        sprintf(buf1,"%s",wind.cFileName);

                        //WriteFile(hfile, buf, sizeof(buf), &dwWritten, NULL);
                    }
                else
                    cout<<"Wrong FILE"<<endl;

            }
           // SetCurrentDirectory(path);
        }
        while(FindNextFile(search1,&wind)!=0);
        FindClose(search1);
    }

   // for(int i=0 ; i < sizeof(buf1) ; i++)
     //   buf[i] = buf1[i];

    return buf1;
}


int main()
{
    LPCSTR path = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE3\\FILE11";
    LPCSTR file = "findfile.txt";
    string buf1;
    char buf[BufferSize];

    cout<<endl<<"Your ShowDirectory function return: "<<ShowDirectory(path,file,buf)<<endl;
    strcpy(buf,file);
    cout<<endl<<buf<<endl<<endl;

    cout<<getenv("path")<<endl;

    //Copy environment value(path):
    char buffer [BufferSize];//buffer for GetEnvironmentValue;
    DWORD old = GetEnvironmentVariable(TEXT("path"),buffer,BufferSize);//Copy to buffer, function return COUNT of symbols that was copied;
    cout<<endl<<"Your symbols count in buffer: "<<old<<endl;//If function is OK, it will return count;

    //Let`s change environment to child process:
    LPCSTR newvalue = "C:\\";
    BOOL sev = SetEnvironmentVariable("path",newvalue);
    if(sev != TRUE)
        printf("Error With Your SetEnvironmentValue Function!\n");


   CHAR chBuf[BUFSIZE];
   DWORD dwRead, dwWritten;
   HANDLE hStdin, hStdout;
   BOOL bSuccess;

   hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
   hStdin = GetStdHandle(STD_INPUT_HANDLE);
   if (
       (hStdout == INVALID_HANDLE_VALUE) ||
       (hStdin == INVALID_HANDLE_VALUE)
      )
      ExitProcess(1);

   // Send something to this process's stdout using printf.
   printf("\n ** This is a message from the child process. ** \n");

   // This simple algorithm uses the existence of the pipes to control execution.
   // It relies on the pipe buffers to ensure that no data is lost.
   // Larger applications would use more advanced process control.

   //for (;;)
   //do
   //char chBuf1[256] = "Tramadol";
   int x=0;
   for (int i=0;i<1;i++)
   {
   // Read from standard input and stop on error or no data.
      bSuccess = ReadFile(hStdin, chBuf, BUFSIZE, &dwRead, NULL);

      if (! bSuccess || dwRead == 0)
         break;
   // Write to standard output and stop on error.

      //bSuccess = WriteFile(hStdout, chBuf1, BUFSIZE, &dwWritten, NULL);
     // cout<<endl<<chBuf;
     cout<<endl<<chBuf;
      if (! bSuccess)
         break;
   }//while(!sizeof(chBuf));

//cin.get();
//cin.get();
  getch();
    system("pause");
    ExitProcess (0);
    return 0;
}
