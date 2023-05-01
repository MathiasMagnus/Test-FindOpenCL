#ifdef __APPLE__ //Mac OSX has a different name for the header file
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

int main()
{
    return sizeof(cl_platform_id) - sizeof(cl_context);
}
