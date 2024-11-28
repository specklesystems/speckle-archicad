/****************************************************************************/
/*																			*/
/*					1D PeriodicInterval of doubles							*/
/* Namespaces:        Contact person:										*/
/*     Geometry          VT													*/
/****************************************************************************/


#if !defined (PERIODIC_INTERVAL_HPP)
#define PERIODIC_INTERVAL_HPP

#pragma once

#include "GeometricDefinitions.h"
#include "RealNumber.h"
#include "Vector3D.hpp"
#include "PagedArray.hpp"

 // swap function
template <class T>
void SWAP(T& a, T& b )
{ T tmp; tmp = a; a = b; b = tmp; }


#define OutsideInterval			0		/* ValueInInterval return values	*/
#define InsideInterval			1
#define OnIntervalBoundary	2

// *****************************************************************************
// A simple 1D interval with handling possible periodicity (e.i. 0-2PI , 0-endt)
// *****************************************************************************
namespace Geometry {

class GEOMETRY_DLL_EXPORT PeriodicInterval
{
	private:
		double  m_Lower;   // lower bound
		double  m_Upper;   // upper bound of the interval
		double  m_Periodicity; // interval Length if it is circular
	public:
		// constructor(s), destructor(s) -----------------------------------------
		PeriodicInterval (void);

		// constructor with 1D region
		PeriodicInterval (double in_Low, double in_High, double in_Periodicity = 0.0);

				// copy constructor
		PeriodicInterval (const PeriodicInterval& in_intval)
				{
					m_Lower					= in_intval.m_Lower;   // lower bound
					m_Upper					= in_intval.m_Upper;   // upper bound of the interval
					m_Periodicity	= in_intval.m_Periodicity; // interval Length if it is circular
				}

		// destructor
		~PeriodicInterval (void);

			bool operator == (const PeriodicInterval& in_intval) const;
			bool operator != (const PeriodicInterval& in_intval) const;

				// ------------------- member functions ----------------------------------
				// get the Start or End value of the interval
			double operator() (int in_Index) const
			{	return in_Index ? m_Upper : m_Lower;	}

			PeriodicInterval& operator= (const PeriodicInterval& in_intval)
				{
					m_Lower					= in_intval.m_Lower;   // lower bound
					m_Upper					= in_intval.m_Upper;   // upper bound of the interval
					m_Periodicity	= in_intval.m_Periodicity; // interval Length if it is circular
					return *this;
				}

				// get/set the start value of the interval
			double GetStart (void) const
			{	return m_Lower;	}
			void SetStart (double in_Value)
			{	m_Lower = in_Value;	}

				// get the End value of the interval
			double GetEnd (void) const
			{	return m_Upper;	}
			void SetEnd (double in_Value)
			{	m_Upper = in_Value;	}

				// gets the size of the interval
			double GetLength (void) const;

				// gets/set the full Length of a -circular-interval
			double GetPeriodicity (void) const
				{ return m_Periodicity; }
			void SetPeriodicity (double in_Periodicity_intval)
				{ m_Periodicity = in_Periodicity_intval; }

				// returns true if it is a circular interval
			bool IsPeriodic (void) const
				{	return (m_Periodicity == 0.0) ? false : true; }

				// checks if a parameter is in the given direction
			bool IsParamInDir (double in_base_par, bool in_dir,
															double in_t, double* out_length = nullptr );

				// merges a value into the interval
			bool MergeValue (double in_Value,
												double in_End_value = INF, double in_Mid_value = INF);

				// merges an interval to the interval
			bool MergeInterval (const PeriodicInterval& in_Intval);

				// interpolates an interval along an 0.0-1.0 range
			double Interpolate (double in_Value) const;

				// relative coordinate of a value(0-1)
			double GetRelativeValue (double in_Value) const;

				// steps on the interval with the given step
			double StepOnInterval (double in_Start_value, double in_Value,
															bool in_Clip = false) const;

				// returns the status of the input value with respect to the interval
			short ValueInInterval ( double in_value, double in_eps = EPS) const;

				// clips a value to the interval
			double ClipValue (double in_value) const;

				// splits the interval into maximum two (valid) segments
			int SplitInterval (double in_value, PeriodicInterval* out_intval_arr) const;

				// intersects two intervals and returns true if a common
				// region exists, false otherwise
			bool XIntervals (const PeriodicInterval& in_intval,
															PeriodicInterval& out_intval, double in_eps = 0.0) const;

			bool XIntervals (const PeriodicInterval& in_intval, double in_eps = 0.0) const;
};

}
#endif
