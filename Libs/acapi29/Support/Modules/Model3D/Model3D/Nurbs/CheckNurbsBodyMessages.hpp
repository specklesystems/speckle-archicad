
#ifndef CHECKNURBSBODYMESSAGES_HPP
#define CHECKNURBSBODYMESSAGES_HPP

#define TRIMOVERLOADED			 70     /*Too many NURBS loops in NURBS trim %d in elem $ELEMNAME$.										*/
#define FACEOVERLOADED			 71     /*Too many NURBS shells in NURBS face %d in elem $ELEMNAME$.									*/
#define INVALIDVERTEXINDEXINEDGE 72     /*Wrong NURBS vertex index [%d] in NURBS edge %d in elem $ELEMNAME$.							*/
#define INVALIDVERTEXINDEXINTRIM 73     /*Wrong NURBS vertex index [%d] in NURBS trim %d in elem $ELEMNAME$.							*/
#define INVALIDEDGEINDEXINTRIM	 74     /*Wrong NURBS edge index [%d] in NURBS trim %d in elem $ELEMNAME$.								*/
#define INVALIDTRIMINDEXINLOOP	 75     /*Wrong NURBS trim index [%d] in NURBS face %d in elem $ELEMNAME$.								*/
#define INVALIDCURVE2DINDEX		 76     /*Wrong NURBS 2D curve index [%d] in NURBS trim %d in elem $ELEMNAME$.							*/
#define INVALIDCURVE3DINDEX		 77     /*Wrong NURBS 3D curve index [%d] in NURBS edge %d in elem $ELEMNAME$.							*/
#define INVALIDSURFACEINDEX		 78     /*Wrong NURBS surface index [%d] in NURBS face %d in elem $ELEMNAME$.							*/
#define INVALIDFACEINDEXINSHELL	 79		/*Wrong NURBS face index [%d] in NURBS shell in elem $ELEMNAME$.								*/
#define EMPTYTRIMLIST			 80     /*Empty NURBS trim list in a loop in NURBS face %d in elem $ELEMNAME$.							*/
#define EMPTYLOOPLIST			 81     /*Empty NURBS loop list in NURBS face %d in elem $ELEMNAME$.									*/
#define EMPTYFACELIST			 82     /*Empty NURBS face list in NURBS shell in elem $ELEMNAME$.										*/
#define EMPTYSHELLLIST			 83		/*Empty NURBS shell list in NURBS lump %d in elem $ELEMNAME$.									*/
#define CURVE2DINVALIDDOUBLE	 84     /*Invalid floating point value in NURBS 2D curve %d in elem $ELEMNAME$.							*/
#define CURVE3DINVALIDDOUBLE	 85     /*Invalid floating point value in NURBS 3D curve %d in elem $ELEMNAME$.							*/
#define SURFACEINVALIDDOUBLE	 86     /*Invalid floating point value in NURBS surface %d in elem $ELEMNAME$.							*/
#define VERTEXINVALIDDOUBLE		 87     /*Invalid floating point value in NURBS vertex %d in elem $ELEMNAME$.							*/
#define EDGEINVALIDDOUBLE		 88     /*Invalid floating point value in NURBS edge %d in elem $ELEMNAME$.								*/
#define TRIMINVALIDDOUBLE		 89     /*Invalid floating point value in NURBS trim %d in elem $ELEMNAME$.								*/
#define FACEINVALIDDOUBLE		 90     /*Invalid floating point value in NURBS face %d in elem $ELEMNAME$.								*/
#define INVALIDCURVE2DPARAMETER	 91     /*Invalid NURBS 2D curve %d in elem $ELEMNAME$.													*/
#define INVALIDCURVE3DPARAMETER	 92     /*Invalid NURBS 3D curve %d in elem $ELEMNAME$.													*/
#define INVALIDSURFACEPARAMETER	 93     /*Invalid NURBS surface %d in elem $ELEMNAME$.													*/
#define WRONGCURVE2DSUBDOMAIN	 94     /*Invalid subdomain for NURBS 2D curve %d in NURBS trim %d in elem $ELEMNAME$.					*/
#define WRONGCURVE3DSUBDOMAIN	 95     /*Invalid subdomain for NURBS 3D curve %d in NURBS edge %d in elem $ELEMNAME$.					*/
#define RINGEDGENOTCLOSEDCURVE	 96     /*NURBS 3D curve %d in NURBS ring edge %d is not a closed curve in elem $ELEMNAME$.				*/
#define EDGEANDVERTEXNOTFIT		 97     /*NURBS vertex %d does not fit on NURBS edge %d in elem $ELEMNAME$.								*/
#define LOOPDEGENERATED			 98     /*Loop is degenerated in NURBS face %d in elem $ELEMNAME$.										*/
#define LOOPNOTCONTINUOUS		 99     /*Loop is not continuous in NURBS face %d in elem $ELEMNAME$.									*/
#define EDGEENDPOINTSNOTFIT		100     /*Endpoints of subsequent NURBS edges [%d, %d] does not fit in NURBS face %d in elem $ELEMNAME$.*/
#define TRIMENDPOINTSNOTFIT		101     /*Endpoints of subsequent NURBS trims [%d, %d] does not fit in NURBS face %d in elem $ELEMNAME$.*/
#define FACETRIMMINGCURVENOTFIT	102     /*NURBS trim %d lies outside the domain of NURBS face %d in elem $ELEMNAME$.					*/
#define FACETRIMANDEDGENOTFIT	103     /*NURBS edge %d does not lie on the boundary of NURBS face %d in elem $ELEMNAME$.				*/
#define FACETRIMANDVERTEXNOTFIT	104     /*NURBS vertex %d does not lie on the boundary of NURBS face %d in elem $ELEMNAME$.				*/
#define SHELLNOTCLOSED			105     /*NURBS shell is not closed in elem $ELEMNAME$.													*/
#define SHELLNOTCONNECTED		106     /*NURBS shell has disjunct parts in elem $ELEMNAME$.											*/
#define EDGEINVALIDSTATE		107     /*Error in NURBS edge %d in elem $ELEMNAME$.													*/
#define TRIMINVALIDSTATE		108     /*Error in NURBS trim %d in elem $ELEMNAME$.													*/
#define INVALIDPEN				109     /*Invalid pen index in NURBS body in elem $ELEMNAME$.											*/
#define INVALIDMATERIAL			110     /*Invalid material index in NURBS body in elem $ELEMNAME$.										*/
#define	INTERNALERROR			111     /*Internal error in NURBS body in elem $ELEMNAME$.												*/


#endif //CHECKNURBSBODYMESSAGES_HPP