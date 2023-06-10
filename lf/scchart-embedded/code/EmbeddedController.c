/*
 * Automatically generated C code by
 * KIELER SCCharts - The Key to Efficient Modeling
 *
 * http://rtsys.informatik.uni-kiel.de/kieler
 */

#include "behavior.h"

#include "EmbeddedController.h"

void logic(TickData* d) {
  d->_g66 = d->_pg57;
  if (d->_g66) {
    d->_EmbeddedController_local__deferred_initial = 0;
  }
  d->_g68 = d->_pg55;
  d->_g66 = d->_GO || d->_g66 || d->_g68;
  if (d->_g66) {
    d->control = swingup_control(d->theta, d->d_theta);
  }
  d->_g68 = d->_pg63;
  if (d->_g68) {
    d->_EmbeddedController_local__deferred_initial = 0;
  }
  d->_cg3 = !d->_EmbeddedController_local__deferred_initial && exit_swingup(d->theta);
  d->_g4 = d->_g66 && d->_cg3;
  if (d->_g4) {
    d->led = 1;
    d->_EmbeddedController_local__Atrig = 0;
    d->_EmbeddedController_local_c = 0;
    d->_EmbeddedController_local_tick = 0;
    d->_EmbeddedController_local__Atrig1 = 0;
  }
  d->_g53 = d->_pg8_e1;
  d->_cg53 = exit_catch(d->d_phi);
  d->_g54 = d->_g53 && d->_cg53;
  if (d->_g54) {
    d->_EmbeddedController_local__Atrig = 1;
  }
  d->_g43 = d->_pg43;
  d->_cg43 = d->_EmbeddedController_local__Atrig;
  d->_g44 = d->_g43 && d->_cg43;
  if (d->_g44) {
    d->_EmbeddedController_local__Atrig1 = 1;
  }
  d->_g40 = d->_pg37;
  if (d->_g40) {
    d->_EmbeddedController_local_c += d->deltaT;
  }
  d->_g23 = d->_pg24;
  d->_g17 = d->_pg15;
  d->_g20_e1 = !(d->_g23 || d->_g17);
  d->_g27 = d->_pg21;
  d->_cg27 = d->_EmbeddedController_local_c >= MSEC(15);
  d->_g28 = d->_g27 && d->_cg27;
  if (d->_g28) {
    d->_EmbeddedController_local__Atrig2 = 1;
  }
  d->_g30 = d->_g27 && !d->_cg27;
  if (d->_g30) {
    d->_EmbeddedController_local__Atrig3 = 1;
  }
  d->sleepT = SEC(1);
  d->_g23 = d->_g17 || d->_g23;
  d->_cg18 = d->_EmbeddedController_local_c < MSEC(15);
  d->_g17 = d->_g23 && d->_cg18;
  if (d->_g17) {
    d->sleepT = (d->sleepT < (MSEC(15) - d->_EmbeddedController_local_c)) ? d->sleepT : (MSEC(15) - d->_EmbeddedController_local_c);
  }
  d->_cg19 = d->_EmbeddedController_local__Atrig2 || d->_EmbeddedController_local__Atrig3 || d->_EmbeddedController_local__Atrig1;
  d->_g18 = d->_g23 && !d->_cg18;
  d->_cg21 = d->_EmbeddedController_local__Atrig2 || d->_EmbeddedController_local__Atrig3 || d->_EmbeddedController_local__Atrig1;
  d->_g20 = (d->_g17 && d->_cg19) || (d->_g18 && d->_cg21);
  d->_g27 = !d->_g27;
  d->_g30 = d->_g28 || d->_g30;
  d->_g28 = (d->_g20_e1 || d->_g20) && (d->_g27 || d->_g30) && (d->_g20 || d->_g30);
  d->_cg31 = d->_EmbeddedController_local__Atrig2;
  d->_g20 = d->_g28 && d->_cg31;
  if (d->_g20) {
    d->_EmbeddedController_local_c -= MSEC(15);
    d->_EmbeddedController_local_tick = 1;
  }
  d->_g29_e2 = d->_g28 && !d->_cg31;
  d->_cg33 = d->_EmbeddedController_local__Atrig3;
  d->_g29 = d->_g29_e2 && d->_cg33;
  if (d->_g29) {
    d->_EmbeddedController_local_tick = 0;
  }
  d->_g20_e1 = d->_pg7;
  d->_cg10 = d->_EmbeddedController_local_tick;
  d->_g31 = d->_g20_e1 && d->_cg10;
  if (d->_g31) {
    d->led = !d->led;
  }
  d->_g11 = d->_g4 || d->_g31 || (d->_g20_e1 && !d->_cg10);
  d->_cg7 = d->_EmbeddedController_local__Atrig1;
  d->_g10 = d->_g11 && d->_cg7;
  d->_g7 = d->_g11 && !d->_cg7;
  d->_g34 = d->_g4 || d->_g20 || d->_g29;
  if (d->_g34) {
    d->_EmbeddedController_local__Atrig2 = 0;
    d->_EmbeddedController_local__Atrig3 = 0;
  }
  d->_cg14 = d->_EmbeddedController_local_c < MSEC(15);
  d->_g32 = d->_g34 && d->_cg14;
  if (d->_g32) {
    d->sleepT = (d->sleepT < (MSEC(15) - d->_EmbeddedController_local_c)) ? d->sleepT : (MSEC(15) - d->_EmbeddedController_local_c);
  }
  d->_cg15 = d->_EmbeddedController_local__Atrig2 || d->_EmbeddedController_local__Atrig3 || d->_EmbeddedController_local__Atrig1;
  d->_g15 = (d->_g32 && !d->_cg15) || (d->_g17 && !d->_cg19);
  d->_g19 = d->_g34 && !d->_cg14;
  d->_cg24 = d->_EmbeddedController_local__Atrig2 || d->_EmbeddedController_local__Atrig3 || d->_EmbeddedController_local__Atrig1;
  d->_g24 = (d->_g18 && !d->_cg21) || (d->_g19 && !d->_cg24);
  d->_cg25 = d->_EmbeddedController_local__Atrig1;
  d->_g21 = d->_g34 && !d->_cg25;
  d->_g13 = d->_g29_e2 && !d->_cg33;
  d->_g33 = d->_g4 || d->_g40;
  d->_cg37 = d->_EmbeddedController_local__Atrig1;
  d->_g40 = d->_g33 && d->_cg37;
  d->_g37 = d->_g33 && !d->_cg37;
  d->_g43 = d->_g4 || (d->_g43 && !d->_cg43);
  d->_g8_e1 = !d->_g7;
  d->_g35_e2 = !(d->_g21 || d->_g24 || d->_g15);
  d->_g38_e3 = !d->_g37;
  d->_g44_e4 = !d->_g43;
  d->_g8 = (d->_g8_e1 || d->_g10) && (d->_g35_e2 || d->_g13) && (d->_g38_e3 || d->_g40) && (d->_g44_e4 || d->_g44) && (d->_g10 || d->_g13 || d->_g40 || d->_g44);
  d->_g38 = d->_pg35_e2;
  if (d->_g38) {
    d->control = catch_control(d->theta, d->d_theta, d->phi, d->d_phi);
  }
  d->_g44 = d->_g4 || d->_g38;
  d->_cg47 = d->_EmbeddedController_local__Atrig;
  d->_g35 = d->_g44 && d->_cg47;
  d->_g35_e2 = d->_g44 && !d->_cg47;
  d->_g8_e1 = d->_g4 || (d->_g53 && !d->_cg53);
  d->_g38_e3 = !(d->_g43 || d->_g7 || d->_g37 || d->_g21 || d->_g24 || d->_g15);
  d->_g44_e4 = !d->_g35_e2;
  d->_g50 = !d->_g8_e1;
  d->_g47 = (d->_g38_e3 || d->_g8) && (d->_g44_e4 || d->_g35) && (d->_g50 || d->_g54) && (d->_g8 || d->_g35 || d->_g54);
  if (d->_g47) {
    d->_EmbeddedController_local_catch_phi = d->phi;
    d->led = 1;
    d->_EmbeddedController_local__Atrig4 = 0;
  }
  d->_g4 = d->_pg45_e1;
  d->_cg63 = exit_stabilize(d->theta);
  d->_g53 = d->_g4 && d->_cg63;
  if (d->_g53) {
    d->_EmbeddedController_local__Atrig4 = 1;
  }
  d->_g48 = d->_pg54;
  if (d->_g48) {
    d->control = stabilize_control(d->theta, d->d_theta, d->phi, d->d_phi, d->_EmbeddedController_local_catch_phi);
  }
  d->_g54_e3 = d->_g47 || d->_g48;
  d->_cg57 = d->_EmbeddedController_local__Atrig4;
  d->_g48_e2 = d->_g54_e3 && d->_cg57;
  d->_g54 = d->_g54_e3 && !d->_cg57;
  d->_g45_e1 = d->_g47 || (d->_g4 && !d->_cg63);
  d->_g45 = !d->_g54;
  d->_g60 = !d->_g45_e1;
  d->_g57 = (d->_g45 || d->_g48_e2) && (d->_g60 || d->_g53) && (d->_g48_e2 || d->_g53);
  if (d->_g57) {
    d->led = 0;
  }
  d->_g55 = d->_g66 && !d->_cg3;
  d->_g63 = d->_GO || d->_g68;
  if (d->_GO) {
    d->_EmbeddedController_local_clk = 0;
    d->_EmbeddedController_local_duration = 0;
    d->sound = 1;
  }
  d->_g58_e1 = d->_pg91;
  if (d->_g58_e1) {
    d->_EmbeddedController_local_clk += d->deltaT;
  }
  d->_g64 = d->_pg86;
  d->_g64_e2 = d->_pg95_e2;
  d->_g58 = !(d->_g64 || d->_g64_e2);
  d->_g3 = d->_pg72;
  d->_g72 = d->_GO || d->_g3;
  if (d->_g72) {
    d->_EmbeddedController_local_duration = SEC(((1 / sound_frequency(d->theta)) / 2));
  }
  d->_g100 = d->_pg82;
  d->_cg94 = d->_EmbeddedController_local_clk >= d->_EmbeddedController_local_duration;
  d->_g95 = d->_g100 && d->_cg94;
  if (d->_g95) {
    d->_EmbeddedController_local__Atrig5 = 1;
  }
  d->_g84 = d->_g64_e2 || d->_g64;
  d->_cg85 = d->_EmbeddedController_local_clk < d->_EmbeddedController_local_duration;
  d->_g90 = d->_g84 && d->_cg85;
  if (d->_g90) {
    d->sleepT = (d->sleepT < (d->_EmbeddedController_local_duration - d->_EmbeddedController_local_clk)) ? d->sleepT : (d->_EmbeddedController_local_duration - d->_EmbeddedController_local_clk);
  }
  d->_cg86 = d->_EmbeddedController_local__Atrig5;
  d->_g85 = d->_g84 && !d->_cg85;
  d->_cg88 = d->_EmbeddedController_local__Atrig5;
  d->_g87 = (d->_g90 && d->_cg86) || (d->_g85 && d->_cg88);
  d->_g95_e2 = !d->_g100;
  d->_g95 = (d->_g58 || d->_g87) && (d->_g95_e2 || d->_g95) && (d->_g87 || d->_g95);
  if (d->_g95) {
    d->sound = !d->sound;
    d->_EmbeddedController_local_clk = 0;
  }
  d->_g87 = d->_GO || d->_g95;
  if (d->_g87) {
    d->_EmbeddedController_local__Atrig5 = 0;
  }
  d->_cg81 = d->_EmbeddedController_local_clk < d->_EmbeddedController_local_duration;
  d->_g87_e1 = d->_g87 && d->_cg81;
  if (d->_g87_e1) {
    d->sleepT = (d->sleepT < (d->_EmbeddedController_local_duration - d->_EmbeddedController_local_clk)) ? d->sleepT : (d->_EmbeddedController_local_duration - d->_EmbeddedController_local_clk);
  }
  d->_cg82 = d->_EmbeddedController_local__Atrig5;
  d->_g95_e2 = (d->_g87_e1 && !d->_cg82) || (d->_g90 && !d->_cg86);
  d->_g96 = d->_g87 && !d->_cg81;
  d->_cg91 = d->_EmbeddedController_local__Atrig5;
  d->_g86 = (d->_g85 && !d->_cg88) || (d->_g96 && !d->_cg91);
  d->_g82 = d->_g87 || (d->_g100 && !d->_cg94);
  d->_g91 = d->_GO || d->_g58_e1;
  d->_cg115 = d->_EmbeddedController_local__Atrig1;
}

void reset(TickData* d) {
  d->_GO = 1;
  d->_TERM = 0;
  d->control = 0;
  d->led = 0;
  d->sound = 1;
  d->deltaT = 0;
  d->sleepT = 0;
  d->_EmbeddedController_local_catch_phi = 0;
  d->_EmbeddedController_local__deferred_initial = 1;
  d->control = 0;
  d->led = 0;
  d->_pg57 = 0;
  d->_pg55 = 0;
  d->_pg63 = 0;
  d->_pg8_e1 = 0;
  d->_pg43 = 0;
  d->_pg37 = 0;
  d->_pg24 = 0;
  d->_pg15 = 0;
  d->_pg21 = 0;
  d->_pg7 = 0;
  d->_pg35_e2 = 0;
  d->_pg45_e1 = 0;
  d->_pg54 = 0;
  d->_pg91 = 0;
  d->_pg86 = 0;
  d->_pg95_e2 = 0;
  d->_pg72 = 0;
  d->_pg82 = 0;
}

void tick(TickData* d) {
  logic(d);

  d->_pg57 = d->_g57;
  d->_pg55 = d->_g55;
  d->_pg63 = d->_g63;
  d->_pg8_e1 = d->_g8_e1;
  d->_pg43 = d->_g43;
  d->_pg37 = d->_g37;
  d->_pg24 = d->_g24;
  d->_pg15 = d->_g15;
  d->_pg21 = d->_g21;
  d->_pg7 = d->_g7;
  d->_pg35_e2 = d->_g35_e2;
  d->_pg45_e1 = d->_g45_e1;
  d->_pg54 = d->_g54;
  d->_pg91 = d->_g91;
  d->_pg86 = d->_g86;
  d->_pg95_e2 = d->_g95_e2;
  d->_pg72 = d->_g72;
  d->_pg82 = d->_g82;
  d->_GO = 0;
}
