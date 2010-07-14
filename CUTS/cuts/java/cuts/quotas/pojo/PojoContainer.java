// -*- Java -*-

//=============================================================================
/**
 *  @file			PojoContainer.java
 *  
 *  $Id$
 *  
 *  @author			James H. Hill
 */
//=============================================================================

package cuts.quotas.pojo;
import java.util.HashMap;
import org.springframework.beans.factory.BeanFactory;

/**
 * @class PojoContainer
 * 
 * Implementation of the container for Pojo's.
 */
public class PojoContainer 
{
  /**
   * Default constructor
   */
	public PojoContainer (BeanFactory beanFactory) 
	{
		this.beanFactory_ = beanFactory;
	}
	
	/**
	 * Install the specified component. This method uses reflection
	 * to locate the component at the specified location.
	 * 
	 * @param[in]      jarFileName       Location of the instance.
	 * @paran[in]      className         Implementation type of the component.
	 * @param[in]      instName          Instance name of the component.
	 */
	Component installComponent (String className, String instName) 
	{
	  Object obj = this.beanFactory_.getBean (className);
	  
	  // Save the component.
	  Component component = (Component)obj;
	  this.instMap_.put (instName, component);
	  
	  return component;
	}
	
	/**
	 * Uninstall the component. This method remove the component from
	 * the container and returns its control to the client.
	 * 
	 * @param[in]      instName          Name of the component instance
	 */
	Component uninstallComponent (String instName) 
	{
	  // Get the component then remove it.
	  Component c = this.instMap_.get (instName);
	  this.instMap_.remove (instName);
	  
	  // Return the component to the caller.
	  return c;
	}
	
	/////////////////////////////////////////////////////////////////////////////
	// private data
	
  /// Bean factory for the container.
  private BeanFactory beanFactory_;
  
  /// Collection of instances in this container.
	private HashMap <String, Component> instMap_;
}