#define GNUC_VERSION (__GNUC__*1000 + __GNUC_MAJOR__*10)
#if (GNUC_VERSION >= 4060) || defined(__clang__)
# pragma GCC diagnostic ignored "-Wdeprecated"
#endif

// XL C++ on AIX does not define VSX and does not
// provide an option to set it. We have to set it
// for the code below. This define must stay in
// sync with the define in test_ppc_power7.cxx.
#if defined(_AIX) && defined(_ARCH_PWR7) && defined(__xlC__)
# define __VSX__ 1
#endif

#include <altivec.h>
int main(int argc, char* argv[])
{
#if defined(_ARCH_PWR7) && defined(__VSX__)
    // PWR7
    __vector unsigned int a = {1,2,3,4};
    __vector unsigned int b = vec_ld(0, (unsigned int*)argv[0]);
    __vector unsigned int c = vec_xor(a, b);

    // VSX
    __vector unsigned int x = {5,6,7,8};
    __vector unsigned int y = vec_xl(0, (unsigned int*)argv[0]);
    __vector unsigned int z = vec_xor(x, y);
    __vector unsigned long xx = {1,2};
    __vector unsigned long yy = (__vector unsigned long)y;
#else
    int x[-1];
#endif
    return 0;
}
