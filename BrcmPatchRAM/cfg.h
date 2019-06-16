//
//  cfg.h
//  BrcmPatchRAM2
//
//  Created by Ariel Abreu on 6/15/19.
//

#ifndef cfg_h
#define cfg_h

#include <Headers/kern_util.hpp>

class Configuration {
public:
  static const char *bootargOff[];
  static const char *bootargDebug[];
  static const char *bootargBeta[];
  
  void readArguments();
  
  bool disabled = false;
  
  Configuration() = default;
};

extern Configuration ADDPR(brcmpr_config);

#endif /* cfg_h */
