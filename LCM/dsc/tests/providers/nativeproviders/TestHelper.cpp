/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include<Shlobj.h>
#include "windows.h"
#include <strsafe.h>
#include<Rpc.h>
#include <MI.h>
#include <nits.h>
#include<SYS\Stat.h>
#include<io.h>
typedef wchar_t MI_Char;


void SetAttrib(PWSTR fileOrDir, DWORD dwDesiredAttrib)
{
        DWORD dwAttrs = GetFileAttributes(fileOrDir);
        if(dwAttrs == INVALID_FILE_ATTRIBUTES)
        {
                NitsAssert(false, L"Invalid File attributes");
                return;
        }
        if(!(dwAttrs & dwDesiredAttrib))
        {
                SetFileAttributes(fileOrDir, dwAttrs|dwDesiredAttrib);
        }
}
        


BOOL IsDots(wchar_t* str) {
        if(wcscmp(str,L".") && wcscmp(str,L"..")) return FALSE;
    return TRUE;
}
BOOL DeleteDirectory(wchar_t* sPath) {
    HANDLE hFind;  // file handle
    WIN32_FIND_DATA FindFileData;

    TCHAR DirPath[MAX_PATH];
    TCHAR FileName[MAX_PATH];
          
    StringCchCopy(DirPath, MAX_PATH, sPath);
    StringCchCat(DirPath,MAX_PATH, L"\\*");    // searching all files
    StringCchCopy(FileName,MAX_PATH,sPath);
    StringCchCat(FileName,MAX_PATH, L"\\");

    hFind = FindFirstFile(DirPath,&FindFileData); // find the first file
    if(hFind == INVALID_HANDLE_VALUE) return FALSE;
    StringCchCopy(DirPath,MAX_PATH,FileName);
        
    bool bSearch = true;
    while(bSearch) { // until we finds an entry
        if(FindNextFile(hFind,&FindFileData)) {
            if(IsDots(FindFileData.cFileName)) continue;
            StringCchCat(FileName,MAX_PATH,FindFileData.cFileName);
            if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

                // we have found a directory, recurse
                SetFileAttributes(FileName, FILE_ATTRIBUTE_NORMAL);
                                if(!DeleteDirectory(FileName)) { 
                                        int lasterror = 0;
                                        lasterror = GetLastError();
                    FindClose(hFind); 
                    return FALSE; // directory couldn't be deleted
                }
                RemoveDirectory(FileName); // remove the empty directory
                StringCchCopy(FileName,MAX_PATH,DirPath);
            }
            else {
                if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
                    _wchmod(FileName, _S_IWRITE); // change read-only file mode
                if(!DeleteFile(FileName)) {  // delete the file
                    FindClose(hFind); 
                    return FALSE; 
                }                 
                StringCchCopy(FileName,MAX_PATH,DirPath);
            }
        }
        else {
            if(GetLastError() == ERROR_NO_MORE_FILES) // no more files there
            bSearch = false;
            else {
                // some error occured, close the handle and return FALSE
                FindClose(hFind); 
                return FALSE;
            }

        }

    }
    FindClose(hFind);  // closing file handle
 
    return RemoveDirectory(sPath); // remove the empty directory

}

void SetSingleFileDir(PWSTR sourceFileName, PWSTR destFileName)
{
        SetAttrib(sourceFileName, FILE_ATTRIBUTE_READONLY);
        SetAttrib(sourceFileName, FILE_ATTRIBUTE_SYSTEM);


}
void FileUnitTestCleanup(bool keepCache = false )
{
        LPTSTR dirName = L"fileunitestdata";
        PWSTR ppszPath;
        const size_t sizeRes = 1024;
        PWSTR dest = new wchar_t[sizeRes];
        ppszPath = new wchar_t[sizeRes];
        DeleteDirectory(dirName);
        if(!keepCache)
        {
                HRESULT res = SHGetKnownFolderPath(FOLDERID_System, 0, NULL, &ppszPath);
                StringCchCopy(dest, sizeRes, ppszPath);
                StringCchCat(dest, sizeRes, L"\\Configuration\\BuiltinProvCache\\MSFT_FileDirectoryConfiguration");
                DeleteDirectory(dest);
        }
        if(!ppszPath)
        delete [] ppszPath;
}

void FileUnitTestGetOperationSetup()
{
        FileUnitTestCleanup(false);
        CreateDirectory(L"fileunitestdata", NULL);
        PWSTR sGUID = NULL;
        GUID guid;
        char DataForFile[] = "1";
        DWORD dwBytesToWrite = (DWORD)strlen(DataForFile);
        DWORD dwBytesWritten = 0;
        CoCreateGuid(&guid);
        if (!( RPC_S_OK == UuidToString( (UUID*)&guid, (RPC_WSTR*)&sGUID)))
        {
                int lastError = GetLastError();
                NitsAssert(false, L"Failed to conver UUID to String");
        }
        //Proceed ahead
        else
        {
                size_t sizeRes = 1024;
                PWSTR singleDestFileName = new wchar_t[sizeRes];
                PWSTR singleDestDirName = new wchar_t[sizeRes];
                PWSTR singleSourceFileName = new wchar_t[sizeRes];
                PWSTR singleSourceDirName = new wchar_t[sizeRes];
                StringCchCopy(singleDestFileName, sizeRes, L"fileunitestdata");
                StringCchCat(singleDestFileName, sizeRes, L"\\singledestfilename");
                StringCchCat(singleDestFileName, sizeRes, sGUID);
                StringCchCat(singleDestFileName, sizeRes, L".txt");
                StringCchCopy(singleDestDirName, sizeRes, L"fileunitestdata");
                StringCchCat(singleDestDirName, sizeRes, L"\\singledestdirname");
                StringCchCat(singleDestDirName, sizeRes, sGUID);
                StringCchCopy(singleSourceFileName, sizeRes, L"fileunitestdata");
                StringCchCat(singleSourceFileName, sizeRes, L"\\singlesourcefilename");
                StringCchCat(singleSourceFileName, sizeRes, sGUID);
                StringCchCat(singleSourceFileName, sizeRes, L".txt");
                StringCchCopy(singleSourceDirName, sizeRes, L"fileunitestdata");
                StringCchCat(singleSourceDirName, sizeRes, L"\\singlesourcedirname");
                StringCchCat(singleSourceDirName, sizeRes, sGUID);
                HANDLE hFile;
                hFile = CreateFile(singleDestFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                if(hFile == INVALID_HANDLE_VALUE)
                {
                        int lastError = GetLastError();
                        NitsAssert(false, L"Failed to create file!");
                        return;
                }
                else
                {
                        if(!(WriteFile(hFile, DataForFile, dwBytesToWrite, &dwBytesWritten, NULL)))
                        {
                                NitsAssert(false, L"Failed to write to file");
                        }
                        else
                        {
                                if(dwBytesWritten != dwBytesToWrite)
                                {
                                        NitsAssert(false, L"Write returned unexpected results");
                                }
                        }
                }
                SetAttrib(singleDestFileName, FILE_ATTRIBUTE_READONLY);
                CloseHandle(hFile);
                CreateDirectory(singleDestDirName, NULL);
                SetAttrib(singleDestDirName, FILE_ATTRIBUTE_READONLY);
        }
}
HANDLE WINAPI CreateFileCustom(PWSTR fileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,  DWORD dwCreationDisposition,  DWORD dwFlagsAndAttributes,HANDLE hTemplateFile)
{
        HANDLE hFile = CreateFile(fileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
        if(hFile == INVALID_HANDLE_VALUE)
        {
                int lastError = GetLastError();
                NitsAssert(false, L"Failed to create file!");
                return hFile;
        }
        return hFile;
}



void FileUnitTestTestOperationSetup(bool keepCache = false)
{
        FileUnitTestCleanup(false);
        size_t sizeRes = 1024;
        wchar_t DataForFile[] = L"1";
        DWORD dwBytesToWrite = (DWORD)wcslen(DataForFile);
        DWORD dwBytesWritten = 0;
        PWSTR singleDestFileWithBom = new wchar_t[sizeRes];
        PWSTR singleDestFileWithoutBom = new wchar_t[sizeRes];
        PWSTR singleSourceFileWithBom = new wchar_t[sizeRes];
        PWSTR singleSourceFileWithoutBom = new wchar_t[sizeRes];
        PWSTR singleDestDirName = new wchar_t[sizeRes];
        PWSTR singleSourceDirName = new wchar_t[sizeRes];
        CreateDirectory(L"fileunitestdata", NULL);
        StringCchCopy(singleSourceFileWithBom, sizeRes, L"fileunitestdata\\singlesourcefilewithbom.txt");
        StringCchCopy(singleSourceFileWithoutBom, sizeRes, L"fileunitestdata\\singlesourcefilewithoutbom.txt");
        HANDLE hFile = CreateFileCustom(singleSourceFileWithBom, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if(hFile == INVALID_HANDLE_VALUE)
                return;
        unsigned char smarker[3];
        smarker[0] = 0xEF;
        smarker[1] = 0xBB;
        smarker[2] = 0xBF;
        if(!(WriteFile(hFile, smarker, 3, &dwBytesWritten, NULL)))
        {
                NitsAssert(false, L"Could not write");
                CloseHandle(hFile);
                return;
        }
        else
        {
                char* utf8 = (char*) malloc((dwBytesToWrite+1)*sizeof(wchar_t));
                int lBytesWritten = WideCharToMultiByte(CP_UTF8, 0, DataForFile, -1, utf8, 1000, NULL, NULL);
                int lastError = GetLastError();
                WriteFile(hFile, utf8, lBytesWritten, &dwBytesWritten, NULL);
                free(utf8);
                CloseHandle(hFile);
        }
        
        hFile = CreateFileCustom(singleSourceFileWithoutBom, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if(hFile == INVALID_HANDLE_VALUE)
        {
                        return;
        }
        else
        {
                if(!(WriteFile(hFile, DataForFile, dwBytesToWrite, &dwBytesWritten, NULL)))
                {
                        NitsAssert(false, L"Failed to write to file");
                        CloseHandle(hFile);
                        return;
                }
                else
                {
                        if(dwBytesWritten != dwBytesToWrite)
                        {
                                NitsAssert(false, L"Write returned unexpected results");
                                CloseHandle(hFile);
                                return;
                        }
                }
                CloseHandle(hFile);
        }
        SetSingleFileDir(singleSourceFileWithBom, singleDestFileWithBom);
        SetSingleFileDir(singleSourceFileWithoutBom, singleDestFileWithoutBom);
}
void WriteToFile(PWSTR fileName, PWSTR content, PWSTR encoding)
{
        FILE* fileHandle = NULL;
        wchar_t buffer[50];
        size_t strsize;
        errno_t err;
        if(lstrcmpi(encoding, L"UTF8") == 0)
        {

                err = _wfopen_s(&fileHandle, fileName,  L"w+,ccs=UTF-8");
                if(err != 0)
                {
                        int lasterror = GetLastError();
                        NitsAssert(false, fileName);
                        return;
                }

        }
        else if(lstrcmpi(encoding, L"UNICODE") == 0)
        {
                err = _wfopen_s(&fileHandle, fileName,  L"w+,ccs=UNICODE");
                if(err != 0)
                {
                        int lasterror = GetLastError();
                        NitsAssert(false, fileName);
                        return;
                }

        }
                wcscpy_s(buffer, sizeof(buffer)/sizeof(wchar_t), content);
                strsize = wcslen(buffer);
                if(fwrite(buffer, sizeof(wchar_t), strsize, fileHandle) != strsize)
                {
                        NitsAssert(false, L"Failed to create file");
                        return;
                }
                fclose(fileHandle);
}
void CopyFileCustom( wchar_t* partialPath1, wchar_t* partialPath2 )
{
   wchar_t full1[_MAX_PATH];
   if( _wfullpath( full1, partialPath1, _MAX_PATH ) == NULL )
           NitsAssert(false, L"failed to get full path");
   else
           wprintf(full1);
  
   wchar_t full2[_MAX_PATH];
   if( _wfullpath( full2, partialPath2, _MAX_PATH ) == NULL )
           NitsAssert(false, L"failed to get full path");
   else
        wprintf( full2);
   CopyFile(full1, full2, FALSE);
   int lasterror = GetLastError();
}

void FileUnitTestSetOperationSetup(bool keepCache = false)
{
        FileUnitTestCleanup(keepCache);
        CreateDirectory(L"fileunitestdata", NULL);
        size_t sizeRes = 1024;
        wchar_t singledestfilecontentmismatch[] = L"fileunitestdata\\singledestfilecontentmismatch.txt";
        wchar_t singledestfileattributesmismatch[] = L"fileunitestdata\\singledestfileattributesmismatch.txt";
        wchar_t singledestfileSourcemismatch[] = L"fileunitestdata\\singledestfileSourcemismatch.txt";
        wchar_t emptyFile[] = L"fileunitestdata\\emptyFile.txt";
        wchar_t singlesource[] = L"fileunitestdata\\singlesource.txt";
        wchar_t singledestdirname[] = L"fileunitestdata\\singledestdirname";
        wchar_t singlesourcedirname[] = L"fileunitestdata\\singlesourcedirname";
        wchar_t DestDirForAbsent[] = L"fileunitestdata\\DestDirForAbsent";
        wchar_t DestFileForAbsent[] = L"fileunitestdata\\DestFileForAbsent.txt";
        wchar_t DestDirNotEmptyForceTrue[] = L"fileunitestdata\\DestDirNotEmptyForceTrue";
        wchar_t DestDirNotEmptyForceFALSE[] = L"fileunitestdata\\DestDirNotEmptyForceFALSE";
        wchar_t DestDirEnsureFileContentForce[] = L"fileunitestdata\\DestDirEnsureFileContentForce";
        wchar_t DestFileEnsureDirForce[] = L"fileunitestdata\\DestFileEnsureDirForce";
        HANDLE hfile;
        PWSTR content = L"1";
        WriteToFile(singlesource, content, L"UTF8");
        WriteToFile(singledestfilecontentmismatch, L"notmatch", L"UTF8");
        WriteToFile(emptyFile, L"notmatch", L"UTF8");
        WriteToFile(singledestfileattributesmismatch, content, L"UTF8");
        WriteToFile(singledestfileSourcemismatch, L"notmatch", L"UTF8");
        SetAttrib(singlesource, FILE_ATTRIBUTE_READONLY);
        SetAttrib(singledestfilecontentmismatch, FILE_ATTRIBUTE_READONLY);
        SetAttrib(singledestfileSourcemismatch, FILE_ATTRIBUTE_READONLY);
        SetAttrib(emptyFile, FILE_ATTRIBUTE_READONLY);
        SetFileAttributes(singledestfileattributesmismatch, FILE_ATTRIBUTE_NORMAL);
        CreateDirectory(L"fileunitestdata\\singlesourcedirname", NULL);
        CreateDirectory(L"fileunitestdata\\singledestdirname", NULL);
        CreateDirectory(L"fileunitestdata\\DestDirForAbsent", NULL);
        CreateDirectory(L"fileunitestdata\\DestDirNotEmptyForceTrue", NULL);
        CreateDirectory(L"fileunitestdata\\DestDirNotEmptyForceTrue\\dir1", NULL);
        CreateDirectory(L"fileunitestdata\\DestDirNotEmptyForceFALSE", NULL);
        CreateDirectory(L"fileunitestdata\\DestDirNotEmptyForceFALSE\\dir1", NULL);
        WriteToFile(DestFileForAbsent, content, L"UNICODE");
        CreateDirectory(L"fileunitestdata\\DestDirEnsureFileContentForce ", NULL);
        WriteToFile(DestFileEnsureDirForce, content, L"UNICODE");
        CreateDirectory(L"fileunitestdata\\Resourcedir", NULL);
        CreateDirectory(L"fileunitestdata\\Resourcedir\\dir1", NULL);
        CreateDirectory(L"fileunitestdata\\Resourcedir\\dir2", NULL);
        CreateDirectory(L"fileunitestdata\\Resourcedir\\dir3", NULL);
        CreateDirectory(L"fileunitestdata\\Resourcedir\\dir4", NULL);
        WriteToFile(L"fileunitestdata\\Resourcedir\\dir2\\file.txt", content, L"UTF8");
        WriteToFile(L"fileunitestdata\\Resourcedir\\file1.txt", content, L"UTF8");
        WriteToFile(L"fileunitestdata\\Resourcedir\\file2.txt", content, L"UTF8");
        SetAttrib(L"fileunitestdata\\Resourcedir", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\Resourcedir\\dir1", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\Resourcedir\\dir2", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\Resourcedir\\dir3", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\Resourcedir\\dir4", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\Resourcedir\\file1.txt", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\Resourcedir\\file2.txt", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\Resourcedir\\dir2\\file.txt", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        wchar_t RDestdirForSet[] = L"fileunitestdata\\RDestdirForSet";
        CreateDirectory(RDestdirForSet, NULL);
        CreateDirectory(L"fileunitestdata\\RDestdirForSet\\dir1", NULL);
        CreateDirectory(L"fileunitestdata\\RDestdirForSet\\dir2", NULL);
        CreateDirectory(L"fileunitestdata\\RDestdirForSet\\dir3", NULL);
        CreateDirectory(L"fileunitestdata\\RDestdirForSet\\dir4", NULL);
        CopyFileCustom(L"fileunitestdata\\Resourcedir\\dir2\\file.txt", L"fileunitestdata\\RDestdirForSet\\dir2\\file.txt");
        CopyFileCustom(L"fileunitestdata\\Resourcedir\\file1.txt", L"fileunitestdata\\RDestdirForSet\\file1.txt");
        CopyFileCustom(L"fileunitestdata\\Resourcedir\\file2.txt", L"fileunitestdata\\RDestdirForSet\\file2.txt");
        SetAttrib(L"fileunitestdata\\RDestdirForSet", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\RDestdirForSet\\dir1", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\RDestdirForSet\\dir2", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\RDestdirForSet\\dir3", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\RDestdirForSet\\dir4", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\RDestdirForSet\\dir2\\file.txt", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\Resourcedir\\file1.txt", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\Resourcedir\\file2.txt", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetFileAttributes(L"fileunitestdata\\RDEstdirForSet\\file1.txt", GetFileAttributes(L"fileunitestdata\\RDEstdirForSet\\file1.txt") & ~FILE_ATTRIBUTE_READONLY);
        DeleteFile(L"fileunitestdata\\RDEstdirForSet\\file1.txt");
        WriteToFile(L"fileunitestdata\\RDEstdirForSet\\dir1\\file.txt", content, L"UTF8");
        SetFileAttributes(L"fileunitestdata\\RDEstdirForSet\\dir4", GetFileAttributes(L"fileunitestdata\\RDEstdirForSet\\dir4") & ~FILE_ATTRIBUTE_READONLY);
        RemoveDirectory(L"fileunitestdata\\RDEstdirForSet\\dir4");
        CreateDirectory(L"fileunitestdata\\RDEstdirForSet\\dir5", NULL);
        SetFileAttributes(L"fileunitestdata\\RDEstdirForSet\\dir2\\file.txt", GetFileAttributes(L"fileunitestdata\\RDEstdirForSet\\dir2\\file.txt") & ~FILE_ATTRIBUTE_READONLY & ~FILE_ATTRIBUTE_SYSTEM & ~FILE_ATTRIBUTE_HIDDEN);
        WriteToFile(L"fileunitestdata\\RDEstdirForSet\\dir2\\file.txt", L"notmatch", L"UNICODE");
        SetFileAttributes(L"fileunitestdata\\RDEstdirForSet\\dir2", GetFileAttributes(L"fileunitestdata\\Resourcedir\\dir2") & ~FILE_ATTRIBUTE_READONLY & ~FILE_ATTRIBUTE_SYSTEM & ~FILE_ATTRIBUTE_HIDDEN);
        SetFileAttributes(L"fileunitestdata\\RDEstdirForSet\\dir3", GetFileAttributes(L"fileunitestdata\\Resourcedir\\dir2") & ~FILE_ATTRIBUTE_READONLY);
        RemoveDirectory(L"fileunitestdata\\RDEstdirForSet\\dir3");
        WriteToFile(L"fileunitestdata\\RDestdirForSet\\dir3", content, L"UNICODE");
        SetAttrib(L"fileunitestdata\\RDEstdirForSet\\dir3", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
        SetAttrib(L"fileunitestdata\\RDestdirForSet\\file2.txt", FILE_ATTRIBUTE_NORMAL);
        DeleteFile(L"fileunitestdata\\RDestdirForSet\\file2.txt");
        CreateDirectory(L"fileunitestdata\\RDestdirForSet\\file2.txt", NULL);
        SetAttrib(L"fileunitestdata\\RDestdirForSet\\file2.txt", FILE_ATTRIBUTE_READONLY|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN);
}

void VerifyProperties(PWSTR fileName, PWSTR resultFile)
{
        DWORD dwAttrib = 0;
        size_t resSize = 1024;
        WIN32_FIND_DATA FindFileData;
        FILE* hFile;
        HANDLE hFind = FindFirstFile(fileName,&FindFileData);
        PWSTR buffer = new wchar_t[resSize];
        StringCchCopy(buffer, resSize, fileName);
        if(hFind == INVALID_HANDLE_VALUE)
        {
                StringCchCat(buffer, resSize, L" not exists");
                WriteToFile(resultFile, buffer, L"UNICODE");
        }
        else
        {
                dwAttrib = GetFileAttributes(fileName);
                if((dwAttrib & FILE_ATTRIBUTE_READONLY) == 0)
                {
                        StringCchCat(buffer, resSize, L" attributes mismatch");
                        WriteToFile(resultFile, buffer, L"UNICODE");
                        CloseHandle(hFind);
                }
        }
}

void VerifySingleFile(PWSTR fileName, PWSTR resultFile,  PWSTR content, PWSTR desiredContents)
{
        FILE* hFile;
        errno_t err  = _wfopen_s( &hFile,fileName, L"r,ccs=UTF-8" );
        wchar_t* subString;
        size_t resSize = 1024;
        DWORD dwBytesRead = 0;
        PWSTR buffer = new wchar_t[resSize];
        wchar_t* contentsOfFile = new wchar_t[resSize];
        StringCchCopy(buffer, resSize, fileName);
        if(err != 0)
        {
                StringCchCat(buffer, resSize, L" not exists");
                WriteToFile(resultFile, buffer, L"UNICODE");
        }
        else
        {
                if(lstrcmpi(content,desiredContents) == 0)
                {
                        fread(contentsOfFile, sizeof(wchar_t), 1024, hFile);
                        subString = wcsstr(contentsOfFile, content);
                        if(subString == NULL)
                        {
                                StringCchCat(buffer, resSize, L" content mimatch");
                                WriteToFile(resultFile, buffer, L"UNICODE");
                        }
                }
                else
                {
                        HANDLE FHILE = (HANDLE) _get_osfhandle(_fileno(hFile));
                        DWORD filesize =  GetFileSize(FHILE, NULL);
                        CloseHandle(FHILE);
                        if(filesize != 0)
                        {
                                StringCchCat(buffer, resSize, L" is not empty");
                                WriteToFile(resultFile, buffer, L"UNICODE");
                        }
                }
        }
        delete [] buffer;
        delete [] contentsOfFile;
        VerifyProperties(fileName, resultFile);
}

void VerifyAbsent(PWSTR fileName, PWSTR resultFile,  bool existing)
{
        size_t resSize = 1024;
        WIN32_FIND_DATA FindFileData;
        PWSTR buffer = new wchar_t[resSize];
        StringCchCopy(buffer, resSize, fileName);
        FILE* hFile;
        HANDLE hFind = FindFirstFile(fileName,&FindFileData);
        if(hFind == INVALID_HANDLE_VALUE)
        {
                if(existing)
                {
                        StringCchCat(buffer, resSize, L"different!");
                        WriteToFile(resultFile, buffer, L"UNICODE");
                }
        }
        else
        {
                if(!existing)
                {
                        StringCchCat(buffer, resSize, L"different!");
                        WriteToFile(resultFile, buffer, L"UNICODE");
                        CloseHandle(hFind);
                }
        }
        delete [] buffer;
}
void FileUnitTestSetOperationVerify()
{
        wchar_t content[] = L"1";
        wchar_t desirecContents[] = L"1";
        HANDLE hFile = CreateFile(L"fileunitestdata\\resultfile", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if(GetLastError() != ERROR_FILE_NOT_FOUND)
        {
                SetFileAttributes(L"result.txt", FILE_ATTRIBUTE_NORMAL);
                DeleteFile(L"result.txt");
                CloseHandle(hFile);
        }
        VerifySingleFile(L"fileunitestdata\\singledestfilecontentmismatch.txt",L"fileunitestdata\\result.txt", content, desirecContents);
        VerifySingleFile(L"fileunitestdata\\singledestfileattributesmismatch.txt",L"fileunitestdata\\result.txt", content, desirecContents);
        VerifySingleFile(L"fileunitestdata\\singledestfileSourcemismatch.txt",L"fileunitestdata\\result.txt", content, desirecContents);
        VerifySingleFile(L"fileunitestdata\\emptyFile.txt",L"fileunitestdata\\result.txt", L"Empty", desirecContents);
        VerifySingleFile(L"fileunitestdata\\singledestfileoriginallynotexistcontent.txt",L"fileunitestdata\\result.txt", content, desirecContents);
        VerifySingleFile(L"fileunitestdata\\test\\test\\test\\test\\test\\singledestfileoriginallynotexistsource.txt",L"fileunitestdata\\result.txt", content, desirecContents);
        VerifySingleFile(L"fileunitestdata\\DestDirEnsureFileContentForce",L"fileunitestdata\\result.txt", content, desirecContents);
        VerifySingleFile(L"fileunitestdata\\notexist\\notexst2\\..\\DestFileParentNotExistContent",L"fileunitestdata\\result.txt", content, desirecContents);

        VerifyProperties(L"fileunitestdata\\singledestdirname", L"fileunitestdata\\result.txt");
        VerifyProperties(L"fileunitestdata\\singledestdiroriginallynotexist", L"fileunitestdata\\result.txt");
        VerifyProperties(L"fileunitestdata\\DestFileEnsureDirForce", L"fileunitestdata\\result.txt");
        VerifyProperties(L"fileunitestdata\\notexist\\DestDirParentNotExistForSet", L"fileunitestdata\\result.txt");
        
        VerifyAbsent(L"fileunitestdata\\DestDirForAbsent", L"fileunitestdata\\result.txt", false);
        VerifyAbsent(L"fileunitestdata\\DestFileForAbsent.txt", L"fileunitestdata\\result.txt", false);
        VerifyAbsent(L"fileunitestdata\\DestDirNotEmptyForceTrue", L"fileunitestdata\\result.txt", false);
        VerifyAbsent(L"fileunitestdata\\DestDirNotEmptyForceFALSE", L"fileunitestdata\\result.txt", true);

        VerifyProperties(L"fileunitestdata\\RDestdirForSet", L"fileunitestdata\\result.txt");
        VerifyProperties(L"fileunitestdata\\RDestdirForSet\\dir1", L"fileunitestdata\\result.txt");
        VerifyProperties(L"fileunitestdata\\RDestdirForSet\\dir2", L"fileunitestdata\\result.txt");
        VerifyProperties(L"fileunitestdata\\RDestdirForSet\\dir3", L"fileunitestdata\\result.txt");
        VerifyProperties(L"fileunitestdata\\RDestdirForSet\\dir4", L"fileunitestdata\\result.txt");

        VerifySingleFile(L"fileunitestdata\\RDestdirForSet\\dir2\\file.txt",L"fileunitestdata\\result.txt", content, desirecContents);
        VerifySingleFile(L"fileunitestdata\\RDestdirForSet\\file1.txt",L"fileunitestdata\\result.txt", content, desirecContents);
        VerifySingleFile(L"fileunitestdata\\RDestdirForSet\\file2.txt",L"fileunitestdata\\result.txt", content, desirecContents);
}




        

