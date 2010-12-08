// -*- Java -*-

//=============================================================================
/**
 *  @file			ComponentBase.java
 *  
 *  $Id$
 *  
 *  @author			James H. Hill
 */
//=============================================================================

package cuts.quotas.pojo;
import cuts.datamodel.DataModel;

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
public class ComponentBase implements Component
{	
	/// Activate the component.
	public void activate () 
	{
		
	}
	
	/// Passivate the component.
	public void passivate () 
	{
		
	}
	
	/// Destroy the component.
	public void destroy () 
	{
		
	}
	
	public void setDataModel (DataModel dm)
	{
	  this.dm_ = dm;
	}
	
	protected DataModel dm_;
};
