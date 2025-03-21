#include "device_manager.h"

void add_device(device_manager_t*dm,device_node_t*new_device)
{
dm->device_count++;

new_device->next=dm->head;
dm->head=new_device;

}
