#include <efi/efi.h>
#include <efi_globals.h>
#include <cstr.h>
#include <kernel.h>

extern "C" EFI_STATUS EFIAPI efi_main(EFI_HANDLE img_handle, EFI_SYSTEM_TABLE *systab)
{
    init_efi_services(systab, img_handle);
    efi_cout_handle->ClearScreen(efi_cout_handle);

    kernel_arguments_t kernel_arguments = {nullptr};

    for (UINTN i = 0; i < systab->NumberOfTableEntries; ++i)
    {
        if (memcmp(efi_systab_handle->ConfigurationTable[i].VendorTable, (void *)"RSD PTR ", 8) == 0)
        {
            acpi_xsdp_t *xsdp = (acpi_xsdp_t *)efi_systab_handle->ConfigurationTable[i].VendorTable;

            if (kernel_arguments.xsdp != nullptr)
            {
                (xsdp->Revision > kernel_arguments.xsdp->Revision) ? kernel_arguments.xsdp = xsdp : kernel_arguments.xsdp;
            }
            else
            {
                kernel_arguments.xsdp = xsdp;
            }
        }
    }

    jump_to_kernel(&kernel_arguments);

    asm volatile("cli;hlt");

    return 0;
}