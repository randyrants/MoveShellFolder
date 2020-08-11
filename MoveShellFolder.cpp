#include "pch.h"
#include "shlobj.h"
#include "ShObjIdl.h"
#include "Shlwapi.h"
#include "vcclr.h"

using namespace System;
using namespace System::IO;

void MoveDirectory(IKnownFolderManager* folderManager, KNOWNFOLDERID guid,  String ^moveTo)
{
    // If there's an existing directory, leave it alone; if we need one create one.  If the create fails, don't try to move anything
    Console::WriteLine("Creating {0}", moveTo);
    try
    {
        if (Directory::Exists(moveTo) == false)
        {
            Directory::CreateDirectory(moveTo);
        }
    }
    catch (Exception^ exception)
    {
        Console::WriteLine(exception->Message);
        return;
    }

    // Tell the folder manager to move all of the files from the current location to the new location and then tell the Shell about it
    Console::WriteLine("Moving to {0}", moveTo);
    LPWSTR error;
    pin_ptr<const wchar_t> ptrNewPath = PtrToStringChars(moveTo); // holds onto the string we've been passed in and converts it to an LPCWSTR
    folderManager->Redirect(guid, NULL, KF_REDIRECT_COPY_CONTENTS | KF_REDIRECT_DEL_SOURCE_CONTENTS | KF_REDIRECT_UNPIN | KF_REDIRECT_PIN, ptrNewPath, 0, NULL, &error);
}

int main(array<System::String ^> ^args)
{
    Console::WriteLine("Starting the app...");

    // Start COM
    CoInitialize(0);

    // Grab an instance of the KnownFolderManager which does all the heavy lifting of moving, pinning, iconizing the folders
    IKnownFolderManager* folderManager = 0;
    CoCreateInstance(CLSID_KnownFolderManager, NULL, CLSCTX_ALL, IID_IKnownFolderManager, (void**)&folderManager);

    // Move the three directories I care about 
    MoveDirectory(folderManager, FOLDERID_Desktop, gcnew String("C:\\Desktop"));
    MoveDirectory(folderManager, FOLDERID_Documents, gcnew String("C:\\Documents"));
    MoveDirectory(folderManager, FOLDERID_Downloads, gcnew String("C:\\Downloads"));

    // Be a good citizen and clean up the COM object
    folderManager->Release();
    folderManager = 0;
    CoUninitialize();

    // Wait until it's done
    Console::WriteLine("Complete!  Press any key to close.");
    Console::ReadKey();
    return 0;
}
