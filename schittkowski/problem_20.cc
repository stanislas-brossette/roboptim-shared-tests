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
    namespace problem20
    {
      struct ExpectedResult
      {
	static const double f0;
	static const double x[];
	static const double fx;
      };
      const double ExpectedResult::f0 = 909.;
      const double ExpectedResult::x[] = {0.5, 5. * std::sqrt (3)};
      const double ExpectedResult::fx = 81.5 - 25. * std::sqrt (3);

      // Same than problem_15
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
	  (2, 1, "100 (x₁ - x₀²)² + (1 - x₀)²")
      {}

      template <typename T>
      void
      F<T>::impl_compute (result_ref result, const_argument_ref& x)
	const throw ()
      {
	result[0] = 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0])
	  + (1 - x[0]) * (1 - x[0]);
      }

      template <>
      void
      F<EigenMatrixSparse>::impl_gradient
      (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad.insert (0) =
	  400. * x[0] * x[0] * x[0]
	  - 400. * x[0] * x[1] + 2 * x[0] - 2;
	grad.insert (1) = -200 * x[0] * x[0] + 200 * x[1];
      }

      template <typename T>
      void
      F<T>::impl_gradient (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad[0] =
	  400. * x[0] * x[0] * x[0]
	  - 400. * x[0] * x[1] + 2 * x[0] - 2;
	grad[1] = -200. * x[0] * x[0] + 200. * x[1];
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
	  (2, 1, "x₀ + x₁²")
      {}

      template <typename T>
      void
      G<T>::impl_compute (result_ref result, const_argument_ref& x)
	const throw ()
      {
	result[0] = x[0] + x[1] * x[1];
      }

      template <>
      void
      G<EigenMatrixSparse>::impl_gradient
      (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad.insert (0) = 1.;
	grad.insert (1) = 2 * x[1];
      }

      template <typename T>
      void
      G<T>::impl_gradient (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad[0] = 1.;
	grad[1] = 2 * x[1];
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
	  (2, 1, "x₀² + x₁")
      {}

      template <typename T>
      void
      G2<T>::impl_compute (result_ref result, const_argument_ref& x)
	const throw ()
      {
	result[0] = x[0] * x[0] + x[1];
      }

      template <>
      void
      G2<EigenMatrixSparse>::impl_gradient
      (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad.insert (0) = 2 * x[0];
	grad.insert (1) = 1.;
      }

      template <typename T>
      void
      G2<T>::impl_gradient (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad[0] = 2 * x[0];
	grad[1] = 1.;
      }


      template <typename T>
      class G3 : public GenericDifferentiableFunction<T>
      {
      public:
	ROBOPTIM_DIFFERENTIABLE_FUNCTION_FWD_TYPEDEFS_
	(GenericDifferentiableFunction<T>);

	explicit G3 () throw ();
	void
	impl_compute (result_ref result, const_argument_ref& x) const throw ();
	void
	impl_gradient (gradient_ref grad, const_argument_ref& x, size_type)
	  const throw ();
      };

      template <typename T>
      G3<T>::G3 () throw ()
	: GenericDifferentiableFunction<T>
	  (2, 1, "x₀² + x₁² - 1")
      {}

      template <typename T>
      void
      G3<T>::impl_compute (result_ref result, const_argument_ref& x)
	const throw ()
      {
	result[0] = x[0] * x[0] + x[1] * x[1] - 1.;
      }

      template <>
      void
      G3<EigenMatrixSparse>::impl_gradient
      (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad.insert (0) = 2. * x[0];
	grad.insert (1) = 2. * x[1];
      }

      template <typename T>
      void
      G3<T>::impl_gradient (gradient_ref grad, const_argument_ref& x, size_type)
	const throw ()
      {
	grad[0] = 2. * x[0];
	grad[1] = 2. * x[1];
      }
    } // end of namespace problem20.
  } // end of namespace schittkowski.
} // end of namespace roboptim.

BOOST_FIXTURE_TEST_SUITE (schittkowski, TestSuiteConfiguration)

BOOST_AUTO_TEST_CASE (schittkowski_problem20)
{
  using namespace roboptim;
  using namespace roboptim::schittkowski::problem20;

  // Tolerances for Boost checks.
  double f0_tol = 1e-4;
  double x_tol = 1e-4;
  double f_tol = 1e-4;

  // Build problem.
  F<functionType_t> f;
  solver_t::problem_t problem (f);

  problem.argumentBounds ()[0] = F<functionType_t>::makeInterval (-0.5, 0.5);

  boost::shared_ptr<G<functionType_t> > g =
    boost::make_shared<G<functionType_t> > ();
  problem.addConstraint (g, G<functionType_t>::makeLowerInterval (0.));
  boost::shared_ptr<G2<functionType_t> > g2 =
    boost::make_shared<G2<functionType_t> > ();
  problem.addConstraint (g2, G2<functionType_t>::makeLowerInterval (0.));
  boost::shared_ptr<G3<functionType_t> > g3 =
    boost::make_shared<G3<functionType_t> > ();
  problem.addConstraint (g3, G3<functionType_t>::makeLowerInterval (0.));

  F<functionType_t>::argument_t x (2);
  x << -2., 1.;
  problem.startingPoint () = x;

  BOOST_CHECK_SMALL_OR_CLOSE (f (x)[0], ExpectedResult::f0, f0_tol);

  std::cout << f.inputSize () << std::endl;
  std::cout << problem.function ().inputSize () << std::endl;

  // Initialize solver.
  SolverFactory<solver_t> factory (SOLVER_NAME, problem);
  solver_t& solver = factory ();
  OptimizationLogger<solver_t> logger
    (solver,
     "/tmp/roboptim-shared-tests/" SOLVER_NAME "/schittkowski/problem-20");

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
