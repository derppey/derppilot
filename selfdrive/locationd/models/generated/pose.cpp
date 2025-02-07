#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.13.2                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_752852575942216847) {
   out_752852575942216847[0] = delta_x[0] + nom_x[0];
   out_752852575942216847[1] = delta_x[1] + nom_x[1];
   out_752852575942216847[2] = delta_x[2] + nom_x[2];
   out_752852575942216847[3] = delta_x[3] + nom_x[3];
   out_752852575942216847[4] = delta_x[4] + nom_x[4];
   out_752852575942216847[5] = delta_x[5] + nom_x[5];
   out_752852575942216847[6] = delta_x[6] + nom_x[6];
   out_752852575942216847[7] = delta_x[7] + nom_x[7];
   out_752852575942216847[8] = delta_x[8] + nom_x[8];
   out_752852575942216847[9] = delta_x[9] + nom_x[9];
   out_752852575942216847[10] = delta_x[10] + nom_x[10];
   out_752852575942216847[11] = delta_x[11] + nom_x[11];
   out_752852575942216847[12] = delta_x[12] + nom_x[12];
   out_752852575942216847[13] = delta_x[13] + nom_x[13];
   out_752852575942216847[14] = delta_x[14] + nom_x[14];
   out_752852575942216847[15] = delta_x[15] + nom_x[15];
   out_752852575942216847[16] = delta_x[16] + nom_x[16];
   out_752852575942216847[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1438979586232603189) {
   out_1438979586232603189[0] = -nom_x[0] + true_x[0];
   out_1438979586232603189[1] = -nom_x[1] + true_x[1];
   out_1438979586232603189[2] = -nom_x[2] + true_x[2];
   out_1438979586232603189[3] = -nom_x[3] + true_x[3];
   out_1438979586232603189[4] = -nom_x[4] + true_x[4];
   out_1438979586232603189[5] = -nom_x[5] + true_x[5];
   out_1438979586232603189[6] = -nom_x[6] + true_x[6];
   out_1438979586232603189[7] = -nom_x[7] + true_x[7];
   out_1438979586232603189[8] = -nom_x[8] + true_x[8];
   out_1438979586232603189[9] = -nom_x[9] + true_x[9];
   out_1438979586232603189[10] = -nom_x[10] + true_x[10];
   out_1438979586232603189[11] = -nom_x[11] + true_x[11];
   out_1438979586232603189[12] = -nom_x[12] + true_x[12];
   out_1438979586232603189[13] = -nom_x[13] + true_x[13];
   out_1438979586232603189[14] = -nom_x[14] + true_x[14];
   out_1438979586232603189[15] = -nom_x[15] + true_x[15];
   out_1438979586232603189[16] = -nom_x[16] + true_x[16];
   out_1438979586232603189[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7614955989455419172) {
   out_7614955989455419172[0] = 1.0;
   out_7614955989455419172[1] = 0.0;
   out_7614955989455419172[2] = 0.0;
   out_7614955989455419172[3] = 0.0;
   out_7614955989455419172[4] = 0.0;
   out_7614955989455419172[5] = 0.0;
   out_7614955989455419172[6] = 0.0;
   out_7614955989455419172[7] = 0.0;
   out_7614955989455419172[8] = 0.0;
   out_7614955989455419172[9] = 0.0;
   out_7614955989455419172[10] = 0.0;
   out_7614955989455419172[11] = 0.0;
   out_7614955989455419172[12] = 0.0;
   out_7614955989455419172[13] = 0.0;
   out_7614955989455419172[14] = 0.0;
   out_7614955989455419172[15] = 0.0;
   out_7614955989455419172[16] = 0.0;
   out_7614955989455419172[17] = 0.0;
   out_7614955989455419172[18] = 0.0;
   out_7614955989455419172[19] = 1.0;
   out_7614955989455419172[20] = 0.0;
   out_7614955989455419172[21] = 0.0;
   out_7614955989455419172[22] = 0.0;
   out_7614955989455419172[23] = 0.0;
   out_7614955989455419172[24] = 0.0;
   out_7614955989455419172[25] = 0.0;
   out_7614955989455419172[26] = 0.0;
   out_7614955989455419172[27] = 0.0;
   out_7614955989455419172[28] = 0.0;
   out_7614955989455419172[29] = 0.0;
   out_7614955989455419172[30] = 0.0;
   out_7614955989455419172[31] = 0.0;
   out_7614955989455419172[32] = 0.0;
   out_7614955989455419172[33] = 0.0;
   out_7614955989455419172[34] = 0.0;
   out_7614955989455419172[35] = 0.0;
   out_7614955989455419172[36] = 0.0;
   out_7614955989455419172[37] = 0.0;
   out_7614955989455419172[38] = 1.0;
   out_7614955989455419172[39] = 0.0;
   out_7614955989455419172[40] = 0.0;
   out_7614955989455419172[41] = 0.0;
   out_7614955989455419172[42] = 0.0;
   out_7614955989455419172[43] = 0.0;
   out_7614955989455419172[44] = 0.0;
   out_7614955989455419172[45] = 0.0;
   out_7614955989455419172[46] = 0.0;
   out_7614955989455419172[47] = 0.0;
   out_7614955989455419172[48] = 0.0;
   out_7614955989455419172[49] = 0.0;
   out_7614955989455419172[50] = 0.0;
   out_7614955989455419172[51] = 0.0;
   out_7614955989455419172[52] = 0.0;
   out_7614955989455419172[53] = 0.0;
   out_7614955989455419172[54] = 0.0;
   out_7614955989455419172[55] = 0.0;
   out_7614955989455419172[56] = 0.0;
   out_7614955989455419172[57] = 1.0;
   out_7614955989455419172[58] = 0.0;
   out_7614955989455419172[59] = 0.0;
   out_7614955989455419172[60] = 0.0;
   out_7614955989455419172[61] = 0.0;
   out_7614955989455419172[62] = 0.0;
   out_7614955989455419172[63] = 0.0;
   out_7614955989455419172[64] = 0.0;
   out_7614955989455419172[65] = 0.0;
   out_7614955989455419172[66] = 0.0;
   out_7614955989455419172[67] = 0.0;
   out_7614955989455419172[68] = 0.0;
   out_7614955989455419172[69] = 0.0;
   out_7614955989455419172[70] = 0.0;
   out_7614955989455419172[71] = 0.0;
   out_7614955989455419172[72] = 0.0;
   out_7614955989455419172[73] = 0.0;
   out_7614955989455419172[74] = 0.0;
   out_7614955989455419172[75] = 0.0;
   out_7614955989455419172[76] = 1.0;
   out_7614955989455419172[77] = 0.0;
   out_7614955989455419172[78] = 0.0;
   out_7614955989455419172[79] = 0.0;
   out_7614955989455419172[80] = 0.0;
   out_7614955989455419172[81] = 0.0;
   out_7614955989455419172[82] = 0.0;
   out_7614955989455419172[83] = 0.0;
   out_7614955989455419172[84] = 0.0;
   out_7614955989455419172[85] = 0.0;
   out_7614955989455419172[86] = 0.0;
   out_7614955989455419172[87] = 0.0;
   out_7614955989455419172[88] = 0.0;
   out_7614955989455419172[89] = 0.0;
   out_7614955989455419172[90] = 0.0;
   out_7614955989455419172[91] = 0.0;
   out_7614955989455419172[92] = 0.0;
   out_7614955989455419172[93] = 0.0;
   out_7614955989455419172[94] = 0.0;
   out_7614955989455419172[95] = 1.0;
   out_7614955989455419172[96] = 0.0;
   out_7614955989455419172[97] = 0.0;
   out_7614955989455419172[98] = 0.0;
   out_7614955989455419172[99] = 0.0;
   out_7614955989455419172[100] = 0.0;
   out_7614955989455419172[101] = 0.0;
   out_7614955989455419172[102] = 0.0;
   out_7614955989455419172[103] = 0.0;
   out_7614955989455419172[104] = 0.0;
   out_7614955989455419172[105] = 0.0;
   out_7614955989455419172[106] = 0.0;
   out_7614955989455419172[107] = 0.0;
   out_7614955989455419172[108] = 0.0;
   out_7614955989455419172[109] = 0.0;
   out_7614955989455419172[110] = 0.0;
   out_7614955989455419172[111] = 0.0;
   out_7614955989455419172[112] = 0.0;
   out_7614955989455419172[113] = 0.0;
   out_7614955989455419172[114] = 1.0;
   out_7614955989455419172[115] = 0.0;
   out_7614955989455419172[116] = 0.0;
   out_7614955989455419172[117] = 0.0;
   out_7614955989455419172[118] = 0.0;
   out_7614955989455419172[119] = 0.0;
   out_7614955989455419172[120] = 0.0;
   out_7614955989455419172[121] = 0.0;
   out_7614955989455419172[122] = 0.0;
   out_7614955989455419172[123] = 0.0;
   out_7614955989455419172[124] = 0.0;
   out_7614955989455419172[125] = 0.0;
   out_7614955989455419172[126] = 0.0;
   out_7614955989455419172[127] = 0.0;
   out_7614955989455419172[128] = 0.0;
   out_7614955989455419172[129] = 0.0;
   out_7614955989455419172[130] = 0.0;
   out_7614955989455419172[131] = 0.0;
   out_7614955989455419172[132] = 0.0;
   out_7614955989455419172[133] = 1.0;
   out_7614955989455419172[134] = 0.0;
   out_7614955989455419172[135] = 0.0;
   out_7614955989455419172[136] = 0.0;
   out_7614955989455419172[137] = 0.0;
   out_7614955989455419172[138] = 0.0;
   out_7614955989455419172[139] = 0.0;
   out_7614955989455419172[140] = 0.0;
   out_7614955989455419172[141] = 0.0;
   out_7614955989455419172[142] = 0.0;
   out_7614955989455419172[143] = 0.0;
   out_7614955989455419172[144] = 0.0;
   out_7614955989455419172[145] = 0.0;
   out_7614955989455419172[146] = 0.0;
   out_7614955989455419172[147] = 0.0;
   out_7614955989455419172[148] = 0.0;
   out_7614955989455419172[149] = 0.0;
   out_7614955989455419172[150] = 0.0;
   out_7614955989455419172[151] = 0.0;
   out_7614955989455419172[152] = 1.0;
   out_7614955989455419172[153] = 0.0;
   out_7614955989455419172[154] = 0.0;
   out_7614955989455419172[155] = 0.0;
   out_7614955989455419172[156] = 0.0;
   out_7614955989455419172[157] = 0.0;
   out_7614955989455419172[158] = 0.0;
   out_7614955989455419172[159] = 0.0;
   out_7614955989455419172[160] = 0.0;
   out_7614955989455419172[161] = 0.0;
   out_7614955989455419172[162] = 0.0;
   out_7614955989455419172[163] = 0.0;
   out_7614955989455419172[164] = 0.0;
   out_7614955989455419172[165] = 0.0;
   out_7614955989455419172[166] = 0.0;
   out_7614955989455419172[167] = 0.0;
   out_7614955989455419172[168] = 0.0;
   out_7614955989455419172[169] = 0.0;
   out_7614955989455419172[170] = 0.0;
   out_7614955989455419172[171] = 1.0;
   out_7614955989455419172[172] = 0.0;
   out_7614955989455419172[173] = 0.0;
   out_7614955989455419172[174] = 0.0;
   out_7614955989455419172[175] = 0.0;
   out_7614955989455419172[176] = 0.0;
   out_7614955989455419172[177] = 0.0;
   out_7614955989455419172[178] = 0.0;
   out_7614955989455419172[179] = 0.0;
   out_7614955989455419172[180] = 0.0;
   out_7614955989455419172[181] = 0.0;
   out_7614955989455419172[182] = 0.0;
   out_7614955989455419172[183] = 0.0;
   out_7614955989455419172[184] = 0.0;
   out_7614955989455419172[185] = 0.0;
   out_7614955989455419172[186] = 0.0;
   out_7614955989455419172[187] = 0.0;
   out_7614955989455419172[188] = 0.0;
   out_7614955989455419172[189] = 0.0;
   out_7614955989455419172[190] = 1.0;
   out_7614955989455419172[191] = 0.0;
   out_7614955989455419172[192] = 0.0;
   out_7614955989455419172[193] = 0.0;
   out_7614955989455419172[194] = 0.0;
   out_7614955989455419172[195] = 0.0;
   out_7614955989455419172[196] = 0.0;
   out_7614955989455419172[197] = 0.0;
   out_7614955989455419172[198] = 0.0;
   out_7614955989455419172[199] = 0.0;
   out_7614955989455419172[200] = 0.0;
   out_7614955989455419172[201] = 0.0;
   out_7614955989455419172[202] = 0.0;
   out_7614955989455419172[203] = 0.0;
   out_7614955989455419172[204] = 0.0;
   out_7614955989455419172[205] = 0.0;
   out_7614955989455419172[206] = 0.0;
   out_7614955989455419172[207] = 0.0;
   out_7614955989455419172[208] = 0.0;
   out_7614955989455419172[209] = 1.0;
   out_7614955989455419172[210] = 0.0;
   out_7614955989455419172[211] = 0.0;
   out_7614955989455419172[212] = 0.0;
   out_7614955989455419172[213] = 0.0;
   out_7614955989455419172[214] = 0.0;
   out_7614955989455419172[215] = 0.0;
   out_7614955989455419172[216] = 0.0;
   out_7614955989455419172[217] = 0.0;
   out_7614955989455419172[218] = 0.0;
   out_7614955989455419172[219] = 0.0;
   out_7614955989455419172[220] = 0.0;
   out_7614955989455419172[221] = 0.0;
   out_7614955989455419172[222] = 0.0;
   out_7614955989455419172[223] = 0.0;
   out_7614955989455419172[224] = 0.0;
   out_7614955989455419172[225] = 0.0;
   out_7614955989455419172[226] = 0.0;
   out_7614955989455419172[227] = 0.0;
   out_7614955989455419172[228] = 1.0;
   out_7614955989455419172[229] = 0.0;
   out_7614955989455419172[230] = 0.0;
   out_7614955989455419172[231] = 0.0;
   out_7614955989455419172[232] = 0.0;
   out_7614955989455419172[233] = 0.0;
   out_7614955989455419172[234] = 0.0;
   out_7614955989455419172[235] = 0.0;
   out_7614955989455419172[236] = 0.0;
   out_7614955989455419172[237] = 0.0;
   out_7614955989455419172[238] = 0.0;
   out_7614955989455419172[239] = 0.0;
   out_7614955989455419172[240] = 0.0;
   out_7614955989455419172[241] = 0.0;
   out_7614955989455419172[242] = 0.0;
   out_7614955989455419172[243] = 0.0;
   out_7614955989455419172[244] = 0.0;
   out_7614955989455419172[245] = 0.0;
   out_7614955989455419172[246] = 0.0;
   out_7614955989455419172[247] = 1.0;
   out_7614955989455419172[248] = 0.0;
   out_7614955989455419172[249] = 0.0;
   out_7614955989455419172[250] = 0.0;
   out_7614955989455419172[251] = 0.0;
   out_7614955989455419172[252] = 0.0;
   out_7614955989455419172[253] = 0.0;
   out_7614955989455419172[254] = 0.0;
   out_7614955989455419172[255] = 0.0;
   out_7614955989455419172[256] = 0.0;
   out_7614955989455419172[257] = 0.0;
   out_7614955989455419172[258] = 0.0;
   out_7614955989455419172[259] = 0.0;
   out_7614955989455419172[260] = 0.0;
   out_7614955989455419172[261] = 0.0;
   out_7614955989455419172[262] = 0.0;
   out_7614955989455419172[263] = 0.0;
   out_7614955989455419172[264] = 0.0;
   out_7614955989455419172[265] = 0.0;
   out_7614955989455419172[266] = 1.0;
   out_7614955989455419172[267] = 0.0;
   out_7614955989455419172[268] = 0.0;
   out_7614955989455419172[269] = 0.0;
   out_7614955989455419172[270] = 0.0;
   out_7614955989455419172[271] = 0.0;
   out_7614955989455419172[272] = 0.0;
   out_7614955989455419172[273] = 0.0;
   out_7614955989455419172[274] = 0.0;
   out_7614955989455419172[275] = 0.0;
   out_7614955989455419172[276] = 0.0;
   out_7614955989455419172[277] = 0.0;
   out_7614955989455419172[278] = 0.0;
   out_7614955989455419172[279] = 0.0;
   out_7614955989455419172[280] = 0.0;
   out_7614955989455419172[281] = 0.0;
   out_7614955989455419172[282] = 0.0;
   out_7614955989455419172[283] = 0.0;
   out_7614955989455419172[284] = 0.0;
   out_7614955989455419172[285] = 1.0;
   out_7614955989455419172[286] = 0.0;
   out_7614955989455419172[287] = 0.0;
   out_7614955989455419172[288] = 0.0;
   out_7614955989455419172[289] = 0.0;
   out_7614955989455419172[290] = 0.0;
   out_7614955989455419172[291] = 0.0;
   out_7614955989455419172[292] = 0.0;
   out_7614955989455419172[293] = 0.0;
   out_7614955989455419172[294] = 0.0;
   out_7614955989455419172[295] = 0.0;
   out_7614955989455419172[296] = 0.0;
   out_7614955989455419172[297] = 0.0;
   out_7614955989455419172[298] = 0.0;
   out_7614955989455419172[299] = 0.0;
   out_7614955989455419172[300] = 0.0;
   out_7614955989455419172[301] = 0.0;
   out_7614955989455419172[302] = 0.0;
   out_7614955989455419172[303] = 0.0;
   out_7614955989455419172[304] = 1.0;
   out_7614955989455419172[305] = 0.0;
   out_7614955989455419172[306] = 0.0;
   out_7614955989455419172[307] = 0.0;
   out_7614955989455419172[308] = 0.0;
   out_7614955989455419172[309] = 0.0;
   out_7614955989455419172[310] = 0.0;
   out_7614955989455419172[311] = 0.0;
   out_7614955989455419172[312] = 0.0;
   out_7614955989455419172[313] = 0.0;
   out_7614955989455419172[314] = 0.0;
   out_7614955989455419172[315] = 0.0;
   out_7614955989455419172[316] = 0.0;
   out_7614955989455419172[317] = 0.0;
   out_7614955989455419172[318] = 0.0;
   out_7614955989455419172[319] = 0.0;
   out_7614955989455419172[320] = 0.0;
   out_7614955989455419172[321] = 0.0;
   out_7614955989455419172[322] = 0.0;
   out_7614955989455419172[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5899861132242380131) {
   out_5899861132242380131[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5899861132242380131[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5899861132242380131[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5899861132242380131[3] = dt*state[12] + state[3];
   out_5899861132242380131[4] = dt*state[13] + state[4];
   out_5899861132242380131[5] = dt*state[14] + state[5];
   out_5899861132242380131[6] = state[6];
   out_5899861132242380131[7] = state[7];
   out_5899861132242380131[8] = state[8];
   out_5899861132242380131[9] = state[9];
   out_5899861132242380131[10] = state[10];
   out_5899861132242380131[11] = state[11];
   out_5899861132242380131[12] = state[12];
   out_5899861132242380131[13] = state[13];
   out_5899861132242380131[14] = state[14];
   out_5899861132242380131[15] = state[15];
   out_5899861132242380131[16] = state[16];
   out_5899861132242380131[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4403213144206436728) {
   out_4403213144206436728[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4403213144206436728[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4403213144206436728[2] = 0;
   out_4403213144206436728[3] = 0;
   out_4403213144206436728[4] = 0;
   out_4403213144206436728[5] = 0;
   out_4403213144206436728[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4403213144206436728[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4403213144206436728[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4403213144206436728[9] = 0;
   out_4403213144206436728[10] = 0;
   out_4403213144206436728[11] = 0;
   out_4403213144206436728[12] = 0;
   out_4403213144206436728[13] = 0;
   out_4403213144206436728[14] = 0;
   out_4403213144206436728[15] = 0;
   out_4403213144206436728[16] = 0;
   out_4403213144206436728[17] = 0;
   out_4403213144206436728[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4403213144206436728[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4403213144206436728[20] = 0;
   out_4403213144206436728[21] = 0;
   out_4403213144206436728[22] = 0;
   out_4403213144206436728[23] = 0;
   out_4403213144206436728[24] = 0;
   out_4403213144206436728[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4403213144206436728[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4403213144206436728[27] = 0;
   out_4403213144206436728[28] = 0;
   out_4403213144206436728[29] = 0;
   out_4403213144206436728[30] = 0;
   out_4403213144206436728[31] = 0;
   out_4403213144206436728[32] = 0;
   out_4403213144206436728[33] = 0;
   out_4403213144206436728[34] = 0;
   out_4403213144206436728[35] = 0;
   out_4403213144206436728[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4403213144206436728[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4403213144206436728[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4403213144206436728[39] = 0;
   out_4403213144206436728[40] = 0;
   out_4403213144206436728[41] = 0;
   out_4403213144206436728[42] = 0;
   out_4403213144206436728[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4403213144206436728[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4403213144206436728[45] = 0;
   out_4403213144206436728[46] = 0;
   out_4403213144206436728[47] = 0;
   out_4403213144206436728[48] = 0;
   out_4403213144206436728[49] = 0;
   out_4403213144206436728[50] = 0;
   out_4403213144206436728[51] = 0;
   out_4403213144206436728[52] = 0;
   out_4403213144206436728[53] = 0;
   out_4403213144206436728[54] = 0;
   out_4403213144206436728[55] = 0;
   out_4403213144206436728[56] = 0;
   out_4403213144206436728[57] = 1;
   out_4403213144206436728[58] = 0;
   out_4403213144206436728[59] = 0;
   out_4403213144206436728[60] = 0;
   out_4403213144206436728[61] = 0;
   out_4403213144206436728[62] = 0;
   out_4403213144206436728[63] = 0;
   out_4403213144206436728[64] = 0;
   out_4403213144206436728[65] = 0;
   out_4403213144206436728[66] = dt;
   out_4403213144206436728[67] = 0;
   out_4403213144206436728[68] = 0;
   out_4403213144206436728[69] = 0;
   out_4403213144206436728[70] = 0;
   out_4403213144206436728[71] = 0;
   out_4403213144206436728[72] = 0;
   out_4403213144206436728[73] = 0;
   out_4403213144206436728[74] = 0;
   out_4403213144206436728[75] = 0;
   out_4403213144206436728[76] = 1;
   out_4403213144206436728[77] = 0;
   out_4403213144206436728[78] = 0;
   out_4403213144206436728[79] = 0;
   out_4403213144206436728[80] = 0;
   out_4403213144206436728[81] = 0;
   out_4403213144206436728[82] = 0;
   out_4403213144206436728[83] = 0;
   out_4403213144206436728[84] = 0;
   out_4403213144206436728[85] = dt;
   out_4403213144206436728[86] = 0;
   out_4403213144206436728[87] = 0;
   out_4403213144206436728[88] = 0;
   out_4403213144206436728[89] = 0;
   out_4403213144206436728[90] = 0;
   out_4403213144206436728[91] = 0;
   out_4403213144206436728[92] = 0;
   out_4403213144206436728[93] = 0;
   out_4403213144206436728[94] = 0;
   out_4403213144206436728[95] = 1;
   out_4403213144206436728[96] = 0;
   out_4403213144206436728[97] = 0;
   out_4403213144206436728[98] = 0;
   out_4403213144206436728[99] = 0;
   out_4403213144206436728[100] = 0;
   out_4403213144206436728[101] = 0;
   out_4403213144206436728[102] = 0;
   out_4403213144206436728[103] = 0;
   out_4403213144206436728[104] = dt;
   out_4403213144206436728[105] = 0;
   out_4403213144206436728[106] = 0;
   out_4403213144206436728[107] = 0;
   out_4403213144206436728[108] = 0;
   out_4403213144206436728[109] = 0;
   out_4403213144206436728[110] = 0;
   out_4403213144206436728[111] = 0;
   out_4403213144206436728[112] = 0;
   out_4403213144206436728[113] = 0;
   out_4403213144206436728[114] = 1;
   out_4403213144206436728[115] = 0;
   out_4403213144206436728[116] = 0;
   out_4403213144206436728[117] = 0;
   out_4403213144206436728[118] = 0;
   out_4403213144206436728[119] = 0;
   out_4403213144206436728[120] = 0;
   out_4403213144206436728[121] = 0;
   out_4403213144206436728[122] = 0;
   out_4403213144206436728[123] = 0;
   out_4403213144206436728[124] = 0;
   out_4403213144206436728[125] = 0;
   out_4403213144206436728[126] = 0;
   out_4403213144206436728[127] = 0;
   out_4403213144206436728[128] = 0;
   out_4403213144206436728[129] = 0;
   out_4403213144206436728[130] = 0;
   out_4403213144206436728[131] = 0;
   out_4403213144206436728[132] = 0;
   out_4403213144206436728[133] = 1;
   out_4403213144206436728[134] = 0;
   out_4403213144206436728[135] = 0;
   out_4403213144206436728[136] = 0;
   out_4403213144206436728[137] = 0;
   out_4403213144206436728[138] = 0;
   out_4403213144206436728[139] = 0;
   out_4403213144206436728[140] = 0;
   out_4403213144206436728[141] = 0;
   out_4403213144206436728[142] = 0;
   out_4403213144206436728[143] = 0;
   out_4403213144206436728[144] = 0;
   out_4403213144206436728[145] = 0;
   out_4403213144206436728[146] = 0;
   out_4403213144206436728[147] = 0;
   out_4403213144206436728[148] = 0;
   out_4403213144206436728[149] = 0;
   out_4403213144206436728[150] = 0;
   out_4403213144206436728[151] = 0;
   out_4403213144206436728[152] = 1;
   out_4403213144206436728[153] = 0;
   out_4403213144206436728[154] = 0;
   out_4403213144206436728[155] = 0;
   out_4403213144206436728[156] = 0;
   out_4403213144206436728[157] = 0;
   out_4403213144206436728[158] = 0;
   out_4403213144206436728[159] = 0;
   out_4403213144206436728[160] = 0;
   out_4403213144206436728[161] = 0;
   out_4403213144206436728[162] = 0;
   out_4403213144206436728[163] = 0;
   out_4403213144206436728[164] = 0;
   out_4403213144206436728[165] = 0;
   out_4403213144206436728[166] = 0;
   out_4403213144206436728[167] = 0;
   out_4403213144206436728[168] = 0;
   out_4403213144206436728[169] = 0;
   out_4403213144206436728[170] = 0;
   out_4403213144206436728[171] = 1;
   out_4403213144206436728[172] = 0;
   out_4403213144206436728[173] = 0;
   out_4403213144206436728[174] = 0;
   out_4403213144206436728[175] = 0;
   out_4403213144206436728[176] = 0;
   out_4403213144206436728[177] = 0;
   out_4403213144206436728[178] = 0;
   out_4403213144206436728[179] = 0;
   out_4403213144206436728[180] = 0;
   out_4403213144206436728[181] = 0;
   out_4403213144206436728[182] = 0;
   out_4403213144206436728[183] = 0;
   out_4403213144206436728[184] = 0;
   out_4403213144206436728[185] = 0;
   out_4403213144206436728[186] = 0;
   out_4403213144206436728[187] = 0;
   out_4403213144206436728[188] = 0;
   out_4403213144206436728[189] = 0;
   out_4403213144206436728[190] = 1;
   out_4403213144206436728[191] = 0;
   out_4403213144206436728[192] = 0;
   out_4403213144206436728[193] = 0;
   out_4403213144206436728[194] = 0;
   out_4403213144206436728[195] = 0;
   out_4403213144206436728[196] = 0;
   out_4403213144206436728[197] = 0;
   out_4403213144206436728[198] = 0;
   out_4403213144206436728[199] = 0;
   out_4403213144206436728[200] = 0;
   out_4403213144206436728[201] = 0;
   out_4403213144206436728[202] = 0;
   out_4403213144206436728[203] = 0;
   out_4403213144206436728[204] = 0;
   out_4403213144206436728[205] = 0;
   out_4403213144206436728[206] = 0;
   out_4403213144206436728[207] = 0;
   out_4403213144206436728[208] = 0;
   out_4403213144206436728[209] = 1;
   out_4403213144206436728[210] = 0;
   out_4403213144206436728[211] = 0;
   out_4403213144206436728[212] = 0;
   out_4403213144206436728[213] = 0;
   out_4403213144206436728[214] = 0;
   out_4403213144206436728[215] = 0;
   out_4403213144206436728[216] = 0;
   out_4403213144206436728[217] = 0;
   out_4403213144206436728[218] = 0;
   out_4403213144206436728[219] = 0;
   out_4403213144206436728[220] = 0;
   out_4403213144206436728[221] = 0;
   out_4403213144206436728[222] = 0;
   out_4403213144206436728[223] = 0;
   out_4403213144206436728[224] = 0;
   out_4403213144206436728[225] = 0;
   out_4403213144206436728[226] = 0;
   out_4403213144206436728[227] = 0;
   out_4403213144206436728[228] = 1;
   out_4403213144206436728[229] = 0;
   out_4403213144206436728[230] = 0;
   out_4403213144206436728[231] = 0;
   out_4403213144206436728[232] = 0;
   out_4403213144206436728[233] = 0;
   out_4403213144206436728[234] = 0;
   out_4403213144206436728[235] = 0;
   out_4403213144206436728[236] = 0;
   out_4403213144206436728[237] = 0;
   out_4403213144206436728[238] = 0;
   out_4403213144206436728[239] = 0;
   out_4403213144206436728[240] = 0;
   out_4403213144206436728[241] = 0;
   out_4403213144206436728[242] = 0;
   out_4403213144206436728[243] = 0;
   out_4403213144206436728[244] = 0;
   out_4403213144206436728[245] = 0;
   out_4403213144206436728[246] = 0;
   out_4403213144206436728[247] = 1;
   out_4403213144206436728[248] = 0;
   out_4403213144206436728[249] = 0;
   out_4403213144206436728[250] = 0;
   out_4403213144206436728[251] = 0;
   out_4403213144206436728[252] = 0;
   out_4403213144206436728[253] = 0;
   out_4403213144206436728[254] = 0;
   out_4403213144206436728[255] = 0;
   out_4403213144206436728[256] = 0;
   out_4403213144206436728[257] = 0;
   out_4403213144206436728[258] = 0;
   out_4403213144206436728[259] = 0;
   out_4403213144206436728[260] = 0;
   out_4403213144206436728[261] = 0;
   out_4403213144206436728[262] = 0;
   out_4403213144206436728[263] = 0;
   out_4403213144206436728[264] = 0;
   out_4403213144206436728[265] = 0;
   out_4403213144206436728[266] = 1;
   out_4403213144206436728[267] = 0;
   out_4403213144206436728[268] = 0;
   out_4403213144206436728[269] = 0;
   out_4403213144206436728[270] = 0;
   out_4403213144206436728[271] = 0;
   out_4403213144206436728[272] = 0;
   out_4403213144206436728[273] = 0;
   out_4403213144206436728[274] = 0;
   out_4403213144206436728[275] = 0;
   out_4403213144206436728[276] = 0;
   out_4403213144206436728[277] = 0;
   out_4403213144206436728[278] = 0;
   out_4403213144206436728[279] = 0;
   out_4403213144206436728[280] = 0;
   out_4403213144206436728[281] = 0;
   out_4403213144206436728[282] = 0;
   out_4403213144206436728[283] = 0;
   out_4403213144206436728[284] = 0;
   out_4403213144206436728[285] = 1;
   out_4403213144206436728[286] = 0;
   out_4403213144206436728[287] = 0;
   out_4403213144206436728[288] = 0;
   out_4403213144206436728[289] = 0;
   out_4403213144206436728[290] = 0;
   out_4403213144206436728[291] = 0;
   out_4403213144206436728[292] = 0;
   out_4403213144206436728[293] = 0;
   out_4403213144206436728[294] = 0;
   out_4403213144206436728[295] = 0;
   out_4403213144206436728[296] = 0;
   out_4403213144206436728[297] = 0;
   out_4403213144206436728[298] = 0;
   out_4403213144206436728[299] = 0;
   out_4403213144206436728[300] = 0;
   out_4403213144206436728[301] = 0;
   out_4403213144206436728[302] = 0;
   out_4403213144206436728[303] = 0;
   out_4403213144206436728[304] = 1;
   out_4403213144206436728[305] = 0;
   out_4403213144206436728[306] = 0;
   out_4403213144206436728[307] = 0;
   out_4403213144206436728[308] = 0;
   out_4403213144206436728[309] = 0;
   out_4403213144206436728[310] = 0;
   out_4403213144206436728[311] = 0;
   out_4403213144206436728[312] = 0;
   out_4403213144206436728[313] = 0;
   out_4403213144206436728[314] = 0;
   out_4403213144206436728[315] = 0;
   out_4403213144206436728[316] = 0;
   out_4403213144206436728[317] = 0;
   out_4403213144206436728[318] = 0;
   out_4403213144206436728[319] = 0;
   out_4403213144206436728[320] = 0;
   out_4403213144206436728[321] = 0;
   out_4403213144206436728[322] = 0;
   out_4403213144206436728[323] = 1;
}
void h_4(double *state, double *unused, double *out_8489697203254357767) {
   out_8489697203254357767[0] = state[6] + state[9];
   out_8489697203254357767[1] = state[7] + state[10];
   out_8489697203254357767[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5679269699215051709) {
   out_5679269699215051709[0] = 0;
   out_5679269699215051709[1] = 0;
   out_5679269699215051709[2] = 0;
   out_5679269699215051709[3] = 0;
   out_5679269699215051709[4] = 0;
   out_5679269699215051709[5] = 0;
   out_5679269699215051709[6] = 1;
   out_5679269699215051709[7] = 0;
   out_5679269699215051709[8] = 0;
   out_5679269699215051709[9] = 1;
   out_5679269699215051709[10] = 0;
   out_5679269699215051709[11] = 0;
   out_5679269699215051709[12] = 0;
   out_5679269699215051709[13] = 0;
   out_5679269699215051709[14] = 0;
   out_5679269699215051709[15] = 0;
   out_5679269699215051709[16] = 0;
   out_5679269699215051709[17] = 0;
   out_5679269699215051709[18] = 0;
   out_5679269699215051709[19] = 0;
   out_5679269699215051709[20] = 0;
   out_5679269699215051709[21] = 0;
   out_5679269699215051709[22] = 0;
   out_5679269699215051709[23] = 0;
   out_5679269699215051709[24] = 0;
   out_5679269699215051709[25] = 1;
   out_5679269699215051709[26] = 0;
   out_5679269699215051709[27] = 0;
   out_5679269699215051709[28] = 1;
   out_5679269699215051709[29] = 0;
   out_5679269699215051709[30] = 0;
   out_5679269699215051709[31] = 0;
   out_5679269699215051709[32] = 0;
   out_5679269699215051709[33] = 0;
   out_5679269699215051709[34] = 0;
   out_5679269699215051709[35] = 0;
   out_5679269699215051709[36] = 0;
   out_5679269699215051709[37] = 0;
   out_5679269699215051709[38] = 0;
   out_5679269699215051709[39] = 0;
   out_5679269699215051709[40] = 0;
   out_5679269699215051709[41] = 0;
   out_5679269699215051709[42] = 0;
   out_5679269699215051709[43] = 0;
   out_5679269699215051709[44] = 1;
   out_5679269699215051709[45] = 0;
   out_5679269699215051709[46] = 0;
   out_5679269699215051709[47] = 1;
   out_5679269699215051709[48] = 0;
   out_5679269699215051709[49] = 0;
   out_5679269699215051709[50] = 0;
   out_5679269699215051709[51] = 0;
   out_5679269699215051709[52] = 0;
   out_5679269699215051709[53] = 0;
}
void h_10(double *state, double *unused, double *out_5978013585373209228) {
   out_5978013585373209228[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5978013585373209228[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5978013585373209228[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7613399179514016916) {
   out_7613399179514016916[0] = 0;
   out_7613399179514016916[1] = 9.8100000000000005*cos(state[1]);
   out_7613399179514016916[2] = 0;
   out_7613399179514016916[3] = 0;
   out_7613399179514016916[4] = -state[8];
   out_7613399179514016916[5] = state[7];
   out_7613399179514016916[6] = 0;
   out_7613399179514016916[7] = state[5];
   out_7613399179514016916[8] = -state[4];
   out_7613399179514016916[9] = 0;
   out_7613399179514016916[10] = 0;
   out_7613399179514016916[11] = 0;
   out_7613399179514016916[12] = 1;
   out_7613399179514016916[13] = 0;
   out_7613399179514016916[14] = 0;
   out_7613399179514016916[15] = 1;
   out_7613399179514016916[16] = 0;
   out_7613399179514016916[17] = 0;
   out_7613399179514016916[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7613399179514016916[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7613399179514016916[20] = 0;
   out_7613399179514016916[21] = state[8];
   out_7613399179514016916[22] = 0;
   out_7613399179514016916[23] = -state[6];
   out_7613399179514016916[24] = -state[5];
   out_7613399179514016916[25] = 0;
   out_7613399179514016916[26] = state[3];
   out_7613399179514016916[27] = 0;
   out_7613399179514016916[28] = 0;
   out_7613399179514016916[29] = 0;
   out_7613399179514016916[30] = 0;
   out_7613399179514016916[31] = 1;
   out_7613399179514016916[32] = 0;
   out_7613399179514016916[33] = 0;
   out_7613399179514016916[34] = 1;
   out_7613399179514016916[35] = 0;
   out_7613399179514016916[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7613399179514016916[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7613399179514016916[38] = 0;
   out_7613399179514016916[39] = -state[7];
   out_7613399179514016916[40] = state[6];
   out_7613399179514016916[41] = 0;
   out_7613399179514016916[42] = state[4];
   out_7613399179514016916[43] = -state[3];
   out_7613399179514016916[44] = 0;
   out_7613399179514016916[45] = 0;
   out_7613399179514016916[46] = 0;
   out_7613399179514016916[47] = 0;
   out_7613399179514016916[48] = 0;
   out_7613399179514016916[49] = 0;
   out_7613399179514016916[50] = 1;
   out_7613399179514016916[51] = 0;
   out_7613399179514016916[52] = 0;
   out_7613399179514016916[53] = 1;
}
void h_13(double *state, double *unused, double *out_1921649809916094897) {
   out_1921649809916094897[0] = state[3];
   out_1921649809916094897[1] = state[4];
   out_1921649809916094897[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2466995873882718908) {
   out_2466995873882718908[0] = 0;
   out_2466995873882718908[1] = 0;
   out_2466995873882718908[2] = 0;
   out_2466995873882718908[3] = 1;
   out_2466995873882718908[4] = 0;
   out_2466995873882718908[5] = 0;
   out_2466995873882718908[6] = 0;
   out_2466995873882718908[7] = 0;
   out_2466995873882718908[8] = 0;
   out_2466995873882718908[9] = 0;
   out_2466995873882718908[10] = 0;
   out_2466995873882718908[11] = 0;
   out_2466995873882718908[12] = 0;
   out_2466995873882718908[13] = 0;
   out_2466995873882718908[14] = 0;
   out_2466995873882718908[15] = 0;
   out_2466995873882718908[16] = 0;
   out_2466995873882718908[17] = 0;
   out_2466995873882718908[18] = 0;
   out_2466995873882718908[19] = 0;
   out_2466995873882718908[20] = 0;
   out_2466995873882718908[21] = 0;
   out_2466995873882718908[22] = 1;
   out_2466995873882718908[23] = 0;
   out_2466995873882718908[24] = 0;
   out_2466995873882718908[25] = 0;
   out_2466995873882718908[26] = 0;
   out_2466995873882718908[27] = 0;
   out_2466995873882718908[28] = 0;
   out_2466995873882718908[29] = 0;
   out_2466995873882718908[30] = 0;
   out_2466995873882718908[31] = 0;
   out_2466995873882718908[32] = 0;
   out_2466995873882718908[33] = 0;
   out_2466995873882718908[34] = 0;
   out_2466995873882718908[35] = 0;
   out_2466995873882718908[36] = 0;
   out_2466995873882718908[37] = 0;
   out_2466995873882718908[38] = 0;
   out_2466995873882718908[39] = 0;
   out_2466995873882718908[40] = 0;
   out_2466995873882718908[41] = 1;
   out_2466995873882718908[42] = 0;
   out_2466995873882718908[43] = 0;
   out_2466995873882718908[44] = 0;
   out_2466995873882718908[45] = 0;
   out_2466995873882718908[46] = 0;
   out_2466995873882718908[47] = 0;
   out_2466995873882718908[48] = 0;
   out_2466995873882718908[49] = 0;
   out_2466995873882718908[50] = 0;
   out_2466995873882718908[51] = 0;
   out_2466995873882718908[52] = 0;
   out_2466995873882718908[53] = 0;
}
void h_14(double *state, double *unused, double *out_125818232234200489) {
   out_125818232234200489[0] = state[6];
   out_125818232234200489[1] = state[7];
   out_125818232234200489[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1716028842875567180) {
   out_1716028842875567180[0] = 0;
   out_1716028842875567180[1] = 0;
   out_1716028842875567180[2] = 0;
   out_1716028842875567180[3] = 0;
   out_1716028842875567180[4] = 0;
   out_1716028842875567180[5] = 0;
   out_1716028842875567180[6] = 1;
   out_1716028842875567180[7] = 0;
   out_1716028842875567180[8] = 0;
   out_1716028842875567180[9] = 0;
   out_1716028842875567180[10] = 0;
   out_1716028842875567180[11] = 0;
   out_1716028842875567180[12] = 0;
   out_1716028842875567180[13] = 0;
   out_1716028842875567180[14] = 0;
   out_1716028842875567180[15] = 0;
   out_1716028842875567180[16] = 0;
   out_1716028842875567180[17] = 0;
   out_1716028842875567180[18] = 0;
   out_1716028842875567180[19] = 0;
   out_1716028842875567180[20] = 0;
   out_1716028842875567180[21] = 0;
   out_1716028842875567180[22] = 0;
   out_1716028842875567180[23] = 0;
   out_1716028842875567180[24] = 0;
   out_1716028842875567180[25] = 1;
   out_1716028842875567180[26] = 0;
   out_1716028842875567180[27] = 0;
   out_1716028842875567180[28] = 0;
   out_1716028842875567180[29] = 0;
   out_1716028842875567180[30] = 0;
   out_1716028842875567180[31] = 0;
   out_1716028842875567180[32] = 0;
   out_1716028842875567180[33] = 0;
   out_1716028842875567180[34] = 0;
   out_1716028842875567180[35] = 0;
   out_1716028842875567180[36] = 0;
   out_1716028842875567180[37] = 0;
   out_1716028842875567180[38] = 0;
   out_1716028842875567180[39] = 0;
   out_1716028842875567180[40] = 0;
   out_1716028842875567180[41] = 0;
   out_1716028842875567180[42] = 0;
   out_1716028842875567180[43] = 0;
   out_1716028842875567180[44] = 1;
   out_1716028842875567180[45] = 0;
   out_1716028842875567180[46] = 0;
   out_1716028842875567180[47] = 0;
   out_1716028842875567180[48] = 0;
   out_1716028842875567180[49] = 0;
   out_1716028842875567180[50] = 0;
   out_1716028842875567180[51] = 0;
   out_1716028842875567180[52] = 0;
   out_1716028842875567180[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_752852575942216847) {
  err_fun(nom_x, delta_x, out_752852575942216847);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1438979586232603189) {
  inv_err_fun(nom_x, true_x, out_1438979586232603189);
}
void pose_H_mod_fun(double *state, double *out_7614955989455419172) {
  H_mod_fun(state, out_7614955989455419172);
}
void pose_f_fun(double *state, double dt, double *out_5899861132242380131) {
  f_fun(state,  dt, out_5899861132242380131);
}
void pose_F_fun(double *state, double dt, double *out_4403213144206436728) {
  F_fun(state,  dt, out_4403213144206436728);
}
void pose_h_4(double *state, double *unused, double *out_8489697203254357767) {
  h_4(state, unused, out_8489697203254357767);
}
void pose_H_4(double *state, double *unused, double *out_5679269699215051709) {
  H_4(state, unused, out_5679269699215051709);
}
void pose_h_10(double *state, double *unused, double *out_5978013585373209228) {
  h_10(state, unused, out_5978013585373209228);
}
void pose_H_10(double *state, double *unused, double *out_7613399179514016916) {
  H_10(state, unused, out_7613399179514016916);
}
void pose_h_13(double *state, double *unused, double *out_1921649809916094897) {
  h_13(state, unused, out_1921649809916094897);
}
void pose_H_13(double *state, double *unused, double *out_2466995873882718908) {
  H_13(state, unused, out_2466995873882718908);
}
void pose_h_14(double *state, double *unused, double *out_125818232234200489) {
  h_14(state, unused, out_125818232234200489);
}
void pose_H_14(double *state, double *unused, double *out_1716028842875567180) {
  H_14(state, unused, out_1716028842875567180);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
