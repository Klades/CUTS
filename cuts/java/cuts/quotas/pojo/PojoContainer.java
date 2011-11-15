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
import java.util.ArrayList;
import java.util.HashMap;
import org.springframework.beans.factory.ListableBeanFactory;
import org.apache.log4j.Logger;

/**
 * @class PojoContainer
 * 
 * Implementation of the container for Pojo's.
 */
public class PojoContainer 
{
  /**
   * Initializing constructor. 
   * 
   * @param[in]       beanFactory         Factory for the container
   */
	public PojoContainer (ListableBeanFactory beanFactory) 
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
	public Component installComponent (String beanName) 
	{
	  // Locate the bean in the factory.
	  Object obj = this.beanFactory_.getBean (beanName);
	  
	  // Save the component.
	  Component component = (Component)obj;
	  this.instMap_.put (beanName, component);
	  
	  return component;
	}
	
	/**
	 * Install all the component instances. This will locate all 
	 * the beans that are a Component, and instantiate them for usage.
	 * 
	 * @return         Collection of installed components.
	 */
	public Component [] installComponentInstances ()
	{
	  String [] beanNames = this.beanFactory_.getBeanNamesForType (Component.class);
	  ArrayList <Component> componentList = new ArrayList <Component> (beanNames.length);
	  
	  for (String beanName : beanNames)
	    componentList.add (this.installComponent (beanName));
	  
	  Component [] components = componentList.toArray (new Component[componentList.size ()]);
	  return components;
	}
	
	/**
	 * Uninstall the component. This method remove the component from
	 * the container and returns its control to the client.
	 * 
	 * @param[in]      instName          Name of the component instance
	 */
	public Component uninstallComponent (String instName) 
	{
	  // Get the component then remove it.
	  Component c = this.instMap_.get (instName);
	  this.instMap_.remove (instName);
	  
	  // Return the component to the caller.
	  return c;
	}
	
	/**
	 * Passivate all the components in the container.
	 */
	public void passivateAll ()
	{
	  // Invoke the passivate () method on each component.
	  for (Component c : this.instMap_.values ())
	    c.passivate ();
	}
	
	/**
	 * Remove all the components in the container. This method will invoke
	 * the destory method on each component before removing it from the
	 * container.
	 */
	public void removeAll ()
	{
	  // Destroy each of the components.
    for (Component c : this.instMap_.values ())
      c.destroy ();	  
    
    // Remove all the items from the map.
    this.instMap_.clear ();
	}
	
	/////////////////////////////////////////////////////////////////////////////
	// private data
	
  /// Bean factory for the container.
  private ListableBeanFactory beanFactory_;
  
  /// Collection of instances in this container.
	private HashMap <String, Component> instMap_ = new HashMap <String, Component> ();
}