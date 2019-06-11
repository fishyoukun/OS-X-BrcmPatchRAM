
#include <Headers/plugin_start.hpp>
#include <Headers/kern_api.hpp>

static const char *bootargOff[] {
    "-brcmpatchoff"
};

static const char *bootargBeta[] {
    "-brcmpatchbeta"
};

PluginConfiguration ADDPR(config) {
    "BrcmPatchRAM2",
    parseModuleVersion("2.2.10"),
    LiluAPI::AllowNormal,
    bootargOff,
    arrsize(bootargOff),
    nullptr,
    0,
    bootargBeta,
    arrsize(bootargBeta),
    KernelVersion::HighSierra,
    KernelVersion::Catalina,
    []() {
        //noBioStart();
    }
};
