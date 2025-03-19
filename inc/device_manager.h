#include "std_types.h"

struct device_node_t
{
CHAR16 dev_signature[8];
UINT32 dev_id;
void*  dev_data;
device_node_t*next;
}__attribute__((packed));
