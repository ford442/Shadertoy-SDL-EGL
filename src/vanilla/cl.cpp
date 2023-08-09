#include "../../include/vanilla/cl.h"

void testclcla(){
cl_device_id device;
  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
  // Create an OpenCL kernel.
cl_program program;
  cl_kernel kernel = clCreateKernel(program, "add", NULL);
 /*
// Create an OpenCL buffer to store the input vectors.
cl_error error;
  cl_mem input_vector_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR, sizeof(float) * 2, NULL, &error);
  // Create an OpenCL buffer to store the output vector.
  cl_mem output_vector_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR, sizeof(float) * 2, NULL, &error);
  // Execute the OpenCL kernel.
  size_t global_work_size = 2;
  size_t local_work_size = 1;
  clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_work_size, &local_work_size, 0, NULL, &event);
  clEnqueueReadBuffer(command_queue, output_vector_buffer, CL_TRUE, 0, sizeof(float) * 2, output_vector, 0, NULL, &event);
  // Wait for the kernel to finish executing.
  clWaitForEvents(1, &event);
  // Check for errors.
  if (error != CL_SUCCESS) {
    fprintf(stderr, "Error creating OpenCL context: %d\n", error);
    */
    return 1;
}

extern"C"{

void testclcl(){
testclcla();
}

}
