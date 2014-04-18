// Copyright (C) 2014 by Benjamin Chretien, CNRS.
//
// This file is part of the roboptim.
//
// roboptim is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// roboptim is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with roboptim.  If not, see <http://www.gnu.org/licenses/>.

#include "common.hh"

namespace roboptim
{
  namespace schittkowski
  {
    namespace problem78
    {
      struct ExpectedResult
      {
	static const double f0;
	static const double x[];
	static const double fx;
      };

      const double ExpectedResult::f0 = -6.;
      const double ExpectedResult::x[] = {-1.717142, 1.595708, 1.827248,
                                          -0.7636429, -0.7636435};
      const double ExpectedResult::fx = -2.91970041;

      template <typename T>
      class F : public GenericDifferentiableFunction<T>
      {
      public:
	ROBOPTIM_DIFFERENTIABLE_FUNCTION_FWD_TYPEDEFS_
	(GenericDifferentiableFunction<T>);

	explicit F () throw ();
	void
	impl_compute (result_ref result, const_argument_ref& x) const throw ();
	void
	impl_gradient (gradient_ref grad, const_argument_ref& x, size_type)
	  const throw ();
      };

      template <typename T>
      F<T>::F () throw ()
	: GenericDifferentiableFunction<T>
	  (5, 1, "x₀x₁x₂x₃x₄")
      {}

      template <typename T>
      void
      F<T>::impl_compute (result_ref result, const_argument_ref& x)
	const throw ()
      {
	result[0] = x[0] * x[1] * x[2] * x[3] * x[4];
      }

      template <>
      void
      F<EigenMatrixSparse>::impl_gradient
      (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad.insert (0) = x[1] * x[2] * x[3] * x[4];
	grad.insert (1) = x[0] * x[2] * x[3] * x[4];
	grad.insert (2) = x[0] * x[1] * x[3] * x[4];
	grad.insert (3) = x[0] * x[1] * x[2] * x[4];
	grad.insert (4) = x[0] * x[1] * x[2] * x[3];
      }

      template <typename T>
      void
      F<T>::impl_gradient (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad (0) = x[1] * x[2] * x[3] * x[4];
	grad (1) = x[0] * x[2] * x[3] * x[4];
	grad (2) = x[0] * x[1] * x[3] * x[4];
	grad (3) = x[0] * x[1] * x[2] * x[4];
	grad (4) = x[0] * x[1] * x[2] * x[3];
      }

      template <typename T>
      class G : public GenericDifferentiableFunction<T>
      {
      public:
	ROBOPTIM_DIFFERENTIABLE_FUNCTION_FWD_TYPEDEFS_
	(GenericDifferentiableFunction<T>);

	explicit G () throw ();
	void
	impl_compute (result_ref result, const_argument_ref& x) const throw ();
	void
	impl_gradient (gradient_ref, const_argument_ref&, size_type)
	  const throw () {}
	void
	impl_jacobian (jacobian_ref jac, const_argument_ref& x)
	  const throw ();
      };

      template <typename T>
      G<T>::G () throw ()
	: GenericDifferentiableFunction<T>
	  (5, 3, "x₀² + x₁² + x₂² + x₃² + x₄² - 10, x₁x₂ - 5x₃x₄, x₀³ + x₁³ + 1")
      {}

      template <typename T>
      void
      G<T>::impl_compute (result_ref result, const_argument_ref& x)
	const throw ()
      {
	result[0] = x[0] * x[0] + x[1] * x[1] + x[2] * x[2]
	  + x[3] * x[3] + x[4] * x[4] - 10;
	result[1] = x[1] * x[2] - 5 * x[3] * x[4];
	result[2] = x[0] * x[0] * x[0] + x[1] * x[1] * x[1] + 1;
      }

      template <>
      void
      G<EigenMatrixSparse>::impl_jacobian
      (jacobian_ref jac, const_argument_ref& x) const throw ()
      {
	jac.insert (0,0) = 2 * x[0];
	jac.insert (0,1) = 2 * x[1];
	jac.insert (0,2) = 2 * x[2];
	jac.insert (0,3) = 2 * x[3];
	jac.insert (0,4) = 2 * x[4];

	jac.insert (1,1) = x[2];
	jac.insert (1,2) = x[1];
	jac.insert (1,3) = -5 * x[4];
	jac.insert (1,4) = -5 * x[3];

	jac.insert (2,0) = 3 * x[0] * x[0];
	jac.insert (2,1) = 3 * x[1] * x[1];
      }

      template <typename T>
      void
      G<T>::impl_jacobian
      (jacobian_ref jac, const_argument_ref& x) const throw ()
      {
	jac.setZero ();

	jac (0,0) = 2 * x[0];
	jac (0,1) = 2 * x[1];
	jac (0,2) = 2 * x[2];
	jac (0,3) = 2 * x[3];
	jac (0,4) = 2 * x[4];

	jac (1,1) = x[2];
	jac (1,2) = x[1];
	jac (1,3) = -5 * x[4];
	jac (1,4) = -5 * x[3];

	jac (2,0) = 3 * x[0] * x[0];
	jac (2,1) = 3 * x[1] * x[1];
      }
    } // end of namespace problem78.
  } // end of namespace schittkowski.
} // end of namespace roboptim.

BOOST_FIXTURE_TEST_SUITE (schittkowski, TestSuiteConfiguration)

BOOST_AUTO_TEST_CASE (schittkowski_problem78)
{
  using namespace roboptim;
  using namespace roboptim::schittkowski::problem78;

  // Tolerances for Boost checks.
  double f0_tol = 1e-4;
  double x_tol = 1e-4;
  double f_tol = 1e-4;

  // Build problem.
  F<functionType_t> f;
  solver_t::problem_t problem (f);

  boost::shared_ptr<G<functionType_t> > g =
    boost::make_shared<G<functionType_t> > ();

  solver_t::problem_t::intervals_t intervals;
  for (F<functionType_t>::size_type i = 0; i < g->outputSize (); ++i)
    intervals.push_back (G<functionType_t>::makeInterval (0., 0.));
  solver_t::problem_t::scales_t scales
    (static_cast<std::size_t> (g->outputSize ()), 1.);

  problem.addConstraint (g, intervals, scales);

  F<functionType_t>::argument_t x (f.inputSize ());
  x << -2, 1.5, 2, -1, -1;
  problem.startingPoint () = x;

  BOOST_CHECK_SMALL_OR_CLOSE (f (x)[0], ExpectedResult::f0, f0_tol);

  std::cout << f.inputSize () << std::endl;
  std::cout << problem.function ().inputSize () << std::endl;

  // Initialize solver.
  SolverFactory<solver_t> factory (SOLVER_NAME, problem);
  solver_t& solver = factory ();
  OptimizationLogger<solver_t> logger
    (solver,
     "/tmp/roboptim-shared-tests/" SOLVER_NAME "/schittkowski/problem-78");

  // Set optional log file for debugging
  SET_LOG_FILE(solver);

  std::cout << f.inputSize () << std::endl;
  std::cout << problem.function ().inputSize () << std::endl;

  // Compute the minimum and retrieve the result.
  solver_t::result_t res = solver.minimum ();

  std::cout << f.inputSize () << std::endl;
  std::cout << problem.function ().inputSize () << std::endl;

  // Display solver information.
  std::cout << solver << std::endl;

  // Process the result
  PROCESS_RESULT();
}

BOOST_AUTO_TEST_SUITE_END ()
