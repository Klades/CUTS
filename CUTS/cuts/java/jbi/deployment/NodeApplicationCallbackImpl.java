// -*- JAVA -*-

package cuts.java.jbi.deployment;

import org.apache.log4j.Logger;
import java.util.HashMap;

/**
 * @class NodeApplicationCallbackImpl
 * 
 * Implementation of the NodeApplicationCallback interface.
 */
public class NodeApplicationCallbackImpl
  extends NodeApplicationCallbackPOA
{
  private final HashMap<String, ApplicationProcess> processMap_ =
    new HashMap<String, ApplicationProcess>();

  private final Logger logger_ = 
    Logger.getLogger(NodeApplicationCallbackImpl.class);

  public NodeApplicationCallbackImpl()
  {

  }

  public void registerProcess(ApplicationProcess process)
  {
    this.logger_.debug("registering process group [" +
                       process.name() + "]");

    this.processMap_.put(process.name(), process);
  }

  public void unregisterProcess(ApplicationProcess process)
  {
    this.logger_.debug("unregistering process group [" +
                       process.name() + "]");

    this.processMap_.remove(process.name());
  }

  public ApplicationProcess getProcess(String name)
  {
    return this.processMap_.get(name);
  }
}
