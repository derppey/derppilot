#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_752852575942216847);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1438979586232603189);
void pose_H_mod_fun(double *state, double *out_7614955989455419172);
void pose_f_fun(double *state, double dt, double *out_5899861132242380131);
void pose_F_fun(double *state, double dt, double *out_4403213144206436728);
void pose_h_4(double *state, double *unused, double *out_8489697203254357767);
void pose_H_4(double *state, double *unused, double *out_5679269699215051709);
void pose_h_10(double *state, double *unused, double *out_5978013585373209228);
void pose_H_10(double *state, double *unused, double *out_7613399179514016916);
void pose_h_13(double *state, double *unused, double *out_1921649809916094897);
void pose_H_13(double *state, double *unused, double *out_2466995873882718908);
void pose_h_14(double *state, double *unused, double *out_125818232234200489);
void pose_H_14(double *state, double *unused, double *out_1716028842875567180);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}