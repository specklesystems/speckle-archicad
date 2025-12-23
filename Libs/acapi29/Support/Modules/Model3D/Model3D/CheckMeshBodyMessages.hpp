#if ! defined CHECK_MESH_BODY_MESSAGES_HPP
#define CHECK_MESH_BODY_MESSAGES_HPP


#define	WRONG_EDGE							17	/* Wrong edge %d in elem $ELEMNAME$. */
#define	TWICE_THE_SAME_PGON_IN_EDGE			18	/* Twice the same neighbouring polygon (%d) in edge %d in elem $ELEMNAME$. */
#define	INVALID_PGON_IN_EDGE				19	/* Invalid pgon%1d  (%d) in edge %d in elem $ELEMNAME$. */
#define	ZERO_VECTOR							21	/* Zero vector %d in elem $ELEMNAME$. */
#define	WRONG_IMAGE_INDEX					23	/* Wrong image index [%d] in pgon %d in elem $ELEMNAME$. */
#define	WRONG_IVECT_IN_PGON					24	/* Wrong ivect [%d] in pgon %d in elem $ELEMNAME$. */
#define WRONG_EDGE_IN_PGON					25	/* Wrong edge [%d] in pgon %d in elem $ELEMNAME$. */
#define	EDGE_LIST_NOT_CONTINUOUS			26	/* Edge list is not continuous in pgon %d (%d) in elem $ELEMNAME$. */
#define	TWO_APICES_IDENTICAL				27	/* Two apices are identical in pgon %d (edge %d) in elem $ELEMNAME$. */
#define	NORMAL_AND_EDGE_NOT_PERPENDICULAR	29	/* Normal vector and edge %d is not perpendicular in pgon %d in elem $ELEMNAME$. */
#define	WRONG_EDGE_LIST_START				30	/* Wrong edge list (.,0 or 0,.) in pgon %d in elem $ELEMNAME$. */
#define	WRONG_EDGE_LIST_DIRECTION			32	/* Wrong edge list direction in pgon %d in elem $ELEMNAME$. */
#define	WRONG_EDGE_LIST_DIRECTION_HOLE		33	/* Wrong edge list direction in hole of pgon %d in elem $ELEMNAME$. */
#define	WRONG_EDGE_LIST_SEPARATOR			34	/* Wrong edge list ( 0,.) in pgon %d in elem $ELEMNAME$. */

#define	EDGE_USED_IN_SAME_DIRECTION			38	/* Edge %d used in same direction in elem $ELEMNAME$. */
#define INVALID_EDGE_IN_PGON				40	/* "Invalid edge %d in pgon %d in elem $ELEMNAME$." */

#endif	// CHECK_MESH_BODY_MESSAGES_HPP