// -*- C++ -*-

//=============================================================================
/**
 * @file        Component.h
 *
 * $Id$
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _CUTS_ANTISPAM_BEHAVIOR_GRAPH_H_
#define _CUTS_ANTISPAM_BEHAVIOR_GRAPH_H_

#include "boost/graph/adjacency_list.hpp"
#include "ace/SString.h"
#include "Antispam_export.h"

/**
 * @struct CUTS_Port_Details
 *
 * Details about the port used in the bahavior graph.
 */
struct CUTS_ANTISPAM_Export CUTS_Port_Details
{
  CUTS_Port_Details (void)
    : input_ (false),
      arrival_rate_ (0.0),
      service_time_ (0.0)
  {

  }

  CUTS_Port_Details (const CUTS_Port_Details & copy)
    : input_ (copy.input_),
      arrival_rate_ (copy.arrival_rate_),
      service_time_ (copy.service_time_)
  {

  }

  const CUTS_Port_Details & operator = (const CUTS_Port_Details & rhs)
  {
    if (this == &rhs)
      return *this;

    this->input_ = rhs.input_;
    this->arrival_rate_ = rhs.arrival_rate_;
    this->service_time_ = rhs.service_time_;

    return *this;
  }

  bool input_;

  double arrival_rate_;

  double service_time_;
};

/**
 * @struct CUTS_Port_Details_Tag
 *
 * Tag for identifying CUTS_Port_Details property in a
 * behavior graph's vertex.
 */
struct CUTS_Port_Details_Tag
{
  /// Type definition for the tag's kind.
  typedef boost::vertex_property_tag kind;
};

/// Type definition of the behavior graph's properties.
typedef
  boost::property <boost::vertex_name_t, ACE_CString,
  boost::property <CUTS_Port_Details_Tag, CUTS_Port_Details > >
  CUTS_Behavior_Graph_Property;

/// Type definition of the behavior graph.
typedef boost::adjacency_list <boost::vecS,
                               boost::vecS,
                               boost::directedS,
                               CUTS_Behavior_Graph_Property>
                               CUTS_Behavior_Graph;


#endif  // !defined _CUTS_ANTISPAM_BEHAVIOR_GRAPH_H_