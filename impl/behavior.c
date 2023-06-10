/*
 * The general implementation of the pendulum control behavior.
 *
 * The control logic and configuration is based on a Ptolemy II 
 * model constructed by Johan Eker and described in this paper:
 * J. Liu, J. Eker, J. W. Janneck, and E. A. Lee,
 * “Realistic simulations of embedded control systems,”
 * IFAC Proceedings Volumes, vol. 35, no. 1, pp. 391–396, 2002.
 *
 * Original implementation in C by Edward A. Lee, see:
 * https://github.com/lf-lang/examples-lingua-franca/tree/383e816627e2668330df3dfc08e7f4202461f42c/C/src/modal_models/FurutaPendulum
 * 
 * @author Edward A. Lee
 * @author Alexander Schulz-Rosengarten
 */

#include "behavior.h"
#include <math.h>

/** Configuration of controller behavior. */
struct {
	double w0;
	double k, n, region1;
	double ci[4], phi2, max_speed;
	double si[4], region2;
} b_conf = {
		// Constants for
		// ... energy calculation
		.w0 = 6.3,
		// ... swing up
		.k = 0.5,		// Energy multiplier to swing up.
		.n = 0.5,		// Bound on swing up control magnitude.
		.region1 = 0.1, // Angular region to exit SwingUp.
		// ... catch
		.ci = {-1.04945717118225, -0.20432286791216, -0.00735846749875, -0.00735846749875}, // Weighting of pendulum state
		.phi2 = -7.0124562, // Offset for weighting of phi
		.max_speed = 0.05, // Speed to exit Catch.
		// ... stabilize
		.si = {-1.70871686211144, -0.30395427746831, -0.03254225945714, -0.05808270221773}, // Weighting of pendulum state 
		.region2 = 0.2, // Angular region to exit Stabilize.
};

// Helper functions

/** Compute the sign (1, -1) for double values. */
double sign(double x) {
	return (x > 0.0) - (x < 0.0);
}

/** Normalize the angle relative to a 2 PI circle. */
double restrict_angle(double a) {
	return ((fmod(fabs(a) + PI, 2 * PI) - PI) * sign(a));
}

/** Compute the energy of the pendulum. */
double get_energy(double d_theta, double r_theta) {
	return 0.5 * d_theta * d_theta / (b_conf.w0 * b_conf.w0) + cos(r_theta) - 1.0;
}

// Control Behavior

/** Compute motor control in SwingUp mode. */
double swingup_control(double theta, double d_theta) {
	double r_theta = restrict_angle(theta);
	double e = get_energy(d_theta, r_theta);
	double c = sign(d_theta * cos(r_theta));
	return sign(e) * MIN(fabs(b_conf.k * e), b_conf.n) * c;
}

/** Determine whether to leave the SwingUp mode. */
char exit_swingup(double theta) {
	return fabs(theta) < b_conf.region1;
}

/** Compute motor control in Catch mode. */
double catch_control(double theta, double d_theta, double phi, double d_phi) {
	double r_theta = restrict_angle(theta);
	return -1.0 * (r_theta * b_conf.ci[0] + d_theta * b_conf.ci[1] + (phi - b_conf.phi2) * b_conf.ci[2] + d_phi * b_conf.ci[3]);
}

/** Determine whether to leave the Catch mode. */
char exit_catch(double d_phi) {
	return fabs(d_phi) < b_conf.max_speed;
}

/** Compute motor control in Stabilize mode. */
double stabilize_control(double theta, double d_theta, double phi, double d_phi, double catch_phi) {
	double r_theta = restrict_angle(theta);
	return -1.0 * (r_theta * b_conf.si[0] + d_theta * b_conf.si[1] + (phi - catch_phi) * b_conf.si[2] + d_phi * b_conf.si[3]);
}

/** Determine whether to leave the Stabilize mode. */
char exit_stabilize(double theta) {
	return fabs(restrict_angle(theta)) > b_conf.region2;
}

// Sound behavior

/** Compute sound frequency based on pendulum position. */
double sound_frequency(double angle) {
	// position 0-1 (0 is up, 1 is down)
	double pos = fabs(restrict_angle(angle)) / PI;
	// Pitches C to B -> 12 semitones
	int tone_idx = (1 - pos) * 12;
	// fn = f0 * (a)^n (C2: 65.41, C1: 32.7)
	double f = 65.41 * pow(pow(2, (1.0 / 12.0)), tone_idx);
	return f;
}
