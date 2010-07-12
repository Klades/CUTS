// -*- Java -*-

package CUTS.quotas.pojo;

/**
 * @interface Component
 * 
 * The interface for all components. This interface defines
 * the required methods that enable components to interface
 * with different containers.
 */
interface Component
{
	/**
	 * Set the component's session context.
	 * 
	 * @param[in]			c			Source context
	 */
	void setSessionContext (Context c);
	
	/// Activate the component.
	void activate ();
	
	/// Passivate the component.
	void passivate ();
	
	/// Destroy the component.
	void destroy ();
};
