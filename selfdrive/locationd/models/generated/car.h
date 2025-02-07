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
void car_err_fun(double *nom_x, double *delta_x, double *out_5979617889551613915);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2829649976459644767);
void car_H_mod_fun(double *state, double *out_3057922570853057598);
void car_f_fun(double *state, double dt, double *out_7312220419989483860);
void car_F_fun(double *state, double dt, double *out_1870503519340438721);
void car_h_25(double *state, double *unused, double *out_353806231527037977);
void car_H_25(double *state, double *unused, double *out_7961614396037722438);
void car_h_24(double *state, double *unused, double *out_7461992751078079557);
void car_H_24(double *state, double *unused, double *out_8806611004821417837);
void car_h_30(double *state, double *unused, double *out_1804437624155921144);
void car_H_30(double *state, double *unused, double *out_3568439336180212423);
void car_h_26(double *state, double *unused, double *out_1611835665493148872);
void car_H_26(double *state, double *unused, double *out_4220111077163666214);
void car_h_27(double *state, double *unused, double *out_4647867036133807668);
void car_H_27(double *state, double *unused, double *out_5743202647980637334);
void car_h_29(double *state, double *unused, double *out_3197235643504924501);
void car_H_29(double *state, double *unused, double *out_7456565374850188367);
void car_h_28(double *state, double *unused, double *out_8732459518857401225);
void car_H_28(double *state, double *unused, double *out_5907779681789832675);
void car_h_31(double *state, double *unused, double *out_6417028994823312959);
void car_H_31(double *state, double *unused, double *out_7992260357914682866);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}