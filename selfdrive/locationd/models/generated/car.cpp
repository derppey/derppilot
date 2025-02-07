#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.13.2                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_5979617889551613915) {
   out_5979617889551613915[0] = delta_x[0] + nom_x[0];
   out_5979617889551613915[1] = delta_x[1] + nom_x[1];
   out_5979617889551613915[2] = delta_x[2] + nom_x[2];
   out_5979617889551613915[3] = delta_x[3] + nom_x[3];
   out_5979617889551613915[4] = delta_x[4] + nom_x[4];
   out_5979617889551613915[5] = delta_x[5] + nom_x[5];
   out_5979617889551613915[6] = delta_x[6] + nom_x[6];
   out_5979617889551613915[7] = delta_x[7] + nom_x[7];
   out_5979617889551613915[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2829649976459644767) {
   out_2829649976459644767[0] = -nom_x[0] + true_x[0];
   out_2829649976459644767[1] = -nom_x[1] + true_x[1];
   out_2829649976459644767[2] = -nom_x[2] + true_x[2];
   out_2829649976459644767[3] = -nom_x[3] + true_x[3];
   out_2829649976459644767[4] = -nom_x[4] + true_x[4];
   out_2829649976459644767[5] = -nom_x[5] + true_x[5];
   out_2829649976459644767[6] = -nom_x[6] + true_x[6];
   out_2829649976459644767[7] = -nom_x[7] + true_x[7];
   out_2829649976459644767[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3057922570853057598) {
   out_3057922570853057598[0] = 1.0;
   out_3057922570853057598[1] = 0.0;
   out_3057922570853057598[2] = 0.0;
   out_3057922570853057598[3] = 0.0;
   out_3057922570853057598[4] = 0.0;
   out_3057922570853057598[5] = 0.0;
   out_3057922570853057598[6] = 0.0;
   out_3057922570853057598[7] = 0.0;
   out_3057922570853057598[8] = 0.0;
   out_3057922570853057598[9] = 0.0;
   out_3057922570853057598[10] = 1.0;
   out_3057922570853057598[11] = 0.0;
   out_3057922570853057598[12] = 0.0;
   out_3057922570853057598[13] = 0.0;
   out_3057922570853057598[14] = 0.0;
   out_3057922570853057598[15] = 0.0;
   out_3057922570853057598[16] = 0.0;
   out_3057922570853057598[17] = 0.0;
   out_3057922570853057598[18] = 0.0;
   out_3057922570853057598[19] = 0.0;
   out_3057922570853057598[20] = 1.0;
   out_3057922570853057598[21] = 0.0;
   out_3057922570853057598[22] = 0.0;
   out_3057922570853057598[23] = 0.0;
   out_3057922570853057598[24] = 0.0;
   out_3057922570853057598[25] = 0.0;
   out_3057922570853057598[26] = 0.0;
   out_3057922570853057598[27] = 0.0;
   out_3057922570853057598[28] = 0.0;
   out_3057922570853057598[29] = 0.0;
   out_3057922570853057598[30] = 1.0;
   out_3057922570853057598[31] = 0.0;
   out_3057922570853057598[32] = 0.0;
   out_3057922570853057598[33] = 0.0;
   out_3057922570853057598[34] = 0.0;
   out_3057922570853057598[35] = 0.0;
   out_3057922570853057598[36] = 0.0;
   out_3057922570853057598[37] = 0.0;
   out_3057922570853057598[38] = 0.0;
   out_3057922570853057598[39] = 0.0;
   out_3057922570853057598[40] = 1.0;
   out_3057922570853057598[41] = 0.0;
   out_3057922570853057598[42] = 0.0;
   out_3057922570853057598[43] = 0.0;
   out_3057922570853057598[44] = 0.0;
   out_3057922570853057598[45] = 0.0;
   out_3057922570853057598[46] = 0.0;
   out_3057922570853057598[47] = 0.0;
   out_3057922570853057598[48] = 0.0;
   out_3057922570853057598[49] = 0.0;
   out_3057922570853057598[50] = 1.0;
   out_3057922570853057598[51] = 0.0;
   out_3057922570853057598[52] = 0.0;
   out_3057922570853057598[53] = 0.0;
   out_3057922570853057598[54] = 0.0;
   out_3057922570853057598[55] = 0.0;
   out_3057922570853057598[56] = 0.0;
   out_3057922570853057598[57] = 0.0;
   out_3057922570853057598[58] = 0.0;
   out_3057922570853057598[59] = 0.0;
   out_3057922570853057598[60] = 1.0;
   out_3057922570853057598[61] = 0.0;
   out_3057922570853057598[62] = 0.0;
   out_3057922570853057598[63] = 0.0;
   out_3057922570853057598[64] = 0.0;
   out_3057922570853057598[65] = 0.0;
   out_3057922570853057598[66] = 0.0;
   out_3057922570853057598[67] = 0.0;
   out_3057922570853057598[68] = 0.0;
   out_3057922570853057598[69] = 0.0;
   out_3057922570853057598[70] = 1.0;
   out_3057922570853057598[71] = 0.0;
   out_3057922570853057598[72] = 0.0;
   out_3057922570853057598[73] = 0.0;
   out_3057922570853057598[74] = 0.0;
   out_3057922570853057598[75] = 0.0;
   out_3057922570853057598[76] = 0.0;
   out_3057922570853057598[77] = 0.0;
   out_3057922570853057598[78] = 0.0;
   out_3057922570853057598[79] = 0.0;
   out_3057922570853057598[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7312220419989483860) {
   out_7312220419989483860[0] = state[0];
   out_7312220419989483860[1] = state[1];
   out_7312220419989483860[2] = state[2];
   out_7312220419989483860[3] = state[3];
   out_7312220419989483860[4] = state[4];
   out_7312220419989483860[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7312220419989483860[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7312220419989483860[7] = state[7];
   out_7312220419989483860[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1870503519340438721) {
   out_1870503519340438721[0] = 1;
   out_1870503519340438721[1] = 0;
   out_1870503519340438721[2] = 0;
   out_1870503519340438721[3] = 0;
   out_1870503519340438721[4] = 0;
   out_1870503519340438721[5] = 0;
   out_1870503519340438721[6] = 0;
   out_1870503519340438721[7] = 0;
   out_1870503519340438721[8] = 0;
   out_1870503519340438721[9] = 0;
   out_1870503519340438721[10] = 1;
   out_1870503519340438721[11] = 0;
   out_1870503519340438721[12] = 0;
   out_1870503519340438721[13] = 0;
   out_1870503519340438721[14] = 0;
   out_1870503519340438721[15] = 0;
   out_1870503519340438721[16] = 0;
   out_1870503519340438721[17] = 0;
   out_1870503519340438721[18] = 0;
   out_1870503519340438721[19] = 0;
   out_1870503519340438721[20] = 1;
   out_1870503519340438721[21] = 0;
   out_1870503519340438721[22] = 0;
   out_1870503519340438721[23] = 0;
   out_1870503519340438721[24] = 0;
   out_1870503519340438721[25] = 0;
   out_1870503519340438721[26] = 0;
   out_1870503519340438721[27] = 0;
   out_1870503519340438721[28] = 0;
   out_1870503519340438721[29] = 0;
   out_1870503519340438721[30] = 1;
   out_1870503519340438721[31] = 0;
   out_1870503519340438721[32] = 0;
   out_1870503519340438721[33] = 0;
   out_1870503519340438721[34] = 0;
   out_1870503519340438721[35] = 0;
   out_1870503519340438721[36] = 0;
   out_1870503519340438721[37] = 0;
   out_1870503519340438721[38] = 0;
   out_1870503519340438721[39] = 0;
   out_1870503519340438721[40] = 1;
   out_1870503519340438721[41] = 0;
   out_1870503519340438721[42] = 0;
   out_1870503519340438721[43] = 0;
   out_1870503519340438721[44] = 0;
   out_1870503519340438721[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1870503519340438721[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1870503519340438721[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1870503519340438721[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1870503519340438721[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1870503519340438721[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1870503519340438721[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1870503519340438721[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1870503519340438721[53] = -9.8000000000000007*dt;
   out_1870503519340438721[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1870503519340438721[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1870503519340438721[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1870503519340438721[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1870503519340438721[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1870503519340438721[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1870503519340438721[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1870503519340438721[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1870503519340438721[62] = 0;
   out_1870503519340438721[63] = 0;
   out_1870503519340438721[64] = 0;
   out_1870503519340438721[65] = 0;
   out_1870503519340438721[66] = 0;
   out_1870503519340438721[67] = 0;
   out_1870503519340438721[68] = 0;
   out_1870503519340438721[69] = 0;
   out_1870503519340438721[70] = 1;
   out_1870503519340438721[71] = 0;
   out_1870503519340438721[72] = 0;
   out_1870503519340438721[73] = 0;
   out_1870503519340438721[74] = 0;
   out_1870503519340438721[75] = 0;
   out_1870503519340438721[76] = 0;
   out_1870503519340438721[77] = 0;
   out_1870503519340438721[78] = 0;
   out_1870503519340438721[79] = 0;
   out_1870503519340438721[80] = 1;
}
void h_25(double *state, double *unused, double *out_353806231527037977) {
   out_353806231527037977[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7961614396037722438) {
   out_7961614396037722438[0] = 0;
   out_7961614396037722438[1] = 0;
   out_7961614396037722438[2] = 0;
   out_7961614396037722438[3] = 0;
   out_7961614396037722438[4] = 0;
   out_7961614396037722438[5] = 0;
   out_7961614396037722438[6] = 1;
   out_7961614396037722438[7] = 0;
   out_7961614396037722438[8] = 0;
}
void h_24(double *state, double *unused, double *out_7461992751078079557) {
   out_7461992751078079557[0] = state[4];
   out_7461992751078079557[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8806611004821417837) {
   out_8806611004821417837[0] = 0;
   out_8806611004821417837[1] = 0;
   out_8806611004821417837[2] = 0;
   out_8806611004821417837[3] = 0;
   out_8806611004821417837[4] = 1;
   out_8806611004821417837[5] = 0;
   out_8806611004821417837[6] = 0;
   out_8806611004821417837[7] = 0;
   out_8806611004821417837[8] = 0;
   out_8806611004821417837[9] = 0;
   out_8806611004821417837[10] = 0;
   out_8806611004821417837[11] = 0;
   out_8806611004821417837[12] = 0;
   out_8806611004821417837[13] = 0;
   out_8806611004821417837[14] = 1;
   out_8806611004821417837[15] = 0;
   out_8806611004821417837[16] = 0;
   out_8806611004821417837[17] = 0;
}
void h_30(double *state, double *unused, double *out_1804437624155921144) {
   out_1804437624155921144[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3568439336180212423) {
   out_3568439336180212423[0] = 0;
   out_3568439336180212423[1] = 0;
   out_3568439336180212423[2] = 0;
   out_3568439336180212423[3] = 0;
   out_3568439336180212423[4] = 1;
   out_3568439336180212423[5] = 0;
   out_3568439336180212423[6] = 0;
   out_3568439336180212423[7] = 0;
   out_3568439336180212423[8] = 0;
}
void h_26(double *state, double *unused, double *out_1611835665493148872) {
   out_1611835665493148872[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4220111077163666214) {
   out_4220111077163666214[0] = 0;
   out_4220111077163666214[1] = 0;
   out_4220111077163666214[2] = 0;
   out_4220111077163666214[3] = 0;
   out_4220111077163666214[4] = 0;
   out_4220111077163666214[5] = 0;
   out_4220111077163666214[6] = 0;
   out_4220111077163666214[7] = 1;
   out_4220111077163666214[8] = 0;
}
void h_27(double *state, double *unused, double *out_4647867036133807668) {
   out_4647867036133807668[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5743202647980637334) {
   out_5743202647980637334[0] = 0;
   out_5743202647980637334[1] = 0;
   out_5743202647980637334[2] = 0;
   out_5743202647980637334[3] = 1;
   out_5743202647980637334[4] = 0;
   out_5743202647980637334[5] = 0;
   out_5743202647980637334[6] = 0;
   out_5743202647980637334[7] = 0;
   out_5743202647980637334[8] = 0;
}
void h_29(double *state, double *unused, double *out_3197235643504924501) {
   out_3197235643504924501[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7456565374850188367) {
   out_7456565374850188367[0] = 0;
   out_7456565374850188367[1] = 1;
   out_7456565374850188367[2] = 0;
   out_7456565374850188367[3] = 0;
   out_7456565374850188367[4] = 0;
   out_7456565374850188367[5] = 0;
   out_7456565374850188367[6] = 0;
   out_7456565374850188367[7] = 0;
   out_7456565374850188367[8] = 0;
}
void h_28(double *state, double *unused, double *out_8732459518857401225) {
   out_8732459518857401225[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5907779681789832675) {
   out_5907779681789832675[0] = 1;
   out_5907779681789832675[1] = 0;
   out_5907779681789832675[2] = 0;
   out_5907779681789832675[3] = 0;
   out_5907779681789832675[4] = 0;
   out_5907779681789832675[5] = 0;
   out_5907779681789832675[6] = 0;
   out_5907779681789832675[7] = 0;
   out_5907779681789832675[8] = 0;
}
void h_31(double *state, double *unused, double *out_6417028994823312959) {
   out_6417028994823312959[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7992260357914682866) {
   out_7992260357914682866[0] = 0;
   out_7992260357914682866[1] = 0;
   out_7992260357914682866[2] = 0;
   out_7992260357914682866[3] = 0;
   out_7992260357914682866[4] = 0;
   out_7992260357914682866[5] = 0;
   out_7992260357914682866[6] = 0;
   out_7992260357914682866[7] = 0;
   out_7992260357914682866[8] = 1;
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

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_5979617889551613915) {
  err_fun(nom_x, delta_x, out_5979617889551613915);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2829649976459644767) {
  inv_err_fun(nom_x, true_x, out_2829649976459644767);
}
void car_H_mod_fun(double *state, double *out_3057922570853057598) {
  H_mod_fun(state, out_3057922570853057598);
}
void car_f_fun(double *state, double dt, double *out_7312220419989483860) {
  f_fun(state,  dt, out_7312220419989483860);
}
void car_F_fun(double *state, double dt, double *out_1870503519340438721) {
  F_fun(state,  dt, out_1870503519340438721);
}
void car_h_25(double *state, double *unused, double *out_353806231527037977) {
  h_25(state, unused, out_353806231527037977);
}
void car_H_25(double *state, double *unused, double *out_7961614396037722438) {
  H_25(state, unused, out_7961614396037722438);
}
void car_h_24(double *state, double *unused, double *out_7461992751078079557) {
  h_24(state, unused, out_7461992751078079557);
}
void car_H_24(double *state, double *unused, double *out_8806611004821417837) {
  H_24(state, unused, out_8806611004821417837);
}
void car_h_30(double *state, double *unused, double *out_1804437624155921144) {
  h_30(state, unused, out_1804437624155921144);
}
void car_H_30(double *state, double *unused, double *out_3568439336180212423) {
  H_30(state, unused, out_3568439336180212423);
}
void car_h_26(double *state, double *unused, double *out_1611835665493148872) {
  h_26(state, unused, out_1611835665493148872);
}
void car_H_26(double *state, double *unused, double *out_4220111077163666214) {
  H_26(state, unused, out_4220111077163666214);
}
void car_h_27(double *state, double *unused, double *out_4647867036133807668) {
  h_27(state, unused, out_4647867036133807668);
}
void car_H_27(double *state, double *unused, double *out_5743202647980637334) {
  H_27(state, unused, out_5743202647980637334);
}
void car_h_29(double *state, double *unused, double *out_3197235643504924501) {
  h_29(state, unused, out_3197235643504924501);
}
void car_H_29(double *state, double *unused, double *out_7456565374850188367) {
  H_29(state, unused, out_7456565374850188367);
}
void car_h_28(double *state, double *unused, double *out_8732459518857401225) {
  h_28(state, unused, out_8732459518857401225);
}
void car_H_28(double *state, double *unused, double *out_5907779681789832675) {
  H_28(state, unused, out_5907779681789832675);
}
void car_h_31(double *state, double *unused, double *out_6417028994823312959) {
  h_31(state, unused, out_6417028994823312959);
}
void car_H_31(double *state, double *unused, double *out_7992260357914682866) {
  H_31(state, unused, out_7992260357914682866);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
