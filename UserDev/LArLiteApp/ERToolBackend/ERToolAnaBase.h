/**
 * \file ERToolAnaBase.h
 *
 * \ingroup LArLite_ERTool
 * 
 * \brief Class def header for a class ERToolAnaBase
 *
 * @author kazuhiro
 */

/** \addtogroup LArLite_ERTool

    @{*/

#ifndef LARLITE_ERTOOLANABASE_H
#define LARLITE_ERTOOLANABASE_H

#include <TStopwatch.h>
#include "Analysis/ana_base.h"
#include "ERToolHelper.h"

#include "ERTool/Base/Manager.h"

namespace larlite {
  /**
     \class ERToolAnaBase
     @brief Base analysis unit class for SPT fmwk. It has features to make SPAData.
     This class implements features to generate SPAData. More elaborate analysis       \n
     unit class may be derived from this class. See ertool::ExampleSPFit for instance. \n
   */
  class ERToolAnaBase : public ana_base{
  
  public:

    /// Default constructor
    ERToolAnaBase();

    /// Default destructor
    virtual ~ERToolAnaBase(){};

    /// Initialization method to be called before the analysis event loop.
    virtual bool initialize();

    /// Analyze a data event-by-event  
    virtual bool analyze(storage_manager* storage);

    /// Finalize method to be called after all events processed.
    virtual bool finalize();

    /**
       @brief Add a generator producer name.
       To be used if one wants to access MC info (like MC vertex information) even if Reco      \n
       objects are being used.                                                                  \n
     */
    void AddGeneratorProducer(const std::string gen) { _name_generator = gen; }


    /**
       @brief Add Shower producer name & if to use MC or not
     */
    void SetShowerProducer(const bool mc, const std::string prod);

    /**
       @brief Add Track producer name & if to use MC or not
     */
    void SetTrackProducer(const bool mc, const std::string prod);

    /**
       @brief Add Vertex producer name & if to use MC or not
     */
    void SetVtxProducer(const bool mc, const std::string prod);

    /**
       @brief get EventData that is used by the manager
     */
    const ::ertool::EventData& GetData(bool mc=false) const { return mc ? _mc_data : _data; }

    /**
       @brief get Particles produced by Algorithm.
     */
    const ::ertool::ParticleSet& GetParticles(bool mc=false) const { return mc ? _McParticles : _RecoParticles; }

    /// Selection manager class instance
    ::ertool::Manager _mgr;

  protected:
    ::ertool::EventData _data;           ///< Data to be filled by this module (main purpose!)
    ::ertool::EventData _mc_data;        ///< Data to be filled by this module (main purpose!)
    ::ertool::ParticleSet _RecoParticles;////<Particles Produced by Algorithm
    ::ertool::ParticleSet _McParticles;  ////<Particles from MC file, if available
    ERToolHelper _helper; ///< SPAHelper helps generating SPAData

  private:
    std::string _name_generator; ///< Generator's producer name
    std::string _name_mcshr;     ///< MCShower producer name
    std::string _name_mctrk;     ///< MCTrack producer name
    std::string _name_mcvtx;     ///< MCVertex producer name
    std::string _name_shower;    ///< 3D shower producer name
    std::string _name_track;     ///< 3D track producer name
    std::string _name_vertex;    ///< 3D vertex producer name
    bool _mcshowers; ///< Boolean. True: use MC for Showers
    bool _mctracks;  ///< Boolean. True: use MC for Tracks
    bool _mcvtx;     ///< Boolean. True: use MC for Vertices

  };
}
#endif

//**************************************************************************
// 
// For Analysis framework documentation, read Manual.pdf here:
//
// http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=3183
//
//**************************************************************************

/** @} */ // end of doxygen group 