/******************************************************************************/
/*  Description:	Compare two XML trees                                     */
/*                                                                            */
/*  Module:			GSXMLUtils                                                */
/*  Namespace:		GSXML                                                     */
/*  Contact person:	BoZ                                                       */
/*                                                                            */
/*  SG compatible                                                             */
/******************************************************************************/

#ifndef	GSXMLCOMPARE_HPP
#define	GSXMLCOMPARE_HPP

// from GSRoot
#include "Owner.hpp"
#include "SharedPtr.hpp"
#include "SharedObject.hpp"
#include "HashSet.hpp"
#include "HashTable.hpp"
#include "UniString.hpp"
#include "StringConversion.hpp"
#include "Location.hpp"

// from GSXML
#include "GSXMLUtilsExport.hpp"
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOM.hpp>
#include "XStr.h"

namespace xercesc = XERCES_CPP_NAMESPACE;

namespace GSXML {

	const double EPS = 1E-05;		//default epsilon for comparing doubles
	const double SmallEps = 1E-12;	//epsilon for comparing epsilons

	class IXMLCompareOptions;
	class XMLNodeComparator;
	class XMLValueComparator;
	class XMLCompareException;
	
	GSXMLUTILS_EXPORT void DoXMLCompare (	const xercesc::DOMDocument* doc1,
											const xercesc::DOMDocument* doc2,
											GSXML::XMLNodeComparator* rootWalker,
											xercesc::DOMNodeFilter* filter,
											const GSXML::IXMLCompareOptions& options);

	GSXMLUTILS_EXPORT void DoXMLCompare (	const xercesc::DOMNode* node1,
											const xercesc::DOMNode* node2,
											GSXML::XMLNodeComparator* rootWalker,
											xercesc::DOMNodeFilter* filter,
											const GSXML::IXMLCompareOptions& options);

	GSXMLUTILS_EXPORT void DoXMLCompare (	const IO::Location& loc1,
											const IO::Location& loc2,
											GSXML::XMLNodeComparator* rootWalker,
											xercesc::DOMNodeFilter* filter,
											const GSXML::IXMLCompareOptions& options);

	/* ########################## Class Definitions ######################### */

	class GSXMLUTILS_EXPORT SkipWhitespaceTextsCompareFilter : public xercesc::DOMNodeFilter {
	public:
		xercesc::DOMNodeFilter::FilterAction acceptNode (const xercesc::DOMNode* node) const override;
	};
	
	class GSXMLUTILS_EXPORT IXMLCompareOptions : public GS::SharedObject {
	public:
		//----- Constructors -----//
		virtual ~IXMLCompareOptions ();
		/* Important: never forget to implement the Clone() method; it can lead to
		*	unwanted behaviour, but can still produce a working code!
		*/
		virtual IXMLCompareOptions* Clone () const = 0;

		//----- Public Getter-Setters -----//
		virtual double	GetDoubleEps () const = 0;

		//----- Methods -----//
		virtual bool						AcceptAttribute (const xercesc::DOMAttr* attr) const = 0;
		virtual bool						AreNodeNamesEqual (	const xercesc::DOMNode* node1,
																const xercesc::DOMNode* node2 ) const = 0;
		virtual void						CompareSpecialTypeNodes (	const xercesc::DOMNode* node1,
																		const xercesc::DOMNode* node2 ) = 0;
		virtual GSXML::XMLValueComparator*	GetAttributeValueComparator (const xercesc::DOMAttr* attr) const = 0;
		virtual GSXML::XMLValueComparator*	GetValueComparator () const = 0;
		virtual GSXML::XMLNodeComparator*	PrepareNodeComparator (	const xercesc::DOMElement* elem1,
																	const xercesc::DOMElement* elem2 ) = 0;
		virtual bool						CanOptionsChangeAndEffectNotChildNodes () const = 0;
	}; //IXMLCompareOptions end

	class GSXMLUTILS_EXPORT StrictOrderAutoValueCompareOptions : public IXMLCompareOptions  {
	public:
		//----- Constructors -----//
		StrictOrderAutoValueCompareOptions ();
		virtual ~StrictOrderAutoValueCompareOptions ();

		//----- Public Getter-Setters -----//
		virtual void			SetDoubleEps (const double eps)			{ doubleEps = eps; }
		virtual double			GetDoubleEps () const override			{ return doubleEps; }
	protected:
		//----- Member variables -----//
		double			doubleEps;			// epsilon for comparing doubles

		//----- Constructors -----//
		virtual StrictOrderAutoValueCompareOptions* Clone () const override;

		//----- Implemented methods -----//
		virtual bool						AcceptAttribute (const xercesc::DOMAttr* attr) const override;
		virtual bool						AreNodeNamesEqual (	const xercesc::DOMNode* node1,
																const xercesc::DOMNode* node2 ) const override;
		virtual void						CompareSpecialTypeNodes (	const xercesc::DOMNode* node1,
																		const xercesc::DOMNode* node2 ) override;
		virtual GSXML::XMLValueComparator*	GetAttributeValueComparator (const xercesc::DOMAttr* attr) const override;
		virtual GSXML::XMLValueComparator*	GetValueComparator () const override;
		virtual GSXML::XMLNodeComparator*	PrepareNodeComparator (	const xercesc::DOMElement* elem1,
																	const xercesc::DOMElement* elem2 ) override;
		virtual bool						CanOptionsChangeAndEffectNotChildNodes () const override;
	}; //StrictOrderAutoValueCompareOptions end

	class GSXMLUTILS_EXPORT AttrRuledCompareOptions : public StrictOrderAutoValueCompareOptions  {
	public:
		//----- Constructors -----//
		AttrRuledCompareOptions ();
		virtual ~AttrRuledCompareOptions ();

		//----- Public Getter-Setters -----//
		virtual void			SetTypeDeciderAtt (const GS::UniString& name)	{ typeDeciderAtt = name; }
		virtual GS::UniString	GetTypeDeciderAtt () const						{ return typeDeciderAtt; }
		virtual void			SetEpsAtt (const GS::UniString& name)			{ epsAtt = name; }
		virtual GS::UniString	GetEpsAtt () const								{ return epsAtt; }
	protected:
		//----- Member variables -----//
		GS::UniString	epsAtt;				// name of attribute which can contain epsilon for the node
		GS::UniString	typeDeciderAtt;		// name of attribute which can contain a node's value type
		GS::UniString	nodeCurrValueType;	// specified in the PARENT node: indicating value type of the current text node (can be empty)

		//----- Constructors -----//
		virtual AttrRuledCompareOptions* Clone () const override;

		//----- Implemented/Overrided methods -----//
		virtual GSXML::XMLNodeComparator*	PrepareNodeComparator (	const xercesc::DOMElement* elem1,
																	const xercesc::DOMElement* elem2 ) override;
		virtual bool						CanOptionsChangeAndEffectNotChildNodes () const override;
		//----- Own helper methods -----//
		virtual const xercesc::DOMAttr*		GetTypeAttribute (const xercesc::DOMElement* elem) const; //returns nullptr if not exists
		virtual void						SetCurrentValueType (	const xercesc::DOMElement* elem1,
																	const xercesc::DOMElement* elem2 );
		virtual void						DoValueTypeSpecificUpdates (const xercesc::DOMElement* elem1,
																		const xercesc::DOMElement* elem2);
		virtual GSXML::XMLValueComparator*	GetValueComparator () const override;
	}; //AttrRuledCompareOptions end

	
	class GSXMLUTILS_EXPORT XMLNodeComparator {
	private:
		// You should implement this:
		virtual void WalkThrough (void) = 0;
	protected:
		IXMLCompareOptions		*options;
		xercesc::DOMTreeWalker	*trWalk1, *trWalk2; //TreeWalkers for 2 trees
		const xercesc::DOMNode	*node1, *node2; //nodes to compare
	public:
		//----- Constructors -----//
		XMLNodeComparator ();
		virtual ~XMLNodeComparator ();

		//----- Methods -----//
		// Do not override this!
		static void CompareAttributes (	const xercesc::DOMElement* e1,
										const xercesc::DOMElement* e2,
										const IXMLCompareOptions& options );
		// Do not override this!
		void	CompareNodes (	xercesc::DOMTreeWalker* tw1,
								xercesc::DOMTreeWalker* tw2,
								IXMLCompareOptions& opt);
		// Do not override this!
		void	ControlNodeComparison ();
	}; //XMLNodeComparator end

	class GSXMLUTILS_EXPORT XMLCompareStrictOrder : public XMLNodeComparator {
	private:
		virtual void WalkThrough (void) override;
	};

	class GSXMLUTILS_EXPORT XMLCompareRotatedOrder : public XMLNodeComparator {
	private:
		virtual void WalkThrough (void) override;
	};

	class GSXMLUTILS_EXPORT XMLCompareNoOrder : public XMLNodeComparator {
	private:
		virtual void WalkThrough (void) override;
	};


	class GSXMLUTILS_EXPORT XMLValueComparator {
	private:
		// You should implement this:
		virtual bool	IsEqual () const = 0;
	protected:
		const IXMLCompareOptions	*options;
		const xercesc::DOMText		*tDom1, *tDom2; //values as dom objects
		GS::UniString				str1, str2;		//values as unistrings
		bool						xmlComparison;	//true: compares DOMTexts; false: compares UniStrings
	public:
		//----- Constructors -----//
		XMLValueComparator ();
		virtual ~XMLValueComparator ();

		//----- Methods -----//
		// Do not override these!
		bool		CompareValues ( const xercesc::DOMText* v1,
									const xercesc::DOMText* v2,
									const IXMLCompareOptions& opt);
		bool		CompareValues ( const GS::UniString& v1,
									const GS::UniString& v2,
									const IXMLCompareOptions& opt);
	}; //XMLValueComparator end

	class GSXMLUTILS_EXPORT XMLCompareAuto : public XMLValueComparator {
	private:
		virtual bool IsEqual () const override;
		XMLValueComparator* GetValueCmp () const;
	};
	
	class GSXMLUTILS_EXPORT XMLCompareInt : public XMLValueComparator {
	private:
		virtual bool IsEqual () const override;
	};
	
	class GSXMLUTILS_EXPORT XMLCompareDouble : public XMLValueComparator {
	private:
		virtual bool IsEqual () const override;
	};
	
	class GSXMLUTILS_EXPORT XMLCompareString : public XMLValueComparator {
	private:
		virtual bool IsEqual () const override;
	};

	class GSXMLUTILS_EXPORT XMLCompareStringCaseSensitive : public XMLCompareString {
	private:
		virtual bool IsEqual () const override;
	};


/**/class GSXMLUTILS_EXPORT XMLCompareException {
	public: enum Side { Left, Right };
	protected:
		IO::RelativeLocation node1path, node2path;
	public:
		XMLCompareException ();
		virtual ~XMLCompareException ();
		XMLCompareException (const xercesc::DOMNode* n1, const xercesc::DOMNode* n2);
		IO::RelativeLocation	GetNodePath (Side which) const;
		GS::UniString			GetNodePathUniString (Side which) const;
		virtual GS::UniString	GetText () const;
	};
/**/class GSXMLUTILS_EXPORT AttributeMissingException : public XMLCompareException {
	private:
		GS::UniString attName;
		Side missingWhere;
	public:
		AttributeMissingException (	const xercesc::DOMNode* n1,
							const xercesc::DOMNode* n2,
							const xercesc::DOMAttr* att,
							const Side missWhere	);
		virtual ~AttributeMissingException ();
		GS::UniString			GetAttributeName () const;
		Side					GetWhereItIsMissing () const;
		virtual GS::UniString	GetText () const override;
	};
/**/class GSXMLUTILS_EXPORT AttributesDontMatchException : public XMLCompareException {
	private:
		GS::UniString attName, att1value, att2value;
	public:
		AttributesDontMatchException (	const xercesc::DOMNode* n1,
								const xercesc::DOMNode* n2,
								const xercesc::DOMAttr* att1,
								const xercesc::DOMAttr* att2 );
		virtual ~AttributesDontMatchException ();
		GS::UniString			GetAttributeName () const;
		GS::UniString			GetAttributeValue (Side which) const;
		virtual GS::UniString	GetText () const override;
	};
/**/class GSXMLUTILS_EXPORT NodeNamesDontMatchException : public XMLCompareException {
	public:
		NodeNamesDontMatchException ( const xercesc::DOMNode* n1, const xercesc::DOMNode* n2 );
		virtual ~NodeNamesDontMatchException ();
		virtual GS::UniString	GetText () const override;
	};
/**/class GSXMLUTILS_EXPORT NodeTypesDontMatchException : public XMLCompareException {
	private:
		xercesc::DOMNode::NodeType node1type, node2type;
	public:
		NodeTypesDontMatchException ( const xercesc::DOMNode* n1, const xercesc::DOMNode* n2 );
		virtual ~NodeTypesDontMatchException ();
		xercesc::DOMNode::NodeType	GetNodeType (Side which) const;
		virtual GS::UniString		GetText () const override;
	};
/**/class GSXMLUTILS_EXPORT NotSupportedNodeTypesException : public XMLCompareException {
	private:
		xercesc::DOMNode::NodeType node1type, node2type;
	public:
		NotSupportedNodeTypesException ( const xercesc::DOMNode* n1, const xercesc::DOMNode* n2 );
		virtual ~NotSupportedNodeTypesException ();
		xercesc::DOMNode::NodeType	GetNodeType (Side which) const;
		virtual GS::UniString		GetText () const override;
	};
/**/class GSXMLUTILS_EXPORT OneNodeHasMoreChildrenThanTheOtherException : public XMLCompareException {
	private:
		Side whichHasMore;
	public:	
		OneNodeHasMoreChildrenThanTheOtherException (const xercesc::DOMNode* n1,
											const xercesc::DOMNode* n2,
											const Side which );
		virtual ~OneNodeHasMoreChildrenThanTheOtherException ();
		Side					GetWhichHasMoreChildren () const;
		virtual GS::UniString	GetText () const override;
	};
/**/class GSXMLUTILS_EXPORT OneNodeIsElementOneIsTextException : public NodeTypesDontMatchException {
	private:
		GS::UniString textNodeValue;
	public:
		OneNodeIsElementOneIsTextException ( const xercesc::DOMNode* n1, const xercesc::DOMNode* n2 );
		virtual ~OneNodeIsElementOneIsTextException ();
		GS::UniString			GetTextValue () const;
		virtual GS::UniString	GetText () const override;
	};
/**/class GSXMLUTILS_EXPORT TextNodeValuesDontMatchException : public XMLCompareException {
	private:
		GS::UniString textNode1value, textNode2value;
	public:
		TextNodeValuesDontMatchException ( const xercesc::DOMNode* n1, const xercesc::DOMNode* n2 );
		virtual ~TextNodeValuesDontMatchException ();
		GS::UniString			GetTextNodeValue (Side which) const;
		virtual GS::UniString	GetText () const override;
	};
/**/class GSXMLUTILS_EXPORT NoElementsInDocumentException : public XMLCompareException {
	private:
		Side inWhich;
	public:
		NoElementsInDocumentException (Side where);
		virtual ~NoElementsInDocumentException ();
		virtual GS::UniString	GetText () const override;
	};

} //GSXML namespace end

#endif
