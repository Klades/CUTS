// -*- Java -*-

package CUTS.quotas.pojo;

/**
 * @class ComponentBase
 * 
 * The base class for all components. This class implements the 
 * required methods of a Component so the concrete classes do
 * not have to implement them. Instead, the concrete class just
 * selects what method it wants to extend/override. This class
 * does not override the setSessionContext method since the 
 * concrete class needs to implement it.
 */
class ComponentBase implements Component
{	
	/// Activate the component.
	void activate () {
		
	}
	
	/// Passivate the component.
	void passivate () {
		
	}
	
	/// Destroy the component.
	void destroy () {
		
	}
};
