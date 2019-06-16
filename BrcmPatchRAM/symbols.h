//
//  symbols.h
//  BrcmPatchRAM2
//
//  Created by Ariel Abreu on 6/15/19.
//

#ifndef symbols_h
#define symbols_h

using IOCatalogue_startMatching_symbol = bool (*)(void *that, OSSymbol const* bundle_identifier);
using IOCatalogue_addDrivers = bool (*)(void *that, OSArray *array, bool doNubMatching);
using IOCatalogue_removeDrivers = bool (*)(void *that, OSDictionary *matching, bool doNubMatching);

#endif /* symbols_h */
