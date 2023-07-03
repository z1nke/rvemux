#ifndef RVEMUX_MACHINE_MMU_HPP
#define RVEMUX_MACHINE_MMU_HPP

#include "Basic/Types.hpp"

#include <cstdio>
#include <elf.h>

namespace rvemux {

class MemManagerUnit {
public:
  void loadELF(const char *Program);

  u64 getEntry() const { return Entry; }
  u64 getHostAlloc() const { return HostAlloc; }
  u64 getGuestAlloc() const { return GuestAlloc; }
  u64 getBaseAddress() const { return BaseAddr; }

private:
  void loadSegment(const Elf64_Phdr &Phdr, FILE *Fp);

private:
  u64 Entry = 0x0;

  // [ ELF | HostAlloc ] --------------> [ ELF |-------|      ]
  //                         to guest          ^       ^
  //                                           |       |
  //                                          Base GuestAlloc
  u64 HostAlloc = 0x0;
  u64 GuestAlloc = 0x0;
  u64 BaseAddr = 0x0;
};

} // namespace rvemux

#endif // RVEMUX_MACHINE_MMU_HPP