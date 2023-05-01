#include <CL/opencl.hpp>

#include <vector>     // std::vector
#include <exception>  // std::runtime_error, std::exception
#include <iostream>   // std::cout
#include <fstream>    // std::ifstream
#include <random>     // std::default_random_engine, std::uniform_real_distribution
#include <algorithm>  // std::transform
#include <cstdlib>    // EXIT_FAILURE
#include <execution>  // std::execution::par_unseq, std::execution::seq
#include <filesystem> // std::filesystem::canonical

#include <CL/Utils/Context.hpp> // cl::util::get_context

int main(int argc, char *argv[])
{
    try
    {
        // Platform & device selection
        cl::Context context =
            cl::util::get_context(
                argc > 1 ? std::atoi(argv[1]) : 0,
                argc > 2 ? std::atoi(argv[2]) : 0,
                CL_DEVICE_TYPE_ALL);
        cl::Device device = context.getInfo<CL_CONTEXT_DEVICES>().at(0);

        std::cout << "Selected platform: " << cl::Platform{device.getInfo<CL_DEVICE_PLATFORM>()}.getInfo<CL_PLATFORM_NAME>() << std::endl;
        std::cout << "Selected device: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
    }
    catch (cl::Error &error) // If any OpenCL error occurs
    {
        std::cerr << error.what() << "(" << error.err() << ")" << std::endl;
        std::exit(error.err());
    }
    catch (std::exception &error) // If STL/CRT error occurs
    {
        std::cerr << error.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
