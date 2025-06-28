#include <kernel.h>
#include <efi_globals.h>

void load_kernel(kernel_handle_t *handle, const char16_t *path)
{

    {
        EFI_FILE_PROTOCOL *root_file;
        EFI_FILE_PROTOCOL *kernel_file;

        efi_fs_protocol_handle->OpenVolume(efi_fs_protocol_handle, &root_file);

        root_file->Open(root_file, &kernel_file, (char16_t *)path, EFI_FILE_MODE_READ, 0);

        root_file->Close(root_file);
    }
}

void jump_to_kernel(kernel_handle_t *handle, kernel_arguments_t *args)
{



}