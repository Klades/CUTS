// -*- java -*-

//=============================================================================
/**
 * @file          JbiShutdownThread.java
 *
 * $Id$
 *
 * @author        James H. Hill
 */
//=============================================================================

package cuts.jbi;

/**
 * @class JbiShutdownThread
 *
 * Thread class that can be registered with the Runtime for handling
 * the shutdown operations of an application/server. This includes
 * handling the Ctrl+C interrupt signal.
 */
public class JbiShutdownThread extends Thread
{
  /// The target application to shutdown.
  private JbiShutdownInterface jbiApp_;

  /**
   * Initializing constructor.
   *
   * @param         jbiApp        Target application to shutdown
   */
  public JbiShutdownThread (JbiShutdownInterface jbiApp)
  {
    this.jbiApp_ = jbiApp;
  }

  /**
   * Run the shutdown thread. This is a callback into the registered
   * application passed in during construction time.
   */
  public void run ()
  {
    this.jbiApp_.shutdownApp ();
  }
}
