// *****************************************************************************
// Geometry, platform-independent
//
// Namespaces:    NLAlg   
// Contact person: AACs
// *****************************************************************************
#ifndef QNewton_hpp 
#define QNewton_hpp
#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------
#include "MatrixAndOp.hpp"

// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace NLAlg {

	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------
	class GEOMETRY_DLL_EXPORT QNewton //Quasi Newton optimization algorithm for unconstrained problems (minimalization of objective function). Gradient must be supplied. 
	{
	public: 
		class OptProblem {
		public: 
			OptProblem (USize nVars_init) : nVars (nVars_init) {} 
			virtual ~OptProblem ();

			virtual double Eval (const LinAlg::MatrixAndOp <double> & x, LinAlg::MatrixAndOp <double> * grd = nullptr) = 0; //eval of objective function, optionally gradient as well! 
			const USize nVars; 
		private:
		}; 

		class Options {
		public: 
			Options () {
				MinStepForBFGS = 0.001; 
				c1 = 1E-4; 
				c2 = 0.9;
				numTrial = 100;
				silent = true;
			}

			double MinStepForBFGS;

			//for line search:
			double c1; 
			double c2;
			USize numTrial; 

			//for debug:
			bool silent;
		};

		QNewton (OptProblem &optProb, const Options	& options); 
		virtual ~QNewton ();

		bool Solve (LinAlg::MatrixAndOp <double> & optVars); 

	private: 
		OptProblem & theProb; 
		const Options theOptions;
	};

} //namespace NLAlg 

#endif //QNewton_hpp
