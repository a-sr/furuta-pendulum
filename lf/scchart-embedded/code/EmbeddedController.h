#ifndef EMBEDDEDCONTROLLER_H
#define EMBEDDEDCONTROLLER_H
/*
 * Automatically generated C code by
 * KIELER SCCharts - The Key to Efficient Modeling
 *
 * http://rtsys.informatik.uni-kiel.de/kieler
 */


typedef struct {
  double theta;
  double d_theta;
  double phi;
  double d_phi;
  double angle;
  double control;
  char led;
  char sound;
  instant_t deltaT;
  instant_t sleepT;
  double _EmbeddedController_local_catch_phi;
  char _EmbeddedController_local__deferred_initial;
  char _EmbeddedController_local__Atrig;
  char _EmbeddedController_local__Atrig4;
  char _EmbeddedController_local__Atrig1;
  instant_t _EmbeddedController_local_c;
  char _EmbeddedController_local_tick;
  char _EmbeddedController_local__Atrig2;
  char _EmbeddedController_local__Atrig3;
  instant_t _EmbeddedController_local_clk;
  instant_t _EmbeddedController_local_duration;
  char _EmbeddedController_local__Atrig5;
  char _g3;
  char _g4;
  char _g7;
  char _g8;
  char _g10;
  char _g11;
  char _g13;
  char _g15;
  char _g17;
  char _g18;
  char _g19;
  char _g20;
  char _g21;
  char _g23;
  char _g24;
  char _g27;
  char _g28;
  char _g29;
  char _g30;
  char _g31;
  char _g32;
  char _g33;
  char _g34;
  char _g35;
  char _g37;
  char _g38;
  char _g40;
  char _g43;
  char _g44;
  char _g45;
  char _g47;
  char _g48;
  char _g50;
  char _g53;
  char _g54;
  char _g55;
  char _g57;
  char _g58;
  char _g60;
  char _g63;
  char _g64;
  char _g66;
  char _g68;
  char _g72;
  char _g82;
  char _g84;
  char _g85;
  char _g86;
  char _g87;
  char _g90;
  char _g91;
  char _g95;
  char _g96;
  char _g100;
  char _GO;
  char _cg3;
  char _cg10;
  char _cg7;
  char _cg14;
  char _cg15;
  char _cg19;
  char _cg18;
  char _cg21;
  char _cg24;
  char _cg25;
  char _cg115;
  char _cg27;
  char _cg31;
  char _cg33;
  char _cg37;
  char _cg43;
  char _cg47;
  char _cg53;
  char _cg57;
  char _cg63;
  char _cg81;
  char _cg82;
  char _cg86;
  char _cg85;
  char _cg88;
  char _cg91;
  char _cg94;
  char _g20_e1;
  char _g29_e2;
  char _g8_e1;
  char _g35_e2;
  char _g38_e3;
  char _g44_e4;
  char _g45_e1;
  char _g48_e2;
  char _g54_e3;
  char _g58_e1;
  char _g64_e2;
  char _g87_e1;
  char _g95_e2;
  char _TERM;
  char _pg57;
  char _pg55;
  char _pg63;
  char _pg8_e1;
  char _pg43;
  char _pg37;
  char _pg24;
  char _pg15;
  char _pg21;
  char _pg7;
  char _pg35_e2;
  char _pg45_e1;
  char _pg54;
  char _pg91;
  char _pg86;
  char _pg95_e2;
  char _pg72;
  char _pg82;
} TickData;

void reset(TickData* d);
void logic(TickData* d);
void tick(TickData* d);

#endif /* !EMBEDDEDCONTROLLER_H */