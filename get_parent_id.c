#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int parentId = get_parent_id();
    printf(2, "Parent id is : %d\n", parentId);
    exit();
}