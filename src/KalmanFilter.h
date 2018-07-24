#ifndef KALMANFILTER_H
#define KALMANFILTER_H

template<typename T>
static inline constexpr T
Square(T a)
{
  return a * a;
}

class KalmanFilter {
  // The state we are tracking, namely:
  double x_abs_;  // The absolute quantity x.
  double x_vel_;  // The rate of change of x, in x units per second squared.

  // Covariance matrix for the state.
  double p_abs_abs_;
  double p_abs_vel_;
  double p_vel_vel_;

  // The variance of the acceleration noise input to the system model, in units
  // per second squared.
  double var_x_accel_;

 public:
  // Constructors: the first allows you to supply the variance of the
  // acceleration noise input to the system model in x units per second squared;
  // the second constructor assumes a variance of 1.0.
  KalmanFilter(double var_x_accel);
  KalmanFilter();

  // The following three methods reset the filter. All of them assign a huge
  // variance to the tracked absolute quantity and a var_x_accel_ variance to
  // its derivative, so the very next measurement will essentially be copied
  // directly into the filter. Still, we provide methods that allow you to
  // specify initial settings for the filter's tracked state.
  //
  // NOTE: "x_abs_value" is meant to connote the value of the absolute quantity
  // x, not the absolute value of x.
  void Reset();
  void Reset(double x_abs_value);
  void Reset(double x_abs_value, double x_vel_value);

  /**
   * Sets the variance of the acceleration noise input to the system model in
   * x units per second squared.
   */
  void SetAccelerationVariance(double var_x_accel) {
    var_x_accel_ = var_x_accel;
  }

  /**
   * Updates state given a direct sensor measurement of the absolute
   * quantity x, the variance of that measurement, and the interval
   * since the last measurement in seconds. This interval must be
   * greater than 0; for the first measurement after a Reset(), it's
   * safe to use 1.0.
   */
  void Update(double z_abs, double var_z_abs, double dt);

  // Getters for the state and its covariance.
  double GetXAbs() const { return x_abs_; }
  double GetXVel() const { return x_vel_; }
  double GetCovAbsAbs() const { return p_abs_abs_; }
  double GetCovAbsVel() const { return p_abs_vel_; }
  double GetCovVelVel() const { return p_vel_vel_; }
};


#endif // KALMANFILTER_H
