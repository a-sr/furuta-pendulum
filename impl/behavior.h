/*
 * Header for  general implementation of the pendulum control behavior.
 *
 * The control logic and configuration is based on a Ptolemy II 
 * model constructed by Johan Eker and described in this paper:
 * J. Liu, J. Eker, J. W. Janneck, and E. A. Lee,
 * “Realistic simulations of embedded control systems,”
 * IFAC Proceedings Volumes, vol. 35, no. 1, pp. 391–396, 2002.
 *
 * @author Alexander Schulz-Rosengarten
 */

#ifndef BEHAVIOR_H
#define BEHAVIOR_H

// Helper functions

// Already defined if in LF context
#ifndef MIN 
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#endif
#ifndef MAX
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#endif

#define PI 3.14159265

/** Compute the sign (1, -1) for double values. */
double sign(double x);

/** Normalize the angle relative to a 2 PI circle. */
double restrict_angle(double a);

/** Compute the energy of the pendulum. */
double get_energy(double d_theta, double r_theta);

// Control Behavior

/** Compute motor control in SwingUp mode. */
double swingup_control(double theta, double d_theta);

/** Determine whether to leave the SwingUp mode. */
char exit_swingup(double theta);

/** Compute motor control in Catch mode. */
double catch_control(double theta, double d_theta, double phi, double d_phi);

/** Determine whether to leave the Catch mode. */
char exit_catch(double d_phi);

/** Compute motor control in Stabilize mode. */
double stabilize_control(double theta, double d_theta, double phi, double d_phi, double catch_phi);

/** Determine whether to leave the Stabilize mode. */
char exit_stabilize(double theta);

// Sound behavior

/** Compute sound frequency based on pendulum position. */
double sound_frequency(double angle);

#endif
