// -*- java -*-

//=============================================================================
/**
 * @file        JbiShutdownInterface.java
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

package cuts.java.jbi;

/**
 * @interface JbiShutdownInterface
 *
 * Interface definition used by the JbiShutdownThread to signal the
 * server application to shutdown. Server applications must implement
 * this interface to ensure a correct and clean shutdown.
 */
public interface JbiShutdownInterface
{
  /// Signal the application to shutdown.
  void shutdownApp ();
}
