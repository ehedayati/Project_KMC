/**
 * Created by Eisa Hedayati on 
 * 11:50 PM
 * 12/15/16.
 */
//
#include "main.h"


unsigned long long getTotalSystemMemory() {
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);

    return (unsigned long long int) (pages * page_size);
}



int GetRamInKB(void) {
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if(meminfo == NULL)
        return -1;

    char line[256];
    while(fgets(line, sizeof(line), meminfo))
    {
        int ram;
        if(sscanf(line, "MemAvailable: %d kB", &ram) == 1)
        {
            fclose(meminfo);
            return ram;
        }
    }

    // If we got here, then we couldn't find the proper line in the meminfo file:
    // do something appropriate like return an error code, throw an exception, etc.
    fclose(meminfo);
    return -1;
}
