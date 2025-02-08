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
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_6151971862348982707) {
   out_6151971862348982707[0] = delta_x[0] + nom_x[0];
   out_6151971862348982707[1] = delta_x[1] + nom_x[1];
   out_6151971862348982707[2] = delta_x[2] + nom_x[2];
   out_6151971862348982707[3] = delta_x[3] + nom_x[3];
   out_6151971862348982707[4] = delta_x[4] + nom_x[4];
   out_6151971862348982707[5] = delta_x[5] + nom_x[5];
   out_6151971862348982707[6] = delta_x[6] + nom_x[6];
   out_6151971862348982707[7] = delta_x[7] + nom_x[7];
   out_6151971862348982707[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8906144065106568249) {
   out_8906144065106568249[0] = -nom_x[0] + true_x[0];
   out_8906144065106568249[1] = -nom_x[1] + true_x[1];
   out_8906144065106568249[2] = -nom_x[2] + true_x[2];
   out_8906144065106568249[3] = -nom_x[3] + true_x[3];
   out_8906144065106568249[4] = -nom_x[4] + true_x[4];
   out_8906144065106568249[5] = -nom_x[5] + true_x[5];
   out_8906144065106568249[6] = -nom_x[6] + true_x[6];
   out_8906144065106568249[7] = -nom_x[7] + true_x[7];
   out_8906144065106568249[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2245417875284688136) {
   out_2245417875284688136[0] = 1.0;
   out_2245417875284688136[1] = 0;
   out_2245417875284688136[2] = 0;
   out_2245417875284688136[3] = 0;
   out_2245417875284688136[4] = 0;
   out_2245417875284688136[5] = 0;
   out_2245417875284688136[6] = 0;
   out_2245417875284688136[7] = 0;
   out_2245417875284688136[8] = 0;
   out_2245417875284688136[9] = 0;
   out_2245417875284688136[10] = 1.0;
   out_2245417875284688136[11] = 0;
   out_2245417875284688136[12] = 0;
   out_2245417875284688136[13] = 0;
   out_2245417875284688136[14] = 0;
   out_2245417875284688136[15] = 0;
   out_2245417875284688136[16] = 0;
   out_2245417875284688136[17] = 0;
   out_2245417875284688136[18] = 0;
   out_2245417875284688136[19] = 0;
   out_2245417875284688136[20] = 1.0;
   out_2245417875284688136[21] = 0;
   out_2245417875284688136[22] = 0;
   out_2245417875284688136[23] = 0;
   out_2245417875284688136[24] = 0;
   out_2245417875284688136[25] = 0;
   out_2245417875284688136[26] = 0;
   out_2245417875284688136[27] = 0;
   out_2245417875284688136[28] = 0;
   out_2245417875284688136[29] = 0;
   out_2245417875284688136[30] = 1.0;
   out_2245417875284688136[31] = 0;
   out_2245417875284688136[32] = 0;
   out_2245417875284688136[33] = 0;
   out_2245417875284688136[34] = 0;
   out_2245417875284688136[35] = 0;
   out_2245417875284688136[36] = 0;
   out_2245417875284688136[37] = 0;
   out_2245417875284688136[38] = 0;
   out_2245417875284688136[39] = 0;
   out_2245417875284688136[40] = 1.0;
   out_2245417875284688136[41] = 0;
   out_2245417875284688136[42] = 0;
   out_2245417875284688136[43] = 0;
   out_2245417875284688136[44] = 0;
   out_2245417875284688136[45] = 0;
   out_2245417875284688136[46] = 0;
   out_2245417875284688136[47] = 0;
   out_2245417875284688136[48] = 0;
   out_2245417875284688136[49] = 0;
   out_2245417875284688136[50] = 1.0;
   out_2245417875284688136[51] = 0;
   out_2245417875284688136[52] = 0;
   out_2245417875284688136[53] = 0;
   out_2245417875284688136[54] = 0;
   out_2245417875284688136[55] = 0;
   out_2245417875284688136[56] = 0;
   out_2245417875284688136[57] = 0;
   out_2245417875284688136[58] = 0;
   out_2245417875284688136[59] = 0;
   out_2245417875284688136[60] = 1.0;
   out_2245417875284688136[61] = 0;
   out_2245417875284688136[62] = 0;
   out_2245417875284688136[63] = 0;
   out_2245417875284688136[64] = 0;
   out_2245417875284688136[65] = 0;
   out_2245417875284688136[66] = 0;
   out_2245417875284688136[67] = 0;
   out_2245417875284688136[68] = 0;
   out_2245417875284688136[69] = 0;
   out_2245417875284688136[70] = 1.0;
   out_2245417875284688136[71] = 0;
   out_2245417875284688136[72] = 0;
   out_2245417875284688136[73] = 0;
   out_2245417875284688136[74] = 0;
   out_2245417875284688136[75] = 0;
   out_2245417875284688136[76] = 0;
   out_2245417875284688136[77] = 0;
   out_2245417875284688136[78] = 0;
   out_2245417875284688136[79] = 0;
   out_2245417875284688136[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8850494657158538667) {
   out_8850494657158538667[0] = state[0];
   out_8850494657158538667[1] = state[1];
   out_8850494657158538667[2] = state[2];
   out_8850494657158538667[3] = state[3];
   out_8850494657158538667[4] = state[4];
   out_8850494657158538667[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8850494657158538667[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8850494657158538667[7] = state[7];
   out_8850494657158538667[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7163430015072164834) {
   out_7163430015072164834[0] = 1;
   out_7163430015072164834[1] = 0;
   out_7163430015072164834[2] = 0;
   out_7163430015072164834[3] = 0;
   out_7163430015072164834[4] = 0;
   out_7163430015072164834[5] = 0;
   out_7163430015072164834[6] = 0;
   out_7163430015072164834[7] = 0;
   out_7163430015072164834[8] = 0;
   out_7163430015072164834[9] = 0;
   out_7163430015072164834[10] = 1;
   out_7163430015072164834[11] = 0;
   out_7163430015072164834[12] = 0;
   out_7163430015072164834[13] = 0;
   out_7163430015072164834[14] = 0;
   out_7163430015072164834[15] = 0;
   out_7163430015072164834[16] = 0;
   out_7163430015072164834[17] = 0;
   out_7163430015072164834[18] = 0;
   out_7163430015072164834[19] = 0;
   out_7163430015072164834[20] = 1;
   out_7163430015072164834[21] = 0;
   out_7163430015072164834[22] = 0;
   out_7163430015072164834[23] = 0;
   out_7163430015072164834[24] = 0;
   out_7163430015072164834[25] = 0;
   out_7163430015072164834[26] = 0;
   out_7163430015072164834[27] = 0;
   out_7163430015072164834[28] = 0;
   out_7163430015072164834[29] = 0;
   out_7163430015072164834[30] = 1;
   out_7163430015072164834[31] = 0;
   out_7163430015072164834[32] = 0;
   out_7163430015072164834[33] = 0;
   out_7163430015072164834[34] = 0;
   out_7163430015072164834[35] = 0;
   out_7163430015072164834[36] = 0;
   out_7163430015072164834[37] = 0;
   out_7163430015072164834[38] = 0;
   out_7163430015072164834[39] = 0;
   out_7163430015072164834[40] = 1;
   out_7163430015072164834[41] = 0;
   out_7163430015072164834[42] = 0;
   out_7163430015072164834[43] = 0;
   out_7163430015072164834[44] = 0;
   out_7163430015072164834[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7163430015072164834[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7163430015072164834[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7163430015072164834[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7163430015072164834[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7163430015072164834[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7163430015072164834[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7163430015072164834[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7163430015072164834[53] = -9.8000000000000007*dt;
   out_7163430015072164834[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7163430015072164834[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7163430015072164834[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7163430015072164834[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7163430015072164834[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7163430015072164834[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7163430015072164834[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7163430015072164834[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7163430015072164834[62] = 0;
   out_7163430015072164834[63] = 0;
   out_7163430015072164834[64] = 0;
   out_7163430015072164834[65] = 0;
   out_7163430015072164834[66] = 0;
   out_7163430015072164834[67] = 0;
   out_7163430015072164834[68] = 0;
   out_7163430015072164834[69] = 0;
   out_7163430015072164834[70] = 1;
   out_7163430015072164834[71] = 0;
   out_7163430015072164834[72] = 0;
   out_7163430015072164834[73] = 0;
   out_7163430015072164834[74] = 0;
   out_7163430015072164834[75] = 0;
   out_7163430015072164834[76] = 0;
   out_7163430015072164834[77] = 0;
   out_7163430015072164834[78] = 0;
   out_7163430015072164834[79] = 0;
   out_7163430015072164834[80] = 1;
}
void h_25(double *state, double *unused, double *out_8033080135131276877) {
   out_8033080135131276877[0] = state[6];
}
void H_25(double *state, double *unused, double *out_9162816601991055826) {
   out_9162816601991055826[0] = 0;
   out_9162816601991055826[1] = 0;
   out_9162816601991055826[2] = 0;
   out_9162816601991055826[3] = 0;
   out_9162816601991055826[4] = 0;
   out_9162816601991055826[5] = 0;
   out_9162816601991055826[6] = 1;
   out_9162816601991055826[7] = 0;
   out_9162816601991055826[8] = 0;
}
void h_24(double *state, double *unused, double *out_936076695566350707) {
   out_936076695566350707[0] = state[4];
   out_936076695566350707[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8887282167364636295) {
   out_8887282167364636295[0] = 0;
   out_8887282167364636295[1] = 0;
   out_8887282167364636295[2] = 0;
   out_8887282167364636295[3] = 0;
   out_8887282167364636295[4] = 1;
   out_8887282167364636295[5] = 0;
   out_8887282167364636295[6] = 0;
   out_8887282167364636295[7] = 0;
   out_8887282167364636295[8] = 0;
   out_8887282167364636295[9] = 0;
   out_8887282167364636295[10] = 0;
   out_8887282167364636295[11] = 0;
   out_8887282167364636295[12] = 0;
   out_8887282167364636295[13] = 0;
   out_8887282167364636295[14] = 1;
   out_8887282167364636295[15] = 0;
   out_8887282167364636295[16] = 0;
   out_8887282167364636295[17] = 0;
}
void h_30(double *state, double *unused, double *out_8308274197415782766) {
   out_8308274197415782766[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6644483643483807199) {
   out_6644483643483807199[0] = 0;
   out_6644483643483807199[1] = 0;
   out_6644483643483807199[2] = 0;
   out_6644483643483807199[3] = 0;
   out_6644483643483807199[4] = 1;
   out_6644483643483807199[5] = 0;
   out_6644483643483807199[6] = 0;
   out_6644483643483807199[7] = 0;
   out_6644483643483807199[8] = 0;
}
void h_26(double *state, double *unused, double *out_6604112144666956504) {
   out_6604112144666956504[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5542424152844439566) {
   out_5542424152844439566[0] = 0;
   out_5542424152844439566[1] = 0;
   out_5542424152844439566[2] = 0;
   out_5542424152844439566[3] = 0;
   out_5542424152844439566[4] = 0;
   out_5542424152844439566[5] = 0;
   out_5542424152844439566[6] = 0;
   out_5542424152844439566[7] = 1;
   out_5542424152844439566[8] = 0;
}
void h_27(double *state, double *unused, double *out_5411990670917429094) {
   out_5411990670917429094[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8819246955284232110) {
   out_8819246955284232110[0] = 0;
   out_8819246955284232110[1] = 0;
   out_8819246955284232110[2] = 0;
   out_8819246955284232110[3] = 1;
   out_8819246955284232110[4] = 0;
   out_8819246955284232110[5] = 0;
   out_8819246955284232110[6] = 0;
   out_8819246955284232110[7] = 0;
   out_8819246955284232110[8] = 0;
}
void h_29(double *state, double *unused, double *out_5136796608632923205) {
   out_5136796608632923205[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6134252299169415015) {
   out_6134252299169415015[0] = 0;
   out_6134252299169415015[1] = 1;
   out_6134252299169415015[2] = 0;
   out_6134252299169415015[3] = 0;
   out_6134252299169415015[4] = 0;
   out_6134252299169415015[5] = 0;
   out_6134252299169415015[6] = 0;
   out_6134252299169415015[7] = 0;
   out_6134252299169415015[8] = 0;
}
void h_28(double *state, double *unused, double *out_410317403256583449) {
   out_410317403256583449[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7230092757470606027) {
   out_7230092757470606027[0] = 1;
   out_7230092757470606027[1] = 0;
   out_7230092757470606027[2] = 0;
   out_7230092757470606027[3] = 0;
   out_7230092757470606027[4] = 0;
   out_7230092757470606027[5] = 0;
   out_7230092757470606027[6] = 0;
   out_7230092757470606027[7] = 0;
   out_7230092757470606027[8] = 0;
}
void h_31(double *state, double *unused, double *out_8963032545949391572) {
   out_8963032545949391572[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4916216050611088090) {
   out_4916216050611088090[0] = 0;
   out_4916216050611088090[1] = 0;
   out_4916216050611088090[2] = 0;
   out_4916216050611088090[3] = 0;
   out_4916216050611088090[4] = 0;
   out_4916216050611088090[5] = 0;
   out_4916216050611088090[6] = 0;
   out_4916216050611088090[7] = 0;
   out_4916216050611088090[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_6151971862348982707) {
  err_fun(nom_x, delta_x, out_6151971862348982707);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8906144065106568249) {
  inv_err_fun(nom_x, true_x, out_8906144065106568249);
}
void car_H_mod_fun(double *state, double *out_2245417875284688136) {
  H_mod_fun(state, out_2245417875284688136);
}
void car_f_fun(double *state, double dt, double *out_8850494657158538667) {
  f_fun(state,  dt, out_8850494657158538667);
}
void car_F_fun(double *state, double dt, double *out_7163430015072164834) {
  F_fun(state,  dt, out_7163430015072164834);
}
void car_h_25(double *state, double *unused, double *out_8033080135131276877) {
  h_25(state, unused, out_8033080135131276877);
}
void car_H_25(double *state, double *unused, double *out_9162816601991055826) {
  H_25(state, unused, out_9162816601991055826);
}
void car_h_24(double *state, double *unused, double *out_936076695566350707) {
  h_24(state, unused, out_936076695566350707);
}
void car_H_24(double *state, double *unused, double *out_8887282167364636295) {
  H_24(state, unused, out_8887282167364636295);
}
void car_h_30(double *state, double *unused, double *out_8308274197415782766) {
  h_30(state, unused, out_8308274197415782766);
}
void car_H_30(double *state, double *unused, double *out_6644483643483807199) {
  H_30(state, unused, out_6644483643483807199);
}
void car_h_26(double *state, double *unused, double *out_6604112144666956504) {
  h_26(state, unused, out_6604112144666956504);
}
void car_H_26(double *state, double *unused, double *out_5542424152844439566) {
  H_26(state, unused, out_5542424152844439566);
}
void car_h_27(double *state, double *unused, double *out_5411990670917429094) {
  h_27(state, unused, out_5411990670917429094);
}
void car_H_27(double *state, double *unused, double *out_8819246955284232110) {
  H_27(state, unused, out_8819246955284232110);
}
void car_h_29(double *state, double *unused, double *out_5136796608632923205) {
  h_29(state, unused, out_5136796608632923205);
}
void car_H_29(double *state, double *unused, double *out_6134252299169415015) {
  H_29(state, unused, out_6134252299169415015);
}
void car_h_28(double *state, double *unused, double *out_410317403256583449) {
  h_28(state, unused, out_410317403256583449);
}
void car_H_28(double *state, double *unused, double *out_7230092757470606027) {
  H_28(state, unused, out_7230092757470606027);
}
void car_h_31(double *state, double *unused, double *out_8963032545949391572) {
  h_31(state, unused, out_8963032545949391572);
}
void car_H_31(double *state, double *unused, double *out_4916216050611088090) {
  H_31(state, unused, out_4916216050611088090);
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
