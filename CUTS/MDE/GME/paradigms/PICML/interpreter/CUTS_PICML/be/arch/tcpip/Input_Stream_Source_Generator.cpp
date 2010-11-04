// $Id$

#include "Input_Stream_Source_Generator.h"
#include "Input_Stream_Aggr_Member_Generator.h"
#include "Input_Stream_Event_Member_Generator.h"
#include "../../lang/cpp/Cpp.h"
#include "boost/bind.hpp"

#include <algorithm>

namespace CUTS_BE_TCPIP
{
//
// Input_Stream_Source_Generator
//
Input_Stream_Source_Generator::
Input_Stream_Source_Generator (std::ostream & out)
: out_ (out)
{
  this->array_method_[PICML::Boolean::meta] = "boolean";
  this->array_method_[PICML::Byte::meta] = "octet";
  this->array_method_[PICML::Char::meta] = "char";

  this->array_method_[PICML::ShortInteger::meta] = "short";
  this->array_method_[PICML::UnsignedShortInteger::meta] = "ushort";

  this->array_method_[PICML::LongInteger::meta] = "long";
  this->array_method_[PICML::UnsignedLongInteger::meta] = "ulong";

  this->array_method_[PICML::LongLongInteger::meta] = "longlong";
  this->array_method_[PICML::UnsignedLongLongInteger::meta] = "ulonglong";

  this->array_method_[PICML::FloatNumber::meta] = "float";
  this->array_method_[PICML::DoubleNumber::meta] = "double";
  this->array_method_[PICML::LongDoubleNumber::meta] = "longdouble";
}

//
// ~Input_Stream_Source_Generator
//
Input_Stream_Source_Generator::~Input_Stream_Source_Generator (void)
{

}

//
// Visit_Event
//
void Input_Stream_Source_Generator::Visit_Event (const PICML::Event & ev)
{
  this->out_
    << "ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR & stream, "
    << CUTS_BE_CPP::fq_type (ev, "::") << " & ev)"
    << "{";

  std::set <PICML::Member> members = ev.Member_children ();
  Input_Stream_Event_Member_Generator emg (this->out_);

  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&PICML::Member::Accept, _1, boost::ref (emg)));

  this->out_ << "return stream.good_bit ();"
             << "}";
}

//
// Visit_Aggregate
//
void Input_Stream_Source_Generator::
Visit_Aggregate (const PICML::Aggregate & aggr)
{
  this->out_
    << "ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR & stream, "
    << CUTS_BE_CPP::fq_type (aggr, "::") << " & val)"
    << "{";

  Input_Stream_Aggr_Member_Generator amg (this->out_);
  std::set <PICML::Member> members = aggr.Member_children ();

  std::for_each (members.begin (),
                 members.end (),
                 boost::bind (&PICML::Member::Accept, _1, boost::ref (amg)));

  this->out_ << "return stream.good_bit ();"
             << "}";
}

//
// Visit_Collection
//
void Input_Stream_Source_Generator::
Visit_Collection (const PICML::Collection & coll)
{
  const std::string name = CUTS_BE_CPP::fq_type (coll, "::");

  this->out_
    << "ACE_CDR::Boolean operator >> (CUTS_TCPIP_InputCDR & stream, "
    << name << " & coll)"
    << "{"
    << "// set the length of the collection" << std::endl
    << "size_t length;"
    << "stream >> length;"
    << "coll.length (length);"
    << std::endl;

  PICML::MemberType mt = coll.ref ();
  const Uml::Class & type = mt.type ();

  if (Udm::IsDerivedFrom (type, PICML::PredefinedType::meta) &&
      type != PICML::String::meta)
  {
    // We can read directly from the buffer.
    this->out_
      << "stream.read_" << this->array_method_[type]
      << "_array (coll.get_buffer (), length);";
  }
  else
  {
    // We have the extract each element separately.
    this->out_
      << "// extract the values of the collection" << std::endl
      << name << "::value_type * iter = coll.get_buffer ();"
      << name << "::value_type * iter_end = iter + length;"
      << std::endl
      << "while (iter != iter_end)" << std::endl
      << "  stream >> *iter ++;";
  }

  this->out_
    << std::endl
    << "return stream.good_bit ();"
    << "}";
}

}