#ifndef STAN_MATH_OPENCL_TRANSPOSE_HPP
#define STAN_MATH_OPENCL_TRANSPOSE_HPP
#ifdef STAN_OPENCL
#include <stan/math/opencl/matrix_cl.hpp>
#include <stan/math/opencl/kernels/transpose.hpp>
#include <CL/cl.hpp>

namespace stan {
namespace math {
/**
 * Takes the transpose of the matrix on the OpenCL device.
 *
 * @param src the input matrix
 *
 * @return transposed input matrix
 *
 */
inline matrix_cl transpose(matrix_cl& src) {
  matrix_cl dst(src.cols(), src.rows());
  if (dst.size() == 0)
    return dst;
  try {
    cl::Event transpose_event = opencl_kernels::transpose(
        cl::NDRange(src.rows(), src.cols()), dst, src, src.rows(), src.cols());
    dst.add_event(transpose_event);
  } catch (const cl::Error& e) {
    check_opencl_error("transpose", e);
  }
  return dst;
}
}  // namespace math
}  // namespace stan

#endif
#endif
