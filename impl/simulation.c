/*
 * A forward Euler simulation for the Furuta pendulum.
 *
 * The simulation implementation is based on a Ptolemy II 
 * model constructed by Johan Eker and described in this paper:
 * J. Liu, J. Eker, J. W. Janneck, and E. A. Lee,
 * “Realistic simulations of embedded control systems,”
 * IFAC Proceedings Volumes, vol. 35, no. 1, pp. 391–396, 2002.
 *
 * Original adaption to C by Edward A. Lee, see:
 * https://github.com/lf-lang/examples-lingua-franca/tree/383e816627e2668330df3dfc08e7f4202461f42c/C/src/modal_models/FurutaPendulum
 * 
 * @author Edward A. Lee
 * @author Alexander Schulz-Rosengarten
 */

#include "simulation.h"
#include <math.h>

// Helper function

// Already defined if in LF context
#ifndef MIN
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#endif

/** Configuration of simulation. */
struct {
	double g;
	double alpha, beta, gamma, epsilon;
} s_conf = {
    .g = 9.81, // Acceleration of gravity.
	.alpha = 0.00260569,
	.beta = 0.05165675,
	.gamma = 9.7055e-4,
	.epsilon = 0.08103060
};

/** Transform the pendulum state into ots next position. */
void simulate(double s[4], double sample_period, double control_u) {
	// Restrict control input
	double c = ((control_u > 0.0) - (control_u < 0.0)) * MIN(0.5, fabs(control_u));

    // Update the state.
    double s0_dot = s[1];
    double s1_dot = 1.0 / (
    		s_conf.alpha * s_conf.beta
            + pow(s_conf.alpha * sin(s[0]), 2.0)
            - pow(s_conf.gamma * cos(s[0]), 2.0)
        ) * (
            (
				s_conf.alpha
				* s_conf.beta
				+ pow(s_conf.alpha * sin(s[0]), 2.0)
			)
            * pow(s[3], 2.0)
            * sin(s[0])
            * cos(s[0])
        -
            pow(s_conf.gamma * s[1], 2.0)
            * sin(s[0])
            * cos(s[0])
        +
            2.0
            * s_conf.alpha
            * s_conf.gamma
            * s[1]
            * s[3]
            * sin(s[0])
            * pow(cos(s[0]), 2.0)
        -
			s_conf.gamma
            * cos(s[0])
            * s_conf.g
            * c
        +
            (
				s_conf.alpha
				* s_conf.beta
				+ pow(s_conf.alpha * sin(s[0]), 2.0)
			)
            * s_conf.epsilon
			/ s_conf.alpha
			* sin(s[0])
        );
    double s2_dot = s[3];
    double s3_dot = (1.0 / (
    		s_conf.alpha * s_conf.beta
            + pow(s_conf.alpha * sin(s[0]), 2.0)
            - pow(s_conf.gamma * cos(s[0]), 2.0)
        )) * (
            -s_conf.gamma
            * s_conf.alpha
            * pow(s[3], 2.0)
            * sin(s[0])
            * pow(cos(s[1]), 2.0)
        -
			s_conf.gamma
            * s_conf.epsilon
            * sin(s[0])
            * cos(s[0])
        +
			s_conf.gamma
            * s_conf.alpha
            * pow(s[1], 2.0)
            * sin(s[0])
        -
            2
            * pow(s_conf.alpha, 2.0)
            * s[1]
            * s[3]
            * sin(s[0])
            * cos(s[0])
        +
			s_conf.alpha
            * s_conf.g
            * c
        );

    double p = sample_period * 1e-9;
    // Update state
    s[0] += s0_dot * p;
    s[1] += s1_dot * p;
    s[2] += s2_dot * p;
    s[3] += s3_dot * p;
}
