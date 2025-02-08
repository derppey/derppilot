#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_7969550519276161680);
void live_err_fun(double *nom_x, double *delta_x, double *out_7907254071085750113);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_365236358483245292);
void live_H_mod_fun(double *state, double *out_420876630805809699);
void live_f_fun(double *state, double dt, double *out_5683589970036438935);
void live_F_fun(double *state, double dt, double *out_2670431034351452108);
void live_h_4(double *state, double *unused, double *out_3617510105830214052);
void live_H_4(double *state, double *unused, double *out_3082151370844455372);
void live_h_9(double *state, double *unused, double *out_9066218489933705973);
void live_H_9(double *state, double *unused, double *out_3323341017474046017);
void live_h_10(double *state, double *unused, double *out_4142473923945904347);
void live_H_10(double *state, double *unused, double *out_3959961515506139278);
void live_h_12(double *state, double *unused, double *out_3106668997606268487);
void live_H_12(double *state, double *unused, double *out_8101607778876417167);
void live_h_35(double *state, double *unused, double *out_4261201479720259317);
void live_H_35(double *state, double *unused, double *out_6448813428217062748);
void live_h_32(double *state, double *unused, double *out_145604149296379797);
void live_H_32(double *state, double *unused, double *out_9153837941118812685);
void live_h_13(double *state, double *unused, double *out_2678954050910694518);
void live_H_13(double *state, double *unused, double *out_7879707890760663499);
void live_h_14(double *state, double *unused, double *out_9066218489933705973);
void live_H_14(double *state, double *unused, double *out_3323341017474046017);
void live_h_33(double *state, double *unused, double *out_473323835959430866);
void live_H_33(double *state, double *unused, double *out_8847373640853631264);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}