 #ifndef _FACE_H_
 #define _FACE_H_
 #if defined EXTERN
 #undef EXTERN
 #endif
 #if defined ___1273
 #define EXTERN
 #else
 #define EXTERN extern
 #endif
#include "ItemAddress.h"
namespace tecplot { class ___460; } namespace tecplot { namespace ___2140 { class ValueProducerInterface; }} inline ___372 ___2008( tecplot::___2090 ___2710, tecplot::___2090 ___2711, tecplot::___2090 ___2712, tecplot::___2090 ___2713) { return ((___2710 == ___2711 && ___2712 == ___2713) || (___2710 == ___2713 && ___2711 == ___2712) || (___2710 == ___2712)                   || (___2711 == ___2713)); } typedef enum { ___1301, ___1302, ___1298, ___1300, END_FaceObscuration_e, ___1299 = ___329 } FaceObscuration_e; EXTERN ___2227 ___1754(___2227 ___2809, ___2227 ___2814, ___2227 ___2817, ___2227 ___1145, ___2227 ___1252); EXTERN void ___1776( ___806 const*                                ___805, ___802 const*                                ___801, ___2227                                      ___3896, tecplot::___2140::ValueProducerInterface const& ___2744, ___1146                               ___3096, ___1146                               ___1138, ___2227&                                     ___2693, ___1172&                                    ___2694, tecplot::___460&                    ___459); EXTERN FaceObscuration_e ___1665( ___806 const*             ___805, ___802 const*             ___801, ___3501                      ___3, ___2227                   ___1145, ___2227                   ___1442, ___372                   ConsiderValueBlanking, ___372                   ConsiderIJKBlanking, ___372                   ConsiderDepthBlanking, ___372                   ConsiderClipBlanking, tecplot::___460& ___459); EXTERN ___1172 ___1765(ZoneType_e ___4693); EXTERN ___1172 ___1666(ZoneType_e ___4693, ___2227  ___1906, ___2227  ___2114, ___2227  ___2159); EXTERN void ___1778(___4582 const ___3142[], ___4582 ___4265[], int32_t& ___2841, ___372 ___1996); EXTERN CollapsedStatus_e ___1774( ___806 const*                                ___804, ___802 const*                                ___800, tecplot::___2140::ValueProducerInterface const& ___3878); EXTERN CollapsedStatus_e ___1774( ___806 const*      ___804, ___802 const*      ___800, tecplot::___2090 ___2710, tecplot::___2090 ___2711, tecplot::___2090 ___2712, tecplot::___2090 ___2713); template <typename T> inline CollapsedStatus_e ___1775( T const* ___1296, size_t   ___2804) { REQUIRE(VALID_REF(___1296)); REQUIRE(2 <= ___2804 && ___2804 <= 4); if (___2804 == 4) { if (___1296[0] == ___1296[1]) { if (___1296[0] == ___1296[2]) { if (___1296[0] == ___1296[3]) return ___509; else return ___508; } else if (___1296[2] == ___1296[3] || ___1296[0] == ___1296[3]) { return ___508; } else { return ___511; } } else if (___1296[1] == ___1296[2]) { if (___1296[1] == ___1296[3] || ___1296[0] == ___1296[3]) return ___508; else return ___511; } else if (___1296[2] == ___1296[3]) { if (___1296[0] == ___1296[2]) return ___508; else return ___511; } else if (___1296[0] == ___1296[3]) { if (___1296[1] == ___1296[3]) return ___508; else return ___511; } else if (___1296[0] == ___1296[2] || ___1296[1] == ___1296[3]) { return ___510; } else { return ___513; } } else if (___2804 == 3) { if (___1296[0] != ___1296[1] && ___1296[0] != ___1296[2] && ___1296[1] != ___1296[2]) return ___513; else if (___1296[0] == ___1296[1] && ___1296[0] == ___1296[2]) return ___509; else return ___508; } else /* if (___2804 == 2) */ { ___478(___2804 == 2); if (___1296[0] != ___1296[1]) return ___513; else return ___509; } } template <typename T> inline CollapsedStatus_e ___1671( ZoneType_e ___4692, T const*   ___1296, ___1172 face) { REQUIRE(___2018(___4692)); REQUIRE(VALID_REF(___1296)); REQUIRE(IMPLICATION(___4692 == ___4696,  face == 0)); REQUIRE(IMPLICATION(___4692 == ___4702, 0 <= face && face <= 2)); REQUIRE(IMPLICATION(___4692 == ___4700,     0 <= face && face <= 3)); REQUIRE(IMPLICATION(___4692 == ___4701,    0 <= face && face <= 3)); REQUIRE(IMPLICATION(___4692 == ___4695,    0 <= face && face <= 5));
size_t ___2804 = 0; T const* ___1438 = ___1296; T ___2314[2]; switch (___4692) { case ___4696: ___2804 = 2; break; case ___4701:   ___2804 = 3; break; case ___4695:   ___2804 = 4; break; case ___4702: case ___4700: { ___2804 = 2; if (face == (___4692 == ___4702 ? 2 : 3)) { ___2314[0] = ___1296[face]; ___2314[1] = ___1296[0]; ___1438 = ___2314; } else { ___1438 = &___1296[face]; } } break; default: ___478(___1305); break; } return ___1775(___1438, ___2804); } EXTERN CollapsedStatus_e ___1671( ___2727            ___2707, tecplot:: ___2090 ___451, ___1172            face);
 #if defined ALLOW_USERDEF_NO_NEIGHBORING_ELEMENT
EXTERN ___372 ___2066(___1292 ___1275, ___2227       ___1145, ___2227       ___1252);
 #endif
 #endif
