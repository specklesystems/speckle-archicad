#ifndef ModelNurbsElementWithTolerance_h__
#define ModelNurbsElementWithTolerance_h__

#pragma once

namespace ModelerAPI
{
	class NurbsElementWithTolerance {
	protected:
		double tolerance;
	public:
		NurbsElementWithTolerance () : tolerance (0.0) {}
		NurbsElementWithTolerance (double tolerance) : tolerance (tolerance) {}
		double	GetTolerance () const { return tolerance; }
	};
} //namespace ModelerAPI
#endif // ModelNurbsElementWithTolerance_h__