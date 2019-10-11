#ifndef _DCOMPLEX_H_

#ifdef __SUNPRO_CC
#   include <complex.h>

    typedef complex dcomplex;

#   define __REAL(complexValue) ::real(complexValue)
#   define __IMAG(complexValue) ::imag(complexValue)
#   define STD(x)             x
#else

#   ifdef _WIN32
#      pragma warning(disable: 4275)
#   endif
#   include <complex>

    typedef std::complex<double> dcomplex;

#   define __REAL(complexValue) complexValue.real()
#   define __IMAG(complexValue) complexValue.imag()
#   define STD(x)             std::x
#endif


#endif // _DCOMPLEX_H_
