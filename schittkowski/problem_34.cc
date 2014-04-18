// Copyright (C) 2014 by Thomas Moulard, AIST, CNRS.
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
    namespace problem34
    {
      struct ExpectedResult
      {
	static const double f0;
	static const double x[];
	static const double fx;
      };
      const double ExpectedResult::f0 = 0.;
      const double ExpectedResult::x[] = {
	std::log (std::log (10.)),
	std::log (10.),
	10.
      };
      const double ExpectedResult::fx = -std::log (std::log (10.));

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
	  (3, 1, "-x₀")
      {}

      template <typename T>
      void
      F<T>::impl_compute (result_ref result, const_argument_ref& x)
	const throw ()
      {
	result[0] = -x[0];
      }

      template <>
      void
      F<EigenMatrixSparse>::impl_gradient
      (gradient_ref grad, const_argument_ref&, size_type)
	const throw ()
      {
	grad.insert (0) = -1.;
	grad.insert (1) = 0.;
	grad.insert (2) = 0.;
      }

      template <typename T>
      void
      F<T>::impl_gradient (gradient_ref grad, const_argument_ref&, size_type)
	const throw ()
      {
	grad[0] = -1.;
	grad[1] = 0.;
	grad[2] = 0.;
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
	impl_gradient (gradient_ref grad, const_argument_ref& x, size_type)
	  const throw ();
      };

      template <typename T>
      G<T>::G () throw ()
	: GenericDifferentiableFunction<T>
	  (3, 1, "x₁ - exp(x₀)")
      {}

      template <typename T>
      void
      G<T>::impl_compute (result_ref result, const_argument_ref& x)
	const throw ()
      {
	result[0] = x[1] - std::exp (x[0]);
      }

      template <>
      void
      G<EigenMatrixSparse>::impl_gradient
      (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad.insert (0) = -std::exp (x[0]);
	grad.insert (1) = 1.;
	grad.insert (2) = 0.;
      }

      template <typename T>
      void
      G<T>::impl_gradient (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad[0] = -std::exp (x[0]);
	grad[1] = 1.;
	grad[2] = 0.;
      }

      template <typename T>
      class G2 : public GenericDifferentiableFunction<T>
      {
      public:
	ROBOPTIM_DIFFERENTIABLE_FUNCTION_FWD_TYPEDEFS_
	(GenericDifferentiableFunction<T>);

	explicit G2 () throw ();
	void
	impl_compute (result_ref result, const_argument_ref& x) const throw ();
	void
	impl_gradient (gradient_ref grad, const_argument_ref& x, size_type)
	  const throw ();
      };

      template <typename T>
      G2<T>::G2 () throw ()
	: GenericDifferentiableFunction<T>
	  (3, 1, "x₂ - exp(x₁)")
      {}

      template <typename T>
      void
      G2<T>::impl_compute (result_ref result, const_argument_ref& x)
	const throw ()
      {
	result[0] = x[2] - std::exp (x[1]);
      }

      template <>
      void
      G2<EigenMatrixSparse>::impl_gradient
      (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad.insert (0) = 0.;
	grad.insert (1) = -std::exp (x[1]);
	grad.insert (2) = 1.;
      }

      template <typename T>
      void
      G2<T>::impl_gradient (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad[0] = 0.;
	grad[1] = -std::exp (x[1]);
	grad[2] = 1.;
      }
    } // end of namespace problem34.
  } // end of namespace schittkowski.
} // end of namespace roboptim.

BOOST_FIXTURE_TEST_SUITE (schittkowski, TestSuiteConfiguration)

BOOST_AUTO_TEST_CASE (schittkowski_problem34)
{
  using namespace roboptim;
  using namespace roboptim::schittkowski::problem34;

  // Tolerances for Boost checks.
  double f0_tol = 1e-4;
  double x_tol = 1e-4;
  double f_tol = 1e-4;

  // Build problem.
  F<functionType_t> f;
  solver_t::problem_t problem (f);

  problem.argumentBounds ()[0] = F<functionType_t>::makeInterval (0., 100.);
  problem.argumentBounds ()[1] = F<functionType_t>::makeInterval (0., 100.);
  problem.argumentBounds ()[2] = F<functionType_t>::makeInterval (0., 10.);

  boost::shared_ptr<G<functionType_t> > g =
    boost::make_shared<G<functionType_t> > ();
  problem.addConstraint (g, G<functionType_t>::makeLowerInterval (0.));
  boost::shared_ptr<G2<functionType_t> > g2 =
    boost::make_shared<G2<functionType_t> > ();
  problem.addConstraint (g2, G2<functionType_t>::makeLowerInterval (0.));

  F<functionType_t>::argument_t x (3);
  x << 0., 1.05, 2.9;
  problem.startingPoint () = x;

  BOOST_CHECK_SMALL_OR_CLOSE (f (x)[0], ExpectedResult::f0, f0_tol);

  std::cout << f.inputSize () << std::endl;
  std::cout << problem.function ().inputSize () << std::endl;

  // Initialize solver.
  SolverFactory<solver_t> factory (SOLVER_NAME, problem);
  solver_t& solver = factory ();
  OptimizationLogger<solver_t> logger
    (solver,
     "/tmp/roboptim-shared-tests/" SOLVER_NAME "/schittkowski/problem-34");

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
