    // ExitBootServices Example
    
    
    #include <efi.h>
    EFI_STATUS efi_main(
        EFI_HANDLE ImageHandle,
        EFI_SYSTEM_TABLE *SystemTable
    ) { 
        UINTN mapSize = 0;
        EFI_MEMORY_DESCRIPTOR *memoryMap = NULL;
        UINTN mapKey = 0;
        UINTN descriptorSize = 0;
        UINT32 descriptorVersion = 0;
        EFI_STATUS status;

        SystemTable->BootServices->GetMemoryMap(
            &mapSize,NULL,&mapKey,&descriptorSize,&descriptorVersion
        );
        mapSize += 2 * descriptorSize;
        SystemTable->BootServices->AllocatePool(
            EfiLoaderData, mapSize, (void**)&memoryMap);
        //getting actual memory map
        SystemTable->BootServices->GetMemoryMap(
            &mapSize, memoryMap, &mapKey, &descriptorSize, &descriptorVersion
        );
        //exiting from BS
        status = SystemTable->BootServices->ExitBootServices(ImageHandle, mapKey);

        //error handling
        if(EFI_ERROR(status))  {
          SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
          SystemTable->ConOut->OutputString(SystemTable->ConOut, 
          L"ExitBootServices Failed.\r\n");
          SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
        }

        //cpu halt
        while(1) __asm__ volatile ("cli; hlt");
    }