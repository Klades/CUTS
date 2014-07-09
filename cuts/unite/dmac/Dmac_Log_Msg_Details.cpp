#include "Dmac_Log_Msg_Details.h"

CUTS_Dmac_Log_Msg_Details::
CUTS_Dmac_Log_Msg_Details (void)
{

}

CUTS_Dmac_Log_Msg_Details::
~CUTS_Dmac_Log_Msg_Details (void)
{

}

double CUTS_Dmac_Log_Msg_Details::time_val (void)
{
  return this->time_val_;
}

std::map <int, std::string> &
CUTS_Dmac_Log_Msg_Details::var_table (void)
{
  return this->var_table_;
}