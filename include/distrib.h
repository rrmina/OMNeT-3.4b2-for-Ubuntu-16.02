//==========================================================================
// DISTRIB.H
//
//                     OMNeT++/OMNEST
//            Discrete System Simulation in C++
//
// Random variate generation
//
// @author Werner Sandmann (ws), Kay Michael Masslow (kmm)
//
// @date 11/26/2002 "doxygenification" (kmm)
// @date 11/20/2002 some final comments (ws)
// @date 10/22/2002 implemented various discrete distributions (kmm)
//
//==========================================================================


#ifndef __DISTRIB_H_
#define __DISTRIB_H_

#include "defs.h"
#include "random.h"


/**
 * @name Continuous distributions
 *
 * @ingroup RandomNumbers
 */
//@{

/**
 * Returns a random variate with uniform distribution in the range [a,b).
 *
 * @param a, b the interval, a<b
 * @param rng the underlying random number generator
 */
SIM_API double uniform(double a, double b, int rng=0);

/**
 * Returns a random variate from the exponential distribution with the
 * given mean (that is, with parameter lambda=1/mean).
 *
 * @param mean mean value
 * @param rng the underlying random number generator
 */
SIM_API double exponential(double mean, int rng=0);

/**
 * Returns a random variate from the normal distribution with the given mean
 * and standard deviation.
 *
 * @param mean mean of the normal distribution
 * @param stddev standard deviation of the normal distribution
 * @param rng the underlying random number generator
 */
SIM_API double normal(double mean, double stddev, int rng=0);

/**
 * Normal distribution truncated to nonnegative values.
 * It is implemented with a loop that discards negative values until
 * a nonnegative one comes. This means that the execution time is not bounded:
 * a large negative mean with much smaller stddev is likely to result
 * in a large number of iterations.
 *
 * The mean and stddev parameters serve as parameters to the normal
 * distribution <i>before</i> truncation. The actual random variate returned
 * will have a different mean and standard deviation.
 *
 * @param mean mean of the normal distribution
 * @param stddev standard deviation of the normal distribution
 * @param rng the underlying random number generator
 */
SIM_API double truncnormal(double mean, double stddev, int rng=0);

/**
 * Returns a random variate from the gamma distribution with parameters
 * alpha>0, theta>0. Alpha is known as the "shape" parameter, and theta
 * as the "scale" parameter.
 *
 * Some sources in the literature use the inverse scale parameter
 * beta = 1 / theta, called the "rate" parameter. Various other notations
 * can be found in the literature; our usage of (alpha,theta) is consistent
 * with Wikipedia and Mathematica (Wolfram Research).
 *
 * Gamma is the generalization of the Erlang distribution for non-integer
 * k values, which becomes the alpha parameter. The chi-square distribution
 * is a special case of the gamma distribution.
 *
 * For alpha=1, Gamma becomes the exponential distribution with mean=theta.
 *
 * The mean of this distribution is alpha*theta, and variance is alpha*theta<sup>2</sup>.
 *
 * Generation: if alpha=1, it is generated as exponential(theta).
 *
 * For alpha>1, we make use of the acceptance-rejection method in
 * "A Simple Method for Generating Gamma Variables", George Marsaglia and
 * Wai Wan Tsang, ACM Transactions on Mathematical Software, Vol. 26, No. 3,
 * September 2000.
 *
 * The alpha<1 case makes use of the alpha>1 algorithm, as suggested by the
 * above paper.
 *
 * @remark the name gamma_d is chosen to avoid ambiguity with
 * a function of the same name
 *
 * @param alpha >0  the "shape" parameter
 * @param theta >0  the "scale" parameter
 * @param rng the underlying random number generator
 */
SIM_API double gamma_d(double alpha, double theta, int rng=0);

/**
 * Returns a random variate from the beta distribution with parameters
 * alpha1, alpha2.
 *
 * Generation is using relationship to Gamma distribution: if Y1 has gamma
 * distribution with alpha=alpha1 and beta=1 and Y2 has gamma distribution
 * with alpha=alpha2 and beta=2, then Y = Y1/(Y1+Y2) has beta distribution
 * with parameters alpha1 and alpha2.
 *
 * @param alpha1, alpha2 >0
 * @param rng the underlying random number generator
 */
SIM_API double beta(double alpha1, double alpha2, int rng=0);

/**
 * Returns a random variate from the Erlang distribution with k phases
 * and mean mean.
 *
 * This is the sum of k mutually independent random variables, each with
 * exponential distribution. Thus, the kth arrival time
 * in the Poisson process follows the Erlang distribution.
 *
 * Erlang with parameters m and k is gamma-distributed with alpha=k
 * and beta=m/k.
 *
 * Generation makes use of the fact that exponential distributions
 * sum up to Erlang.
 *
 * @param k number of phases, k>0
 * @param mean >0
 * @param rng the underlying random number generator
 */
SIM_API double erlang_k(unsigned int k, double mean, int rng=0);

/**
 * Returns a random variate from the chi-square distribution
 * with k degrees of freedom.  The chi-square distribution arises
 * in statistics. If Yi are k independent random variates from the normal
 * distribution with unit variance, then the sum-of-squares (sum(Yi^2))
 * has a chi-square distribution with k degrees of freedom.
 *
 * The expected value of this distribution is k. Chi_square with parameter
 * k is gamma-distributed with alpha=k/2, beta=2.
 *
 * Generation is using relationship to gamma distribution.
 *
 * @param k degrees of freedom, k>0
 * @param rng the underlying random number generator
 */
SIM_API double chi_square(unsigned int k, int rng=0);

/**
 * Returns a random variate from the student-t distribution with
 * i degrees of freedom. If Y1 has a normal distribution and Y2 has a chi-square
 * distribution with k degrees of freedom then X = Y1 / sqrt(Y2/k)
 * has a student-t distribution with k degrees of freedom.
 *
 * Generation is using relationship to gamma and chi-square.
 *
 * @param i degrees of freedom, i>0
 * @param rng the underlying random number generator
 */
SIM_API double student_t(unsigned int i, int rng=0);

/**
 * Returns a random variate from the Cauchy distribution (also called
 * Lorentzian distribution) with parameters a,b where b>0.
 *
 * This is a continuous distribution describing resonance behavior.
 * It also describes the distribution of horizontal distances at which
 * a line segment tilted at a random angle cuts the x-axis.
 *
 * Generation uses inverse transform.
 *
 * @param a
 * @param b  b>0
 * @param rng the underlying random number generator
 */
SIM_API double cauchy(double a, double b, int rng=0);

/**
 * Returns a random variate from the triangular distribution with parameters
 * a <= b <= c.
 *
 * Generation uses inverse transform.
 *
 * @param a, b, c   a <= b <= c
 * @param rng the underlying random number generator
 */
SIM_API double triang(double a, double b, double c, int rng=0);

/**
 * Returns a random variate from the lognormal distribution with "scale"
 * parameter m and "shape" parameter w. m and w correspond to the parameters
 * of the underlying normal distribution (m: mean, w: standard deviation.)
 *
 * Generation is using relationship to normal distribution.
 *
 * @param m  "scale" parameter, m>0
 * @param w  "shape" parameter, w>0
 * @param rng the underlying random number generator
 */
inline double lognormal(double m, double w, int rng=0)
{
    return exp(normal(m, w, rng));
}

/**
 * Returns a random variate from the Weibull distribution with parameters
 * a, b > 0, where a is the "scale" parameter and b is the "shape" parameter.
 * Sometimes Weibull is given with alpha and beta parameters, then alpha=b
 * and beta=a.
 *
 * The Weibull distribution gives the distribution of lifetimes of objects.
 * It was originally proposed to quantify fatigue data, but it is also used
 * in reliability analysis of systems involving a "weakest link," e.g.
 * in calculating a device's mean time to failure.
 *
 * When b=1, Weibull(a,b) is exponential with mean a.
 *
 * Generation uses inverse transform.
 *
 * @param a  the "scale" parameter, a>0
 * @param b  the "shape" parameter, b>0
 * @param rng the underlying random number generator
 */
SIM_API double weibull(double a, double b, int rng=0);

/**
 * Returns a random variate from the shifted generalized Pareto distribution.
 *
 * Generation uses inverse transform.
 *
 * @param a,b  the usual parameters for generalized Pareto
 * @param c    shift parameter for left-shift
 * @param rng the underlying random number generator
 */
SIM_API double pareto_shifted(double a, double b, double c, int rng=0);

//@}

/**
 * @name Discrete distributions
 *
 * @ingroup RandomNumbers
 */
//@{

/**
 * Returns a random integer with uniform distribution in the range [a,b],
 * inclusive. (Note that the function can also return b.)
 *
 * @param a, b  the interval, a<b
 * @param rng the underlying random number generator
 */
SIM_API int intuniform(int a, int b, int rng=0);

/**
 * Returns the result of a Bernoulli trial with probability p,
 * that is, 1 with probability p and 0 with probability (1-p).
 *
 * Generation is using elementary look-up.
 *
 * @param p  0=<p<=1
 * @param rng the underlying random number generator
 */
inline int bernoulli(double p, int rng=0)
{
    double U = genk_dblrand(rng);
    return (p > U) ? 1 : 0;
}

/**
 * Returns a random integer from the binomial distribution with
 * parameters n and p, that is, the number of successes in n independent
 * trials with probability p.
 *
 * Generation is using the relationship to Bernoulli distribution (runtime
 * is proportional to n).
 *
 * @param n n>=0
 * @param p 0<=p<=1
 * @param rng the underlying random number generator
 */
SIM_API int binomial(int n, double p, int rng=0);

/**
 * Returns a random integer from the geometric distribution with parameter p,
 * that is, the number of independent trials with probability p until the
 * first success.
 *
 * This is the n=1 special case of the negative binomial distribution.
 *
 * Generation uses inverse transform.
 *
 * @param p  0<p<=1
 * @param rng the underlying random number generator
 */
SIM_API int geometric(double p, int rng=0);

/**
 * Returns a random integer from the negative binomial distribution with
 * parameters n and p, that is, the number of failures occurring before
 * n successes in independent trials with probability p of success.
 *
 * Generation is using the relationship to geometric distribution (runtime is
 * proportional to n).
 *
 * @param n  n>=0
 * @param p  0<p<1
 * @param rng the underlying random number generator
 */
SIM_API int negbinomial(int n, double p, int rng=0);

//
// hypergeometric() doesn't work yet
//
// /**
//  * Returns a random integer from the hypergeometric distribution with
//  * parameters a,b and n.
//  *
//  * If you have a+b items (a items of type A and b items of type B)
//  * and you draw n items from them without replication, this function
//  * will return the number of type A items in the drawn set.
//  *
//  * Generation uses inverse transform due to Fishman (see Banks, page 165).
//  *
//  * @param a, b  a,b>0
//  * @param n     0<=n<=a+b
//  * @param rng the underlying random number generator
//  */
// SIM_API int hypergeometric(int a, int b, int n, int rng=0);

/**
 * Returns a random integer from the Poisson distribution with parameter lambda,
 * that is, the number of arrivals over unit time where the time between
 * successive arrivals follow exponential distribution with parameter lambda.
 *
 * Lambda is also the mean (and variance) of the distribution.
 *
 * Generation method depends on value of lambda:
 *
 *   - 0<lambda<=30: count number of events
 *   - lambda>30: Acceptance-Rejection due to Atkinson (see Banks, page 166)
 *
 * @param lambda  > 0
 * @param rng the underlying random number generator
 */
SIM_API int poisson(double lambda, int rng=0);

//@}

/**
 * @name Compatibility
 *
 * @ingroup RandomNumbers
 */
//@{
/**
 * DEPRECATED: use uniform() instead.
 */
SIM_API double genk_uniform(double gen_nr, double a, double b);

/**
 * DEPRECATED: use intuniform() instead.
 */
SIM_API double genk_intuniform(double gen_nr, double a, double b);

/**
 * DEPRECATED: use exponential() instead.
 */
SIM_API double genk_exponential(double gen_nr, double p);

/**
 * DEPRECATED: use normal() instead.
 */
SIM_API double genk_normal(double gen_nr, double mean, double variance);

/**
 * DEPRECATED: use truncnormal() instead.
 */
SIM_API double genk_truncnormal(double gen_nr, double mean, double variance);
//@}


#endif


