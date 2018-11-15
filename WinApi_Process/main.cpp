#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <stdio.h>
#include <conio.h>



#define MASK_FOUND L"*"
#define Size 256
#define BufferSize 256
#define BUFSIZE 256

using namespace std;

HANDLE newstdread1, newstdwrite1;

void CreateDirSystem(LPSTR Dir,int i)//create System of Directories (recursive)
{
    if(i<14)
    {
        char buf[256];
        sprintf(buf,"%s\\FILE%d",Dir,i);
        i++;
        CreateDirectory(buf,NULL);
        CreateDirSystem(buf,i);
    }
}


void CopyDirSystem(LPSTR Dir, LPSTR Dir2)
{
    char buf[256]={0};
    char buf2[256]={0};
    sprintf(buf, "%s\\%s", Dir, "*");

    WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    hf=FindFirstFile(buf, &FindFileData);

    int count = 0;
    if (hf!=INVALID_HANDLE_VALUE)
    {
        do
        {
            sprintf(buf, "%s\\%s", Dir, FindFileData.cFileName);

            cout<<buf<<"\n";

            if( !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
            {
                cout<<"File: "<<FindFileData.cFileName<<endl;
                count++;
                sprintf(buf2, "%s\\%s", Dir2, FindFileData.cFileName);
                CreateFile(buf2,GENERIC_READ | GENERIC_WRITE,FILE_SHARE_WRITE | FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
                CopyFile(buf,buf2,FALSE);
                CopyDirSystem(buf,Dir2);
            }
        }
        while (FindNextFile(hf,&FindFileData)!=0);
        cout<<count<<endl;
        FindClose(hf);
    }
}

//аеяйнмевмн оюонй:
/*void CreateDirSystem(LPSTR Dir)
{
    char buf[256];
    int i = 11;
    sprintf(buf,"%s\\FILE%d",Dir,i++);
    do
    {
        CreateDirectory(buf,NULL);
        CreateDirSystem(buf);
    }while(i!=15);
}
*/
void ChildProcess(LPCSTR process1,LPCSTR newvalue,STARTUPINFO si1,PROCESS_INFORMATION pi1)
{
    //STARTUPINFO si1 = {0};
    //PROCESS_INFORMATION pi1 = {0};
    //Cout << old PATH:
    cout<<"Your Old PATH Environment: "<<getenv("path")<<endl;

    //Copy environment value(path):
    char buffer [BufferSize];//buffer for GetEnvironmentValue;
    DWORD old = GetEnvironmentVariable(TEXT("path"),buffer,BufferSize);//Copy to buffer, function return COUNT of symbols that was copied;
    cout<<endl<<"Your symbols count in buffer: "<<old<<endl;//If function is OK, it will return count;

    //Let`s change environment to child process:
    newvalue = "C:\\";
    BOOL sev = SetEnvironmentVariable("path",newvalue);
    if(sev != TRUE)
        printf("Error With Your SetEnvironmentVariable Function!\n");

    //Create Child Process, that will have new Environment(with our changes : newvalue);
    if(!CreateProcess(NULL, LPSTR(process1),NULL,NULL, FALSE, CREATE_NEW_CONSOLE,NULL,NULL,&si1,&pi1) )
    {
        cout<<"Your CreateProcess (cr_p) ERROR!"<<GetLastError()<<endl;
    }
    //Return old PATH value:
    SetEnvironmentVariable("path",buffer);

    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);

}









int main()
{
    HANDLE hfile;
    HANDLE *hProc;//pointer to massive of descriptors

    LPSTR path1 = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE3";
    LPSTR path2 = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE3\\FILE11";
    LPSTR path3 = "C:\\Users\\Gennady\\Desktop\\WinApi\\FILE3";

    LPCSTR process1 = "C:\\Users\\Gennady\\Downloads\\Win32Lab2018\\WinApiLab3\\Process1\\bin\\Release\\Process1.exe";


    BOOL cr_p;
    STARTUPINFO si = {0};
    ZeroMemory(&si,sizeof(STARTUPINFO));
    si.cb = sizeof(si);

    PROCESS_INFORMATION pi = {0};

    LPSTR path = "E:\\alkelpad\\AkelPad.exe";
    if(!CreateProcess(NULL, path,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi) )
    {
        cout<<"Your CreateProcess (cr_p) ERROR!"<<GetLastError()<<endl;
    }
        int i = 11;
        CreateDirSystem(path1,i);

        CopyDirSystem(path2, path3);
        cout<<endl;
        TCHAR buffer[Size];
        DWORD bufsize = Size;
        cout<<"Your Result(GetWindowsDirectory) :"<<GetWindowsDirectory(buffer,bufsize)<<endl;//<<"Your Error: "<<GetLastError()<<endl;
        cout<<"Your Buf:"<<buffer<<endl;
        TCHAR szDir[256];
        GetCurrentDirectory (255, szDir);
        cout<<endl<<"Your Current Directory: "<<szDir<<endl;

        LPVOID enstr = GetEnvironmentStrings();
        LPSTR str = (LPSTR)enstr;
        cout<<endl<<"Your Variable Environments: "<<endl;//Your ConsoleCommand: SET;
        while (str [0] != '\0' )
        {
            str = str + strlen (str) + 1;
            cout<<str<<endl;
        }
        FreeEnvironmentStrings( (LPSTR)enstr );


    //Snapshot:
    HANDLE hs = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//(AllProcessSnapshot, RootProcess);
    if(!hs)
        cout<<"Your CreateToolhelp32Snapshot (hs) ERROR!"<<GetLastError()<<endl;
    PROCESSENTRY32 pe = {0};
    pe.dwSize = sizeof(PROCESSENTRY32);// because structure PROCESSENTRY32 divided intp two parts for ASCII and UNICODE

    HANDLE process;//process that we will close;

    Process32First(hs,&pe);
    printf("Pr_id\t|Exe\t\t|C.Threat\n");
    do
    {
        printf("%d\t|%s\t|%d\n",pe.th32ProcessID,pe.szExeFile,pe.cntThreads);
    }while(Process32Next(hs,&pe));
    CloseHandle(hs);

    if(process)
    {
        TerminateProcess(process,0);
        CloseHandle(process);
    }
    STARTUPINFO si1 = {sizeof(si1)};
    SECURITY_ATTRIBUTES sa;
    PROCESS_INFORMATION pi1;
    char buf[1024];
    char buf1[20] = " ORAL CUMSHOT ";
    char t = '\n';
    HANDLE newstdread, newstdwrite;//хэндлы потоков для пайпа
    //инициализируем нужные поля SECURITY_ATTRIBUTES
    //HANDLE newstdread1, newstdwrite1;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = true;       //разрешаем наследование дескрипторов
    //***************создаем анонимный канал***************
    if (!CreatePipe(&newstdread, &newstdwrite, &sa, 0))   //создаем пайп для stdin
    {
        cout << "I can't CreatePipe";
        getch();
        return 0;
    }
    else
        cout << "\nPipe Created!\n";
    //******выведем на экран дескриптор потока ввода анонимного канала************
    cout << "The read HANDLE of PIPE = " << newstdread << endl;
    //******обнуляем поля STARTUPINFO и задаем нужные значения************
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si1.cb = sizeof(STARTUPINFO);
    si1.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si1.wShowWindow = SW_NORMAL;
    //*****подменяем стандартный дескриптор ввода, дескриптором ввода анонимного канала*****
    si1.hStdInput = newstdread;
    si1.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si1.hStdError = si.hStdOutput;
    //LPCSTR process1 = "C:\\Users\\Gennady\\Downloads\\Win32Lab2018\\WinApiLab3\\Process1\\bin\\Release\\Process1.exe";
    //TCHAR czCommandLine[] = "c:\\windows\\system32\\cmd.exe";
    //ChildProcess(process1,"C:\\",si1,pi1);
    if (!CreateProcess(NULL, LPSTR(process1), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1))
    {
        cout << "I can't CreateProcess";
        getch();
        CloseHandle(newstdread);
        CloseHandle(newstdwrite);
        return 0;
    }
    else
        cout << "\nProcess Created!!!\n";
    cout << buf;

    unsigned long bread;
    DWORD dwRead;
    cout << "STD INPUT HANDLE = " << GetStdHandle(STD_INPUT_HANDLE) << endl;
    cout << "STD OUTPUT HANDLE = " << GetStdHandle(STD_OUTPUT_HANDLE) << endl;
    int x =0;
    BOOL bSuccess;
    char chBuf1[256];
    cout<<sizeof(buf1);
    //int bytesin = sizeof(buf1);
    for(int i=0;i<1;i++)
    {
        //ReadFile(newstdread,buf1, sizeof(buf1), bytesin, NULL);
            WriteFile(newstdwrite, buf1, sizeof(buf1), &bread, NULL);
            if(bread != sizeof(buf1))
            {
                break;
            }
           // ReadFile(newstdread, chBuf1, sizeof(chBuf1), &dwRead, NULL);
           // cout<<"CHBUF1"<<chBuf1<<endl;
    }//while(true);
    //cout<<endl<<"CHBUF1"<<chBuf1;
    TerminateProcess(pi.hProcess,0);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    CloseHandle(newstdread);
    CloseHandle(newstdwrite);
    system("PAUSE");


    return 0;
}
