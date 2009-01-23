// $Id$

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include "boost/bind.hpp"

template <typename T>
class Host
{
public:
  typedef T item_type;

  typedef std::vector <T> collection_type;

  typedef typename collection_type::iterator iterator;

  typedef typename collection_type::const_iterator const_iterator;

  Host (void)
  {

  }

  Host (const std::string & name)
    : name_ (name)
  {

  }

  Host (const Host & host)
    : name_ (host.name_),
      items_ (host.items_)
  {

  }

  const Host & operator = (const Host & host)
  {
    if (this == &host)
      return *this;

    this->items_ = host.items_;
    return *this;
  }

  void install (const std::string & item)
  {
    this->items_.push_back (item);
  }

  iterator begin (void)
  {
    return this->items_.begin ();
  }

  const_iterator begin (void) const
  {
    return this->items_.begin ();
  }

  iterator end (void)
  {
    return this->items_.end ();
  }

  const_iterator end (void) const
  {
    return this->items_.end ();
  }

  const std::string & name (void) const
  {
    return this->name_;
  }

private:
  std::string name_;

  collection_type items_;
};

/**
 * @class CUTS_Unique_Deployments
 */
template <typename T>
class CUTS_Unique_Deployments
{
public:
  typedef Host <T> host_type;

  typedef typename host_type::item_type item_type;

  /// Type definition of a deployment.
  typedef std::vector <host_type> deployment_type;

  typedef std::list <deployment_type> collection_type;

  typedef typename collection_type::iterator iterator;

  typedef typename collection_type::const_iterator const_iterator;

  /// Default constructor.
  CUTS_Unique_Deployments (void)
    : hosts_ (0),
      deployments_ (1, deployment_type (hosts_))
  {

  }


  /// Destructor.
  ~CUTS_Unique_Deployments (void)
  {

  }

  void insert (host_type host)
  {
    if (this->deployments_.size () > 1)
      return;

    this->deployments_.front ().push_back (host);
    ++ this->hosts_;
  }

  void calculate (T item)
  {
    size_t iterations = this->deployments_.size ();

    for (size_t i = 0; i < iterations; ++ i)
    {
      this->calculate_i (this->deployments_.front (), item);
      this->deployments_.pop_front ();
    }
  }

  size_t size (void) const
  {
    return this->deployments_.size ();
  }

  iterator begin (void)
  {
    return this->deployments_.begin ();
  }

  const_iterator begin (void) const
  {
    return this->deployments_.begin ();
  }

  iterator end (void)
  {
    return this->deployments_.end ();
  }

  const_iterator end (void) const
  {
    return this->deployments_.end ();
  }

  const deployment_type & operator [] (size_t index) const
  {
    return this->deployments_[index];
  }

private:
  void calculate_i (const deployment_type & deployment, T item)
  {
    for (size_t i = 0; i < deployment.size (); ++ i)
    {
      // Insert the item into the deployment.
      deployment_type updated (deployment);
      updated[i].install (item);

      // Save the updated deployment.
      this->deployments_.push_back (updated);
    }
  }

  /// Number of hosts in each deployment.
  size_t hosts_;

  /// Collection of unique deployments.
  std::list <deployment_type> deployments_;
};

template <typename T>
struct item_print
{
  typedef T item_type;

  typedef void result_type;

  item_print (std::ostream & ostr, const std::string & hostname)
    : ostr_ (ostr),
      hostname_ (hostname)
  {

  }

  void operator () (T item)
  {
    this->ostr_ << "  host." << item << "="
                << this->hostname_ << std::endl;
  }

private:
  std::ostream & ostr_;

  const std::string & hostname_;
};

template <typename T>
struct host_printer
{
  typedef T item_type;

  typedef void result_type;

  host_printer (std::ostream & ostr)
    : ostr_ (ostr)
  {

  }

  void operator () (const Host <T> & host) const
  {
    std::for_each (host.begin (),
                   host.end (),
                   boost::bind (item_print <std::string> (this->ostr_, host.name ()),
                                _1));
  }

private:
  std::ostream & ostr_;
};

template <typename T>
struct deployment_printer
{
  typedef typename CUTS_Unique_Deployments <T>::collection_type::value_type value_type;

  typedef void result_type;

  deployment_printer (std::ostream & ostr)
    : ostr_ (ostr),
      count_ (0)
  {

  }

  void operator () (const value_type & deployment)
  {
    this->ostr_ << "Deployment" << ++ this->count_ << std::endl
                << "{" << std::endl;

    std::for_each (deployment.begin (),
                   deployment.end (),
                   boost::bind (host_printer <std::string> (this->ostr_), _1));

    this->ostr_ << "}" << std::endl
                << std::endl;
  }

private:
  std::ostream & ostr_;

  size_t count_;
};

//
// main
//
int main (int argc, char * argv [])
{
  CUTS_Unique_Deployments <std::string> unique_deployments;
  unique_deployments.insert (Host <std::string> ("Host1"));
  unique_deployments.insert (Host <std::string> ("Host2"));
  unique_deployments.insert (Host <std::string> ("Host3"));

  unique_deployments.calculate ("inst1");
  unique_deployments.calculate ("inst2");
  unique_deployments.calculate ("inst3");
  unique_deployments.calculate ("inst4");
  unique_deployments.calculate ("inst5");
  unique_deployments.calculate ("inst6");
  unique_deployments.calculate ("inst7");

  std::cerr << "Number of unique deployments : "
            << unique_deployments.size ();

  std::for_each (unique_deployments.begin (),
                 unique_deployments.end (),
                 boost::bind (deployment_printer <std::string> (std::cerr), _1));

  return 0;
}
