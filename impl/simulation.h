/*
 * Header for the forward Euler simulation for the Furuta pendulum.
 *
 * The simulation implementation is based on a Ptolemy II
 * model constructed by Johan Eker and described in this paper:
 * J. Liu, J. Eker, J. W. Janneck, and E. A. Lee,
 * “Realistic simulations of embedded control systems,”
 * IFAC Proceedings Volumes, vol. 35, no. 1, pp. 391–396, 2002.
 *
 * Original implementation in C by Edward A. Lee, see:
 * https://github.com/lf-lang/examples-lingua-franca/tree/383e816627e2668330df3dfc08e7f4202461f42c/C/src/modal_models/FurutaPendulum
 *
 * @author Alexander Schulz-Rosengarten
 */

#ifndef SIMULATION_H
#define SIMULATION_H

 /** Transform the pendulum state into ots next position. */
void simulate(double s[4], double sample_period, double control_u);

#endif
