#include <iostream>
#include <bitset>
#include <intrin.h>
#include "util.h"

const bool check_avx_support() {

    int cpuInfo[4];

    __cpuid(cpuInfo, 1);

    unsigned int eax = cpuInfo[0];
    unsigned int ebx = cpuInfo[1];
    unsigned int ecx = cpuInfo[2];
    unsigned int edx = cpuInfo[3];

    bool osxsave = (ecx & (1 << 27)) != 0;
    bool avx = (ecx & (1 << 28)) != 0;

    if (osxsave && avx) {
        unsigned long long xcrFeatureMask = _xgetbv(0);

        return (xcrFeatureMask & 0x6) == 0x6;
    }

    return false;
}

const bool check_avx512_support() {
    unsigned int eax, ebx, ecx, edx;

    // CPUID function 7, sub-leaf 0
    __cpuidex(reinterpret_cast<int*>(&eax), 7, 0);

    // Check if bit 16 of EBX is set (AVX512F support)
    return (eax & (1 << 16)) != 0;
}

void logSIMDSupport() {
    if (check_avx_support) {
        logger::consoleLog("CPU supports AVX vectorization", INFO);
    }
    if (check_avx512_support) {
        logger::consoleLog("CPU supports AVX-512 vectorization", INFO);
    }
}