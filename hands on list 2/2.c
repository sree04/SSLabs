Write a program to print the system resource limits. Use getrlimit system call.


#include <stdio.h> // for printf func
#include <stdlib.h>//for standard libraries
#include <sys/resource.h>// for resource limit related func and ds

void print_resource_limit(int resource, const char *resource_name)// specifies which resource limit to retrieve
{
    struct rlimit rlim; // struct to hold info abt resource limits

    if (getrlimit(resource, &rlim) == 0)//retrieve the resource limit for specified resource
    {
        printf("%s resource limits:\n", resource_name);
        printf("  Soft Limit: %lu\n", rlim.rlim_cur);
        printf("  Hard Limit: %lu\n", rlim.rlim_max);
    } else {
        perror("getrlimit");
    }
}

int main() {
    // Print resource limits for various resources
    // shows how to retieve and print resouce limits for different aspects of system resource management
    print_resource_limit(RLIMIT_CORE, "Core");
    print_resource_limit(RLIMIT_CPU, "CPU");
    print_resource_limit(RLIMIT_DATA, "Data");
    print_resource_limit(RLIMIT_FSIZE, "File Size");
    print_resource_limit(RLIMIT_NOFILE, "Number of File Descriptors");
    print_resource_limit(RLIMIT_STACK, "Stack");

    return 0;
}

