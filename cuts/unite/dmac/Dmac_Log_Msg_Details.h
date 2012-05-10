// $Id:

#ifndef _CUTS_DMAC_LOG_MSG_DETAILS_H_
#define _CUTS_DMAC_LOG_MSG_DETAILS_H_

#include <map>
#include <string>

class CUTS_Dmac_Log_Format;
class CUTS_Dmac_Candidate_Relation;

class CUTS_Dmac_Log_Msg_Details
{
public:

  CUTS_Dmac_Log_Msg_Details (void);

  ~CUTS_Dmac_Log_Msg_Details (void);

  double time_val (void);

  friend class CUTS_Dmac_Log_Format;

  friend class CUTS_Dmac_Candidate_Relation;

private:

  long lid_;

  double time_val_;

  std::map <int, std::string> var_table_;

};


#endif