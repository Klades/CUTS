// -*- Java -*-

//=============================================================================
/**
 *  @file      Component.java
 *
 *  $Id$
 *
 *  @author      James H. Hill
 */
//=============================================================================

package cuts.quotas.pojo;

/**
 * @interface Component
 *
 * The interface for all components. This interface defines
 * the required methods that enable components to interface
 * with different containers.
 */
public interface Component
{
  /// Activate the component.
  void activate ();

  /// Passivate the component.
  void passivate ();

  /// Destroy the component.
  void destroy ();
};
