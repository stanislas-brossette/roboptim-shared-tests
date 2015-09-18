﻿// Copyright (C) 2014 by Thomas Moulard, AIST, CNRS.
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
    namespace problem24
    {
      template <typename T>
      class F : public GenericDifferentiableFunction<T>
      {
      public:
	ROBOPTIM_DIFFERENTIABLE_FUNCTION_FWD_TYPEDEFS_
	(GenericDifferentiableFunction<T>);

	explicit F ();
	void
	impl_compute (result_ref result, const_argument_ref x) const;
	void
	impl_gradient (gradient_ref grad, const_argument_ref x, size_type)
	  const;
      };

      template <typename T>
      F<T>::F ()
	: GenericDifferentiableFunction<T>
	  (2, 1, "1/(27√3) ((x₀ - 3)² - 9) x₁³")
      {}

      template <typename T>
      void
      F<T>::impl_compute (result_ref result, const_argument_ref x)
	const
      {
	double alpha = 1. / (27 * std::sqrt (3));
	result[0] =
	  alpha
	  * (std::pow(x[0] - 3, 2) - 9)
	  * std::pow (x[1], 3);
      }

      template <>
      void
      F<EigenMatrixSparse>::impl_gradient
      (gradient_ref grad, const_argument_ref x, size_type)
	const
      {
	double alpha = 1. / (27 * std::sqrt (3));
	grad.coeffRef (0) =
	  2 * alpha * (x[0] - 3) * std::pow (x[1], 3);
	grad.coeffRef (1) =
	  3. * alpha * (std::pow(x[0] - 3, 2) - 9) * std::pow (x[1], 2);
      }

      template <typename T>
      void
      F<T>::impl_gradient (gradient_ref grad, const_argument_ref x, size_type)
	const
      {
	double alpha = 1. / (27 * std::sqrt (3));
	grad[0] =
	  2 * alpha * (x[0] - 3) * std::pow (x[1], 3);
	grad[1] =
	  3. * alpha * (std::pow(x[0] - 3, 2) - 9) * std::pow (x[1], 2);
      }

      template <typename T>
      class G : public GenericDifferentiableFunction<T>
      {
      public:
	ROBOPTIM_DIFFERENTIABLE_FUNCTION_FWD_TYPEDEFS_
	(GenericDifferentiableFunction<T>);

	explicit G ();
	void
	impl_compute (result_ref result, const_argument_ref x) const;
	void
	impl_gradient (gradient_ref grad, const_argument_ref x, size_type)
	  const;
      };

      template <typename T>
      G<T>::G ()
	: GenericDifferentiableFunction<T>
	  (2, 1, "x₀/√3 - x₁")
      {}

      template <typename T>
      void
      G<T>::impl_compute (result_ref result, const_argument_ref x)
	const
      {
	result[0] = x[0] / std::sqrt (3.) - x[1];
      }

      template <>
      void
      G<EigenMatrixSparse>::impl_gradient
      (gradient_ref grad, const_argument_ref, size_type)
	const
      {
	grad.coeffRef (0) = 1. / std::sqrt (3);
	grad.coeffRef (1) = -1.;
      }

      template <typename T>
      void
      G<T>::impl_gradient (gradient_ref grad, const_argument_ref, size_type)
	const
      {
	grad[0] = 1. / std::sqrt (3.);
	grad[1] = -1.;
      }

      template <typename T>
      class G2 : public GenericDifferentiableFunction<T>
      {
      public:
	ROBOPTIM_DIFFERENTIABLE_FUNCTION_FWD_TYPEDEFS_
	(GenericDifferentiableFunction<T>);

	explicit G2 ();
	void
	impl_compute (result_ref result, const_argument_ref x) const;
	void
	impl_gradient (gradient_ref grad, const_argument_ref x, size_type)
	  const;
      };

      template <typename T>
      G2<T>::G2 ()
	: GenericDifferentiableFunction<T>
	  (2, 1, "x₀ + √3 x₁")
      {}

      template <typename T>
      void
      G2<T>::impl_compute (result_ref result, const_argument_ref x)
	const
      {
	result[0] = x[0] + std::sqrt (3.) * x[1];
      }

      template <>
      void
      G2<EigenMatrixSparse>::impl_gradient
      (gradient_ref grad, const_argument_ref, size_type)
	const
      {
	grad.coeffRef (0) = 1.;
	grad.coeffRef (1) = std::sqrt (3);
      }

      template <typename T>
      void
      G2<T>::impl_gradient (gradient_ref grad, const_argument_ref, size_type)
	const
      {
	grad[0] = 1.;
	grad[1] = std::sqrt (3);
      }

      template <typename T>
      class G3 : public GenericDifferentiableFunction<T>
      {
      public:
	ROBOPTIM_DIFFERENTIABLE_FUNCTION_FWD_TYPEDEFS_
	(GenericDifferentiableFunction<T>);

	explicit G3 ();
	void
	impl_compute (result_ref result, const_argument_ref x) const;
	void
	impl_gradient (gradient_ref grad, const_argument_ref x, size_type)
	  const;
      };

      template <typename T>
      G3<T>::G3 ()
	: GenericDifferentiableFunction<T>
	  (2, 1, "-x₀ - √3 x₁ + 6")
      {}

      template <typename T>
      void
      G3<T>::impl_compute (result_ref result, const_argument_ref x)
	const
      {
	result[0] = -x[0] - std::sqrt (3.) * x[1] + 6;
      }

      template <>
      void
      G3<EigenMatrixSparse>::impl_gradient
      (gradient_ref grad, const_argument_ref, size_type)
	const
      {
	grad.coeffRef (0) = -1.;
	grad.coeffRef (1) = -std::sqrt (3);
      }

      template <typename T>
      void
      G3<T>::impl_gradient (gradient_ref grad, const_argument_ref, size_type)
	const
      {
	grad[0] = -1.;
	grad[1] = -std::sqrt (3);
      }

    } // end of namespace problem24.
  } // end of namespace schittkowski.
} // end of namespace roboptim.

BOOST_FIXTURE_TEST_SUITE (schittkowski, TestSuiteConfiguration)

BOOST_AUTO_TEST_CASE (schittkowski_problem24)
{
  using namespace roboptim;
  using namespace roboptim::schittkowski::problem24;

  // Tolerances for Boost checks.
  double f0_tol = 1e-4;
  double x_tol = 1e-4;
  double f_tol = 1e-4;

  ExpectedResult expectedResult;
  expectedResult.f0 = -0.013364589564574673;
  expectedResult.x = (ExpectedResult::argument_t (2) << 3., std::sqrt (3)).finished ();
  expectedResult.fx = -1.;

  // Build problem.
  boost::shared_ptr<F<functionType_t> > f (new F<functionType_t> ());
  solver_t::problem_t problem (f);

  problem.argumentBounds ()[0] = F<functionType_t>::makeLowerInterval (0.);
  problem.argumentBounds ()[1] = F<functionType_t>::makeLowerInterval (0.);

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
  x << 1., 0.5;
  problem.startingPoint () = x;

  BOOST_CHECK_SMALL_OR_CLOSE ((*f) (x)[0], expectedResult.f0, f0_tol);

  std::cout << f->inputSize () << std::endl;
  std::cout << problem.function ().inputSize () << std::endl;

  // Initialize solver.
  SolverFactory<solver_t> factory (SOLVER_NAME, problem);
  solver_t& solver = factory ();
  // Set optimization logger
  SET_OPTIMIZATION_LOGGER (solver, "schittkowski/problem-24");

  // Set optional log file for debugging
  SET_LOG_FILE(solver);

  std::cout << f->inputSize () << std::endl;
  std::cout << problem.function ().inputSize () << std::endl;

  // Compute the minimum and retrieve the result.
  solver_t::result_t res = solver.minimum ();

  std::cout << f->inputSize () << std::endl;
  std::cout << problem.function ().inputSize () << std::endl;

  // Display solver information.
  std::cout << solver << std::endl;

  // Process the result
  PROCESS_RESULT();
}

BOOST_AUTO_TEST_SUITE_END ()
