#ifdef __APPLE__ //Mac OSX has a different name for the header file
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

#include <CL/Utils/Utils.h>

#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <stdint.h> // UINTMAX_MAX

int main(int argc, char* argv[])
{
    cl_int error = CL_SUCCESS;
    cl_device_id device = NULL;

    OCLERROR_PAR(
        device = cl_util_get_device(
            argc > 1 ? atoi(argv[1]) : 0,
            argc > 2 ? atoi(argv[2]) : 0,
            CL_DEVICE_TYPE_ALL,
            &error),
        error, end);

    cl_util_print_device_info(device);

    end:
    if (error) cl_util_print_error(error);
    return error;

    return 0;
}
