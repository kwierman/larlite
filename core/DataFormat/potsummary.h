/**
 * \file potsummary.h
 *
 * \ingroup DataFormat
 * 
 * \brief Class def header for potsummary data container
 *
 * @author Kazu - Nevis 2013
 */

/** \addtogroup DataFormat

    @{*/

#ifndef LARLITE_POTSUMMARY_H
#define LARLITE_POTSUMMARY_H

#include "data_base.h"
#include <vector>
namespace larlite{
  /**
     \class potsummary
     LArSoft Potsummary class equivalent data container
  */
  class potsummary : public event_base {
    
  public:

    /// Default constructor
    potsummary(std::string name="noname") : event_base(data::kPOTSummary,name) 
    { clear_data(); }
    
    /// Default copy constructor
    potsummary(const potsummary& original) : event_base(original),
					     totpot(original.totpot),
					     totgoodpot(original.totgoodpot),
					     totspills(original.totspills),
					     goodspills(original.goodspills)
    {}    
    /// Default destructor
    virtual ~potsummary(){}

    void clear_data();

    double totpot;
    double totgoodpot;
    int totspills;
    int goodspills;

    friend std::ostream& operator<< (std::ostream& o, potsummary const& a);
    
  private:
    
    ////////////////////////
    ClassDef(potsummary,3)
    ////////////////////////
      
  };
}
#endif
/** @} */ // end of doxygen group 