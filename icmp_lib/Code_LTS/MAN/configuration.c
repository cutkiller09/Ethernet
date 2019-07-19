/***************************************************************/
/* FUNCTION : Export data, constants, types and functions      */
/*                                                             */
/* ENVIRONMENT : PPC5554                                       */
/***************************************************************/
#include "standard.h"

#include "interface.h"
#include "arinc_int.h"

#include "configuration.h"


/***************************************************************/
/*                                                             */
/*                         GLOBAL DATA                         */
/*                                                             */
/***************************************************************/
T_BSP_CONFIGURATION         I_BSP_conf;


/***************************************************************/
/*                                                             */
/*                      GLOBAL CONSTANTS                       */
/*                                                             */
/***************************************************************/

/* Default ARINC filter definition */
const UNS16 K_TAB_arinc_rx_filter[ARINC_RX_FILTER_TABLE_SIZE] =
{
    /* SDI 00 */
    (UNS16) 0xFFFF, /* Label 0200 & Label 00 */
    (UNS16) 0xFFFF, /* Label 0201 & Label 01 */
    (UNS16) 0xFFFF, /* Label 0202 & Label 02 */
    (UNS16) 0xFFFF, /* Label 0203 & Label 03 */
    (UNS16) 0xFFFF, /* Label 0204 & Label 04 */
    (UNS16) 0xFFFF, /* Label 0205 & Label 05 */
    (UNS16) 0xFFFF, /* Label 0206 & Label 06 */
    (UNS16) 0xFFFF, /* Label 0207 & Label 07 */
    (UNS16) 0xFFFF, /* Label 0210 & Label 010 */
    (UNS16) 0xFFFF, /* Label 0211 & Label 011 */
    (UNS16) 0xFFFF, /* Label 0212 & Label 012 */
    (UNS16) 0xFFFF, /* Label 0213 & Label 013 */
    (UNS16) 0xFFFF, /* Label 0214 & Label 014 */
    (UNS16) 0xFFFF, /* Label 0215 & Label 015 */
    (UNS16) 0xFFFF, /* Label 0216 & Label 016 */
    (UNS16) 0xFFFF, /* Label 0217 & Label 017 */
    (UNS16) 0xFFFF, /* Label 0220 & Label 020 */
    (UNS16) 0xFFAA, /* Label 0221 & Label 021 */
    (UNS16) 0xFFEE, /* Label 0222 & Label 022 */
    (UNS16) 0xFFFF, /* Label 0223 & Label 023 */
    (UNS16) 0xFFFF, /* Label 0224 & Label 024 */
    (UNS16) 0xFFFF, /* Label 0225 & Label 025 */
    (UNS16) 0xFFFF, /* Label 0226 & Label 026 */
    (UNS16) 0xFFFF, /* Label 0227 & Label 027 */
    (UNS16) 0xFFFF, /* Label 0230 & Label 030 */
    (UNS16) 0xFFFF, /* Label 0231 & Label 031 */
    (UNS16) 0xFFFF, /* Label 0232 & Label 032 */
    (UNS16) 0xFFFF, /* Label 0233 & Label 033 */
    (UNS16) 0xFFFF, /* Label 0234 & Label 034 */
    (UNS16) 0xFFFF, /* Label 0235 & Label 035 */
    (UNS16) 0xFFFF, /* Label 0236 & Label 036 */
    (UNS16) 0xFFFF, /* Label 0237 & Label 037 */
    (UNS16) 0xFFFF, /* Label 0240 & Label 040 */
    (UNS16) 0xFFFF, /* Label 0241 & Label 041 */
    (UNS16) 0xFFFF, /* Label 0242 & Label 042 */
    (UNS16) 0xFFFF, /* Label 0243 & Label 043 */
    (UNS16) 0xFFFF, /* Label 0244 & Label 044 */
    (UNS16) 0xFFFF, /* Label 0245 & Label 045 */
    (UNS16) 0xFFFF, /* Label 0246 & Label 046 */
    (UNS16) 0xFFFF, /* Label 0247 & Label 047 */
    (UNS16) 0xFFFF, /* Label 0250 & Label 050 */
    (UNS16) 0xFFFF, /* Label 0251 & Label 051 */
    (UNS16) 0xFFFF, /* Label 0252 & Label 052 */
    (UNS16) 0xFFFF, /* Label 0253 & Label 053 */
    (UNS16) 0xFFFF, /* Label 0254 & Label 054 */
    (UNS16) 0xFFFF, /* Label 0255 & Label 055 */
    (UNS16) 0xFFFF, /* Label 0256 & Label 056 */
    (UNS16) 0xFFFF, /* Label 0257 & Label 057 */
    (UNS16) 0xFFFF, /* Label 0260 & Label 060 */
    (UNS16) 0xFFFF, /* Label 0261 & Label 061 */
    (UNS16) 0xFFFF, /* Label 0262 & Label 062 */
    (UNS16) 0xFFFF, /* Label 0263 & Label 063 */
    (UNS16) 0xFFFF, /* Label 0264 & Label 064 */
    (UNS16) 0xFFFF, /* Label 0265 & Label 065 */
    (UNS16) 0xFFFF, /* Label 0266 & Label 066 */
    (UNS16) 0xFFFF, /* Label 0267 & Label 067 */
    (UNS16) 0xFFFF, /* Label 0270 & Label 070 */
    (UNS16) 0xFFFF, /* Label 0271 & Label 071 */
    (UNS16) 0xFFFF, /* Label 0272 & Label 072 */
    (UNS16) 0xFFFF, /* Label 0273 & Label 073 */
    (UNS16) 0xFFFF, /* Label 0274 & Label 074 */
    (UNS16) 0xFFFF, /* Label 0275 & Label 075 */
    (UNS16) 0xFFFF, /* Label 0276 & Label 076 */
    (UNS16) 0xFFFF, /* Label 0277 & Label 077 */
    (UNS16) 0xFFFF, /* Label 0300 & Label 0100 */
    (UNS16) 0xFFFF, /* Label 0301 & Label 0101 */
    (UNS16) 0xFFFF, /* Label 0302 & Label 0102 */
    (UNS16) 0xFFFF, /* Label 0303 & Label 0103 */
    (UNS16) 0xFFFF, /* Label 0304 & Label 0104 */
    (UNS16) 0xFFFF, /* Label 0305 & Label 0105 */
    (UNS16) 0xFFFF, /* Label 0306 & Label 0106 */
    (UNS16) 0xFFFF, /* Label 0307 & Label 0107 */
    (UNS16) 0xFFFF, /* Label 0310 & Label 0110 */
    (UNS16) 0xFFFF, /* Label 0311 & Label 0111 */
    (UNS16) 0xFFFF, /* Label 0312 & Label 0112 */
    (UNS16) 0xFFFF, /* Label 0313 & Label 0113 */
    (UNS16) 0xFFFF, /* Label 0314 & Label 0114 */
    (UNS16) 0xFFFF, /* Label 0315 & Label 0115 */
    (UNS16) 0xFFFF, /* Label 0316 & Label 0116 */
    (UNS16) 0xFFFF, /* Label 0317 & Label 0117 */
    (UNS16) 0xFFFF, /* Label 0320 & Label 0120 */
    (UNS16) 0xFFFF, /* Label 0321 & Label 0121 */
    (UNS16) 0xFFFF, /* Label 0322 & Label 0122 */
    (UNS16) 0xFFFF, /* Label 0323 & Label 0123 */
    (UNS16) 0xFFFF, /* Label 0324 & Label 0124 */
    (UNS16) 0xFFFF, /* Label 0325 & Label 0125 */
    (UNS16) 0xFFFF, /* Label 0326 & Label 0126 */
    (UNS16) 0xFFFF, /* Label 0327 & Label 0127 */
    (UNS16) 0xFFFF, /* Label 0330 & Label 0130 */
    (UNS16) 0xFFFF, /* Label 0331 & Label 0131 */
    (UNS16) 0xFFFF, /* Label 0332 & Label 0132 */
    (UNS16) 0xFFFF, /* Label 0333 & Label 0133 */
    (UNS16) 0xFFFF, /* Label 0334 & Label 0134 */
    (UNS16) 0xFFFF, /* Label 0335 & Label 0135 */
    (UNS16) 0xFFFF, /* Label 0336 & Label 0136 */
    (UNS16) 0xFFFF, /* Label 0337 & Label 0137 */
    (UNS16) 0xFFFF, /* Label 0340 & Label 0140 */
    (UNS16) 0xFFFF, /* Label 0341 & Label 0141 */
    (UNS16) 0xFFFF, /* Label 0342 & Label 0142 */
    (UNS16) 0xFFFF, /* Label 0343 & Label 0143 */
    (UNS16) 0xFFFF, /* Label 0344 & Label 0144 */
    (UNS16) 0xFFFF, /* Label 0345 & Label 0145 */
    (UNS16) 0xFFFF, /* Label 0346 & Label 0146 */
    (UNS16) 0xFFFF, /* Label 0347 & Label 0147 */
    (UNS16) 0xFFFF, /* Label 0350 & Label 0150 */
    (UNS16) 0xFFFF, /* Label 0351 & Label 0151 */
    (UNS16) 0xFFFF, /* Label 0352 & Label 0152 */
    (UNS16) 0xFFFF, /* Label 0353 & Label 0153 */
    (UNS16) 0xFFFF, /* Label 0354 & Label 0154 */
    (UNS16) 0xFFFF, /* Label 0355 & Label 0155 */
    (UNS16) 0xFFFF, /* Label 0356 & Label 0156 */
    (UNS16) 0xFFFF, /* Label 0357 & Label 0157 */
    (UNS16) 0x11FF, /* Label 0360 & Label 0160 */
    (UNS16) 0xFFFF, /* Label 0361 & Label 0161 */
    (UNS16) 0xFFFF, /* Label 0362 & Label 0162 */
    (UNS16) 0xFFFF, /* Label 0363 & Label 0163 */
    (UNS16) 0xFFFF, /* Label 0364 & Label 0164 */
    (UNS16) 0xFFFF, /* Label 0365 & Label 0165 */
    (UNS16) 0xFFFF, /* Label 0366 & Label 0166 */
    (UNS16) 0xFFFF, /* Label 0367 & Label 0167 */
    (UNS16) 0xFFFF, /* Label 0370 & Label 0170 */
    (UNS16) 0xFFFF, /* Label 0371 & Label 0171 */
    (UNS16) 0xFFFF, /* Label 0372 & Label 0172 */
    (UNS16) 0xFFFF, /* Label 0373 & Label 0173 */
    (UNS16) 0xFFFF, /* Label 0374 & Label 0174 */
    (UNS16) 0xFFFF, /* Label 0375 & Label 0175 */
    (UNS16) 0xFFFF, /* Label 0376 & Label 0176 */
    (UNS16) 0xFFFF, /* Label 0377 & Label 0177 */
              
    /* SDI 01 */
    (UNS16) 0xFFFF, /* Label 0200 & Label 00 */
    (UNS16) 0xFFFF, /* Label 0201 & Label 01 */
    (UNS16) 0xFFFF, /* Label 0202 & Label 02 */
    (UNS16) 0xFFFF, /* Label 0203 & Label 03 */
    (UNS16) 0xFFFF, /* Label 0204 & Label 04 */
    (UNS16) 0xFFFF, /* Label 0205 & Label 05 */
    (UNS16) 0xFFFF, /* Label 0206 & Label 06 */
    (UNS16) 0xFFFF, /* Label 0207 & Label 07 */
    (UNS16) 0xFFFF, /* Label 0210 & Label 010 */
    (UNS16) 0xFFFF, /* Label 0211 & Label 011 */
    (UNS16) 0xFFFF, /* Label 0212 & Label 012 */
    (UNS16) 0xFFFF, /* Label 0213 & Label 013 */
    (UNS16) 0xFFFF, /* Label 0214 & Label 014 */
    (UNS16) 0xFFFF, /* Label 0215 & Label 015 */
    (UNS16) 0xFFFF, /* Label 0216 & Label 016 */
    (UNS16) 0xFFFF, /* Label 0217 & Label 017 */
    (UNS16) 0xFFFF, /* Label 0220 & Label 020 */
    (UNS16) 0xFFBB, /* Label 0221 & Label 021 */
    (UNS16) 0xFFFF, /* Label 0222 & Label 022 */
    (UNS16) 0xFFFF, /* Label 0223 & Label 023 */
    (UNS16) 0xFFFF, /* Label 0224 & Label 024 */
    (UNS16) 0xFFFF, /* Label 0225 & Label 025 */
    (UNS16) 0xFFFF, /* Label 0226 & Label 026 */
    (UNS16) 0xFFFF, /* Label 0227 & Label 027 */
    (UNS16) 0xFFFF, /* Label 0230 & Label 030 */
    (UNS16) 0xFFFF, /* Label 0231 & Label 031 */
    (UNS16) 0xFFFF, /* Label 0232 & Label 032 */
    (UNS16) 0xFFFF, /* Label 0233 & Label 033 */
    (UNS16) 0xFFFF, /* Label 0234 & Label 034 */
    (UNS16) 0xFFFF, /* Label 0235 & Label 035 */
    (UNS16) 0xFFFF, /* Label 0236 & Label 036 */
    (UNS16) 0xFFFF, /* Label 0237 & Label 037 */
    (UNS16) 0xFFFF, /* Label 0240 & Label 040 */
    (UNS16) 0xFFFF, /* Label 0241 & Label 041 */
    (UNS16) 0xFFFF, /* Label 0242 & Label 042 */
    (UNS16) 0xFFFF, /* Label 0243 & Label 043 */
    (UNS16) 0xFFFF, /* Label 0244 & Label 044 */
    (UNS16) 0xFFFF, /* Label 0245 & Label 045 */
    (UNS16) 0xFFFF, /* Label 0246 & Label 046 */
    (UNS16) 0xFFFF, /* Label 0247 & Label 047 */
    (UNS16) 0xFFFF, /* Label 0250 & Label 050 */
    (UNS16) 0xFFFF, /* Label 0251 & Label 051 */
    (UNS16) 0xFFFF, /* Label 0252 & Label 052 */
    (UNS16) 0xFFFF, /* Label 0253 & Label 053 */
    (UNS16) 0xFFFF, /* Label 0254 & Label 054 */
    (UNS16) 0xFFFF, /* Label 0255 & Label 055 */
    (UNS16) 0xFFFF, /* Label 0256 & Label 056 */
    (UNS16) 0xFFFF, /* Label 0257 & Label 057 */
    (UNS16) 0xFFFF, /* Label 0260 & Label 060 */
    (UNS16) 0xFFFF, /* Label 0261 & Label 061 */
    (UNS16) 0xFFFF, /* Label 0262 & Label 062 */
    (UNS16) 0xFFFF, /* Label 0263 & Label 063 */
    (UNS16) 0xFFFF, /* Label 0264 & Label 064 */
    (UNS16) 0xFFFF, /* Label 0265 & Label 065 */
    (UNS16) 0xFFFF, /* Label 0266 & Label 066 */
    (UNS16) 0xFFFF, /* Label 0267 & Label 067 */
    (UNS16) 0xFFFF, /* Label 0270 & Label 070 */
    (UNS16) 0xFFFF, /* Label 0271 & Label 071 */
    (UNS16) 0xFFFF, /* Label 0272 & Label 072 */
    (UNS16) 0xFFFF, /* Label 0273 & Label 073 */
    (UNS16) 0xFFFF, /* Label 0274 & Label 074 */
    (UNS16) 0xFFFF, /* Label 0275 & Label 075 */
    (UNS16) 0xFFFF, /* Label 0276 & Label 076 */
    (UNS16) 0xFFFF, /* Label 0277 & Label 077 */
    (UNS16) 0xFFFF, /* Label 0300 & Label 0100 */
    (UNS16) 0xFFFF, /* Label 0301 & Label 0101 */
    (UNS16) 0xFFFF, /* Label 0302 & Label 0102 */
    (UNS16) 0xFFFF, /* Label 0303 & Label 0103 */
    (UNS16) 0xFFFF, /* Label 0304 & Label 0104 */
    (UNS16) 0xFFFF, /* Label 0305 & Label 0105 */
    (UNS16) 0xFFFF, /* Label 0306 & Label 0106 */
    (UNS16) 0xFFFF, /* Label 0307 & Label 0107 */
    (UNS16) 0xFFFF, /* Label 0310 & Label 0110 */
    (UNS16) 0xFFFF, /* Label 0311 & Label 0111 */
    (UNS16) 0xFFFF, /* Label 0312 & Label 0112 */
    (UNS16) 0xFFFF, /* Label 0313 & Label 0113 */
    (UNS16) 0xFFFF, /* Label 0314 & Label 0114 */
    (UNS16) 0xFFFF, /* Label 0315 & Label 0115 */
    (UNS16) 0xFFFF, /* Label 0316 & Label 0116 */
    (UNS16) 0xFFFF, /* Label 0317 & Label 0117 */
    (UNS16) 0xFFFF, /* Label 0320 & Label 0120 */
    (UNS16) 0xFFFF, /* Label 0321 & Label 0121 */
    (UNS16) 0xFFFF, /* Label 0322 & Label 0122 */
    (UNS16) 0xFFFF, /* Label 0323 & Label 0123 */
    (UNS16) 0xFFFF, /* Label 0324 & Label 0124 */
    (UNS16) 0xFFFF, /* Label 0325 & Label 0125 */
    (UNS16) 0xFFFF, /* Label 0326 & Label 0126 */
    (UNS16) 0xFFFF, /* Label 0327 & Label 0127 */
    (UNS16) 0xFFFF, /* Label 0330 & Label 0130 */
    (UNS16) 0xFFFF, /* Label 0331 & Label 0131 */
    (UNS16) 0xFFFF, /* Label 0332 & Label 0132 */
    (UNS16) 0xFFFF, /* Label 0333 & Label 0133 */
    (UNS16) 0xFFFF, /* Label 0334 & Label 0134 */
    (UNS16) 0xFFFF, /* Label 0335 & Label 0135 */
    (UNS16) 0xFFFF, /* Label 0336 & Label 0136 */
    (UNS16) 0xFFFF, /* Label 0337 & Label 0137 */
    (UNS16) 0xFFFF, /* Label 0340 & Label 0140 */
    (UNS16) 0xFFFF, /* Label 0341 & Label 0141 */
    (UNS16) 0xFFFF, /* Label 0342 & Label 0142 */
    (UNS16) 0xFFFF, /* Label 0343 & Label 0143 */
    (UNS16) 0xFFFF, /* Label 0344 & Label 0144 */
    (UNS16) 0xFFFF, /* Label 0345 & Label 0145 */
    (UNS16) 0xFFFF, /* Label 0346 & Label 0146 */
    (UNS16) 0xFFFF, /* Label 0347 & Label 0147 */
    (UNS16) 0xFFFF, /* Label 0350 & Label 0150 */
    (UNS16) 0xFFFF, /* Label 0351 & Label 0151 */
    (UNS16) 0xFFFF, /* Label 0352 & Label 0152 */
    (UNS16) 0xFFFF, /* Label 0353 & Label 0153 */
    (UNS16) 0xFFFF, /* Label 0354 & Label 0154 */
    (UNS16) 0xFFFF, /* Label 0355 & Label 0155 */
    (UNS16) 0xFFFF, /* Label 0356 & Label 0156 */
    (UNS16) 0xFFFF, /* Label 0357 & Label 0157 */
    (UNS16) 0x22FF, /* Label 0360 & Label 0160 */
    (UNS16) 0xFFFF, /* Label 0361 & Label 0161 */
    (UNS16) 0xFFFF, /* Label 0362 & Label 0162 */
    (UNS16) 0xFFFF, /* Label 0363 & Label 0163 */
    (UNS16) 0xFFFF, /* Label 0364 & Label 0164 */
    (UNS16) 0xFFFF, /* Label 0365 & Label 0165 */
    (UNS16) 0xFFFF, /* Label 0366 & Label 0166 */
    (UNS16) 0xFFFF, /* Label 0367 & Label 0167 */
    (UNS16) 0xFFFF, /* Label 0370 & Label 0170 */
    (UNS16) 0xFFFF, /* Label 0371 & Label 0171 */
    (UNS16) 0xFFFF, /* Label 0372 & Label 0172 */
    (UNS16) 0xFFFF, /* Label 0373 & Label 0173 */
    (UNS16) 0xFFFF, /* Label 0374 & Label 0174 */
    (UNS16) 0xFFFF, /* Label 0375 & Label 0175 */
    (UNS16) 0xFFFF, /* Label 0376 & Label 0176 */
    (UNS16) 0xFFFF, /* Label 0377 & Label 0177 */
              
    /* SDI 10 */
    (UNS16) 0xFFFF, /* Label 0200 & Label 00 */
    (UNS16) 0xFFFF, /* Label 0201 & Label 01 */
    (UNS16) 0xFFFF, /* Label 0202 & Label 02 */
    (UNS16) 0xFFFF, /* Label 0203 & Label 03 */
    (UNS16) 0xFFFF, /* Label 0204 & Label 04 */
    (UNS16) 0xFFFF, /* Label 0205 & Label 05 */
    (UNS16) 0xFFFF, /* Label 0206 & Label 06 */
    (UNS16) 0xFFFF, /* Label 0207 & Label 07 */
    (UNS16) 0xFFFF, /* Label 0210 & Label 010 */
    (UNS16) 0xFFFF, /* Label 0211 & Label 011 */
    (UNS16) 0xFFFF, /* Label 0212 & Label 012 */
    (UNS16) 0xFFFF, /* Label 0213 & Label 013 */
    (UNS16) 0xFFFF, /* Label 0214 & Label 014 */
    (UNS16) 0xFFFF, /* Label 0215 & Label 015 */
    (UNS16) 0xFFFF, /* Label 0216 & Label 016 */
    (UNS16) 0xFFFF, /* Label 0217 & Label 017 */
    (UNS16) 0xFFFF, /* Label 0220 & Label 020 */
    (UNS16) 0xFFCC, /* Label 0221 & Label 021 */
    (UNS16) 0xFFFF, /* Label 0222 & Label 022 */
    (UNS16) 0xFFFF, /* Label 0223 & Label 023 */
    (UNS16) 0xFFFF, /* Label 0224 & Label 024 */
    (UNS16) 0xFFFF, /* Label 0225 & Label 025 */
    (UNS16) 0xFFFF, /* Label 0226 & Label 026 */
    (UNS16) 0xFFFF, /* Label 0227 & Label 027 */
    (UNS16) 0xFFFF, /* Label 0230 & Label 030 */
    (UNS16) 0xFFFF, /* Label 0231 & Label 031 */
    (UNS16) 0xFFFF, /* Label 0232 & Label 032 */
    (UNS16) 0xFFFF, /* Label 0233 & Label 033 */
    (UNS16) 0xFFFF, /* Label 0234 & Label 034 */
    (UNS16) 0xFFFF, /* Label 0235 & Label 035 */
    (UNS16) 0xFFFF, /* Label 0236 & Label 036 */
    (UNS16) 0xFFFF, /* Label 0237 & Label 037 */
    (UNS16) 0xFFFF, /* Label 0240 & Label 040 */
    (UNS16) 0xFFFF, /* Label 0241 & Label 041 */
    (UNS16) 0xFFFF, /* Label 0242 & Label 042 */
    (UNS16) 0xFFFF, /* Label 0243 & Label 043 */
    (UNS16) 0xFFFF, /* Label 0244 & Label 044 */
    (UNS16) 0xFFFF, /* Label 0245 & Label 045 */
    (UNS16) 0xFFFF, /* Label 0246 & Label 046 */
    (UNS16) 0xFFFF, /* Label 0247 & Label 047 */
    (UNS16) 0xFFFF, /* Label 0250 & Label 050 */
    (UNS16) 0xFFFF, /* Label 0251 & Label 051 */
    (UNS16) 0xFFFF, /* Label 0252 & Label 052 */
    (UNS16) 0xFFFF, /* Label 0253 & Label 053 */
    (UNS16) 0xFFFF, /* Label 0254 & Label 054 */
    (UNS16) 0xFFFF, /* Label 0255 & Label 055 */
    (UNS16) 0xFFFF, /* Label 0256 & Label 056 */
    (UNS16) 0xFFFF, /* Label 0257 & Label 057 */
    (UNS16) 0xFFFF, /* Label 0260 & Label 060 */
    (UNS16) 0xFFFF, /* Label 0261 & Label 061 */
    (UNS16) 0xFFFF, /* Label 0262 & Label 062 */
    (UNS16) 0xFFFF, /* Label 0263 & Label 063 */
    (UNS16) 0xFFFF, /* Label 0264 & Label 064 */
    (UNS16) 0xFFFF, /* Label 0265 & Label 065 */
    (UNS16) 0xFFFF, /* Label 0266 & Label 066 */
    (UNS16) 0xFFFF, /* Label 0267 & Label 067 */
    (UNS16) 0xFFFF, /* Label 0270 & Label 070 */
    (UNS16) 0xFFFF, /* Label 0271 & Label 071 */
    (UNS16) 0xFFFF, /* Label 0272 & Label 072 */
    (UNS16) 0xFFFF, /* Label 0273 & Label 073 */
    (UNS16) 0xFFFF, /* Label 0274 & Label 074 */
    (UNS16) 0xFFFF, /* Label 0275 & Label 075 */
    (UNS16) 0xFFFF, /* Label 0276 & Label 076 */
    (UNS16) 0xFFFF, /* Label 0277 & Label 077 */
    (UNS16) 0xFFFF, /* Label 0300 & Label 0100 */
    (UNS16) 0xFFFF, /* Label 0301 & Label 0101 */
    (UNS16) 0xFFFF, /* Label 0302 & Label 0102 */
    (UNS16) 0xFFFF, /* Label 0303 & Label 0103 */
    (UNS16) 0xFFFF, /* Label 0304 & Label 0104 */
    (UNS16) 0xFFFF, /* Label 0305 & Label 0105 */
    (UNS16) 0xFFFF, /* Label 0306 & Label 0106 */
    (UNS16) 0xFFFF, /* Label 0307 & Label 0107 */
    (UNS16) 0xFFFF, /* Label 0310 & Label 0110 */
    (UNS16) 0xFFFF, /* Label 0311 & Label 0111 */
    (UNS16) 0xFFFF, /* Label 0312 & Label 0112 */
    (UNS16) 0xFFFF, /* Label 0313 & Label 0113 */
    (UNS16) 0xFFFF, /* Label 0314 & Label 0114 */
    (UNS16) 0xFFFF, /* Label 0315 & Label 0115 */
    (UNS16) 0xFFFF, /* Label 0316 & Label 0116 */
    (UNS16) 0xFFFF, /* Label 0317 & Label 0117 */
    (UNS16) 0xFFFF, /* Label 0320 & Label 0120 */
    (UNS16) 0xFFFF, /* Label 0321 & Label 0121 */
    (UNS16) 0xFFFF, /* Label 0322 & Label 0122 */
    (UNS16) 0xFFFF, /* Label 0323 & Label 0123 */
    (UNS16) 0xFFFF, /* Label 0324 & Label 0124 */
    (UNS16) 0xFFFF, /* Label 0325 & Label 0125 */
    (UNS16) 0xFFFF, /* Label 0326 & Label 0126 */
    (UNS16) 0xFFFF, /* Label 0327 & Label 0127 */
    (UNS16) 0xFFFF, /* Label 0330 & Label 0130 */
    (UNS16) 0xFFFF, /* Label 0331 & Label 0131 */
    (UNS16) 0xFFFF, /* Label 0332 & Label 0132 */
    (UNS16) 0xFFFF, /* Label 0333 & Label 0133 */
    (UNS16) 0xFFFF, /* Label 0334 & Label 0134 */
    (UNS16) 0xFFFF, /* Label 0335 & Label 0135 */
    (UNS16) 0xFFFF, /* Label 0336 & Label 0136 */
    (UNS16) 0xFFFF, /* Label 0337 & Label 0137 */
    (UNS16) 0xFFFF, /* Label 0340 & Label 0140 */
    (UNS16) 0xFFFF, /* Label 0341 & Label 0141 */
    (UNS16) 0xFFFF, /* Label 0342 & Label 0142 */
    (UNS16) 0xFFFF, /* Label 0343 & Label 0143 */
    (UNS16) 0xFFFF, /* Label 0344 & Label 0144 */
    (UNS16) 0xFFFF, /* Label 0345 & Label 0145 */
    (UNS16) 0xFFFF, /* Label 0346 & Label 0146 */
    (UNS16) 0xFFFF, /* Label 0347 & Label 0147 */
    (UNS16) 0xFFFF, /* Label 0350 & Label 0150 */
    (UNS16) 0xFFFF, /* Label 0351 & Label 0151 */
    (UNS16) 0xFFFF, /* Label 0352 & Label 0152 */
    (UNS16) 0xFFFF, /* Label 0353 & Label 0153 */
    (UNS16) 0xFFFF, /* Label 0354 & Label 0154 */
    (UNS16) 0xFFFF, /* Label 0355 & Label 0155 */
    (UNS16) 0xFFFF, /* Label 0356 & Label 0156 */
    (UNS16) 0xFFFF, /* Label 0357 & Label 0157 */
    (UNS16) 0x33FF, /* Label 0360 & Label 0160 */
    (UNS16) 0xFFFF, /* Label 0361 & Label 0161 */
    (UNS16) 0xFFFF, /* Label 0362 & Label 0162 */
    (UNS16) 0xFFFF, /* Label 0363 & Label 0163 */
    (UNS16) 0xFFFF, /* Label 0364 & Label 0164 */
    (UNS16) 0xFFFF, /* Label 0365 & Label 0165 */
    (UNS16) 0xFFFF, /* Label 0366 & Label 0166 */
    (UNS16) 0xFFFF, /* Label 0367 & Label 0167 */
    (UNS16) 0xFFFF, /* Label 0370 & Label 0170 */
    (UNS16) 0xFFFF, /* Label 0371 & Label 0171 */
    (UNS16) 0xFFFF, /* Label 0372 & Label 0172 */
    (UNS16) 0xFFFF, /* Label 0373 & Label 0173 */
    (UNS16) 0xFFFF, /* Label 0374 & Label 0174 */
    (UNS16) 0xFFFF, /* Label 0375 & Label 0175 */
    (UNS16) 0xFFFF, /* Label 0376 & Label 0176 */
    (UNS16) 0xFFFF, /* Label 0377 & Label 0177 */
              
    /* SDI 11 */
    (UNS16) 0xFFFF, /* Label 0200 & Label 00 */
    (UNS16) 0xFFFF, /* Label 0201 & Label 01 */
    (UNS16) 0xFFFF, /* Label 0202 & Label 02 */
    (UNS16) 0xFFFF, /* Label 0203 & Label 03 */
    (UNS16) 0xFFFF, /* Label 0204 & Label 04 */
    (UNS16) 0xFFFF, /* Label 0205 & Label 05 */
    (UNS16) 0xFFFF, /* Label 0206 & Label 06 */
    (UNS16) 0xFFFF, /* Label 0207 & Label 07 */
    (UNS16) 0xFFFF, /* Label 0210 & Label 010 */
    (UNS16) 0xFFFF, /* Label 0211 & Label 011 */
    (UNS16) 0xFFFF, /* Label 0212 & Label 012 */
    (UNS16) 0xFFFF, /* Label 0213 & Label 013 */
    (UNS16) 0xFFFF, /* Label 0214 & Label 014 */
    (UNS16) 0xFFFF, /* Label 0215 & Label 015 */
    (UNS16) 0xFFFF, /* Label 0216 & Label 016 */
    (UNS16) 0xFFFF, /* Label 0217 & Label 017 */
    (UNS16) 0xFFFF, /* Label 0220 & Label 020 */
    (UNS16) 0xFFDD, /* Label 0221 & Label 021 */
    (UNS16) 0xFFFF, /* Label 0222 & Label 022 */
    (UNS16) 0xFFFF, /* Label 0223 & Label 023 */
    (UNS16) 0xFFFF, /* Label 0224 & Label 024 */
    (UNS16) 0xFFFF, /* Label 0225 & Label 025 */
    (UNS16) 0xFFFF, /* Label 0226 & Label 026 */
    (UNS16) 0xFFFF, /* Label 0227 & Label 027 */
    (UNS16) 0xFFFF, /* Label 0230 & Label 030 */
    (UNS16) 0xFFFF, /* Label 0231 & Label 031 */
    (UNS16) 0xFFFF, /* Label 0232 & Label 032 */
    (UNS16) 0xFFFF, /* Label 0233 & Label 033 */
    (UNS16) 0xFFFF, /* Label 0234 & Label 034 */
    (UNS16) 0xFFFF, /* Label 0235 & Label 035 */
    (UNS16) 0xFFFF, /* Label 0236 & Label 036 */
    (UNS16) 0xFFFF, /* Label 0237 & Label 037 */
    (UNS16) 0xFFFF, /* Label 0240 & Label 040 */
    (UNS16) 0xFFFF, /* Label 0241 & Label 041 */
    (UNS16) 0xFFFF, /* Label 0242 & Label 042 */
    (UNS16) 0xFFFF, /* Label 0243 & Label 043 */
    (UNS16) 0xFFFF, /* Label 0244 & Label 044 */
    (UNS16) 0xFFFF, /* Label 0245 & Label 045 */
    (UNS16) 0xFFFF, /* Label 0246 & Label 046 */
    (UNS16) 0xFFFF, /* Label 0247 & Label 047 */
    (UNS16) 0xFFFF, /* Label 0250 & Label 050 */
    (UNS16) 0xFFFF, /* Label 0251 & Label 051 */
    (UNS16) 0xFFFF, /* Label 0252 & Label 052 */
    (UNS16) 0xFFFF, /* Label 0253 & Label 053 */
    (UNS16) 0xFFFF, /* Label 0254 & Label 054 */
    (UNS16) 0xFFFF, /* Label 0255 & Label 055 */
    (UNS16) 0xFFFF, /* Label 0256 & Label 056 */
    (UNS16) 0xFFFF, /* Label 0257 & Label 057 */
    (UNS16) 0xFFFF, /* Label 0260 & Label 060 */
    (UNS16) 0xFFFF, /* Label 0261 & Label 061 */
    (UNS16) 0xFFFF, /* Label 0262 & Label 062 */
    (UNS16) 0xFFFF, /* Label 0263 & Label 063 */
    (UNS16) 0xFFFF, /* Label 0264 & Label 064 */
    (UNS16) 0xFFFF, /* Label 0265 & Label 065 */
    (UNS16) 0xFFFF, /* Label 0266 & Label 066 */
    (UNS16) 0xFFFF, /* Label 0267 & Label 067 */
    (UNS16) 0xFFFF, /* Label 0270 & Label 070 */
    (UNS16) 0xFFFF, /* Label 0271 & Label 071 */
    (UNS16) 0xFFFF, /* Label 0272 & Label 072 */
    (UNS16) 0xFFFF, /* Label 0273 & Label 073 */
    (UNS16) 0xFFFF, /* Label 0274 & Label 074 */
    (UNS16) 0xFFFF, /* Label 0275 & Label 075 */
    (UNS16) 0xFFFF, /* Label 0276 & Label 076 */
    (UNS16) 0xFFFF, /* Label 0277 & Label 077 */
    (UNS16) 0xFFFF, /* Label 0300 & Label 0100 */
    (UNS16) 0xFFFF, /* Label 0301 & Label 0101 */
    (UNS16) 0xFFFF, /* Label 0302 & Label 0102 */
    (UNS16) 0xFFFF, /* Label 0303 & Label 0103 */
    (UNS16) 0xFFFF, /* Label 0304 & Label 0104 */
    (UNS16) 0xFFFF, /* Label 0305 & Label 0105 */
    (UNS16) 0xFFFF, /* Label 0306 & Label 0106 */
    (UNS16) 0xFFFF, /* Label 0307 & Label 0107 */
    (UNS16) 0xFFFF, /* Label 0310 & Label 0110 */
    (UNS16) 0xFFFF, /* Label 0311 & Label 0111 */
    (UNS16) 0xFFFF, /* Label 0312 & Label 0112 */
    (UNS16) 0xFFFF, /* Label 0313 & Label 0113 */
    (UNS16) 0xFFFF, /* Label 0314 & Label 0114 */
    (UNS16) 0xFFFF, /* Label 0315 & Label 0115 */
    (UNS16) 0xFFFF, /* Label 0316 & Label 0116 */
    (UNS16) 0xFFFF, /* Label 0317 & Label 0117 */
    (UNS16) 0xFFFF, /* Label 0320 & Label 0120 */
    (UNS16) 0xFFFF, /* Label 0321 & Label 0121 */
    (UNS16) 0xFFFF, /* Label 0322 & Label 0122 */
    (UNS16) 0xFFFF, /* Label 0323 & Label 0123 */
    (UNS16) 0xFFFF, /* Label 0324 & Label 0124 */
    (UNS16) 0xFFFF, /* Label 0325 & Label 0125 */
    (UNS16) 0xFFFF, /* Label 0326 & Label 0126 */
    (UNS16) 0xFFFF, /* Label 0327 & Label 0127 */
    (UNS16) 0xFFFF, /* Label 0330 & Label 0130 */
    (UNS16) 0xFFFF, /* Label 0331 & Label 0131 */
    (UNS16) 0xFFFF, /* Label 0332 & Label 0132 */
    (UNS16) 0xFFFF, /* Label 0333 & Label 0133 */
    (UNS16) 0xFFFF, /* Label 0334 & Label 0134 */
    (UNS16) 0xFFFF, /* Label 0335 & Label 0135 */
    (UNS16) 0xFFFF, /* Label 0336 & Label 0136 */
    (UNS16) 0xFFFF, /* Label 0337 & Label 0137 */
    (UNS16) 0xFFFF, /* Label 0340 & Label 0140 */
    (UNS16) 0xFFFF, /* Label 0341 & Label 0141 */
    (UNS16) 0xFFFF, /* Label 0342 & Label 0142 */
    (UNS16) 0xFFFF, /* Label 0343 & Label 0143 */
    (UNS16) 0xFFFF, /* Label 0344 & Label 0144 */
    (UNS16) 0xFFFF, /* Label 0345 & Label 0145 */
    (UNS16) 0xFFFF, /* Label 0346 & Label 0146 */
    (UNS16) 0xFFFF, /* Label 0347 & Label 0147 */
    (UNS16) 0xFFFF, /* Label 0350 & Label 0150 */
    (UNS16) 0xFFFF, /* Label 0351 & Label 0151 */
    (UNS16) 0xFFFF, /* Label 0352 & Label 0152 */
    (UNS16) 0xFFFF, /* Label 0353 & Label 0153 */
    (UNS16) 0xFFFF, /* Label 0354 & Label 0154 */
    (UNS16) 0xFFFF, /* Label 0355 & Label 0155 */
    (UNS16) 0xFFFF, /* Label 0356 & Label 0156 */
    (UNS16) 0xFFFF, /* Label 0357 & Label 0157 */
    (UNS16) 0x44FF, /* Label 0360 & Label 0160 */
    (UNS16) 0xFFFF, /* Label 0361 & Label 0161 */
    (UNS16) 0xFFFF, /* Label 0362 & Label 0162 */
    (UNS16) 0xFFFF, /* Label 0363 & Label 0163 */
    (UNS16) 0xFFFF, /* Label 0364 & Label 0164 */
    (UNS16) 0xFFFF, /* Label 0365 & Label 0165 */
    (UNS16) 0xFFFF, /* Label 0366 & Label 0166 */
    (UNS16) 0xFFFF, /* Label 0367 & Label 0167 */
    (UNS16) 0xFFFF, /* Label 0370 & Label 0170 */
    (UNS16) 0xFFFF, /* Label 0371 & Label 0171 */
    (UNS16) 0xFFFF, /* Label 0372 & Label 0172 */
    (UNS16) 0xFFFF, /* Label 0373 & Label 0173 */
    (UNS16) 0xFFFF, /* Label 0374 & Label 0174 */
    (UNS16) 0xFFFF, /* Label 0375 & Label 0175 */
    (UNS16) 0xFFFF, /* Label 0376 & Label 0176 */
    (UNS16) 0xFFFF  /* Label 0377 & Label 0177 */
};


/***************************************************************/
/*                                                             */
/*                       LOCAL CONSTANTS                       */
/*                                                             */
/***************************************************************/

/* ---- ARINC CONFIGURATION ---- */
#define ARINC_HIGH_SPEED           ((BOOLEAN) TRUE)
#define ARINC_LOW_SPEED            ((BOOLEAN) FALSE)
#define ARINC_TX_LABEL_NUMBER_LOW  ((UNS8)    16)
#define ARINC_MAX_LABEL_HIGH_SPEED  ((UNS8)    69)
#define ARINC_MAX_LABEL_LOW_SPEED   ((UNS8)    8)



/* AC Motor configuration : */
/* Time values for f tcr2 = 14 MHz */
/*   OVERLAP_TIME = 0x005208  (1.5  ms) */
/*   PWM_OFF_TIME = 0x0001E0 (34.35 us => 79% of 23kHz) */
/*   PWM_ON_TIME  = 0x000080 (9.13 us => 21% of 23kHz)  */
#define OVERLAP_TIME_STM (UNS32)0x005208
#define PWM_OFF_TIME_STM (UNS32)0x0001E0
#define PWM_ON_TIME_STM  (UNS32)0x000080




/***************************************************************/
/*                                                             */
/*                         LOCAL TYPES                         */
/*                                                             */
/***************************************************************/


/***************************************************************/
/*                                                             */
/*                         LOCAL DATA                          */
/*                                                             */
/***************************************************************/

/***************************************************************/
/* Global function : InitializeConfiguration                   */
/***************************************************************/
void InitializeConfiguration(void)
{
    UNS32 i;
        

    /* - CAN */
    for (i = 0; i < (UNS32)CAN_MB_NUMBER; i++)
    {
        I_BSP_conf.can_A_message_box_conf.box[i].CS.R = 0;
        I_BSP_conf.can_A_message_box_conf.box[i].ID.R = 0;
        I_BSP_conf.can_A_message_box_conf.TAB_list_of_rx_MB[i] = 0;
        I_BSP_conf.can_B_message_box_conf.box[i].CS.R = 0;
        I_BSP_conf.can_B_message_box_conf.box[i].ID.R = 0;
        I_BSP_conf.can_B_message_box_conf.TAB_list_of_rx_MB[i] = 0;
		I_BSP_conf.can_C_message_box_conf.box[i].CS.R = 0;
        I_BSP_conf.can_C_message_box_conf.box[i].ID.R = 0;
        I_BSP_conf.can_C_message_box_conf.TAB_list_of_rx_MB[i] = 0;
    }
    I_BSP_conf.can_A_message_box_conf.CR.R = 0;
    I_BSP_conf.can_A_message_box_conf.MAXMB = 0;
    I_BSP_conf.can_A_message_box_conf.RXGMASK = 0;
    I_BSP_conf.can_A_message_box_conf.RX14MASK = 0;
    I_BSP_conf.can_A_message_box_conf.RX15MASK = 0;
    I_BSP_conf.can_A_message_box_conf.IMRL = 0;
    I_BSP_conf.can_A_message_box_conf.IMRH = 0;
    I_BSP_conf.can_A_message_box_conf.F_can_enable = 0;
    I_BSP_conf.can_A_message_box_conf.number_of_rx_MB = 0;
    I_BSP_conf.can_B_message_box_conf.CR.R = 0;
    I_BSP_conf.can_B_message_box_conf.MAXMB = 0;
    I_BSP_conf.can_B_message_box_conf.RXGMASK = 0;
    I_BSP_conf.can_B_message_box_conf.RX14MASK = 0;
    I_BSP_conf.can_B_message_box_conf.RX15MASK = 0;
    I_BSP_conf.can_B_message_box_conf.IMRL = 0;
    I_BSP_conf.can_B_message_box_conf.IMRH = 0;
    I_BSP_conf.can_B_message_box_conf.F_can_enable = 0;
    I_BSP_conf.can_B_message_box_conf.number_of_rx_MB = 0;
	I_BSP_conf.can_C_message_box_conf.CR.R = 0;
    I_BSP_conf.can_C_message_box_conf.MAXMB = 0;
    I_BSP_conf.can_C_message_box_conf.RXGMASK = 0;
    I_BSP_conf.can_C_message_box_conf.RX14MASK = 0;
    I_BSP_conf.can_C_message_box_conf.RX15MASK = 0;
    I_BSP_conf.can_C_message_box_conf.IMRL = 0;
    I_BSP_conf.can_C_message_box_conf.IMRH = 0;
    I_BSP_conf.can_C_message_box_conf.F_can_enable = 0;
    I_BSP_conf.can_C_message_box_conf.number_of_rx_MB = 0;
    I_BSP_Out.can_A_status.F_transmit_failure = 0;
    I_BSP_Out.can_B_status.F_transmit_failure = 0;
	I_BSP_Out.can_C_status.F_transmit_failure = 0;

    /* - ARINC 429 */
    I_BSP_conf.arinc_conf.TAB_address_arinc_rx_filter = (UNS32)&K_TAB_arinc_rx_filter;
    I_BSP_conf.arinc_conf.channel_TX1 = ARINC_HIGH_SPEED;
    I_BSP_conf.arinc_conf.channel_TX2 = ARINC_HIGH_SPEED;
    I_BSP_conf.arinc_conf.channel_RX1 = ARINC_HIGH_SPEED;
    I_BSP_conf.arinc_conf.channel_RX2 = ARINC_HIGH_SPEED;
    I_BSP_conf.arinc_conf.channel_RX3 = ARINC_HIGH_SPEED;
    I_BSP_conf.arinc_conf.channel_RX4 = ARINC_HIGH_SPEED;
    I_BSP_conf.arinc_conf.channel_RX5 = ARINC_HIGH_SPEED;
    for (i = 0 ; i < (UNS32)ARINC_TX_NB ; i ++)
    {
        I_BSP_conf.arinc_conf.TAB_tx_buffer_size_configuration[i] = ARINC_TX_LABEL_NUMBER_LOW;
    }
    I_BSP_conf.arinc_conf.TAB_rx_robustness_nbr_it_max[RX1] = ARINC_MAX_LABEL_HIGH_SPEED;
    I_BSP_conf.arinc_conf.TAB_rx_robustness_nbr_it_max[RX2] = ARINC_MAX_LABEL_HIGH_SPEED;
    I_BSP_conf.arinc_conf.TAB_rx_robustness_nbr_it_max[RX3] = ARINC_MAX_LABEL_HIGH_SPEED;
    I_BSP_conf.arinc_conf.TAB_rx_robustness_nbr_it_max[RX4] = ARINC_MAX_LABEL_HIGH_SPEED;
    I_BSP_conf.arinc_conf.TAB_rx_robustness_nbr_it_max[RX5] = ARINC_MAX_LABEL_HIGH_SPEED;

    /* - Stepper Motor 2 phases */
    I_BSP_conf.stp_motor_conf.motor[0].overlap_time = OVERLAP_TIME_STM;
    I_BSP_conf.stp_motor_conf.motor[0].pwm_off_time = PWM_OFF_TIME_STM;
    I_BSP_conf.stp_motor_conf.motor[0].pwm_on_time  = PWM_ON_TIME_STM;
	
	/* AD2S1210 RDC */
    I_BSP_conf.ad2s1210_config.LOS_THRESHOLD_configuration = 0.0;
    I_BSP_conf.ad2s1210_config.DOS_OVERRANGE_THRESHOLD_configuration = 0.0;
    I_BSP_conf.ad2s1210_config.DOS_MISMATCH_THRESHOLD_configuration = 0.0;
    I_BSP_conf.ad2s1210_config.DOS_RESET_MAX_THRESHOLD_configuration = 0.0;
    I_BSP_conf.ad2s1210_config.DOS_RESET_MIN_THRESHOLD_configuration = 0.0;
    I_BSP_conf.ad2s1210_config.LOT_HIGH_THRESHOLD_configuration = 0.0;
    I_BSP_conf.ad2s1210_config.LOT_LOW_THRESHOLD_configuration = 0.0;

    I_BSP_conf.ad2s1210_config.F_AD2S1210_perform_config = FALSE;
    I_BSP_conf.ad2s1210_config.FREQ_POBA_configuration = 0.0;
    I_BSP_conf.ad2s1210_config.FREQ_POBB_configuration = 0.0;
	
	/* - Leak Detection timings configuration */
    I_BSP_conf.leak_detection_conf.clock_period       = 0;
    I_BSP_conf.leak_detection_conf.init_test_delay    = 0;
    I_BSP_conf.leak_detection_conf.setup_test_delay   = 0;
    I_BSP_conf.leak_detection_conf.setup_mux_delay    = 0;
    I_BSP_conf.leak_detection_conf.setup_conf_delay   = 0;
    I_BSP_conf.leak_detection_conf.pulse_width        = 0;
    I_BSP_conf.leak_detection_conf.leak_timeout       = 0;
    
}

