#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_6151971862348982707);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8906144065106568249);
void car_H_mod_fun(double *state, double *out_2245417875284688136);
void car_f_fun(double *state, double dt, double *out_8850494657158538667);
void car_F_fun(double *state, double dt, double *out_7163430015072164834);
void car_h_25(double *state, double *unused, double *out_8033080135131276877);
void car_H_25(double *state, double *unused, double *out_9162816601991055826);
void car_h_24(double *state, double *unused, double *out_936076695566350707);
void car_H_24(double *state, double *unused, double *out_8887282167364636295);
void car_h_30(double *state, double *unused, double *out_8308274197415782766);
void car_H_30(double *state, double *unused, double *out_6644483643483807199);
void car_h_26(double *state, double *unused, double *out_6604112144666956504);
void car_H_26(double *state, double *unused, double *out_5542424152844439566);
void car_h_27(double *state, double *unused, double *out_5411990670917429094);
void car_H_27(double *state, double *unused, double *out_8819246955284232110);
void car_h_29(double *state, double *unused, double *out_5136796608632923205);
void car_H_29(double *state, double *unused, double *out_6134252299169415015);
void car_h_28(double *state, double *unused, double *out_410317403256583449);
void car_H_28(double *state, double *unused, double *out_7230092757470606027);
void car_h_31(double *state, double *unused, double *out_8963032545949391572);
void car_H_31(double *state, double *unused, double *out_4916216050611088090);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}