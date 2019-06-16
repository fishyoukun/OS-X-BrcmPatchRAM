
#include <Headers/plugin_start.hpp>
#include <Headers/kern_api.hpp>

#include "cfg.h"
#include "Common.h"
#include "symbols.h"

IOCatalogue_startMatching_symbol ADDPR(startMatching_symbol) {};
IOCatalogue_addDrivers ADDPR(addDrivers) {};
IOCatalogue_removeDrivers ADDPR(removeDrivers) {};

void ADDPR(processSymbols)(KernelPatcher &patcher) {
  if (!ADDPR(startMatching_symbol))
  {
    ADDPR(startMatching_symbol) = reinterpret_cast<IOCatalogue_startMatching_symbol>(patcher.solveSymbol(KernelPatcher::KernelID, "__ZN11IOCatalogue13startMatchingEPK8OSSymbol"));
    if (!ADDPR(startMatching_symbol))
      SYSLOG("BRCMPATCH", "Fail to resolve IOCatalogue::startMatching method, error = %d", patcher.getError());
  }
  
  if (!ADDPR(addDrivers))
  {
    ADDPR(addDrivers) = reinterpret_cast<IOCatalogue_addDrivers>(patcher.solveSymbol(KernelPatcher::KernelID, "__ZN11IOCatalogue10addDriversEP7OSArrayb"));
    if (!ADDPR(addDrivers))
      SYSLOG("BRCMPATCH", "Fail to resolve IOCatalogue::removeDrivers method, error = %d", patcher.getError());
  }
  
  if (!ADDPR(removeDrivers))
  {
    ADDPR(removeDrivers) = reinterpret_cast<IOCatalogue_removeDrivers>(patcher.solveSymbol(KernelPatcher::KernelID, "__ZN11IOCatalogue13removeDriversEP12OSDictionaryb"));
    if (!ADDPR(removeDrivers))
      SYSLOG("BRCMPATCH", "Fail to resolve IOCatalogue::removeDrivers method, error = %d", patcher.getError());
  }
  
  // Ignore all the errors for other processors
  patcher.clearError();
};

const char *Configuration::bootargOff[] {
  "-brcmproff"
};

const char *Configuration::bootargDebug[] {
  "-brcmprdbg"
};

const char *Configuration::bootargBeta[] {
  "-brcmprbeta"
};

Configuration ADDPR(brcmpr_config);

void Configuration::readArguments() {
  disabled = checkKernelArgument(bootargOff[0]);
}

PluginConfiguration ADDPR(config) {
  xStringify(PRODUCT_NAME),
  parseModuleVersion(xStringify(MODULE_VERSION)),
  LiluAPI::AllowNormal | LiluAPI::AllowInstallerRecovery | LiluAPI::AllowSafeMode,
  ADDPR(brcmpr_config).bootargOff,
  arrsize(ADDPR(brcmpr_config).bootargOff),
  ADDPR(brcmpr_config).bootargDebug,
  arrsize(ADDPR(brcmpr_config).bootargDebug),
  ADDPR(brcmpr_config).bootargBeta,
  arrsize(ADDPR(brcmpr_config).bootargBeta),
  KernelVersion::Mojave,
  KernelVersion::Catalina,
  []() {
    ADDPR(brcmpr_config).readArguments();
    lilu.onPatcherLoadForce([](void *user, KernelPatcher &patcher) {
      ADDPR(processSymbols)(patcher);
    });
  }
};
