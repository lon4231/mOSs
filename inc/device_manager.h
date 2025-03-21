#pragma once

#include "std_types.h"

enum DEVICE_IDS
{
DEVICE_ID_FRAMEBUFFER,

};

struct device_node_t
{
CHAR16 dev_signature[8];
UINT32 dev_id;
void*  dev_data;
device_node_t*next;
}__attribute__((packed));

struct device_manager_t
{
UINTN device_count;
device_node_t*head;
};

void add_device(device_manager_t*dm,device_node_t*new_device);


