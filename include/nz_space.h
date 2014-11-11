#ifndef NZ_SPACE_H
#define NZ_SPACE_H

#ifdef __linux__
#ifdef __KERNEL__
#define NZ_KERNELSPACE
#else
#define NZ_USERSPACE
#endif // __KERNEL__
#else
#define NZ_USERSPACE
#endif // __linux__

#endif // NZ_SPACE_H