/**
 * @file      JbiClientAppShutdownThread.java
 *
 * $Id$
 *
 * @author    James H. Hill
 */

package cuts.java.jbi.client;

/**
 * Thread that is responsible for handling the shutdown of the 
 * JbiClient. This class is registered as a shutdown hook for
 * with the virtual machine. Whenever the user presses Ctrl + C
 * the run () method is invoked.
 */
class JbiClientAppShutdownThread extends Thread
{
	/// Target JBI client.
	private JbiClient jbiClient_ = null;
	
	/**
	  * Initializing constructor.
	  *
	  * @param[in]       client        The target client.
	  */
	public JbiClientAppShutdownThread (JbiClient client)
	{
	  this.jbiClient_ = client;
	}
	
	/**
	  * Callback method for the thread routine.
	  */
	public void run ()
	{
	  this.jbiClient_.shutdown ();
	}
}
