#ifndef ERTOOL_ERALGOTRACKPID_CXX
#define ERTOOL_ERALGOTRACKPID_CXX

#include "ERAlgoTrackPid.h"
#include <sstream>
namespace ertool {
  
  ERAlgoTrackPid::ERAlgoTrackPid(const std::string& name) 
    : AlgoBase(name)
    , _algoPid_tree(nullptr)
  {
    // histogram to hold the energy of each reconstructed michel electron
    
  }

  void ERAlgoTrackPid::Reset()
  {   }

  void ERAlgoTrackPid::AcceptPSet(const ::fcllite::PSet& cfg)
  {

    return;
  }

  void ERAlgoTrackPid::ProcessBegin()
  {

    if (_algoPid_tree) { delete _algoPid_tree; }
    _algoPid_tree = new TTree("_algoPid_tree","algoPid Tree");
    _algoPid_tree->Branch("_part_pid"     ,&_part_pid     ,"_part_pid/D     ");
    
    return;
  }

  bool ERAlgoTrackPid::Reconstruct(const EventData &data, ParticleGraph& graph)
  {

    int Pdg = -1; 
    // Loop through Particles associated with a track
    for (auto const& t : graph.GetParticleNodes(RecoType_t::kTrack)){
      
      // get track object
      auto& part = graph.GetParticle(t);
      auto const& track = data.Track(part.RecoID());

      
      if ((track._pid_score[Track::kProton]<track._pid_score[Track::kPion])&&
	  (track._pid_score[Track::kProton]<track._pid_score[Track::kKaon])&&
	  (track._pid_score[Track::kProton]<track._pid_score[Track::kMuon]))      Pdg = 2212;
     
      if ((track._pid_score[Track::kPion]<track._pid_score[Track::kProton])&&
	  (track._pid_score[Track::kPion]<track._pid_score[Track::kKaon])&&
	  (track._pid_score[Track::kPion]<track._pid_score[Track::kMuon]))        Pdg = 211; 

      if ((track._pid_score[Track::kKaon]<track._pid_score[Track::kProton])&&
	  (track._pid_score[Track::kKaon]<track._pid_score[Track::kPion])&&
	  (track._pid_score[Track::kKaon]<track._pid_score[Track::kMuon]))        Pdg = 321;

      if ((track._pid_score[Track::kMuon]<track._pid_score[Track::kProton])&&
	  (track._pid_score[Track::kMuon]<track._pid_score[Track::kPion])&&
	  (track._pid_score[Track::kMuon]<track._pid_score[Track::kKaon]))        Pdg = 13;      
      
      part.SetParticleInfo(Pdg,
			   ParticleMass(Pdg),
			   part.Vertex(),
			   part.Momentum(),
			   part.RecoScore(),
			   part.ProcessType());

      if (Debug()) {
	std::stringstream ss;
	ss<<"I found a track!!!\n I assigned the PdgCode for its particle to be "<<Pdg;
	Debug(__FUNCTION__,ss.str());
      }
      _part_pid = Pdg;
      
      _algoPid_tree->Fill();
    }//End loop over tracks

    
    return true;
  }

  void ERAlgoTrackPid::ProcessEnd(TFile* fout)
  {
    /*
   if(fout){
      fout->cd();
      if(mu_energy)
      mu_energy->Write();
      if(muTru_energy)
      muTru_energy->Write();
    }
    */
  }

  
  void ERAlgoTrackPid::InitializeHistos(){
    
    /*
    if(!mu_energy)
      mu_energy = new TH1F("mu_energy","mu_energy",100,0,2000);
    if(!muTru_energy)
      muTru_energy = new TH1F("muTru_energy","muTru_energy",100,0,2000);
    */

  }


  void ERAlgoTrackPid::Finalize()
  {

    //    std::cout<<"Number of mu's found is "<<n_mu<<std::endl;
  }

  void ERAlgoTrackPid::ClearTree(){

    _part_pid         = -1 ;
    
    return;
  }

}

#endif
