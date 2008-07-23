#ifndef _T2M_ACTORS_H_
#define _T2M_ACTORS_H_

#include "gme/GME.h"

namespace T2M_actor
{
	template <typename iterator_t>
	struct create_model
	{
		create_model (GME::Model & model, GME::Object & parent, std::string kind)
			: model_ (model), parent_ (parent), kind_ (kind)
		{

		}

		void operator () (iterator_t const & first, iterator_t const & last) const
		{
			std::string name (first, last);

			GME::Collection_T <GME::Object> children;
			GME::Collection_T <GME::Object>::iterator child_i;
			parent_.children (children);
			
			bool flag = false;
			for(child_i = children.begin(); child_i != children.end(); child_i++)
			{
				if(child_i->name() == name)
				{
					model_ = GME::Model::_narrow(*child_i);
					flag = true;
					break;
				}
			}

			if(!flag)
			{
				// This won't work if the parent is a folder.
				model_ = GME::Model::_create ("State", GME::Model::_narrow(parent_));
				model_.name(name);
			}
		}

	private:
		GME::Model & model_;
		GME::Object & parent_;
		std::string kind_;
	};

	template <typename iterator_t>
	struct create_connection
	{
		create_connection (GME::Connection & connection, GME::Object & parent, GME::Model & src, GME::Model & dst, std::string kind)
			: conn_ (connection), parent_ (parent), src_ (src), dst_ (dst), kind_ (kind)
		{

		}

		void operator () (iterator_t const & first, iterator_t const & last) const
		{
				// This won't work if the parent is a folder.
			conn_ = GME::Connection::_create (kind_, GME::Model::_narrow(parent_), src_, dst_);
		}

	private:
		GME::Connection & conn_;
		GME::Object & parent_;
		GME::Model & src_;
		GME::Model & dst_;
		std::string kind_;
	};
}

#endif  // !defined _T2M_ACTORS_H_